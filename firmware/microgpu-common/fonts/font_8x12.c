#include <assert.h>
#include "microgpu-common/common.h"
#include "font_8x12.h"

// Byte data taken from https://github.com/WildernessLabs/Meadow.Foundation/blob/e7a26cd567/Source/Meadow.Foundation.Libraries_and_Frameworks/Graphics.MicroGraphics/Driver/Fonts/Font8x12.cs
const uint8_t data[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // U+0020 (space)
        0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, // U+0021 (!)
        0x24, 0x24, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // U+0022 (")
        0x00, 0x14, 0x14, 0x7f, 0x14, 0x7f, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00, // U+0023 (#)
        0x08, 0x3e, 0x49, 0x09, 0x3e, 0x48, 0x49, 0x3e, 0x08, 0x00, 0x00, 0x00, // U+0024 ($)
        0x02, 0x45, 0x22, 0x10, 0x08, 0x04, 0x22, 0x51, 0x20, 0x00, 0x00, 0x00, // U+0025 (%)
        0x00, 0x04, 0x0a, 0x0a, 0x04, 0x2a, 0x11, 0x11, 0x2e, 0x00, 0x00, 0x00, // U+0026 (&)
        0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // U+0027 (')
        0x08, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, // U+0028 (()
        0x08, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x08, 0x00, 0x00, 0x00, // U+0029 ())
        0x00, 0x08, 0x2a, 0x1c, 0x7f, 0x1c, 0x2a, 0x08, 0x00, 0x00, 0x00, 0x00, // U+002A (*)
        0x00, 0x08, 0x08, 0x08, 0x7f, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // U+002B (+)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x02, 0x00, // U+002C (,)
        0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // U+002D (-)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, // U+002E (.)
        0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, // U+002F (/)
        0x3e, 0x41, 0x61, 0x51, 0x49, 0x45, 0x43, 0x41, 0x3e, 0x00, 0x00, 0x00, // U+0030 (0)
        0x08, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1c, 0x00, 0x00, 0x00, // U+0031 (1)
        0x3e, 0x41, 0x40, 0x20, 0x18, 0x04, 0x02, 0x01, 0x7f, 0x00, 0x00, 0x00, // U+0032 (2)
        0x3e, 0x41, 0x40, 0x40, 0x3c, 0x40, 0x40, 0x41, 0x3e, 0x00, 0x00, 0x00, // U+0033 (3)
        0x20, 0x30, 0x28, 0x24, 0x22, 0x7f, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, // U+0034 (4)
        0x7f, 0x01, 0x01, 0x01, 0x3f, 0x40, 0x40, 0x41, 0x3e, 0x00, 0x00, 0x00, // U+0035 (5)
        0x3e, 0x41, 0x01, 0x01, 0x3f, 0x41, 0x41, 0x41, 0x3e, 0x00, 0x00, 0x00, // U+0036 (6)
        0x7f, 0x40, 0x20, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // U+0037 (7)
        0x3e, 0x41, 0x41, 0x41, 0x3e, 0x41, 0x41, 0x41, 0x3e, 0x00, 0x00, 0x00, // U+0038 (8)
        0x3e, 0x41, 0x41, 0x41, 0x7e, 0x40, 0x40, 0x41, 0x3e, 0x00, 0x00, 0x00, // U+0039 (9)
        0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, // U+003A (:)
        0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x02, 0x00, // U+003B (//)
        0x10, 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x10, 0x00, 0x00, 0x00, // U+003C (<)
        0x00, 0x00, 0x00, 0x7f, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // U+003D (=)
        0x04, 0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08, 0x04, 0x00, 0x00, 0x00, // U+003E (>)
        0x3e, 0x41, 0x41, 0x20, 0x10, 0x08, 0x08, 0x00, 0x08, 0x00, 0x00, 0x00, // U+003F (?)
        0x3e, 0x41, 0x59, 0x55, 0x55, 0x25, 0x1d, 0x41, 0x3e, 0x00, 0x00, 0x00, // U+0040 (@)
        0x1c, 0x22, 0x41, 0x41, 0x7f, 0x41, 0x41, 0x41, 0x41, 0x00, 0x00, 0x00, // U+0041 (A)
        0x3f, 0x41, 0x41, 0x41, 0x3f, 0x41, 0x41, 0x41, 0x3f, 0x00, 0x00, 0x00, // U+0042 (B)
        0x3c, 0x42, 0x01, 0x01, 0x01, 0x01, 0x01, 0x42, 0x3c, 0x00, 0x00, 0x00, // U+0043 (C)
        0x3f, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x3f, 0x00, 0x00, 0x00, // U+0044 (D)
        0x7f, 0x01, 0x01, 0x01, 0x0f, 0x01, 0x01, 0x01, 0x7f, 0x00, 0x00, 0x00, // U+0045 (E)
        0x7f, 0x01, 0x01, 0x01, 0x0f, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, // U+0046 (F)
        0x3c, 0x42, 0x01, 0x01, 0x01, 0x71, 0x41, 0x42, 0x3c, 0x00, 0x00, 0x00, // U+0047 (G)
        0x41, 0x41, 0x41, 0x41, 0x7f, 0x41, 0x41, 0x41, 0x41, 0x00, 0x00, 0x00, // U+0048 (H)
        0x1c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1c, 0x00, 0x00, 0x00, // U+0049 (I)
        0x38, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x11, 0x0e, 0x00, 0x00, 0x00, // U+004A (J)
        0x21, 0x11, 0x09, 0x05, 0x03, 0x05, 0x09, 0x11, 0x21, 0x00, 0x00, 0x00, // U+004B (K)
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x3f, 0x00, 0x00, 0x00, // U+004C (L)
        0x41, 0x63, 0x55, 0x49, 0x41, 0x41, 0x41, 0x41, 0x41, 0x00, 0x00, 0x00, // U+004D (M)
        0x41, 0x41, 0x43, 0x45, 0x49, 0x51, 0x61, 0x41, 0x41, 0x00, 0x00, 0x00, // U+004E (N)
        0x1c, 0x22, 0x41, 0x41, 0x41, 0x41, 0x41, 0x22, 0x1c, 0x00, 0x00, 0x00, // U+004F (O)
        0x3f, 0x41, 0x41, 0x41, 0x3f, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, // U+0050 (P)
        0x1c, 0x22, 0x41, 0x41, 0x41, 0x41, 0x51, 0x22, 0x5c, 0x00, 0x00, 0x00, // U+0051 (Q)
        0x3f, 0x41, 0x41, 0x41, 0x3f, 0x41, 0x41, 0x41, 0x41, 0x00, 0x00, 0x00, // U+0052 (R)
        0x3e, 0x41, 0x01, 0x01, 0x3e, 0x40, 0x40, 0x41, 0x3e, 0x00, 0x00, 0x00, // U+0053 (S)
        0x7f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // U+0054 (T)
        0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x3e, 0x00, 0x00, 0x00, // U+0055 (U)
        0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x22, 0x14, 0x08, 0x00, 0x00, 0x00, // U+0056 (V)
        0x41, 0x41, 0x41, 0x41, 0x41, 0x49, 0x55, 0x63, 0x41, 0x00, 0x00, 0x00, // U+0057 (W)
        0x41, 0x41, 0x22, 0x14, 0x08, 0x14, 0x22, 0x41, 0x41, 0x00, 0x00, 0x00, // U+0058 (X)
        0x41, 0x41, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // U+0059 (Y)
        0x7f, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x7f, 0x00, 0x00, 0x00, // U+005A (Z)
        0x3c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x3c, 0x00, 0x00, 0x00, // U+005B ([)
        0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, // U+005C (\)
        0x1e, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1e, 0x00, 0x00, 0x00, // U+005D (])
        0x08, 0x14, 0x22, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // U+005E (^)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, // U+005F (_)
        0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // U+0060 (`)
        0x00, 0x00, 0x00, 0x1c, 0x22, 0x21, 0x21, 0x31, 0x2e, 0x00, 0x00, 0x00, // U+0061 (a)
        0x01, 0x01, 0x01, 0x1d, 0x23, 0x21, 0x21, 0x23, 0x1d, 0x00, 0x00, 0x00, // U+0062 (b)
        0x00, 0x00, 0x00, 0x1e, 0x21, 0x01, 0x01, 0x21, 0x1e, 0x00, 0x00, 0x00, // U+0063 (c)
        0x20, 0x20, 0x20, 0x2e, 0x31, 0x21, 0x21, 0x31, 0x2e, 0x00, 0x00, 0x00, // U+0064 (d)
        0x00, 0x00, 0x00, 0x1e, 0x21, 0x21, 0x3f, 0x01, 0x3e, 0x00, 0x00, 0x00, // U+0065 (e)
        0x18, 0x04, 0x04, 0x04, 0x1f, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, // U+0066 (f)
        0x00, 0x00, 0x00, 0x2c, 0x32, 0x21, 0x21, 0x21, 0x3e, 0x20, 0x21, 0x1e, // U+0067 (g)
        0x01, 0x01, 0x01, 0x0d, 0x13, 0x21, 0x21, 0x21, 0x21, 0x00, 0x00, 0x00, // U+0068 (h)
        0x00, 0x08, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // U+0069 (i)
        0x00, 0x08, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x09, 0x06, 0x00, // U+006A (j)
        0x01, 0x01, 0x11, 0x09, 0x05, 0x03, 0x05, 0x09, 0x11, 0x00, 0x00, 0x00, // U+006B (k)
        0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // U+006C (l)
        0x00, 0x00, 0x00, 0x36, 0x49, 0x49, 0x49, 0x49, 0x49, 0x00, 0x00, 0x00, // U+006D (m)
        0x00, 0x00, 0x00, 0x1d, 0x23, 0x21, 0x21, 0x21, 0x21, 0x00, 0x00, 0x00, // U+006E (n)
        0x00, 0x00, 0x00, 0x1e, 0x21, 0x21, 0x21, 0x21, 0x1e, 0x00, 0x00, 0x00, // U+006F (o)
        0x00, 0x00, 0x00, 0x1d, 0x23, 0x21, 0x21, 0x23, 0x1d, 0x01, 0x01, 0x01, // U+0070 (p)
        0x00, 0x00, 0x00, 0x2e, 0x31, 0x21, 0x21, 0x31, 0x2e, 0x20, 0x20, 0x20, // U+0071 (q)
        0x00, 0x00, 0x00, 0x1d, 0x23, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, // U+0072 (r)
        0x00, 0x00, 0x00, 0x1e, 0x21, 0x06, 0x18, 0x21, 0x1e, 0x00, 0x00, 0x00, // U+0073 (s)
        0x00, 0x08, 0x08, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // U+0074 (t)
        0x00, 0x00, 0x00, 0x21, 0x21, 0x21, 0x21, 0x21, 0x1e, 0x00, 0x00, 0x00, // U+0075 (u)
        0x00, 0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x0a, 0x04, 0x00, 0x00, 0x00, // U+0076 (v)
        0x00, 0x00, 0x00, 0x41, 0x41, 0x41, 0x49, 0x49, 0x36, 0x00, 0x00, 0x00, // U+0077 (w)
        0x00, 0x00, 0x00, 0x21, 0x12, 0x0c, 0x0c, 0x12, 0x21, 0x00, 0x00, 0x00, // U+0078 (x)
        0x00, 0x00, 0x00, 0x21, 0x21, 0x21, 0x21, 0x21, 0x3e, 0x20, 0x21, 0x1e, // U+0079 (y)
        0x00, 0x00, 0x00, 0x3f, 0x10, 0x08, 0x04, 0x02, 0x3f, 0x00, 0x00, 0x00, // U+007A (z)
        0x18, 0x04, 0x04, 0x04, 0x02, 0x04, 0x04, 0x04, 0x18, 0x00, 0x00, 0x00, // U+007B ({)
        0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, // U+007C (|)
        0x0c, 0x10, 0x10, 0x10, 0x20, 0x10, 0x10, 0x10, 0x0c, 0x00, 0x00, 0x00, // U+007D (})
        0x26, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // U+007E (~)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // U+007F
};

void write_char(Mgpu_Texture *texture, char character, Mgpu_Color color, uint16_t startX, uint16_t startY) {
    if (startX >= texture->width || startY >= texture->height || character < 0x20 || character > 0x7f) {
        return;
    }

    uint16_t endX = min(texture->width, startX + 8);
    uint8_t width = endX - startX;
    const uint8_t *byte = data + ((character - 0x20) * 12);
    Mgpu_Color *rowStart = texture->pixels + (startY * texture->width + startX);

    for (int row = 0; row < 12; row++) {
        Mgpu_Color *pixel = rowStart;
        for (int shift = 0; shift < width; shift++) {
            uint8_t mask = 0x01 << shift;
            if ((*byte & mask) == mask) {
                *pixel = color;
            }

            pixel++;
        }

        rowStart += texture->width;
        byte++;
    }
}

void mgpu_font_8x12_write(Mgpu_Texture *texture, char *text, Mgpu_Color color, uint16_t startX, uint16_t startY) {
    assert(texture != NULL);
    assert(text != NULL);

    while (*text != '\0') {
        write_char(texture, *text, color, startX, startY);
        text++;
        startX += 8;
    }
}