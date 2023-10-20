#ifndef SERIAL_TFT_CONTROL_BUS_REGISTERS_H_
#define SERIAL_TFT_CONTROL_BUS_REGISTERS_H_

#include "../system/include/cmsis/stm32f4xx.h"

#include <stdbool.h>
#include <stdlib.h> 
#include <math.h>
#include <string.h>

#include "st7735_register.h"  // 1.6

#include "st7735s_reg.h"      // 0.96
#include "st7789v_reg.h"  // 1.3
#include "st7789v3_reg.h"  // 1.69
#include "st7789_reg.h"  // 2.4

#include "ili9341_reg.h"  // 2.2
#include "ili9488_reg.h"  // 3.5


#define STFTCB_COLOR_WHITE      0xFFFF
#define STFTCB_COLOR_BLACK      0x0000
#define STFTCB_COLOR_BLUE       0x001F
#define STFTCB_COLOR_BRED       0xF81F
#define STFTCB_COLOR_GRED 		0xFFE0
#define STFTCB_COLOR_GBLUE		0x07FF
#define STFTCB_COLOR_RED        0xF800
#define STFTCB_COLOR_MAGENTA    0xF81F
#define STFTCB_COLOR_GREEN      0x07E0
#define STFTCB_COLOR_CYAN       0x7FFF
#define STFTCB_COLOR_YELLOW     0xFFE0
#define STFTCB_COLOR_BROWN 		0xBC40
#define STFTCB_COLOR_BRRED 		0xFC07
#define STFTCB_COLOR_GRAY  		0x8430
#define STFTCB_COLOR_GRAY0      0xEF7D
#define STFTCB_COLOR_GRAY1      0x8410
#define STFTCB_COLOR_GRAY2      0x4208
#define STFTCB_COLOR_DARKBLUE   0x01CF
#define STFTCB_COLOR_LIGHTBLUE  0x7D7C
#define STFTCB_COLOR_GRAYBLUE   0x5458
#define STFTCB_COLOR_LIGHTGREEN 0x841F
#define STFTCB_COLOR_LIGHTGRAY  0xEF5B
#define STFTCB_COLOR_LGRAY 	    0xC618
#define STFTCB_COLOR_LGRAYBLUE  0xA651

#define STFTCB_HEIGHT ST7735_HEIGHT // Ось Y
#define STFTCB_WIDTH  ST7735_WIDTH  // Ось X
#define STFTCB_SIZE   (STFTCB_HEIGHT * STFTCB_WIDTH)

/* Display position
 *  +---------------+
 *  |+---~...~---> X|
 *  ||              |
 *  ||              |
 *  |~              |
 *  |:              |
 *  |~              |
 *  ||              |
 *  |V              |
 *  |Y              |
 *  +---------------+
 *     <STFTCBus>
 * */
#define STFTCB_POINT(arr, y, x) (arr[((y * ST7735_WIDTH) + x)])

#define STFTCB_CASET 0x2A
#define STFTCB_PASET 0x2B
#define STFTCB_RAMWR 0x2C
#define STFTCB_RAMRD 0x2E

// RESET | RST | RES
#define STFTCB_RESET_ON   GPIOB->ODR |= GPIO_ODR_OD12
#define STFTCB_RESET_OFF  GPIOB->ODR &= ~GPIO_ODR_OD12

// D/C | AO | RS
#define	STFTCB_DC_ON	  GPIOB->ODR |= GPIO_ODR_OD14
#define	STFTCB_DC_OFF     GPIOB->ODR &= ~GPIO_ODR_OD14

// SPI_SS(CS)
#define	STFTCB_CS_ON	  GPIOB->ODR |= GPIO_ODR_OD15
#define	STFTCB_CS_OFF	  GPIOB->ODR &= ~GPIO_ODR_OD15

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

#include "./stftcb_spi.h"

#endif  // SERIAL_TFT_CONTROL_BUS_REGISTERS_H_
