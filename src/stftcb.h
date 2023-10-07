#ifndef SERIAL_TFT_CONTROL_BUS_H_
#define SERIAL_TFT_CONTROL_BUS_H_

/*
 *  На дисплее ILI9488 и ST7735 одинаковые разъемы +- одинаковые. Это говорит о том, что подключение можно \
 *  стандартизировать.
 * */

#include "../system/include/cmsis/stm32f4xx.h"
#include "./spi.h"

//#include "./stftcb_options.h"
#include "./st7735_register.h"


#define STFTCB_HEIGHT ST7735_HEIGHT
#define STFTCB_WIGTH  ST7735_WIDTH
#define STFTCB_SIZE   (STFTCB_HEIGHT * STFTCB_WIGTH)
#include <stdbool.h>
#include <stdlib.h> 
#include <math.h>
#include <string.h>

/** Есть большие(сторона > 255) и маленькие(сторона < 255) дисплеи. Для скорости обработки данных на \
 *  маленьких дисплеях стоит использовать другие функции, которые не дробят uint16_t на 2 uint8_t
 * */
#define USING_SMALL_TFT 1 

#define STFTCB_CASET 0x2A
#define STFTCB_PASET 0x2B
#define STFTCB_RAMWR 0x2C
#define STFTCB_RAMRD 0x2E

#define STFTCB_ARRAY_SIZE (STFTCB_SIZE * sizeof(uint16_t))

extern uint16_t stftcb_array_tx[STFTCB_ARRAY_SIZE];
uint16_t stftcb_array_tx[STFTCB_ARRAY_SIZE];
uint8_t stftcb_array_tx_status = 0x00;

void STFTCB_init();
void STFTCB_GPIO_init();
void STFTCB_memset();
void mymemset(uint32_t *msg, uint16_t clr, const uint32_t size);
void STFTCB_DMA_init();

void stftcb_sendCmd1byte(uint8_t cmd);
void stftcb_sendData1byte(uint8_t dt);
void stftcb_sendCmd2byte(uint16_t cmd);
void stftcb_sendData2byte(uint16_t dt);

void stftcb_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
//void stftcb_DrawPixel(uint8_t x, uint8_t y, uint16_t color);
//void stftcb_DrawHorizonLine(uint8_t x, uint8_t y, uint8_t _length, uint16_t color, const uint16_t _wight_);
//void stftcb_DrawVerticalLine(uint8_t x, uint8_t y, uint8_t _height, uint16_t color, const uint16_t _height_);
//void stftcb_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color);

void STFTCB_init() {
    SPI1_init();
    STFTCB_GPIO_init();
    STFTCB_memset();
    STFTCB_DMA_init();
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

void STFTCB_memset() {
    memset(&stftcb_array_tx[0], 0x0000, STFTCB_ARRAY_SIZE);
}

void mymemset(uint32_t *msg, uint16_t clr, const uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        *(msg + i) = ((clr << 16) | clr);
    }
}

void STFTCB_DMA_init() {
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	DMA2_Stream3->CR &= ~DMA_SxCR_EN;
	while ((DMA2_Stream3->CR) & DMA_SxCR_EN){;}
    // MSIZE | PSIZE в этом собака зарыта
	DMA2_Stream3->CR = ((0x03 << 25) | DMA_SxCR_MINC | DMA_SxCR_DIR_0 | DMA_SxCR_MSIZE_0 | DMA_SxCR_PSIZE_0 | DMA_SxCR_TCIE 
                           /* | DMA_SxCR_HTIE | DMA_SxCR_TEIE | DMA_SxCR_DMEIE*//* | DMA_SxCR_CIRC*/);
	//DMA2_Stream3->FCR=0;
	//DMA2_Stream3->FCR &= ~DMA_SxFCR_DMDIS;

    DMA2->LIFCR |= DMA_LIFCR_CTCIF3; 
    //(DMA_LIFCR_CTCIF3 | DMA_LIFCR_CHTIF3 | DMA_LIFCR_CTEIF3 | DMA_LIFCR_CDMEIF3 | DMA_LIFCR_CFEIF3);
	DMA2_Stream3->PAR = (uint32_t)&SPI1->DR;
	DMA2_Stream3->M0AR = (uint32_t)&stftcb_array_tx[0];
	DMA2_Stream3->NDTR = STFTCB_SIZE;
//	DMA2_Stream3->CR |= DMA_SxCR_EN;

	NVIC_EnableIRQ(DMA2_Stream3_IRQn);
    NVIC_SetPriority(DMA2_Stream3_IRQn, 2);
}

void SPI_1byte_mode_on() {
    SPI1->CR1 &= ~SPI_CR1_SPE;
    SPI1->CR1 &= ~SPI_CR1_DFF;
    SPI1->CR1 |= SPI_CR1_SPE;
}

void SPI_2byte_mode_on() {
    SPI1->CR1 &= ~SPI_CR1_SPE;
    SPI1->CR1 |= SPI_CR1_DFF;
    SPI1->CR1 |= SPI_CR1_SPE;
}

