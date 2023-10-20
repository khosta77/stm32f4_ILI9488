#ifndef SERIAL_TFT_CONTROL_BUS_H_
#define SERIAL_TFT_CONTROL_BUS_H_

#include "../system/include/cmsis/stm32f4xx.h"
#include "./stftcb_spi.h"

//#include "./stftcb_options.h"
#include "./st7735_register.h"

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

#include <stdbool.h>
#include <stdlib.h> 
#include <math.h>
#include <string.h>

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

// Объявление существования массива для передачи данных
extern uint16_t stftcb_array_tx_0[STFTCB_SIZE];
extern uint16_t stftcb_array_tx_1[STFTCB_SIZE];

// Сам массив. По хорошему его надо чисто либо в main определить
uint16_t stftcb_array_tx_0[STFTCB_SIZE];
uint16_t stftcb_array_tx_1[STFTCB_SIZE];

// Переменная статуса
uint8_t stftcb_array_tx_status = 0x00;
uint8_t stftcb_array_tx_mxar = 0x00;

//// Функция инициализации
void STFTCB_init();
static void STFTCB_GPIO_init();
static void STFTCB_memset0();
static void STFTCB_DMA_init();

//// Отправка команды, либо данных настройки по SPI в обход DMA
// Одно байтовый формат
void stftcb_sendCmd1byte(uint8_t cmd);
void stftcb_sendData1byte(uint8_t dt);

// Дву байтовый формат
void stftcb_sendCmd2byte(uint16_t cmd);
void stftcb_sendData2byte(uint16_t dt);

//// Работа с кадром
// Задача размеров окна
#if (STFTCB_WIDTH < 0xFF)
void stftcb_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
#else
void stftcb_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
#endif
void stftcb_SetFullAddressWindow();

// Обоновление кадра
void stftcb_updateFrame();

//// Функции отрисовки объектов
void stftcb_DrawFillBackground(uint16_t color);
void stftcb_DrawPixel(uint16_t y, uint16_t x, uint16_t color);
uint8_t stftcb_DrawHorizonLine(uint16_t y, uint16_t x0, uint16_t x1, uint16_t color);
uint8_t stftcb_DrawVerticalLine(uint16_t x, uint16_t y0, uint16_t y1, uint16_t color);
void stftcb_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void stftcb_DrawNoFillRectangle(uint16_t x0, uint16_t y0, uint16_t x2, uint16_t y2, float alpha, uint16_t color);
void stftcb_DrawFillRectangle(uint16_t x0, uint16_t y0, uint16_t x2, uint16_t y2, float alpha, uint16_t color);
//void stftcb_DrawNoFillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
//                               float alpha, uint16_t color);
//void stftcb_DrawFillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
//                             float alpha, uint16_t color);
void stftcb_DrawNoFillCicle(int16_t x0, int16_t y0, int16_t R, uint16_t color);
void stftcb_DrawFillCicle(int16_t x0, int16_t y0, int16_t R, uint16_t color);



/** @brief STFTCB_init - инициализация интерфейса serial tft control bus
 * */
void STFTCB_init() {
    SPI_init();
    STFTCB_GPIO_init();
    STFTCB_memset0();
    STFTCB_DMA_init();
}

/** @brief STFTCB_GPIO_init - инициализация GPIO для различных команд
 *                            B12 ---> RESET | RST | RES - аппаратный сброс (сброс на низком уровне)
 *                            B14 ---> D/C   | AO  | RS  - Выбор данных/команды. (некоторые ЖК-платы \
 *                                                         называют это постоянным током или D / C). При \
 *                                                         подаче высокого напряжения это означает отправку \
 *                                                         данных, при подаче низкого напряжения это \
 *                                                         означает отправку команды.
 *                            B15 ---> SPI_SS(CS)        - Выбор микросхемы (некоторые ЖК-дисплеи называют \
 *                                                         это SS)
 * */
static void STFTCB_GPIO_init() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER |= (GPIO_MODER_MODER12_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0);
}

/** @brief STFTCB_memset_0 - обнуление массива
 * */
static void STFTCB_memset0() {
    memset(&stftcb_array_tx_0[0], 0x0000, (STFTCB_SIZE * sizeof(uint16_t)));
    memset(&stftcb_array_tx_1[0], 0x0000, (STFTCB_SIZE * sizeof(uint16_t)));
}

static void STFTCB_DMA_init() {
    DMA2_Stream3->M0AR = (uint32_t)&stftcb_array_tx_0[0];
    DMA2_Stream3->M1AR = (uint32_t)&stftcb_array_tx_1[0];
	DMA2_Stream3->NDTR = STFTCB_SIZE;
}

/** @brief DMA2_Stream3_IRQHandler - прерывание при завершение передачи данных по SPI
 * */
