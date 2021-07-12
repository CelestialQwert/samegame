#include <stdint.h>
#include <gb/cgb.h>
#include <gb/gb.h>

#include "play_bg.h"
#include "gfx/play_background.h"
#include "gfx/gametiles.h"

const uint16_t bgPalette[] = {
    gametilesCGBPal0c0, gametilesCGBPal0c1, gametilesCGBPal0c2, gametilesCGBPal0c3
};

void init_border_gfx(){
    set_bkg_palette(0, 1, bgPalette);
    set_bkg_palette(4, 1, bgPalette);
    set_bkg_palette(5, 1, bgPalette);
    set_bkg_palette(6, 1, bgPalette);
    set_bkg_palette(7, 1, bgPalette);

    set_bkg_data(0, 17, gametiles);
    set_bkg_tiles(0, 0, 20, 18, play_backgroundPLN0);
}