#ifndef SERIAL_TFT_CONTROL_BUS_H_
#define SERIAL_TFT_CONTROL_BUS_H_

/*
 *  На дисплее ILI9488 и ST7735 одинаковые разъемы +- одинаковые. Это говорит о том, что подключение можно \
 *  стандартизировать.
 * */

#include "../system/include/cmsis/stm32f4xx.h"
#include "./spi.h"

#include <stdbool.h>
#include <stdlib.h> 
#include <math.h>

/** Есть большие(сторона > 255) и маленькие(сторона < 255) дисплеи. Для скорости обработки данных на \
 *  маленьких дисплеях стоит использовать другие функции, которые не дробят uint16_t на 2 uint8_t
 * */
#define USING_SMALL_TFT 1 

#define STFTCB_CASET 0x2A
#define STFTCB_PASET 0x2B
#define STFTCB_RAMWR 0x2C
#define STFTCB_RAMRD 0x2E

void STFTCB_init();
void STFTCB_GPIO_init();

void stftcb_sendCmd(uint8_t cmd);
void stftcb_sendData(uint8_t dt);


void STFTCB_init() {
    SPI1_init();
    STFTCB_GPIO_init();
}

/** @ STFTCB_GPIO_init - инициализация GPIO для различных команд
 *                       B12 ---> RESET | RST | RES - аппаратный сброс (сброс на низком уровне)
 *                       B14 ---> D/C   | AO  | RS  - Выбор данных/команды. (некоторые ЖК-платы называют \
 *                                                    это постоянным током или D / C). При подаче высокого \
 *                                                    напряжения это означает отправку данных, при подаче \
 *                                                    низкого напряжения это означает отправку команды.
 *                       B15 ---> SPI_SS(CS)        - Выбор микросхемы (некоторые ЖК-дисплеи называют это SS)
 * */
void STFTCB_GPIO_init() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER |= (GPIO_MODER_MODER12_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0);
    GPIOB->OSPEEDR |= ((GPIO_OSPEEDER_OSPEEDR12_1 | GPIO_OSPEEDER_OSPEEDR12_0) |
                       (GPIO_OSPEEDER_OSPEEDR14_1 | GPIO_OSPEEDER_OSPEEDR14_0) |
                       (GPIO_OSPEEDER_OSPEEDR15_1 | GPIO_OSPEEDER_OSPEEDR15_0));
}

// RESET | RST | RES
#define STFTCB_RESET_ON   GPIOB->ODR |= GPIO_ODR_OD12
#define STFTCB_RESET_OFF  GPIOB->ODR &= ~GPIO_ODR_OD12

// D/C | AO | RS
#define	STFTCB_DC_ON	  GPIOB->ODR |= GPIO_ODR_OD14
#define	STFTCB_DC_OFF     GPIOB->ODR &= ~GPIO_ODR_OD14

// SPI_SS(CS)
#define	STFTCB_CS_ON	  GPIOB->ODR |= GPIO_ODR_OD15
#define	STFTCB_CS_OFF	  GPIOB->ODR &= ~GPIO_ODR_OD15

// lcd7735_sendCmd 
void stftcb_sendCmd(uint8_t cmd) {
    STFTCB_DC_OFF;
    SPI1_transmit(cmd);
}

// lcd7735_sendData
void stftcb_sendData(uint8_t dt) {
    STFTCB_DC_ON;
    SPI1_transmit(dt);
}

#define ST7735_USING 1

#if USING_SMALL_TFT
void stftcb_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void stftcb_DrawPixel(uint8_t x, uint8_t y, uint16_t color);
void stftcb_DrawHorizonLine(uint8_t x, uint8_t y, uint8_t _length, uint16_t color, const uint16_t _wight_);
void stftcb_DrawVerticalLine(uint8_t x, uint8_t y, uint8_t _height, uint16_t color, const uint16_t _height_);
void stftcb_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color);

void stftcb_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    stftcb_sendCmd(STFTCB_CASET);  // Column addr set
	stftcb_sendData(0x00);         //        XS15 ~ XS8
	stftcb_sendData(x0);           // XSTART XS7 ~ XS0
	stftcb_sendData(0x00);         //        XE15 ~ XE8
	stftcb_sendData(x1);           // XEND   XE7 ~ XE0

	stftcb_sendCmd(STFTCB_PASET);  // Row addr set
	stftcb_sendData(0x00);
	stftcb_sendData(y0);           // YSTART
	stftcb_sendData(0x00);
	stftcb_sendData(y1);           // END

	stftcb_sendCmd(STFTCB_RAMWR);
}

void stftcb_DrawPixel(uint8_t x, uint8_t y, uint16_t color) {
    stftcb_SetAddressWindow(x, y, x + 1, y + 1);
	stftcb_sendData(((uint8_t)((color & 0xFF00) >> 8)));
	stftcb_sendData(((uint8_t)(color & 0x00FF)));
}

void stftcb_DrawHorizonLine(uint8_t x, uint8_t y, uint8_t _length, uint16_t color, const uint16_t _wight_) {
	STFTCB_CS_OFF;
    if ((x + _length - 1) >= _wight_)  
        _length = _wight_ - x;
    stftcb_SetAddressWindow(x, y, (x + _length - 1), y);

    uint8_t lc = ((uint8_t)((color & 0xFF00) >> 8));
    uint8_t rc = ((uint8_t)(color & 0x00FF)); 
    while (_length--) {
        stftcb_sendData(lc);
        stftcb_sendData(rc);
    }
	STFTCB_CS_ON;
}