void DMA2_Stream3_IRQHandler(void) {
    // Прерывания по завершению передачи
    if (DMA2->LISR & (DMA_LISR_TCIF3)) {
		GPIOD->ODR ^= GPIO_ODR_OD15;
		//printf("finished transfered\r\n");
		stftcb_array_tx_status = 0x00;
		DMA2_Stream3->CR &= ~DMA_SxCR_EN;
		DMA2->LIFCR |= DMA_LIFCR_CTCIF3;
	}

/*  // Прерывания на половине передачи
	if (DMA2->LISR & (DMA_LISR_HTIF3)) {
		GPIOD->ODR ^= GPIO_ODR_OD12;
		//printf("half transfered\r\n");
		DMA2->LIFCR |= DMA_LIFCR_CHTIF3;
	}
*/

/*  // Прерывания при ошибке передачи
    if (DMA2->LISR & (DMA_LISR_TEIF3)) {
		//printf("transfer error interrupt\r\n");
		DMA2->LIFCR |= (DMA_LIFCR_CTEIF3);
	}
*/

/*  // Прерывания при ошибке direct-режима(чтобы это не значило)
    if (DMA2->LISR & (DMA_LISR_DMEIF3)) {
		//printf("Direct mode interrupt error\r\n");
		DMA2->LIFCR |= (DMA_LIFCR_CDMEIF3);
	}
*/

/*  // Прерывания при ошибке FIFO
    if (DMA2->LISR & (DMA_LISR_FEIF3)) {
		//printf("FIFO error interrupt\r\n");
		DMA2->LIFCR |= (DMA_LIFCR_CFEIF3);
	}
*/

//	NVIC_ClearPendingIRQ(DMA2_Stream3_IRQn);
}

void stftcb_sendCmd1byte(uint8_t cmd) {
    STFTCB_DC_OFF;
    SPI_transmit(cmd);
}

void stftcb_sendData1byte(uint8_t dt) {
    STFTCB_DC_ON;
    SPI_transmit(dt);
}

void stftcb_sendCmd2byte(uint16_t cmd) {
    STFTCB_DC_OFF;
    SPI_transmit(cmd);
}

void stftcb_sendData2byte(uint16_t dt) {
    STFTCB_DC_ON;
    SPI_transmit(dt);
}

#if (STFTCB_WIDTH < 0xFF)
void stftcb_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
#else
void stftcb_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
#endif
    SPI_1byte_mode_on();
    stftcb_sendCmd1byte(STFTCB_CASET);  // Column addr set
#if (STFTCB_WIDTH < 0xFF)
    stftcb_sendData1byte(0x00);
    stftcb_sendData1byte((x0));                    // XSTART  XS7 ~ XS0
    stftcb_sendData1byte(0x00);
    stftcb_sendData1byte((x1));                    // XEND    XE7 ~ XE0

#else
    stftcb_sendData1byte(((0xFF00 & (x0)) >> 8));
    stftcb_sendData1byte(((x0) & 0x00FF));
	stftcb_sendData1byte(((0xFF00 & (x1)) >> 8));
    stftcb_sendData1byte(((x1) & 0x00FF));
#endif

    stftcb_sendCmd1byte(STFTCB_PASET);  // Row addr set
#if (STFTCB_HEIGHT < 0xFF)
    stftcb_sendData1byte(0x00);
    stftcb_sendData1byte((y0));
    stftcb_sendData1byte(0x00);
    stftcb_sendData1byte((y1));
#else
    stftcb_sendData1byte(((0xFF00 & (y0)) >> 8));
    stftcb_sendData1byte(((y0) & 0x00FF));
    stftcb_sendData1byte(((0xFF00 & (y1)) >> 8));
    stftcb_sendData1byte(((y1) & 0x00FF));
#endif

	stftcb_sendCmd1byte(STFTCB_RAMWR);
}

void stftcb_SetFullAddressWindow() {
    SPI_1byte_mode_on();
    stftcb_sendCmd1byte(STFTCB_CASET);  // Column addr set
	stftcb_sendData1byte(0x00);
    stftcb_sendData1byte(0x00);         // XSTART XS7 ~ XS0
#if (STFTCB_WIDTH < 0xFF)
    stftcb_sendData1byte(0x00);
    stftcb_sendData1byte((STFTCB_WIDTH - 1));                    // XEND   XE7 ~ XE0
#else
	stftcb_sendData1byte(((0xFF00 & (STFTCB_WIDTH - 1)) >> 8));
    stftcb_sendData1byte(((STFTCB_WIDTH - 1) & 0x00FF));         // XEND   XE7 ~ XE0  
#endif

    stftcb_sendCmd1byte(STFTCB_PASET);  // Row addr set
    stftcb_sendData1byte(0x00);
    stftcb_sendData1byte(0x00);         // YSTART
#if (STFTCB_HEIGHT < 0xFF)
    stftcb_sendData1byte(0x00);
    stftcb_sendData1byte((STFTCB_HEIGHT - 1));                    // YEND
#else
    stftcb_sendData1byte(((0xFF00 & (STFTCB_HEIGHT - 1)) >> 8));
    stftcb_sendData1byte(((STFTCB_HEIGHT - 1) & 0x00FF));         // YEND
#endif

	stftcb_sendCmd1byte(STFTCB_RAMWR);
}

/** @brief stftcb_updateFrame - функция обновления кадра
 * */
