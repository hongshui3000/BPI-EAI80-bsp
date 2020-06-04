#include <string.h>

#include "draw.h"
#include "font.h"
#include "hzk16.h"
#define PIC_WIDTH  LCD_UI_W
#define PIC_HEIGHT LCD_UI_H

extern uint32_t ui_buf_addr;
//ARGB8888

static void lcd_draw_point(uint16_t dx, uint16_t dy, uint32_t color);

const unsigned char logo[LOGOSIZE] =   /* 0X00,0X20,0X10,0X00,0X10,0X00,0X00,0X1B, */
{
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XA7, 0X6E, 0X1C, 0X00,
    0XC1, 0X79, 0X11, 0X00, 0XC1, 0X79, 0X11, 0X00, 0XC1, 0X79, 0X11, 0X00, 0XC1, 0X79, 0X11, 0X00,
    0XC1, 0X79, 0X11, 0X00, 0XC1, 0X79, 0X11, 0X00, 0XC1, 0X79, 0X11, 0X00, 0XC0, 0X78, 0X11, 0X00,
    0XA2, 0X6C, 0X1F, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0XBE, 0X78, 0X13, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XBB, 0X75, 0X13, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XC2, 0X79, 0X10, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC1, 0X7A, 0X13, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XC2, 0X78, 0X10, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X78, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X78, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X78, 0X0F, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XC1, 0X78, 0X0F, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC1, 0X78, 0X0E, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XC1, 0X77, 0X0E, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC4, 0X7D, 0X18, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X84, 0X5E, 0X2A, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0X2E, 0X22, 0X11, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC1, 0X7D, 0X1B, 0X00, 0XC2, 0X7D, 0X1A, 0X00,
    0XC2, 0X7D, 0X1A, 0X00, 0XC2, 0X7D, 0X1A, 0X00, 0XC2, 0X7D, 0X1A, 0X00, 0XC2, 0X7D, 0X1A, 0X00,
    0XC2, 0X7D, 0X1A, 0X00, 0XC2, 0X7D, 0X1A, 0X00, 0XC2, 0X7D, 0X1A, 0X00, 0XC2, 0X7D, 0X1A, 0X00,
    0XC2, 0X7D, 0X1A, 0X00, 0XC2, 0X7D, 0X1A, 0X00, 0XC2, 0X7D, 0X1A, 0X00, 0XC2, 0X7D, 0X1A, 0X00,
    0XC2, 0X7D, 0X1A, 0X00, 0XC2, 0X7D, 0X1A, 0X00, 0XC4, 0X7C, 0X17, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XA8, 0X6D, 0X1A, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X9F, 0X6E, 0X27, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0X79, 0X58, 0X27, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XE5, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XA7, 0X6F, 0X21, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0XB3, 0X71, 0X13, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X19, 0X11, 0XD2, 0X00,
    0X2F, 0X24, 0X15, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X06, 0X05, 0X06, 0X00,
    0X00, 0X00, 0X00, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0X43, 0X33, 0X1D, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0XBB, 0X76, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X0E, 0X0C, 0X09, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XCA, 0X8E, 0X3A, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X1D, 0X16, 0XD8, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X92, 0X66, 0X26, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0XBE, 0X76, 0X0F, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0X86, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XAE, 0X72, 0X1E, 0X00,
    0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X13, 0X0E, 0X3A, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X16, 0X12, 0XBB, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0XC2, 0X7D, 0X1A, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00, 0XC2, 0X79, 0X11, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X0A, 0X07, 0XF6, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0XBE, 0X7A, 0X19, 0X00, 0XC2, 0X79, 0X11, 0X00, 0X7A, 0X57, 0X25, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X0D, 0X0A, 0XF0, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XA9, 0X6C, 0X15, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X1F, 0X17, 0XCE, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XC7, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XD7, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X13, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00,
    0X00, 0X00, 0XFF, 0X00, 0X05, 0X03, 0XF2, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X24, 0X1A, 0XB4, 0X00, 0X00, 0X00, 0XFA, 0X00, 0X01, 0X01, 0XFC, 0X00, 0X00, 0X00, 0XFE, 0X00,
    0X00, 0X00, 0XFE, 0X00, 0X01, 0X01, 0XFC, 0X00, 0X00, 0X00, 0XFA, 0X00, 0X26, 0X1D, 0XAA, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,

};

