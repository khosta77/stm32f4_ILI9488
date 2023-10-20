#ifndef SERIAL_TFT_CONTROL_BUS_REGISTERS_H_
#define SERIAL_TFT_CONTROL_BUS_REGISTERS_H_



/* Возможны случаи когда нет надобности в том, чтобы выводить текст, для этого раскомментировать строчку ниже
 * */

//#define STFTCB_TEXT

/* Регистры для работы с текстом
 * */
#ifndef STFTCB_TEXT
#define STFTCB_TEXT_COLOR           0xFFFF
#define STFTCB_TEXT_ORIENTATION     0x01  // 0x00 горизонтальный | 0x01 вертикальный
#define STFTCB_TEXT_FLIP_HORIZONTAL 0x00  // 0x00 к VCC | 0x01 к LED
#define STFTCB_TEXT_FLIP_VERTICAL   0x01  // Отзеркаливание текста

#include "stftcb_font.h"
#endif  // STFTCB_TEXT

#endif  // SERIAL_TFT_CONTROL_BUS_REGISTERS_H_
