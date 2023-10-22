#ifndef SERIAL_TFT_CONTROL_BUS_REGISTERS_H_
#define SERIAL_TFT_CONTROL_BUS_REGISTERS_H_

#include "../system/include/cmsis/stm32f4xx.h"

#include <stdbool.h>
#include <stdlib.h> 
#include <math.h>
#include <string.h>

//// Выбор модели дисплея
/* Выбрать модель контроллера и выставить 1 на нем, в противном случае 0
 * */
#define ST7735S__080x160  (0)  // 0.96 // 0x01
#define ST7789V__240x240  (0)  // 1.3  // 0x02
#define ST7735___128x160  (1)  // 1.6  // 0x03
#define ST7789V3_240x280  (0)  // 1.69 // 0x04
#define ILI9341__240x320  (0)  // 2.2  // 0x05
#define ST7789___240x320  (0)  // 2.4  // 0x06
#define ILI9488__320x480  (0)  // 3.5  // 0x07

/* STFTCB_DISPLAY_MODEL - Модель дисплея из списка выше ^
 * STFTCB_ILIST_DEVICE - 0x01 - ILI; 0x00 ST
 * */

#if   ST7735S__080x160
  #define STFTCB_HEIGHT        160   // Y
  #define STFTCB_WIDTH         80    // X
  #define STFTCB_DISPLAY_MODEL 0x01
  #define STFTCB_ILIST_DEVICE  0x00
#elif ST7789V__240x240
  #define STFTCB_HEIGHT        240   // Y
  #define STFTCB_WIDTH         240   // X
  #define STFTCB_DISPLAY_MODEL 0x02
  #define STFTCB_ILIST_DEVICE  0x00
#elif ST7735___128x160
  #define STFTCB_HEIGHT        160   // Y
  #define STFTCB_WIDTH         128   // X
  #define STFTCB_DISPLAY_MODEL 0x03
  #define STFTCB_ILIST_DEVICE  0x00
#elif ST7789V3_240x280
  #define STFTCB_HEIGHT        280   // Y
  #define STFTCB_WIDTH         240   // X
  #define STFTCB_DISPLAY_MODEL 0x04
  #define STFTCB_ILIST_DEVICE  0x00
#elif ILI9341__240x320
  #define STFTCB_HEIGHT        320   // Y
  #define STFTCB_WIDTH         240   // X
  #define STFTCB_DISPLAY_MODEL 0x05
  #define STFTCB_ILIST_DEVICE  0x01
#elif ST7789___240x320
  #define STFTCB_HEIGHT        320   // Y
  #define STFTCB_WIDTH         240   // X
  #define STFTCB_DISPLAY_MODEL 0x06
  #define STFTCB_ILIST_DEVICE  0x00
#elif ILI9488__320x480
  #define STFTCB_HEIGHT        480   // Y
  #define STFTCB_WIDTH         320   // X
  #define STFTCB_DISPLAY_MODEL 0x07
  #define STFTCB_ILIST_DEVICE  0x01
#endif

// Общий размер массива
#define STFTCB_SIZE   (STFTCB_HEIGHT * STFTCB_WIDTH)

// Макрос для удобного работа с точкой, в некоторых случаях
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

//// Макросы для работы с дисплеем
// Level 1
#define STFTCB_NOP
#define STFTCB_SOFTRES
#define STFTCB_RDII
#define STFTCB_RDS
#define STFTCB_RDPW
#define STFTCB_RDMADCTL
#define STFTCB_RDPF
#define STFTCB_RDIF
#define STFTCB_RDSM
#define STFTCB_RDSDR
#define STFTCB_ESM
#define STFTCB_SO
#define STFTCB_PMO
#define STFTCB_NDMO
#define STFTCB_IDOFF
#define STFTCB_IDON
#define STFTCB_CASET 0x2A
#define STFTCB_RASET 0x2B
#define STFTCB_RAMWR 0x2C
#define STFTCB_COLORSET
#define STFTCB_RAMRD 0x2E
#define STFTCB_PARAREA
#define STFTCB_VSD
#define STFTCB_TELOFF
#define STFTCB_TELON
#define STFTCB_RAMAC
#define STFTCB_VSSA
#define STFTCB_IMOFF
#define STFTCB_IMON
#define STFTCB_COLMODPFS
#define STFTCB_RAMWC
#define STFTCB_RAMRC
#define STFTCB_STEARSCAN
#define STFTCB_GSCAN
#define STFTCB_WDISBRIG
#define STFTCB_RDISBRIG
#define STFTCB_WCTRLDIS
#define STFTCB_RCTRLDIS
#define STFTCB_WCABC
#define STFTCB_RCABC
#define STFTCB_WCABCMB
#define STFTCB_RCABCMB
#define STFTCB_RID1
#define STFTCB_RID2
#define STFTCB_RID3
// Level 2
#define STFTCB_RGBISC
#define STFTCB_FRC1
#define STFTCB_FRC2
#define STFTCB_FRC3
#define STFTCB_DISINVC
#define STFTCB_BLANKPORCHC
#define STFTCB_DISFUNC
#define STFTCB_ENTRYMS
#define STFTCB_BC1
#define STFTCB_BC2
#define STFTCB_BC3
#define STFTCB_BC4
#define STFTCB_BC5
#define STFTCB_BC6
#define STFTCB_BC7
#define STFTCB_BC8
#define STFTCB_PC1
#define STFTCB_PC2
#define STFTCB_VCOMC1
#define STFTCB_VCOM2
#define STFTCB_NVMW
#define STFTCB_NVMPK
#define STFTCB_NVMSR
#define STFTCB_RID4
#define STFTCB_PGC
#define STFTCB_NGC
#define STFTCB_DGC1
#define STFTCB_DGC2
#define STFTCB_IC