void stftcb_updateFrame() {
    while (stftcb_array_tx_status != 0x00) {;}  // Ждем пока предыдущая передача не закончится
    stftcb_SetFullAddressWindow();
    
    SPI_2byte_mode_on();
    STFTCB_DC_ON;
    DMA2_Stream3->CR &= ~DMA_SxCR_EN;
	while ((DMA2_Stream3->CR) & DMA_SxCR_EN){;}
    
    if (stftcb_array_tx_mxar == 0) {
        DMA2_Stream3->CR &= ~DMA_SxCR_CT;
        stftcb_array_tx_mxar = 0x01;
    } else {
        DMA2_Stream3->CR |= DMA_SxCR_CT;
        stftcb_array_tx_mxar = 0x00;
    }

    stftcb_array_tx_status = 0x11;
	DMA2_Stream3->NDTR = STFTCB_SIZE;
    DMA2_Stream3->CR |= DMA_SxCR_MINC;
    DMA2_Stream3->CR |= DMA_SxCR_EN;
}


/*=========================================================================================================*/
/*                              Функции отрисовки объектов в кадре                                         */
/*=========================================================================================================*/
/** @brief stftcb_DrawPixel - отрисовка одного пикселя в заднной точке. Функция работает крайне медленно,
 *                            лучше исполозовать такую конструкцию
 *  for (uint16_t i = 0, I = 0; i < STFTCB_HEIGHT; i++, I += STFTCB_WIDTH) {
 *      for (uint16_t j = 0; j < STFTCB_WIDTH; j += ) {
 *          tft_display[I + j] = colors[color];
 *       }
 *   }
 *
 * */
void stftcb_DrawPixel(uint16_t y, uint16_t x, uint16_t color) {
    if (stftcb_array_tx_mxar == 0)
        STFTCB_POINT(stftcb_array_tx_0, y, x) = color;
    else
        STFTCB_POINT(stftcb_array_tx_1, y, x) = color;
}

/** @brief stftcb_DrawHorizonLine - отрисовка линии по горизонтали
 * */
uint8_t stftcb_DrawHorizonLine(uint16_t y, uint16_t x0, uint16_t x1, uint16_t color) {
    if ((x0 > x1) || (x1 < STFTCB_WIDTH) || (y < STFTCB_HEIGHT))
        return 0xFF;

    const uint16_t Y = y * STFTCB_WIDTH;
    for (uint16_t x = x0; x < x1; x++)
        if (stftcb_array_tx_mxar == 0)
            stftcb_array_tx_0[(Y + x)] = color;
        else
            stftcb_array_tx_1[(Y + x)] = color;
 
    return 0x00;
}

/** @brief stftcb_DrawHorizonLine - отрисовка линии по вертикали
 * */
uint8_t stftcb_DrawVerticalLine(uint16_t x, uint16_t y0, uint16_t y1, uint16_t color) {
    if ((y0 > y1) || (y1 < STFTCB_HEIGHT) || (x < STFTCB_WIDTH))
        return 0xFF;

    for (uint16_t y = y0, Y = (y0 * STFTCB_WIDTH); y < y1; y++, Y += STFTCB_WIDTH)
        if (stftcb_array_tx_mxar == 0)
            stftcb_array_tx_0[(Y + x)] = color;
        else
            stftcb_array_tx_1[(Y + x)] = color;

    return 0x00;
}

static void stftcb_DrawLine0(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color, 
                             const int16_t deltaX, const int16_t deltaY, const int16_t signX,
                             const int16_t signY, int16_t error, int16_t error2);
static void stftcb_DrawLine1(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color, 
                             const int16_t deltaX, const int16_t deltaY, const int16_t signX,
                             const int16_t signY, int16_t error, int16_t error2);

/** @brief stftcb_DrawLine - отрисовка линии, по диагонали, с помощью алгоритма Брезенхэма ссылка: \
 *                           https://ru.wikibooks.org/wiki/Реализации_алгоритмов/Алгоритм_Брезенхэма
 * */
