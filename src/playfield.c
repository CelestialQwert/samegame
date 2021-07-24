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
uint8_t column_tiles[sx];
uint8_t adj = 0;
uint8_t kill_x[40];
uint8_t kill_y[40];
uint8_t kill_idx = 0;
uint8_t kill_add_idx = 0;

uint8_t num_tile_types = 4;


void update_bkg_playfield(uint8_t fx, uint8_t fy, uint8_t val){
    VBK_REG = 1;
    set_bkg_tiles(1+fx, 1+fy, 1, 1, gametile_palettes + val);
    VBK_REG = 0;
    set_bkg_tiles(1+fx, 1+fy, 1, 1, c+val);
}

void update_playfield(uint8_t fx, uint8_t fy, uint8_t val){
    playfield[fx][fy] = val;
}

void update_tile(uint8_t fx, uint8_t fy, uint8_t val){
    update_playfield(fx, fy, val);
    update_bkg_playfield(fx, fy, val);
}

void init_playfield(){
    set_bkg_palette(1, 3, tilePalette);
    for (x=0; x<sx; x++){
        column_tiles[x] = 15;
        for (y=0; y<sy; y++){
            i = randuint8(num_tile_types) + 1;
            //i = 1;
            playfield[x][y] = i;
            update_bkg_playfield(x, y, i);
        }
    }
    for (i=0; i<40; i++){
        kill_x[i] = 0;
        kill_y[i] = 0;
    }
}

void select_tile(uint8_t tx, uint8_t ty){
    if (check_tile_for_adjacent(tx, ty) > 0){
        add_tile_to_kill(tx, ty);
        kill_tiles();
        drop_tiles();
        shift_columns();
        i=0;
    }
}

void add_tile_to_kill(uint8_t kx, uint8_t ky){
    kill_x[kill_add_idx] = kx;
    kill_y[kill_add_idx] = ky;
    kill_add_idx++;
    if (kill_add_idx == 40){
        kill_add_idx = 0;
    }
}

void kill_tiles(){
    while (kill_idx != kill_add_idx){
        kill_tile_then_add_adjacent(kill_x[kill_idx], kill_y[kill_idx]);
    }
}

void kill_tile_then_add_adjacent(uint8_t tx, uint8_t ty){
    a = check_tile_for_adjacent(tx, ty);
    kill_tile(tx, ty);
    if (a & 1 << 3){
        add_tile_to_kill(tx, ty+1);
    }
    if (a & 1 << 2){
        add_tile_to_kill(tx, ty-1);
    }
    if (a & 1 << 1){
        add_tile_to_kill(tx-1, ty);
    }
    if (a & 1){
        add_tile_to_kill(tx+1, ty);
    }
    i++;
}

uint8_t check_tile_for_adjacent(uint8_t tx, uint8_t ty){
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

void kill_tile(uint8_t tx, uint8_t ty){
    erase_tile(tx, ty);
    kill_x[kill_idx] = 0;
    kill_y[kill_idx] = 0;
    kill_idx++;
    if (kill_idx == 40){
        kill_idx = 0;
    }
}

void erase_tile(uint8_t tx, uint8_t ty){
    if (playfield[tx][ty] == 0){
        return;
    }
    playfield[tx][ty] = 0;
    update_bkg_playfield(tx, ty, 0);
    column_tiles[tx] -= 1;
    wait_vbl_done();
    i=0;
}

void drop_tiles(){
    for (x=0; x<sx; x++){
        for (y=sy-1; y!=255; y--){
            if (playfield[x][y] != 0){
                continue;
            }
            for(i=y-1; i!=255; i--){
                a = playfield[x][i];
                if (a == 0){
                    continue;
                }
                playfield[x][i] = 0;
                update_bkg_playfield(x, i, 0);
                playfield[x][y] = a;
                update_bkg_playfield(x, y, a);
                break;
            }
        }
    }
}

void shift_columns(){
    for (x=sx-1; x!=255; x--){
        if (column_tiles[x] != 0){
            continue;
        }
        for(i=x-1; i!=255; i--){
            if (column_tiles[i] == 0){
                continue;
            }
            for(j=0; j<sy; j++){
                a = playfield[i][j];
                playfield[x][j] = a;
                update_bkg_playfield(x, j, a);
                playfield[i][j] = 0;
                update_bkg_playfield(i, j, 0);
            }
            column_tiles[x] = column_tiles[i];
            column_tiles[i] = 0;
            break;
        }
    } 
}