//// Посчитанные заранее цвета в формате RGB565
#define STFTCB_COLOR_WHITE          0xFFFF
#define STFTCB_COLOR_BLACK          0x0000
#define STFTCB_COLOR_BLUE           0x001F
#define STFTCB_COLOR_BRED           0xF81F
#define STFTCB_COLOR_GRED 		    0xFFE0
#define STFTCB_COLOR_GBLUE		    0x07FF
#define STFTCB_COLOR_RED            0xF800
#define STFTCB_COLOR_MAGENTA        0xF81F
#define STFTCB_COLOR_GREEN          0x07E0
#define STFTCB_COLOR_CYAN           0x7FFF
#define STFTCB_COLOR_YELLOW         0xFFE0
#define STFTCB_COLOR_BROWN 		    0xBC40
#define STFTCB_COLOR_BRRED 		    0xFC07
#define STFTCB_COLOR_GRAY  		    0x8430
#define STFTCB_COLOR_GRAY0          0xEF7D
#define STFTCB_COLOR_GRAY1          0x8410
#define STFTCB_COLOR_GRAY2          0x4208
#define STFTCB_COLOR_DARKBLUE       0x01CF
#define STFTCB_COLOR_LIGHTBLUE      0x7D7C
#define STFTCB_COLOR_GRAYBLUE       0x5458
#define STFTCB_COLOR_LIGHTGREEN     0x841F
#define STFTCB_COLOR_LIGHTGRAY      0xEF5B
#define STFTCB_COLOR_LGRAY 	        0xC618
#define STFTCB_COLOR_LGRAYBLUE      0xA651

//// Интерфейс STFTCB
// SPI
/* Задача SPI интерфейса
 * */
#define STFTCB_SPI                  SPI1

/* Настройка тактирования
 * */
#define STFTCB_SPI_RCC              RCC->APB2ENR |= RCC_APB2ENR_SPI1EN 
#define STFTCB_SPI_DMA_RCC          RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN

/* Деление частоты SPI, от частоты шины. Baud Rate control, управление скоростью передачи.
 * 000: fPCLK/2
 * 001: fPCLK/4
 * 010: fPCLK/8
 * 011: fPCLK/16
 * 100: fPCLK/32
 * 101: fPCLK/64
 * 110: fPCLK/128
 * 111: fPCLK/256
 * Настаивать по SPI_CR1_BR_X
 * */
#define STFTCB_SPI_BR               ()

/* инициализация GPIO для SPI1 так как нам надо только отправлять данные в режиме Master, то надо \
 * инициализировать только две ножки, тактирование(SPI_SCK) и Master Out Slave In (SPI_MOSI).
 *  PA5 ---> SPI1_SCK
 *  PA6 ---> SPI1_MISO
 *  PA7 ---> SPI1_MOSI
 * */
#define STFTCB_SPI_GPIO_SCK_RCC     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN
#define STFTCB_SPI_GPIO_SCK_MODER   GPIOA->MODER |= GPIO_MODER_MODER5_1
#define STFTCB_SPI_GPIO_SCK_AFR 	GPIOA->AFR[0] |= (GPIO_AFRL_AFSEL5_2 | GPIO_AFRL_AFSEL5_0)

#define STFTCB_SPI_GPIO_MISO_RCC    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN
#define STFTCB_SPI_GPIO_MISO_MODER  GPIOA->MODER |= GPIO_MODER_MODER6_1
#define STFTCB_SPI_GPIO_MISO_AFR    GPIOA->AFR[0] |= (GPIO_AFRL_AFSEL6_2 | GPIO_AFRL_AFSEL6_0)