void stftcb_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
    const int16_t deltaX = abs(x1 - x0);
    const int16_t deltaY = abs(y1 - y0);
    const int16_t signX = (x0 < x1) ? 1 : -1;
    const int16_t signY = (y0 < y1) ? 1 : -1;
    int16_t error = deltaX - deltaY;
    int16_t error2;
    if (stftcb_array_tx_mxar == 0) {
        stftcb_DrawLine0(x0, y0, x1, y1, color, deltaX, deltaY, signX, signY, error, error2);
#if 0
        STFTCB_POINT(stftcb_array_tx_0, y1, x1) = color;
        while (x0 != x1 || y0 != y1) {
            STFTCB_POINT(stftcb_array_tx_0, y0, x0) = color;
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
#endif
    } else {
        stftcb_DrawLine1(x0, y0, x1, y1, color, deltaX, deltaY, signX, signY, error, error2);
#if 0
        STFTCB_POINT(stftcb_array_tx_1, y1, x1) = color;
        while (x0 != x1 || y0 != y1) {
            STFTCB_POINT(stftcb_array_tx_1, y0, x0) = color;
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
#endif
    }
}

static void stftcb_DrawLine0(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color, 
                             const int16_t deltaX, const int16_t deltaY, const int16_t signX, 
                             const int16_t signY, int16_t error, int16_t error2) {
    STFTCB_POINT(stftcb_array_tx_0, y1, x1) = color;
    while (x0 != x1 || y0 != y1) {
        STFTCB_POINT(stftcb_array_tx_0, y0, x0) = color;
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
}

static void stftcb_DrawLine1(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color, 
                             const int16_t deltaX, const int16_t deltaY, const int16_t signX,
                             const int16_t signY, int16_t error, int16_t error2) {
    STFTCB_POINT(stftcb_array_tx_1, y1, x1) = color;
    while (x0 != x1 || y0 != y1) {
        STFTCB_POINT(stftcb_array_tx_1, y0, x0) = color;
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
}

/* @brief stftcb_DrawFillBackground - закрашивает в выбранный цвет задний фон
 * */
void stftcb_DrawFillBackground(uint16_t color) {
    if (stftcb_array_tx_mxar == 0)
        memset(&stftcb_array_tx_0[0], color, (STFTCB_SIZE * sizeof(uint16_t)));
    else
        memset(&stftcb_array_tx_1[0], color, (STFTCB_SIZE * sizeof(uint16_t)));
}

#define ROTATION_X(x, x0, y, y0, cosa, sina) ((x - x0) * cosa - (y - y0) * sina + x0)
#define ROTATION_Y(x, x0, y, y0, cosa, sina) ((x - x0) * sina + (y - y0) * cosa + y0)

/** @brief stftcb_DrawNoFillRectangle - отрисовка НЕ закрашенного треугольника, без или с поворотом.
 *    (x0, y0)    (x1, y1)
 *            +--+
 *            |  |
 *            +--+
 *    (x3, y3)    (x2, y2)
 * */
void stftcb_DrawNoFillRectangle(uint16_t x0, uint16_t y0, uint16_t x2, uint16_t y2, float alpha, uint16_t color) {
    const uint16_t deltaX = ((x2 + x0) / 2);
    const uint16_t deltaY = ((y2 + y0) / 2);

    float Asin = sin((alpha * M_PI / 180));
    float Acos = cos((alpha * M_PI / 180));

    uint16_t x1 = x2, y1 = y0; 
    uint16_t x3 = x0, y3 = y2;

    // Повернутые кординаты
    uint16_t x0n = ROTATION_X(x0, deltaX, y0, deltaY, Acos, Asin);
    uint16_t y0n = ROTATION_Y(x0, deltaX, y0, deltaY, Acos, Asin);
    
    uint16_t x1n = ROTATION_X(x1, deltaX, y1, deltaY, Acos, Asin);
    uint16_t y1n = ROTATION_Y(x1, deltaX, y1, deltaY, Acos, Asin);
    
    uint16_t x2n = ROTATION_X(x2, deltaX, y2, deltaY, Acos, Asin);
    uint16_t y2n = ROTATION_Y(x2, deltaX, y2, deltaY, Acos, Asin);
    
    uint16_t x3n = ROTATION_X(x3, deltaX, y3, deltaY, Acos, Asin);
    uint16_t y3n = ROTATION_Y(x3, deltaX, y3, deltaY, Acos, Asin);

    stftcb_DrawLine(x0n, y0n, x1n, y1n, color);
    stftcb_DrawLine(x1n, y1n, x2n, y2n, color);
    stftcb_DrawLine(x2n, y2n, x3n, y3n, color);
    stftcb_DrawLine(x3n, y3n, x0n, y0n, color);
}

/** @brief stftcb_DrawFillRectangle - отрисовка Закрашенного треугольника, без или с поворотом.
 *                                    Есть искажение, при наложении фигур
 *    (x0, y0)    (x1, y1)
 *            +--+
 *            |  |
 *            +--+
 *    (x3, y3)    (x2, y2)
 * */
void stftcb_DrawFillRectangle(uint16_t x0, uint16_t y0, uint16_t x2, uint16_t y2, float alpha, uint16_t color) {
    //// 0. Отрисовка контура
    const uint16_t deltaX = ((x2 + x0) / 2);
    const uint16_t deltaY = ((y2 + y0) / 2);

    float Asin = sin((alpha * M_PI / 180));
    float Acos = cos((alpha * M_PI / 180));

    uint16_t x1 = x2, y1 = y0; 
    uint16_t x3 = x0, y3 = y2;

    // Повернутые кординаты
    uint16_t x0n = ROTATION_X(x0, deltaX, y0, deltaY, Acos, Asin);
    uint16_t y0n = ROTATION_Y(x0, deltaX, y0, deltaY, Acos, Asin);
    
    uint16_t x1n = ROTATION_X(x1, deltaX, y1, deltaY, Acos, Asin);
    uint16_t y1n = ROTATION_Y(x1, deltaX, y1, deltaY, Acos, Asin);
    
    uint16_t x2n = ROTATION_X(x2, deltaX, y2, deltaY, Acos, Asin);
    uint16_t y2n = ROTATION_Y(x2, deltaX, y2, deltaY, Acos, Asin);
    
    uint16_t x3n = ROTATION_X(x3, deltaX, y3, deltaY, Acos, Asin);
    uint16_t y3n = ROTATION_Y(x3, deltaX, y3, deltaY, Acos, Asin);

    stftcb_DrawLine(x0n, y0n, x1n, y1n, color);
    stftcb_DrawLine(x1n, y1n, x2n, y2n, color);
    stftcb_DrawLine(x2n, y2n, x3n, y3n, color);
    stftcb_DrawLine(x3n, y3n, x0n, y0n, color);
    //// 1. Закраска
    /** Первый алгоритм
     * */
    uint16_t x[4] = {x0n, x1n, x2n, x3n};
    uint16_t y[4] = {y0n, y1n, y2n, y3n};
    uint8_t min_i = 0, max_i = 0;
    for (uint8_t i = 1; i < 4; ++i) {
        if (y[i] > y[max_i])
            max_i = i;
        if (y[i] < y[min_i]) 
            min_i = i;
    }

    uint8_t mrk_back = 0x00, mrk_front = 0x00;
    if (stftcb_array_tx_mxar == 0) {  // Это ублюдски сделано. Надо как то передалть, но позже
        for (uint16_t Y = ((y[min_i] + 1) * STFTCB_WIDTH), Ym = (y[max_i] * STFTCB_WIDTH); Y < Ym; ++Y) {
            if (stftcb_array_tx_0[Y] == color) {  // Осуществлеям проверку на определние находимся \
                                            // ли мы на границе контура
                if (mrk_back == 0x00) {
                    if (mrk_front == 0x00) {
                        mrk_back = 0x11;
                    }
                } else {
                    if (mrk_front == 0x11) {
                        mrk_back = 0x00;
                    }
                }
            } else {
                if (mrk_back == 0x11) {
                    mrk_front = 0x11;
                    stftcb_array_tx_0[Y] = color;
                } else {
                    mrk_front = 0x00;
                }
            }
        }
    } else {
        for (uint16_t Y = ((y[min_i] + 1) * STFTCB_WIDTH), Ym = (y[max_i] * STFTCB_WIDTH); Y < Ym; ++Y) {
            if (stftcb_array_tx_1[Y] == color) {  // Осуществлеям проверку на определние находимся \
                                            // ли мы на границе контура
                if (mrk_back == 0x00) {
                    if (mrk_front == 0x00) {
                        mrk_back = 0x11;
                    }
                } else {
                    if (mrk_front == 0x11) {
                        mrk_back = 0x00;
                    }
                }
            } else {
                if (mrk_back == 0x11) {
                    mrk_front = 0x11;
                    stftcb_array_tx_1[Y] = color;
                } else {
                    mrk_front = 0x00;
                }
            }
        }
    }
}

/** @brief stftcb_DrawNoFillCicle - рисует контур круга
 * */
void stftcb_DrawNoFillCicle(int16_t x0, int16_t y0, int16_t R, uint16_t color) {
    int16_t x = 0;
    int16_t y = R;
    int16_t delta = 1 - 2 * R;
    int16_t error = 0;
    if (stftcb_array_tx_mxar == 0) {
        while (y >= x) {
            stftcb_array_tx_0[(y0 + y) * STFTCB_WIDTH + (x0 + x)] = color;
            stftcb_array_tx_0[(y0 - y) * STFTCB_WIDTH + (x0 + x)] = color;
            stftcb_array_tx_0[(y0 + y) * STFTCB_WIDTH + (x0 - x)] = color;
            stftcb_array_tx_0[(y0 - y) * STFTCB_WIDTH + (x0 - x)] = color;
            stftcb_array_tx_0[(y0 + x) * STFTCB_WIDTH + (x0 + y)] = color;
            stftcb_array_tx_0[(y0 - x) * STFTCB_WIDTH + (x0 + y)] = color;
            stftcb_array_tx_0[(y0 + x) * STFTCB_WIDTH + (x0 - y)] = color;
            stftcb_array_tx_0[(y0 - x) * STFTCB_WIDTH + (x0 - y)] = color;
            error = 2 * (delta + y) - 1;
            if ((delta < 0) && (error <= 0)) {
                delta += (2 * (++x)) + 1;
            } else {
                if ((delta > 0) && (error > 0)) {
                    delta -= (2 * (--y)) + 1;
                } else {
                    delta += 2 * (++x - --y);
                }
            }
        }
    } else {
        while (y >= x) {
            stftcb_array_tx_1[(y0 + y) * STFTCB_WIDTH + (x0 + x)] = color;
            stftcb_array_tx_1[(y0 - y) * STFTCB_WIDTH + (x0 + x)] = color;
            stftcb_array_tx_1[(y0 + y) * STFTCB_WIDTH + (x0 - x)] = color;
            stftcb_array_tx_1[(y0 - y) * STFTCB_WIDTH + (x0 - x)] = color;
            stftcb_array_tx_1[(y0 + x) * STFTCB_WIDTH + (x0 + y)] = color;
            stftcb_array_tx_1[(y0 - x) * STFTCB_WIDTH + (x0 + y)] = color;
            stftcb_array_tx_1[(y0 + x) * STFTCB_WIDTH + (x0 - y)] = color;
            stftcb_array_tx_1[(y0 - x) * STFTCB_WIDTH + (x0 - y)] = color;
            error = 2 * (delta + y) - 1;
            if ((delta < 0) && (error <= 0)) {
                delta += (2 * (++x)) + 1;
            } else {
                if ((delta > 0) && (error > 0)) {
                    delta -= (2 * (--y)) + 1;
                } else {
                    delta += 2 * (++x - --y);
                }
            }
        } 
    }
}

/** @brief stftcb_DrawFillCicle - закраска с бликами происходит, почему так не понимаю, если отдельно 
 *                                выводить, то все нормально
 * */
void stftcb_DrawFillCicle(int16_t x0, int16_t y0, int16_t R, uint16_t color) {
    int16_t x = 0;
    int16_t y = R;
    int16_t delta = 3 - 2 * y;
    if (stftcb_array_tx_mxar == 0) {
        while (x <= y) {
            stftcb_array_tx_0[(y0 + y) * STFTCB_WIDTH + (x0 + x)] = color;
            stftcb_array_tx_0[(y0 - y) * STFTCB_WIDTH + (x0 + x)] = color;
            stftcb_array_tx_0[(y0 + y) * STFTCB_WIDTH + (x0 - x)] = color;
            stftcb_array_tx_0[(y0 - y) * STFTCB_WIDTH + (x0 - x)] = color;
            stftcb_array_tx_0[(y0 + x) * STFTCB_WIDTH + (x0 + y)] = color;
            stftcb_array_tx_0[(y0 - x) * STFTCB_WIDTH + (x0 + y)] = color;
            stftcb_array_tx_0[(y0 + x) * STFTCB_WIDTH + (x0 - y)] = color;
            stftcb_array_tx_0[(y0 - x) * STFTCB_WIDTH + (x0 - y)] = color;
            delta += delta < 0 ? 4 * x + 6 : 4 * (x - y--) + 10;
            ++x;
        }
    } else {
        while (x <= y) {
            stftcb_array_tx_1[(y0 + y) * STFTCB_WIDTH + (x0 + x)] = color;
            stftcb_array_tx_1[(y0 - y) * STFTCB_WIDTH + (x0 + x)] = color;
            stftcb_array_tx_1[(y0 + y) * STFTCB_WIDTH + (x0 - x)] = color;
            stftcb_array_tx_1[(y0 - y) * STFTCB_WIDTH + (x0 - x)] = color;
            stftcb_array_tx_1[(y0 + x) * STFTCB_WIDTH + (x0 + y)] = color;
            stftcb_array_tx_1[(y0 - x) * STFTCB_WIDTH + (x0 + y)] = color;
            stftcb_array_tx_1[(y0 + x) * STFTCB_WIDTH + (x0 - y)] = color;
            stftcb_array_tx_1[(y0 - x) * STFTCB_WIDTH + (x0 - y)] = color;
            delta += delta < 0 ? 4 * x + 6 : 4 * (x - y--) + 10;
            ++x; 
        } 
    }
    uint8_t mrk_back = 0x00, mrk_front = 0x00;
    if (stftcb_array_tx_mxar == 0) {  // Это ублюдски сделано. Надо как то передалть, но позже
        for (uint16_t Y = ((y0 - R + 1) * STFTCB_WIDTH), Ym = (y0 + R * STFTCB_WIDTH); Y < Ym; ++Y) {
            if (stftcb_array_tx_0[Y] == color) {  // Осуществлеям проверку на определние находимся \
                                            // ли мы на границе контура
                if (mrk_back == 0x00) {
                    if (mrk_front == 0x00) {
                        mrk_back = 0x11;
                    }
                } else {
                    if (mrk_front == 0x11) {
                        mrk_back = 0x00;
                    }
                }
            } else {
                if (mrk_back == 0x11) {
                    mrk_front = 0x11;
                    stftcb_array_tx_0[Y] = color;
                } else {
                    mrk_front = 0x00;
                }
            }
        }
    } else {
        for (uint16_t Y = ((y0 - R + 1) * STFTCB_WIDTH), Ym = ((y0 + R) * STFTCB_WIDTH); Y < Ym; ++Y) {
            if (stftcb_array_tx_1[Y] == color) {  // Осуществлеям проверку на определние находимся \
                                            // ли мы на границе контура
                if (mrk_back == 0x00) {
                    if (mrk_front == 0x00) {
                        mrk_back = 0x11;
                    }
                } else {
                    if (mrk_front == 0x11) {
                        mrk_back = 0x00;
                    }
                }
            } else {
                if (mrk_back == 0x11) {
                    mrk_front = 0x11;
                    stftcb_array_tx_1[Y] = color;
                } else {
                    mrk_front = 0x00;
                }
            }
        }
    }
}
/*=========================================================================================================*/
/*                                              Шрифты                                                     */
/*=========================================================================================================*/
#if 0
#define STFTCB_TEXT_COLOR           0xFFFF
#define STFTCB_TEXT_ORIENTATION     0x01  // 0x00 горизонтальный | 0x01 вертикальный
#define STFTCB_TEXT_FLIP_HORIZONTAL 0x00  // 0x00 к VCC | 0x01 к LED
#define STFTCB_TEXT_FLIP_VERTICAL   0x01  // Отзеркаливание текста 

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

static uint16_t get_symbol_id(char c) {
    switch (c) {
        case 32:
            return 0;  // space
        case 48:
            return 8;  // 0
        case 49:
            return 16;  // 1
        case 50:
            return 24;  // 2
        case 51:
            return 32;  // 3
        case 52:
            return 40;  // 4
        case 53:
            return 48;  // 5
        case 54:
            return 56;  // 6
        case 55:
            return 64;  // 7
        case 56:
            return 72;  // 8
        case 57:
            return 80;  // 9
        default:
            GPIOD->ODR |= GPIO_ODR_OD14;
    }
}

#if STFTCB_TEXT_ORIENTATION
static void draw_symbol_v(uint16_t id, const uint16_t y, const uint16_t x) {
    uint8_t b = 0x00;
    if (stftcb_array_tx_mxar == 0x00) {  // Смотри комментарий в draw_symbol_h
#if STFTCB_TEXT_FLIP_HORIZONTAL
        for (uint8_t i = 0; i < 8; i++) {
            b = MyFont[(id + i)];
            for (uint16_t j = 0; j < 8; j++) {
#else
        for (uint8_t i = 0, k = 7; i < 8; i++, k--) {
            b = MyFont[(id + k)];
            for (uint16_t j = 7; j != 0xFFFF; j--) {
#endif
                if (b & 0x80) stftcb_array_tx_0[(y + i) * STFTCB_WIDTH + (x + j)] = STFTCB_TEXT_COLOR;
                b <<= 1;
            }
        }
    } else {
#if STFTCB_TEXT_FLIP_HORIZONTAL
        for (uint8_t i = 0; i < 8; i++) {
            b = MyFont[(id + i)];
            for (uint16_t j = 0; j < 8; j++) {
#else
        for (uint8_t i = 0, k = 7; i < 8; i++, k--) {
            b = MyFont[(id + k)];
            for (uint16_t j = 7; j != 0xFFFF; j--) {
#endif
                if (b & 0x80) stftcb_array_tx_1[(y + i) * STFTCB_WIDTH + (x + j)] = STFTCB_TEXT_COLOR;
                b <<= 1;
            }
        }
    }
}
#else
static void draw_symbol_h(uint16_t id, const uint16_t y, const uint16_t x) {
    uint8_t b = 0x00;
    if (stftcb_array_tx_mxar == 0x00) {  // Как же ужасно это выглядит. Но такое разделение нужно, \
                                         // чтобы в цикле не проводить однотипную проверку на нужный \
                                         // нам массив записи, хоть это и ужасно выглядит, но пару тактов \
                                         // экономит, надо подумать как можно это исправить. 17.10.23
#if STFTCB_TEXT_FLIP_HORIZONTAL
        for (uint8_t i = 0; i < 8; i++) {
            b = MyFont[(id + i)];
            for (uint16_t j = 0; j < 8; j++) {
#else
        for (uint8_t i = 0, k = 7; i < 8; i++, k--) {
            b = MyFont[(id + k)];
            for (uint16_t j = 7; j != 0xFFFF; j--) {
#endif
                if (b & 0x01) stftcb_array_tx_0[(y + j) * STFTCB_WIDTH + (x + i)] = STFTCB_TEXT_COLOR;
                b >>= 1;
            }
        }
    } else {
#if STFTCB_TEXT_FLIP_HORIZONTAL
        for (uint8_t i = 0; i < 8; i++) {
            b = MyFont[(id + i)];
            for (uint16_t j = 0; j < 8; j++) {
#else
        for (uint8_t i = 0, k = 7; i < 8; i++, k--) {
            b = MyFont[(id + k)];
            for (uint16_t j = 7; j != 0xFFFF; j--) {
#endif
                if (b & 0x01) stftcb_array_tx_1[(y + j) * STFTCB_WIDTH + (x + i)] = STFTCB_TEXT_COLOR;
                b >>= 1;
            }
        }
    }
}
#endif

#if STFTCB_TEXT_FLIP_VERTICAL
void reverse(char* str) {
    uint16_t n = strlen(str);
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        char ch = str[i];
        str[i] = str[j];
        str[j] = ch;
    }
}
#endif

void printt(uint16_t x0, uint16_t y0, const char *str) {
    const uint16_t Ssize = strlen(str);
    uint16_t sid;

#if STFTCB_TEXT_FLIP_VERTICAL
    char nstr[128] = "";
    strcpy(nstr, str);
    reverse(nstr);
#endif

    for (uint16_t c = 0; c < Ssize; c++) {
#if STFTCB_TEXT_FLIP_VERTICAL
        sid = get_symbol_id(*(nstr + c));
#else
        sid = get_symbol_id(*(str + c));
#endif

#if STFTCB_TEXT_ORIENTATION
        draw_symbol_v(sid, y0, x0);
        x0 += 8;
#else
        draw_symbol_h(sid, y0, x0);
        y0 += 8;
#endif
    }
}

#if STFTCB_TEXT_ORIENTATION
static void draw_symbol_V(uint16_t id, const uint16_t y, const uint16_t x) {
    uint8_t b = 0x00;
    if (stftcb_array_tx_mxar == 0x00) {  // Смотри комментарий в draw_symbol_H
#if STFTCB_TEXT_FLIP_HORIZONTAL
        for (uint8_t i = 0; i < 8; i++) {
            b = MyFont[(id + i)];
            for (uint16_t j = 0; j < 8; j++) {
#else
        for (uint8_t i = 0, k = 7; i < 8; i++, k--) {
            b = MyFont[(id + k)];
            for (uint16_t j = 7; j != 0xFFFF; j--) {
#endif
                if (b & 0x80) {
                    stftcb_array_tx_0[(y + 2 * i) * STFTCB_WIDTH + (x + 2 * j)] = STFTCB_TEXT_COLOR;
                    stftcb_array_tx_0[(y + 2 * i) * STFTCB_WIDTH + (x + 2 * j + 1)] = STFTCB_TEXT_COLOR;
                    stftcb_array_tx_0[(y + 2 * i + 1) * STFTCB_WIDTH + (x + 2 * j)] = STFTCB_TEXT_COLOR;
                    stftcb_array_tx_0[(y + 2 * i + 1) * STFTCB_WIDTH + (x + 2 * j + 1)] = STFTCB_TEXT_COLOR;
                }
                b <<= 1;
            }
        }
    } else {
#if STFTCB_TEXT_FLIP_HORIZONTAL
        for (uint8_t i = 0; i < 8; i++) {
            b = MyFont[(id + i)];
            for (uint16_t j = 0; j < 8; j++) {
#else
        for (uint8_t i = 0, k = 7; i < 8; i++, k--) {
            b = MyFont[(id + k)];
            for (uint16_t j = 7; j != 0xFFFF; j--) {
#endif
                if (b & 0x80) {
                    stftcb_array_tx_1[(y + 2 * i) * STFTCB_WIDTH + (x + 2 * j)] = STFTCB_TEXT_COLOR;
                    stftcb_array_tx_1[(y + 2 * i) * STFTCB_WIDTH + (x + 2 * j + 1)] = STFTCB_TEXT_COLOR;
                    stftcb_array_tx_1[(y + 2 * i + 1) * STFTCB_WIDTH + (x + 2 * j)] = STFTCB_TEXT_COLOR;
                    stftcb_array_tx_1[(y + 2 * i + 1) * STFTCB_WIDTH + (x + 2 * j + 1)] = STFTCB_TEXT_COLOR;
                }
                b <<= 1;
            }
        }
    }
}
#else
static void draw_symbol_H(uint16_t id, const uint16_t y, const uint16_t x) {
    uint8_t b = 0x00;
    if (stftcb_array_tx_mxar == 0x00) {  // Смотри комментарий к малому.
#if STFTCB_TEXT_FLIP_HORIZONTAL
        for (uint8_t i = 0; i < 8; i++) {
            b = MyFont[(id + i)];
            for (uint16_t j = 0; j < 8; j++) {
#else
        for (uint8_t i = 0, k = 7; i < 8; i++, k--) {
            b = MyFont[(id + k)];
            for (uint16_t j = 7; j != 0xFFFF; j--) {
#endif
                if (b & 0x01) {
                    stftcb_array_tx_0[(y + j * 2) * STFTCB_WIDTH + (x + 2 * i)] = STFTCB_TEXT_COLOR;
                    stftcb_array_tx_0[(y + j * 2) * STFTCB_WIDTH + (x + 2 * i + 1)] = STFTCB_TEXT_COLOR;
                    stftcb_array_tx_0[(y + j * 2 + 1) * STFTCB_WIDTH + (x + 2 * i)] = STFTCB_TEXT_COLOR;
                    stftcb_array_tx_0[(y + j * 2 + 1) * STFTCB_WIDTH + (x + 2 * i + 1)] = STFTCB_TEXT_COLOR;
                }
                b >>= 1;
            }
        }
    } else {
#if STFTCB_TEXT_FLIP_HORIZONTAL
        for (uint8_t i = 0; i < 8; i++) {
            b = MyFont[(id + i)];
            for (uint16_t j = 0; j < 8; j++) {
#else
        for (uint8_t i = 0, k = 7; i < 8; i++, k--) {
            b = MyFont[(id + k)];
            for (uint16_t j = 7; j != 0xFFFF; j--) {
#endif
                if (b & 0x01) {
                    stftcb_array_tx_1[(y + (j * 2)) * STFTCB_WIDTH + (x + 2 * i)] = STFTCB_TEXT_COLOR;
                    stftcb_array_tx_1[(y + (j * 2)) * STFTCB_WIDTH + (x + 2 * i + 1)] = STFTCB_TEXT_COLOR;
                    stftcb_array_tx_1[(y + (j * 2 + 1)) * STFTCB_WIDTH + (x + 2 * i)] = STFTCB_TEXT_COLOR;
                    stftcb_array_tx_1[(y + (j * 2 + 1)) * STFTCB_WIDTH + (x + 2 * i + 1)] = STFTCB_TEXT_COLOR;
                }
                b >>= 1;
            }
        }
    }
}
#endif

void printT(uint16_t x0, uint16_t y0, const char *str) {
    const uint16_t Ssize = strlen(str);  // (sizeof(str) / sizeof(char));
    uint16_t sid;

#if STFTCB_TEXT_FLIP_VERTICAL
    char nstr[128] = "";
    strcpy(nstr, str);
    reverse(nstr);
#endif

    for (uint16_t c = 0; c < Ssize; c++) {
#if STFTCB_TEXT_FLIP_VERTICAL
        sid = get_symbol_id(*(nstr + c));
#else
        sid = get_symbol_id(*(str + c));
#endif

#if STFTCB_TEXT_ORIENTATION
        draw_symbol_V(sid, y0, x0);
        x0 += 16;
#else
        draw_symbol_H(sid, y0, x0);
        y0 += 16;
#endif
    }
}
#endif  // text

#endif  // SERIAL_TFT_CONTROL_BUS_H_