void DMA2_Stream3_IRQHandler(void) {
    if (DMA2->LISR & (DMA_LISR_TCIF3)) {
		GPIOD->ODR ^= GPIO_ODR_OD15;
		//printf("finished transfered\r\n");
		stftcb_array_tx_status = 0x00;
		DMA2_Stream3->CR &= ~DMA_SxCR_EN;
		DMA2->LIFCR |= DMA_LIFCR_CTCIF3;
	}

/*
	if (DMA2->LISR & (DMA_LISR_HTIF3)) {
		GPIOD->ODR ^= GPIO_ODR_OD12;
		//printf("half transfered\r\n");
		DMA2->LIFCR |= DMA_LIFCR_CHTIF3;
	}
*/

/*
    if (DMA2->LISR & (DMA_LISR_TEIF3)) {
		//printf("transfer error interrupt\r\n");
		DMA2->LIFCR |= (DMA_LIFCR_CTEIF3);
	}
*/

/*
    if (DMA2->LISR & (DMA_LISR_DMEIF3)) {
		//printf("Direct mode interrupt error\r\n");
		DMA2->LIFCR |= (DMA_LIFCR_CDMEIF3);
	}
*/

/*
    if (DMA2->LISR & (DMA_LISR_FEIF3)) {
		//printf("FIFO error interrupt\r\n");
		DMA2->LIFCR |= (DMA_LIFCR_CFEIF3);
	}
*/

//	NVIC_ClearPendingIRQ(DMA2_Stream3_IRQn);
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

void stftcb_sendCmd1byte(uint8_t cmd) {
    STFTCB_DC_OFF;
    SPI1_transmit(cmd);
}

void stftcb_sendData1byte(uint8_t dt) {
    STFTCB_DC_ON;
    SPI1_transmit(dt);
}

void stftcb_sendCmd2byte(uint16_t cmd) {
    STFTCB_DC_OFF;
    SPI1_transmit(cmd);
}

void stftcb_sendData2byte(uint16_t dt) {
    STFTCB_DC_ON;
    SPI1_transmit(dt);
}

void stftcb_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    SPI_1byte_mode_on();
    stftcb_sendCmd1byte(STFTCB_CASET);  // Column addr set
	stftcb_sendData1byte(0x00);
    stftcb_sendData1byte(x0);           // XSTART XS7 ~ XS0
	stftcb_sendData1byte(0x00);
    stftcb_sendData1byte(x1);           // XEND   XE7 ~ XE0

	stftcb_sendCmd1byte(STFTCB_PASET);  // Row addr set
	stftcb_sendData1byte(0x00);
    stftcb_sendData1byte(y0);           // YSTART
	stftcb_sendData1byte(0x00);
    stftcb_sendData1byte(y1);           // END

	stftcb_sendCmd1byte(STFTCB_RAMWR);
}

/*
void stftcb_DrawPixel(uint8_t x, uint8_t y, uint16_t color) {
    stftcb_SetAddressWindow(x, y, x + 1, y + 1);
	stftcb_sendData1byte(((uint8_t)((color & 0xFF00) >> 8)));
	stftcb_sendData1byte(((uint8_t)(color & 0x00FF)));
}
*/

/*
void stftcb_DrawHorizonLine(uint8_t x, uint8_t y, uint8_t _length, uint16_t color, const uint16_t _wight_) {
	//STFTCB_CS_OFF;
    if ((x + _length - 1) >= _wight_)  
        _length = _wight_ - x;
    stftcb_SetAddressWindow(x, y, (x + _length - 1), y);

    uint8_t lc = ((uint8_t)((color & 0xFF00) >> 8));
    uint8_t rc = ((uint8_t)(color & 0x00FF)); 
    while (_length--) {
        stftcb_sendData1byte(lc);
        stftcb_sendData1byte(rc);
    }
	//STFTCB_CS_ON;
}
*/

/*
void stftcb_DrawVerticalLine(uint8_t x, uint8_t y, uint8_t _height, uint16_t color, const uint16_t _height_) {
	//STFTCB_CS_OFF;
    if ((y + _height - 1) >= _height_) 
        _height = _height_ - y;
    stftcb_SetAddressWindow(x, y, x, y + _height - 1);

    uint8_t lc = ((uint8_t)((color & 0xFF00) >> 8));
    uint8_t rc = ((uint8_t)(color & 0x00FF));
    while (_height--) {
        stftcb_sendData1byte(lc);
        stftcb_sendData1byte(rc);
    }
	//STFTCB_CS_ON;
}
*/

#if 0
/** Алгоритм Брезенхэма // https://ru.wikibooks.org/wiki/Реализации_алгоритмов/Алгоритм_Брезенхэма
 * */
void stftcb_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color) {
	//STFTCB_CS_OFF;
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
	//STFTCB_CS_ON;
}
#endif

void stftcb_DrawFillEasyRectangle(uint8_t x, uint8_t y, uint8_t _wight, uint8_t _height, uint16_t color) {
    //STFTCB_CS_OFF;
    while (stftcb_array_tx_status != 0x00) {;}
    for (uint32_t t = 0; t < 0x1FFFF0; t++);
    stftcb_SetAddressWindow(x, y, (x + _wight - 1), (y + _height - 1));
    SPI_2byte_mode_on();
    STFTCB_DC_ON;
    DMA2_Stream3->CR &= ~DMA_SxCR_EN;
    for (uint16_t i = 0; i < STFTCB_SIZE; i++) {
        stftcb_array_tx[i] = color;
    }
   // memset(&stftcb_array_tx[0], color, STFTCB_ARRAY_SIZE);
    stftcb_array_tx_status = 0x11;
	DMA2_Stream3->NDTR = STFTCB_SIZE;
    DMA2_Stream3->CR |= DMA_SxCR_MINC;
    DMA2_Stream3->CR |= DMA_SxCR_EN;
    //for (y = _height; y > 0; y--) {
      //  for (x = _wight; x > 0; x--) {
		//		stftcb_sendData2bite(color);
        //}
    //}
	//STFTCB_CS_ON;
}

/*
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
*/

#endif  // SERIAL_TFT_CONTROL_BUS_H_
