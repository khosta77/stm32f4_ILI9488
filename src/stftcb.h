#ifndef SERIAL_TFT_CONTROL_BUS_H_
#define SERIAL_TFT_CONTROL_BUS_H_

/*
 *  На дисплее ILI9488 и ST7735 одинаковые разъемы +- одинаковые. Это говорит о том, что подключение можно \
 *  стандартизировать.
 * */

#include "../system/include/cmsis/stm32f4xx.h"
#include "./spi.h"

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