//@Todo: Alpha blending problems
void lcd_drawlogo(int x, int y, unsigned int color)
{
    int j = 0;
    int i = 0;
    int index = 0;
    int w = 32;
    int h = 32;
    unsigned int *addr = (unsigned int *)logo;
    for (i = 0; i < h; i++)
    {
        for (j = 0; j < w; j++)
        {
            lcd_draw_point(x + i, y + j, addr[index]);
            index += 1;
        }
    }
}

void lcd_clear_area(int x, int y, int w, int h)
{
    int j = 0;
    unsigned char *start_addr;
    for (j = 0; j < h; j++)
    {
        start_addr = ((unsigned char *)ui_buf_addr) + (PIC_WIDTH * (y + j) + x) * 4;
        memset(start_addr, 0, w * 4);
    }
}

static void lcd_draw_point(uint16_t dx, uint16_t dy, uint32_t color)
{
    *(uint32_t *)((uint32_t)ui_buf_addr + ((PIC_WIDTH * dy + dx) << 2)) = color;
}

static void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1; //计算坐标增量
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if (delta_x > 0)
    {
        incx = 1;    //设置单步方向
    }
    else if (delta_x == 0)
    {
        incx = 0;    //垂直线
    }
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
    {
        incy = 1;
    }
    else if (delta_y == 0)
    {
        incy = 0;    //水平线
    }
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
    {
        distance = delta_x;    //选取基本增量坐标轴
    }
    else
    {
        distance = delta_y;
    }
    for (t = 0; t <= distance + 1; t++) //画线输出
    {
        lcd_draw_point(uRow, uCol, color); //画点
        xerr += delta_x ;
        yerr += delta_y ;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}


void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color)
{
    lcd_draw_line(x1, y1, x2, y1, color);
    lcd_draw_line(x1, y1, x1, y2, color);
    lcd_draw_line(x1, y2, x2, y2, color);
    lcd_draw_line(x2, y1, x2, y2, color);
}

//bbggrr24(h-l) ==> argb32
void lcd_draw_rgb24(unsigned char *src, int x, int y, int w, int h)
{
    int i, j, cnt = 0;
    unsigned int color = 0xff000000;
    unsigned char *b = src;
    unsigned char *g = src + w * h;
    unsigned char *r = src + w * h * 2;

    for (j = 0; j < h; j++)
    {
        for (i = 0; i < w; i++)
        {
            color = 0xff000000;
            color |= *(r + cnt);//r
            color |= *(g + cnt) << 8; //g
            color |= *(b + cnt) << 16; //b
            lcd_draw_point(x + i, y + j, color);
            cnt++;
        }
    }
}

static void lcd_showchar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint8_t mode, uint32_t color)
{
    uint8_t temp, t1, t;
    uint16_t y0 = y;
    uint8_t csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);
    num = num - ' ';
    for (t = 0; t < csize; t++)
    {
        if (size == 12)
        {
            temp = asc2_1206[num][t];
        }
        else if (size == 16)
        {
            temp = asc2_1608[num][t];
        }
        else if (size == 24)
        {
            temp = asc2_2412[num][t];
        }
        else if (size == 32)
        {
            temp = asc2_3216[num][t];
        }
        else
        {
            return;
        }
        for (t1 = 0; t1 < 8; t1++)
        {
            if (temp & 0x80)
            {
                lcd_draw_point(x, y, color);
            }
            else if (mode == 0)
            {
                lcd_draw_point(x, y, BACK_COLOR);
            }
            temp <<= 1;
            y++;
            if (y >= PIC_HEIGHT)
            {
                return;
            }
            if ((y - y0) == size)
            {
                y = y0;
                x++;
                if (x >= PIC_WIDTH)
                {
                    return;
                }
                break;
            }
        }
    }
}

