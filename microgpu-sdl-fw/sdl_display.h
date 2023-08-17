#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "framebuffer.h"
#include "display.h"

/*
 * Creates an SDL implementation of the microgpu display interface.
 */
Mgpu_Display *mgpu_sdl_display_create();

/*
 * Frees all memory relating to the SDL display interface
 */
void mgpu_sdl_display_free(Mgpu_Display *display);
