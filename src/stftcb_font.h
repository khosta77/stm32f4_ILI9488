#ifndef SERIAL_TFT_CONTROL_BUS_FONT_H_
#define SERIAL_TFT_CONTROL_BUS_FONT_H_

#include "stftcb_reg.h"

uint8_t MyFont[] = {
    0b00000000,  // empty
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01111110,

    0b00111100,  // 0
    0b01000010,
    0b01000010,
    0b01000010,
    0b01000010,
    0b01000010,
    0b01000010,
    0b00111100,

    0b00000110,  // 1
    0b00001010,
    0b00010010,
    0b00100010,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000010,

    0b00111100,  // 2
    0b01000010,
    0b01000010,
    0b00100010,
    0b00000100,
    0b00111000,
    0b01000000,
    0b01111110,

    0b00111100,  // 3
    0b01000010,
    0b00000010,
    0b00000010,
    0b00011100,
    0b00000010,
    0b01000010,
    0b00111100,

    0b01000010,  // 4
    0b01000010,
    0b01000010,
    0b01000010,
    0b01111110,
    0b00000010,
    0b00000010,
    0b00000010,

    0b01111110,  // 5
    0b01000000,
    0b01000000,
    0b01111000,
    0b00000100,
    0b00000010,
    0b00000010,
    0b01111100,

    0b00110000,  // 6
    0b00100000,
    0b01000000,
    0b01111100,
    0b01000010,
    0b01000010,
    0b01000010,
    0b00111100,

    0b01111110,  // 7
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000010,

    0b00111100,  // 8
    0b01000010,
    0b01000010,
    0b00111100,
    0b00111100,
    0b01000010,
    0b01000010,
    0b00111100,

    0b00111100,  // 9
    0b01000010,
    0b01000010,
    0b01000010,
    0b00111110,
    0b00000010,
    0b00000100,
    0b01111100,

};


#endif  // SERIAL_TFT_CONTROL_BUS_FONT_H_
