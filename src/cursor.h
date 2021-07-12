#ifndef __cursor_INCLUDE
#define __cursor_INCLUDE

extern const uint16_t cursorPalette[];

extern uint8_t cursor_x;
extern uint8_t cursor_y;
extern uint8_t holdtime;

void init_cursor();
void set_cursor();
void check_input();

#endif