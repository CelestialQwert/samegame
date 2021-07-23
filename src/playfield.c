#include <stdint.h>
#include <stdbool.h>
#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>

#include "playfield.h"
#include "vars.h"
#include "random.h"

const uint16_t tilePalette[] = {
    gametilesCGBPal1c0, gametilesCGBPal1c1, gametilesCGBPal1c2, gametilesCGBPal1c3,
    gametilesCGBPal2c0, gametilesCGBPal2c1, gametilesCGBPal2c2, gametilesCGBPal2c3,
    gametilesCGBPal3c0, gametilesCGBPal3c1, gametilesCGBPal3c2, gametilesCGBPal3c3
};

const uint8_t gametile_palettes[] = {0, 1, 1, 2, 2, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0};

uint8_t playfield[sx][sy];
uint8_t trk_x = 0;
uint8_t trk_y = 0;
uint8_t trk_adj = 0;

void update_bkg_playfield(uint8_t fx, uint8_t fy, uint8_t val){
    VBK_REG = 1;
    set_bkg_tiles(1+fx, 1+fy, 1, 1, gametile_palettes + val);
    VBK_REG = 0;
    set_bkg_tiles(1+fx, 1+fy, 1, 1, c+val);
}

void update_playfield(uint8_t fx, uint8_t fy, uint8_t val){
    playfield[fx][fy] = val;
}

void init_playfield(){
    set_bkg_palette(1, 3, tilePalette);
    for (y=sy-1; y!=255; y--){
        for (x=0; x<sx; x++){
            i = randuint8(3) + 1;
            playfield[x][y] = i;
            update_bkg_playfield(x, y, i);
        }
    } 
}

void kill_tile(uint8_t tx, uint8_t ty){
    playfield[tx][ty] = 0;
    update_bkg_playfield(tx, ty, 0);
    // wait_vbl_done();
}

uint8_t check_tile_for_adjacent(uint8_t tx, uint8_t ty){
    trk_x = tx;
    trk_y = ty;
    uint8_t val = playfield[tx][ty];
    if (val == 0){
        return 0;
    }
    uint8_t good = 0;
    //down
    if (ty != sy-1){
        if (playfield[tx][ty+1] == val){
            good |= 1 << 3;
        }
    }
    //up
    if (ty != 0){
        if (playfield[tx][ty-1] == val){
            good |= 1 << 2;
        }
    }
    //left
    if (tx != 0){
        if (playfield[tx-1][ty] == val){
            good |= 1 << 1;
        }
    }
    //right
    if (tx != sx-1){
        if (playfield[tx+1][ty] == val){
            good |= 1;
        }
    }
    return good;
}

void check_then_kill_tile(uint8_t tx, uint8_t ty){
    uint8_t adj = check_tile_for_adjacent(tx, ty);
    trk_adj = adj;
    kill_tile(tx, ty);
    if (adj & 1 << 3){
        check_then_kill_tile(tx, ty+1);
    }
    if (adj & 1 << 2){
        check_then_kill_tile(tx, ty-1);
    }
    if (adj & 1 << 1){
        check_then_kill_tile(tx-1, ty);
    }
    if (adj & 1){
        check_then_kill_tile(tx+1, ty);
    }
    
}

void select_tile(uint8_t tx, uint8_t ty){
    if (check_tile_for_adjacent(tx, ty) > 0){
        check_then_kill_tile(tx, ty);
    }
}