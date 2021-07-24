#include <stdint.h>

#include "gfx/gametiles.h"

#ifndef __playfield_INCLUDE
#define __playfield_INCLUDE

#define xo 15
#define yo 23
#define sx 18
#define sy 15

extern const uint16_t tilePalette[];
extern const uint8_t gametile_palettes[];

extern uint8_t playfield[sx][sy];
extern uint8_t adj;
extern uint8_t kill_x[40];
extern uint8_t kill_y[40];
extern uint8_t kill_idx;
extern uint8_t kill_add_idx;
extern uint8_t num_tile_types;

void update_bkg_playfield(uint8_t fx, uint8_t fy, uint8_t val);
void update_playfield(uint8_t fx, uint8_t fy, uint8_t val);
void update_tile(uint8_t fx, uint8_t fy, uint8_t val);
void init_playfield();
void select_tile(uint8_t tx, uint8_t ty);
void add_tile_to_kill(uint8_t kx, uint8_t ky);
void kill_tiles();
void kill_tile_then_add_adjacent(uint8_t tx, uint8_t ty);
uint8_t check_tile_for_adjacent(uint8_t tx, uint8_t ty);
void kill_tile(uint8_t tx, uint8_t ty);
void erase_tile(uint8_t tx, uint8_t ty);
void drop_tiles();
void shift_columns();
#endif