void lcd_draw_text(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint8_t *p, uint32_t color)
{
    uint8_t x0 = x;
    width += x;
    height += y;
    while ((*p <= '~') && (*p >= ' '))
    {
        if (x >= width)
        {
            x = x0;
            y += size;
        }
        if (y >= height)
        {
            break;
        }
        lcd_showchar(x, y, *p, size, 1, color);
        x += size / 2;
        p++;
    }
}

static void lcd_draw_chchar(uint16_t x, uint16_t y, char *chchar, uint8_t size, uint8_t mode, uint32_t color)
{
    uint8_t temp, t1, t;
    uint16_t x0 = x;
    char data;
    int i = 0, j = 0, k = 0;
    char data_out[32];

    GetOneHz16(chchar, data_out);

    if (size == 16)
    {
        for (i = 0; i < 16; i++)
        {
            for (j = 0; j < 2; j++)
            {
                data = data_out[i * 2 + j];
                for (k = 7; k >= 0; k--)
                {
                    if (data & (1 << k))
                    {
                        lcd_draw_point(x, y, color);
                    }
                    else if (mode == 0)
                    {
                        lcd_draw_point(x, y, BACK_COLOR);
                    }
                    x++;
                    if (y >= PIC_HEIGHT)
                    {
                        return;
                    }
                    if ((x - x0) == size)
                    {
                        x = x0;
                        y++;
                        if (x >= PIC_WIDTH)
                        {
                            return;
                        }
                        break;
                    }
                }
            }
        }
    }
    else if (size == 32)
    {
        for (i = 0; i < 16; i++)
        {
            for (j = 0; j < 2; j++)
            {
                data = data_out[i * 2 + j];
                for (k = 7; k >= 0; k--)
                {
                    if (data & (1 << k))
                    {
                        lcd_draw_point(x, y, color);
                        lcd_draw_point(x + 1, y, color);
                        lcd_draw_point(x, y + 1, color);
                        lcd_draw_point(x + 1, y + 1, color);
                    }
                    else if (mode == 0)
                    {
                        lcd_draw_point(x, y, BACK_COLOR);
                        lcd_draw_point(x + 1, y, BACK_COLOR);
                        lcd_draw_point(x, y + 1, BACK_COLOR);
                        lcd_draw_point(x + 1, y + 1, BACK_COLOR);
                    }
                    x += 2;
                    if (y >= PIC_HEIGHT)
                    {
                        return;
                    }
                    if ((x - x0) == size)
                    {
                        x = x0;
                        y += 2;
                        if (x >= PIC_WIDTH)
                        {
                            return;
                        }
                        break;
                    }
                }
            }
        }
    }
}

/*input:GBK, output:32byte array(16bit X 16bit)*/
static int GetOneHz16(uint8_t *gbk, uint8_t *DataOut)
{
    uint32_t i;
    uint8_t *FontPos;
    uint32_t q, w;

    q = gbk[0];
    w = gbk[1];

    if ((q < 0xa1) || (w < 0xa1))
    {
        return 0;//not in the arry
    }

    q -= 0xa1;
    w -= 0xa1;

    FontPos = (uint8_t *)gFontHzk16 + (q * 94 + w) * 32;
    for (i = 0; i < 32; i++)
    {
        *DataOut++ = *FontPos++;
    }

    return 1;
}

void lcd_draw_chstr(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *chstr, uint32_t color)
{
    uint8_t x0 = x;
    uint8_t i = 0;
    width += x;
    height += y;
    char chchar[2];
    while (*(chstr + i) != 0x00)
    {
        if (x >= width)
        {
            x = x0;
            y += size;
        }
        if (y >= height)
        {
            break;
        }
        chchar[1] = chstr[i + 1];
        chchar[0] = chstr[i];

        lcd_draw_chchar(x, y, &chchar, size, 1, color);
        x += size;
        i += 2;
    }
}

void lcd_clear(void)
{
    memset((unsigned char *)ui_buf_addr, 0, PIC_WIDTH * PIC_HEIGHT * 4);
    lcd_draw_rectangle(0, 0, PIC_WIDTH - 1, PIC_HEIGHT - 1, 0xFFFFFFFF);
    lcd_drawlogo(PIC_WIDTH - LOGO_W - 1, 1, 0xFFFF0000); //
}

