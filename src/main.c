#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <stdio.h>
#include <rand.h>

#include "cursor.h"
#include "playfield.h"
#include "play_bg.h"
#include "random.h"
#include "vars.h"
#include "gfx/cursor_gfx.h"
#include "gfx/gametiles.h"
#include "gfx/play_background.h"

void init(){
    set_bkg_palette(0, 1, bgPalette);
    SHOW_SPRITES;
    DISPLAY_ON;
}

void main(){

    init();

    printf(" \n\n\n\n\n      SAMEGAME\n\n\n\n\n    PRESS START!\n");
    // abuse user input for seed generation
    waitpad(J_START);
    
    init_random();
    init_border_gfx();
    init_playfield();
    init_cursor();
    
    while(1) { 
        check_input();
        set_cursor();
        wait_vbl_done();
    }
}