void stftcb_DrawVerticalLine(uint8_t x, uint8_t y, uint8_t _height, uint16_t color, const uint16_t _height_) {
	STFTCB_CS_OFF;
    if ((y + _height - 1) >= _height_) 
        _height = _height_ - y;
    stftcb_SetAddressWindow(x, y, x, y + _height - 1);

    uint8_t lc = ((uint8_t)((color & 0xFF00) >> 8));
    uint8_t rc = ((uint8_t)(color & 0x00FF));
    while (_height--) {
        stftcb_sendData(lc);
        stftcb_sendData(rc);
    }
	STFTCB_CS_ON;
}

/** Алгоритм Брезенхэма // https://ru.wikibooks.org/wiki/Реализации_алгоритмов/Алгоритм_Брезенхэма
 * */
void stftcb_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color) {
	STFTCB_CS_OFF;
    const int16_t deltaX = abs(x1 - x0);
    const int16_t deltaY = abs(y1 - y0);
    const int16_t signX = (x0 < x1) ? 1 : -1;
    const int16_t signY = (y0 < y1) ? 1 : -1;
    int16_t error = deltaX - deltaY;
    int16_t error2;
    stftcb_DrawPixel(x1, y1, color);
    while (x0 != x1 || y0 != y1) {
        stftcb_DrawPixel(x0, y0, color);
        error2 = error * 2;
        if (error2 > -deltaY) {
            error -= deltaY;
            x0 += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            y0 += signY;
        }
    }
	STFTCB_CS_ON;
}

void stftcb_DrawFillEasyRectangle(uint8_t x, uint8_t y, uint8_t _wight, uint8_t _height, uint16_t color) {
    // clipping
//    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
//    if((x + w - 1) >= ST7735_WIDTH) w = ST7735_WIDTH - x;
//    if((y + h - 1) >= ST7735_HEIGHT) h = ST7735_HEIGHT - y;

    STFTCB_CS_OFF;
    stftcb_SetAddressWindow(x, y, (x + _wight - 1), (y + _height - 1));
    STFTCB_DC_ON;

    uint8_t lc = ((uint8_t)((color & 0xFF00) >> 8));
    uint8_t rc = ((uint8_t)(color & 0x00FF));
    for (y = _height; y > 0; y--) {
        for (x = _wight; x > 0; x--) {
					stftcb_sendData(lc);
					stftcb_sendData(rc);
        }
    }
	STFTCB_CS_ON;
}

#define ROTATION_X(x, x0, y, y0, cosa, sina) ((x - x0) * cosa + (y - y0) * sina + x0)
#define ROTATION_Y(x, x0, y, y0, cosa, sina) ((x - x0) * sina - (y - y0) * cosa + y0)

void stftcb_DrawFillRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, float alpha, uint16_t color) {
    const uint8_t deltaX = ((x1 + x0) / 2);
    const uint8_t deltaY = ((y1 + y0) / 2);

    float Asin = sin((alpha * M_PI / 180));
    float Acos = cos((alpha * M_PI / 180));

    uint8_t x2 = x0; uint8_t y2 = y1; uint8_t x3 = x1; uint8_t y3 = y0;
    // Повернутые кординаты
    x0 = ROTATION_X(x0, deltaX, y0, deltaY, Acos, Asin);
    y0 = ROTATION_Y(x0, deltaX, y0, deltaY, Acos, Asin);
    x1 = ROTATION_X(x1, deltaX, y1, deltaY, Acos, Asin);
    y1 = ROTATION_Y(x1, deltaX, y1, deltaY, Acos, Asin);
    x2 = ROTATION_X(x2, deltaX, y2, deltaY, Acos, Asin);
    y2 = ROTATION_Y(x2, deltaX, y2, deltaY, Acos, Asin);
    x3 = ROTATION_X(x3, deltaX, y3, deltaY, Acos, Asin);
    y3 = ROTATION_Y(x3, deltaX, y3, deltaY, Acos, Asin);

    stftcb_DrawLine(x0, y0, x2, y2, color);
    stftcb_DrawLine(x2, y2, x1, y1, color);
    stftcb_DrawLine(x1, y1, x3, y3, color);
    stftcb_DrawLine(x3, y3, x0, y0, color);
}
#else
#if 0
void stftcb_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

void stftcb_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    stftcb_sendCmd(STFTCB_CASET);                    // Column addr set
	stftcb_sendData((uint8_t)((x0 & 0xFF00) >> 8));  //        XS15 ~ XS8
	stftcb_sendData((uint8_t)(x0 & 0x00FF));         // XSTART XS7 ~ XS0
	stftcb_sendData((uint8_t)((x1 & 0xFF00) >> 8));  //        XE15 ~ XE8
	stftcb_sendData((uint8_t)(x1 & 0x00FF));         // XEND   XE7 ~ XE0

	stftcb_sendCmd(STFTCB_PASET);                    // Row addr set
	stftcb_sendData((uint8_t)((y0 & 0xFF00) >> 8));
	stftcb_sendData((uint8_t)(y0 & 0x00FF));         // YSTART
	stftcb_sendData((uint8_t)((y1 & 0xFF00) >> 8));
	stftcb_sendData((uint8_t)(y1 & 0x00FF));         // END

	stftcb_sendCmd(STFTCB_RAMWR);
}
#endif
#endif

#endif  // SERIAL_TFT_CONTROL_BUS_H_