#define STFTCB_SPI_GPIO_MOSI_RCC    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN
#define STFTCB_SPI_GPIO_MOSI_MODER  GPIOA->MODER |= GPIO_MODER_MODER7_1
#define STFTCB_SPI_GPIO_MOSI_AFR 	GPIOA->AFR[0] |= (GPIO_AFRL_AFSEL7_2 | GPIO_AFRL_AFSEL7_0)

/* Поток DMA, для SPI1 выбран DMA2_Stream3
 * */
#define STFTCB_SPI_DMA_SxCR         DMA2_Stream3

/* Канал DMA
 * */
#define STFTCB_SPI_DMA_SxCR_CH      (0x03 << 25)

/* Прерывание
 * */
#define STFTCB_SPI_DMA_IRQN         DMA2_Stream3_IRQn

/* Прерывания по завершению передачи */
#define STFTCB_SPI_DMA_TCIF         (DMA2->LISR & (DMA_LISR_TCIF3))
#define STFTCB_SPI_DMA_CTCIF        DMA2->LIFCR |= DMA_LIFCR_CTCIF3

/* Прерывания на половине передачи */
#define STFTCB_SPI_DMA_HTIF         (DMA2->LISR & (DMA_LISR_HTIF3))
#define STFTCB_SPI_DMA_CHTIF        DMA2->LIFCR |= DMA_LIFCR_CHTIF3

/* Прерывания при ошибке передачи */
#define STFTCB_SPI_DMA_TEIF         (DMA2->LISR & (DMA_LISR_TEIF3))
#define STFTCB_SPI_DMA_CTEIF        DMA2->LIFCR |= (DMA_LIFCR_CTEIF3)

/* Прерывания при ошибке direct-режима(чтобы это не значило) */
#define STFTCB_SPI_DMA_DMEIF        (DMA2->LISR & (DMA_LISR_DMEIF3))
#define STFTCB_SPI_DMA_CDMEIF       DMA2->LIFCR |= (DMA_LIFCR_CDMEIF3)

/* Прерывания при ошибке FIFO */
#define STFTCB_SPI_DMA_FEIF         (DMA2->LISR & (DMA_LISR_FEIF3))
#define STFTCB_SPI_DMA_CFEIF        DMA2->LIFCR |= (DMA_LIFCR_CFEIF3)

// RESET | RST | RES
/* Аппаратный сброс (сброс на низком уровне)
 *  B12 ---> RESET | RST | RES 
 * */
#define STFTCB_RESET_RCC            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN
#define STFTCB_RESET_MODER          GPIOB->MODER |= GPIO_MODER_MODER12_0
#define STFTCB_RESET_ON             GPIOB->ODR |= GPIO_ODR_OD12
#define STFTCB_RESET_OFF            GPIOB->ODR &= ~GPIO_ODR_OD12

// D/C | AO | RS
/* Выбор данных/команды. (некоторые ЖК-платы называют это постоянным током или D / C). При подаче высокого \
 * напряжения это означает отправку данных, при подаче низкого напряжения это означает отправку команды.
 *  B14 ---> D/C | AO | RS
 * */
#define STFTCB_DC_RCC               RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN
#define STFTCB_DC_MODER             GPIOB->MODER |= GPIO_MODER_MODER14_0
#define	STFTCB_DC_ON	            GPIOB->ODR |= GPIO_ODR_OD14
#define	STFTCB_DC_OFF               GPIOB->ODR &= ~GPIO_ODR_OD14

// SPI_SS(CS)
/* Выбор микросхемы (некоторые ЖК-дисплеи называют это SS)
 *  B15 ---> SPI_SS(CS)
 * */
#define STFTCB_CS_RCC               RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN
#define STFTCB_CS_MODER             GPIOB->MODER |= GPIO_MODER_MODER15_0
#define	STFTCB_CS_ON	            GPIOB->ODR |= GPIO_ODR_OD15
#define	STFTCB_CS_OFF	            GPIOB->ODR &= ~GPIO_ODR_OD15

//// Текст
/* Возможны случаи когда нет надобности в том, чтобы выводить текст, для этого закомментировать строчку ниже
 * */
#define STFTCB_TEXT

/* Регистры для работы с текстом
 * */
#ifdef STFTCB_TEXT
#define STFTCB_TEXT_COLOR           0xFFFF
#define STFTCB_TEXT_ORIENTATION     0x01  // 0x00 горизонтальный | 0x01 вертикальный
#define STFTCB_TEXT_FLIP_HORIZONTAL 0x00  // 0x00 к VCC | 0x01 к LED
#define STFTCB_TEXT_FLIP_VERTICAL   0x01  // Отзеркаливание текста

#include "stftcb_font.h"
#endif  // STFTCB_TEXT

#include "./stftcb_spi.h"

#endif  // SERIAL_TFT_CONTROL_BUS_REGISTERS_H_
