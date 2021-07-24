#include <stdint.h>
#include <gb/cgb.h>
#include <gb/gb.h>

#include "cursor.h"
#include "playfield.h"
#include "vars.h"
#include "gfx/cursor_gfx.h"
#include "gfx/gametiles.h"

const uint16_t cursorPalette[] = {
    gametilesCGBPal0c0, gametilesCGBPal0c1, gametilesCGBPal0c2, gametilesCGBPal0c3
};

uint8_t cursor_x = 0;
uint8_t cursor_y = 0;

uint8_t holdtime = 0;

void init_cursor(){
    set_sprite_palette(0, 1, cursorPalette);
    set_sprite_data(0, 4, cursor_gfx);
    for (i=0; i<4; i++){
        set_sprite_tile(i, i);
    }
}

void set_cursor(){
    move_sprite(0, cursor_x*8+xo, cursor_y*8+yo);
    move_sprite(1, cursor_x*8+xo, cursor_y*8+yo+8);
    move_sprite(2, cursor_x*8+xo+8, cursor_y*8+yo);
    move_sprite(3, cursor_x*8+xo+8, cursor_y*8+yo+8);
}

void check_input(){
    switch(joypad()) {
        case J_A:
            if (holdtime == 0){
                select_tile(cursor_x, cursor_y);
            }
            holdtime = 8;
            break;
        case J_START:
            if (holdtime == 0){
                init_playfield();
            }
            holdtime = 8;
            break;
        case J_SELECT:
            if (holdtime == 0){
                num_tile_types += 1;
                if (num_tile_types == 7){num_tile_types = 2;}
                init_playfield();
            }
            holdtime = 8;
            break;
        case J_LEFT:
            if (holdtime % 8 == 0){
                cursor_x = (cursor_x+sx-1) % sx;
            }
            holdtime += 1;
            break;
        case J_RIGHT:
            if (holdtime % 8 == 0){
                cursor_x = (cursor_x+sx+1) % sx;
            }
            holdtime += 1;
            break;
        case J_UP:
            if (holdtime % 8 == 0){
                cursor_y = (cursor_y+sy-1) % sy;
            }
            holdtime += 1;
            break;
        case J_DOWN:
            if (holdtime % 8 == 0){
                cursor_y = (cursor_y+sy+1) % sy;
            }
            holdtime += 1;
            break;
        default:
            holdtime = 0;
    }
}