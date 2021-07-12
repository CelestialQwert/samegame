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

void update_bkg_playfield(uint8_t fx, uint8_t fy, uint8_t val);
void update_playfield(uint8_t fx, uint8_t fy, uint8_t val);
void init_playfield();
void kill_tile(uint8_t tx, uint8_t ty);

#endif