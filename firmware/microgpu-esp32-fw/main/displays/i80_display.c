#include <esp_lcd_panel_io.h>
#include <esp_log.h>
#include <esp_lcd_panel_vendor.h>
#include <esp_lcd_panel_ops.h>
#include "microgpu-common/color.h"
#include "microgpu-common/display.h"
#include "../common.h"
#include "i80_display.h"

#ifndef MGPU_COLOR_MODE_USE_RGB565
#error "Color mode RGB565 required"
#endif

void init_ili9341_panel(esp_lcd_panel_io_handle_t io_handle,
                        esp_lcd_panel_handle_t *panel,
                        const Mgpu_DisplayOptions *options) {
    // ILI9341 is NOT a distinct driver, but a special case of ST7789
    // (essential registers are identical). A few lines further down in this code,
    // it's shown how to issue additional device-specific commands.
    ESP_LOGI(LOG_TAG, "Install LCD driver of ili9341 (st7789 compatible)");
    esp_lcd_panel_dev_config_t panel_config = {
            .reset_gpio_num = options->controlPins.reset,
            .rgb_endian = LCD_RGB_ENDIAN_BGR,
            .bits_per_pixel = 16,
    };

    esp_lcd_panel_handle_t panel_handle = NULL;
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle));

    esp_lcd_panel_reset(panel_handle);
    esp_lcd_panel_init(panel_handle);

    // Set inversion, x/y coordinate order, x/y mirror according to your LCD module spec
    // the gap is LCD panel specific, even panels with the same driver IC, can have different gap value
    esp_lcd_panel_swap_xy(panel_handle, true);
    esp_lcd_panel_invert_color(panel_handle, false);

    // ILI9341 is very similar to ST7789 and shares the same driver.
    // Anything unconventional (such as this custom gamma table) can
    // be issued here in user code and need not modify the driver.
    esp_lcd_panel_io_tx_param(io_handle, 0xF2, (uint8_t[]) {0}, 1); // 3Gamma function disable
    esp_lcd_panel_io_tx_param(io_handle, 0x26, (uint8_t[]) {1}, 1); // Gamma curve 1 selected
    esp_lcd_panel_io_tx_param(io_handle, 0xE0, (uint8_t[]) {          // Set positive gamma
            0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00}, 15);
    esp_lcd_panel_io_tx_param(io_handle, 0xE1, (uint8_t[]) {          // Set negative gamma
            0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F}, 15);

    *panel = panel_handle;
}

void init_i80_bus(const Mgpu_DisplayOptions *options, esp_lcd_panel_io_handle_t *io_handle) {
    esp_lcd_i80_bus_handle_t bus = NULL;
    esp_lcd_i80_bus_config_t busConfig = {
            .clk_src = LCD_CLK_SRC_DEFAULT,
            .dc_gpio_num = options->controlPins.dataCommand,
            .wr_gpio_num = options->controlPins.writeClock,
            .data_gpio_nums = {
                    options->dataPins.data0,
                    options->dataPins.data1,
                    options->dataPins.data2,
                    options->dataPins.data3,
                    options->dataPins.data4,
                    options->dataPins.data5,
                    options->dataPins.data6,
                    options->dataPins.data7,
            },
            .bus_width = 8,
            .max_transfer_bytes = options->pixelWidth * options->pixelHeight * sizeof(Mgpu_Color),
            .psram_trans_align = 64,
            .sram_trans_align = 4,
    };

    ESP_ERROR_CHECK(esp_lcd_new_i80_bus(&busConfig, &bus));
    esp_lcd_panel_io_i80_config_t ioConfig = {
            .cs_gpio_num = options->controlPins.chipSelect,
            .pclk_hz = 2 * 1000 * 1000, // Example uses 2Mhz when PSRAM is used
            .trans_queue_depth = 10,
            .dc_levels = {
                    .dc_idle_level = 0,
                    .dc_cmd_level = 0,
                    .dc_dummy_level = 0,
                    .dc_data_level = 1,
            },
            .flags = {
                    .swap_color_bytes = true, // I think this will do BGR without this
            },
            .lcd_cmd_bits = 8, // Might need to be adjusted for other displays
            .lcd_param_bits = 8, // Might need to be adjusted for other displays
    };

    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i80(bus, &ioConfig, io_handle));
}

void log_display_options(const Mgpu_DisplayOptions *options) {
    ESP_LOGI(LOG_TAG, "Microgpu i80 LCD display options:");
    ESP_LOGI(LOG_TAG, "Display resolution: %u x %u", options->pixelWidth, options->pixelHeight);
    ESP_LOGI(LOG_TAG, "Reset pin: %u", options->controlPins.reset);
    ESP_LOGI(LOG_TAG, "Chip select pin: %u", options->controlPins.chipSelect);
    ESP_LOGI(LOG_TAG, "DC pin: %u", options->controlPins.dataCommand);
    ESP_LOGI(LOG_TAG, "Write clock pin: %u", options->controlPins.writeClock);
    ESP_LOGI(LOG_TAG, "Data0 pin: %u", options->dataPins.data0);
    ESP_LOGI(LOG_TAG, "Data1 pin: %u", options->dataPins.data1);
    ESP_LOGI(LOG_TAG, "Data2 pin: %u", options->dataPins.data2);
    ESP_LOGI(LOG_TAG, "Data3 pin: %u", options->dataPins.data3);
    ESP_LOGI(LOG_TAG, "Data4 pin: %u", options->dataPins.data4);
    ESP_LOGI(LOG_TAG, "Data5 pin: %u", options->dataPins.data5);
    ESP_LOGI(LOG_TAG, "Data6 pin: %u", options->dataPins.data6);
    ESP_LOGI(LOG_TAG, "Data7 pin: %u", options->dataPins.data7);
}

Mgpu_Display *mgpu_display_new(const Mgpu_Allocator *allocator, const Mgpu_DisplayOptions *options) {
    assert(allocator != NULL);
    assert(options != NULL);

    log_display_options(options);

    esp_lcd_panel_io_handle_t ioHandle = NULL;
    init_i80_bus(options, &ioHandle);

    esp_lcd_panel_handle_t panel_handle = NULL;
    init_ili9341_panel(ioHandle, &panel_handle, options);

    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

    Mgpu_Display *display = allocator->AllocateFn(sizeof(Mgpu_Display));
    display->allocator = allocator;
    display->panel = panel_handle;
    display->pixelWidth = options->pixelWidth;
    display->pixelHeight = options->pixelHeight;

    return display;
}

void mgpu_display_free(Mgpu_Display *display) {
    if (display) {
        display->allocator->FreeFn(display);
    }
}

void mgpu_display_get_dimensions(Mgpu_Display *display, uint16_t *width, uint16_t *height) {
    assert(display != NULL);
    assert(width != NULL);
    assert(height != NULL);

    *width = display->pixelWidth;
    *height = display->pixelHeight;
}

Mgpu_FrameBuffer *mgpu_display_render(Mgpu_Display *display, Mgpu_FrameBuffer *frameBuffer) {
    assert(display != NULL);
    assert(frameBuffer != NULL);
    assert(frameBuffer->scale == 1 && "TODO: Implement scaling support");

    esp_lcd_panel_draw_bitmap(display->panel, 0, 0, display->pixelWidth, display->pixelHeight, frameBuffer->pixels);

    // Release the frame buffer back. This *may* not be valid as draw might be async via dma??
    return frameBuffer;
}
