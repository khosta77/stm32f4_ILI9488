#ifndef SERIAL_TFT_CONTROL_BUS_REGISTERS_H_
#define SERIAL_TFT_CONTROL_BUS_REGISTERS_H_

#include "../system/include/cmsis/stm32f4xx.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <math.h>
#include <string.h>

//// Выбор модели дисплея
/* Выбрать модель контроллера и выставить 1 на нем, в противном случае 0
 * */
#define ST7735S__080x160            (0)  // 0.96 // 0x01  // Отсутствует
#define ST7789V__240x240            (0)  // 1.3  // 0x02  // Использует другой интерфейс
#define ST7735___128x160            (0)  // 1.8  // 0x03
#define ST7789V3_240x280            (0)  // 1.69 // 0x04  // Не распаяна
#define ILI9341__240x320            (0)  // 2.2  // 0x05
#define ST7789___240x320            (0)  // 2.4  // 0x06
#define ILI9488__320x480            (1)  // 3.5  // 0x07

/* STFTCB_DISPLAY_MODEL - Модель дисплея из списка выше ^
 * STFTCB_ILIST_DEVICE - 0x01 - ILI; 0x00 ST
 * */
#if   ST7735S__080x160
  #define STFTCB_HEIGHT             160   // Y
  #define STFTCB_WIDTH              80    // X
  #define STFTCB_COLOR_MODE         2
  #define STFTCB_DISPLAY_MODEL      0x01
  #define STFTCB_ILIST_DEVICE       0x00
#elif ST7789V__240x240
  #define STFTCB_HEIGHT             240   // Y
  #define STFTCB_WIDTH              240   // X
  #define STFTCB_COLOR_MODE         2
  #define STFTCB_DISPLAY_MODEL      0x02
  #define STFTCB_ILIST_DEVICE       0x00
#elif ST7735___128x160
  #define STFTCB_HEIGHT             160   // Y
  #define STFTCB_WIDTH              128   // X
  #define STFTCB_COLOR_MODE         2
  #define STFTCB_DISPLAY_MODEL      0x03
  #define STFTCB_ILIST_DEVICE       0x00
#elif ST7789V3_240x280
  #define STFTCB_HEIGHT             280   // Y
  #define STFTCB_WIDTH              240   // X
  #define STFTCB_COLOR_MODE         2
  #define STFTCB_DISPLAY_MODEL      0x04
  #define STFTCB_ILIST_DEVICE       0x00
#elif ILI9341__240x320
  #define STFTCB_HEIGHT             320   // Y
  #define STFTCB_WIDTH              240   // X
  #define STFTCB_COLOR_MODE         2
  #define STFTCB_DISPLAY_MODEL      0x05
  #define STFTCB_ILIST_DEVICE       0x01
#elif ST7789___240x320
  #define STFTCB_HEIGHT             320   // Y
  #define STFTCB_WIDTH              240   // X
  #define STFTCB_COLOR_MODE         2
  #define STFTCB_DISPLAY_MODEL      0x06
  #define STFTCB_ILIST_DEVICE       0x00
#elif ILI9488__320x480
  #define STFTCB_HEIGHT             480   // Y
  #define STFTCB_WIDTH              320   // X
  #define STFTCB_COLOR_MODE         3
  #define STFTCB_DISPLAY_MODEL      0x07
  #define STFTCB_ILIST_DEVICE       0x01
#endif

// Общий размер массива
#define STFTCB_SIZE                 (STFTCB_HEIGHT * STFTCB_WIDTH)

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
#define STFTCB_POINT(arr, y, x)     (arr[((y * STFTCB_WIDTH) + x)])
#define STFTCB_DELAY(time)          for (uint32_t t = 0; t < time; t++)

//// Макросы для работы с дисплеем
// Level 1
#define STFTCB_NOP                  0x00  // NOP
#define STFTCB_SOFTRES              0x01  // Software Reset
#define STFTCB_RDII                 0x04  // Read display identification information
#define STFTCB_RDS                  0x09  // Read Display Status
#define STFTCB_RDPW                 0x0A  // Read Display Power Mode
#define STFTCB_RDMADCTL             0x0B  // Read Display MADCTL
#define STFTCB_RDPF                 0x0C  // Read Display Pixel Format
#define STFTCB_RDIF                 0x0D  // Read Display Image Format
#define STFTCB_RDSM                 0x0E  // Read Display Signal Mode
#define STFTCB_RDSDR                0x0F  // Read Display Self-Diagnostic Result
#define STFTCB_SLPIN                0x10  // Enter Sleep Mode
#define STFTCB_SLPOUT               0x11  // Sleep Out
#define STFTCB_PMO                  0x12  // Partial Mode ON
#define STFTCB_NDMO                 0x13  // Normal Display Mode ON
#define STFTCB_DIOFF                0x20  // Display Inversion OFF
#define STFTCB_DION                 0x21  // Display Inversion ON
#define STFTCB_GAMMS                0x26  // Gamma Set
#define STFTCB_DISPOFF              0x28  // Display OFF
#define STFTCB_DISPON               0x29  // Display ON
#define STFTCB_CASET                0x2A  // Column Address Set
#define STFTCB_RASET                0x2B  // Page Address Set
#define STFTCB_RAMWR                0x2C  // Memory Write
#define STFTCB_COLORSET             0x2D  // Color Set
#define STFTCB_RAMRD                0x2E  // Memory Read 
#define STFTCB_PARAREA              0x30  // Partial Area
#define STFTCB_VSD                  0x33  // Vertical Scrolling Definition
#define STFTCB_TELOFF               0x34  // Tearing Effect Line OFF
#define STFTCB_TELON                0x35  // Tearing Effect Line ON
#define STFTCB_RAMAC                0x36  // Memory Access Control
#define STFTCB_VSSA                 0x37  // Vertical Scrolling Start Address
#define STFTCB_IMOFF                0x38  // Idle Mode OFF
#define STFTCB_IMON                 0x39  // Idle Mode ON
#define STFTCB_COLMODPFS            0x3A  // COLMOD: Pixel Format Set 
#define STFTCB_RAMWC                0x3C  // Write_Memory_Continue
#define STFTCB_RAMRC                0x3E  // Read_Memory_Continue
#define STFTCB_STEARSCAN            0x44  // Set_Tear_Scanline
#define STFTCB_GSCAN                0x45  // Get_Scanline
#define STFTCB_WDISBRIG             0x51  // Write Display Brightness
#define STFTCB_RDISBRIG             0x52  // Read Display Brightness
#define STFTCB_WCTRLDIS             0x53  // Write CTRL Display
#define STFTCB_RCTRLDIS             0x54  // Read CTRL Display
#define STFTCB_WCABC                0x55  // Write Content Adaptive Brightness Control 
#define STFTCB_RCABC                0x56  // Read Content Adaptive Brightness Control 
#define STFTCB_WCABCMB              0x5E  // Write CABC Minimum Brightness
#define STFTCB_RCABCMB              0x5F  // Read CABC Minimum Brightness
#define STFTCB_RID1                 0xDA  // Read ID1 
#define STFTCB_RID2                 0xDB  // Read ID2 
#define STFTCB_RID3                 0xDC  // ReadID3

// Level 2
#define STFTCB_RGBISC               0xB0  // RGB Interface Signal Control 
#define STFTCB_FRC1                 0xB1  // Frame Rate Control (In Normal Mode/Full Colors)
#define STFTCB_FRC2                 0xB2  // Frame Rate Control (In Idle Mode/8 colors)
#define STFTCB_FRC3                 0xB3  // Frame Rate control (In Partial Mode/Full Colors)
#define STFTCB_DISINVC              0xB4  // Display Inversion Control 
#define STFTCB_BLANKPORCHC          0xB5  // Blanking Porch Control
#define STFTCB_DISFUNC              0xB6  // Display Function Control 
#define STFTCB_ENTRYMS              0xB7  // Entry Mode Set
#define STFTCB_BC1                  0xB8  // Backlight Control 1
#define STFTCB_BC2                  0xB9  // Backlight Control 2
#define STFTCB_BC3                  0xBA  // Backlight Control 3
#define STFTCB_BC4                  0xBB  // Backlight Control 4
#define STFTCB_BC5                  0xBC  // Backlight Control 5
#define STFTCB_BC7                  0xBE  // Backlight Control 7
#define STFTCB_BC8                  0xBF  // Backlight Control 8
#define STFTCB_PC1                  0xC0  // Power Control 1
#define STFTCB_PC2                  0xC1  // Power Control 2
#define STFTCB_VCOMC1               0xC5  // VCOM Control 1
#define STFTCB_VCOM2                0xC7  // VCOM Control 2
#define STFTCB_NVMW                 0xD0  // NV Memory Write
#define STFTCB_NVMPK                0xD1  // NV Memory Protection Key
#define STFTCB_NVMSR                0xD2  // NV Memory Status Read
#define STFTCB_RID4                 0xD3  // Read ID4
#define STFTCB_PGC                  0xE0  // Positive Gamma Correction
#define STFTCB_NGC                  0xE1  // Negative Gamma Correction
#define STFTCB_DGC1                 0xE2  // Digital Gamma Control 1
#define STFTCB_DGC2                 0xE3  // Digital Gamma Control 2
#define STFTCB_IC                   0xF6  // Interface Control

//// Посчитанные заранее цвета в формате RGB565
#define STFTCB_COLOR_WHITE          0xFFFF
#define STFTCB_COLOR_BLACK          0x0000
#define STFTCB_COLOR_BLUE           0x001F
#define STFTCB_COLOR_BRED           0xF81F
#define STFTCB_COLOR_GRED           0xFFE0
#define STFTCB_COLOR_GBLUE          0x07FF
#define STFTCB_COLOR_RED            0xF800
#define STFTCB_COLOR_MAGENTA        0xF81F
#define STFTCB_COLOR_GREEN          0x07E0
#define STFTCB_COLOR_CYAN           0x7FFF
#define STFTCB_COLOR_YELLOW         0xFFE0
#define STFTCB_COLOR_BROWN          0xBC40
#define STFTCB_COLOR_BRRED          0xFC07
#define STFTCB_COLOR_GRAY           0x8430
#define STFTCB_COLOR_GRAY0          0xEF7D
#define STFTCB_COLOR_GRAY1          0x8410
#define STFTCB_COLOR_GRAY2          0x4208
#define STFTCB_COLOR_DARKBLUE       0x01CF
#define STFTCB_COLOR_LIGHTBLUE      0x7D7C
#define STFTCB_COLOR_GRAYBLUE       0x5458
#define STFTCB_COLOR_LIGHTGREEN     0x841F
#define STFTCB_COLOR_LIGHTGRAY      0xEF5B
#define STFTCB_COLOR_LGRAY          0xC618
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
#define STFTCB_SPI_BR               (0)

/* инициализация GPIO для SPI1 так как нам надо только отправлять данные в режиме Master, то надо \
 * инициализировать только две ножки, тактирование(SPI_SCK) и Master Out Slave In (SPI_MOSI).
 *  PA5 ---> SPI1_SCK
 *  PA6 ---> SPI1_MISO
 *  PA7 ---> SPI1_MOSI
 * */
#define STFTCB_SPI_GPIO_SCK_RCC     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN
#define STFTCB_SPI_GPIO_SCK_MODER   GPIOA->MODER |= GPIO_MODER_MODER5_1
#define STFTCB_SPI_GPIO_SCK_PUPDR   GPIOA->PUPDR |= GPIO_PUPDR_PUPD5_1
#define STFTCB_SPI_GPIO_SCK_OSPDR   GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_1;
#define STFTCB_SPI_GPIO_SCK_AFR     GPIOA->AFR[0] |= (GPIO_AFRL_AFSEL5_2 | GPIO_AFRL_AFSEL5_0)

#define STFTCB_SPI_GPIO_MISO_RCC    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN
#define STFTCB_SPI_GPIO_MISO_MODER  GPIOA->MODER |= GPIO_MODER_MODER6_1
#define STFTCB_SPI_GPIO_MISO_PUPDR  GPIOA->PUPDR |= GPIO_PUPDR_PUPD6_1
#define STFTCB_SPI_GPIO_MISO_OSPDR  GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;
#define STFTCB_SPI_GPIO_MISO_AFR    GPIOA->AFR[0] |= (GPIO_AFRL_AFSEL6_2 | GPIO_AFRL_AFSEL6_0)

#define STFTCB_SPI_GPIO_MOSI_RCC    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN
#define STFTCB_SPI_GPIO_MOSI_MODER  GPIOA->MODER |= GPIO_MODER_MODER7_1
#define STFTCB_SPI_GPIO_MOSI_PUPDR  GPIOA->PUPDR |= GPIO_PUPDR_PUPD7_1
#define STFTCB_SPI_GPIO_MOSI_OSPDR  GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_1;
#define STFTCB_SPI_GPIO_MOSI_AFR    GPIOA->AFR[0] |= (GPIO_AFRL_AFSEL7_2 | GPIO_AFRL_AFSEL7_0)

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
#define STFTCB_RESET_RCC            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN
#define STFTCB_RESET_MODER          GPIOC->MODER |= GPIO_MODER_MODER4_0
#define STFTCB_RESET_ON             GPIOC->ODR |= GPIO_ODR_OD4
#define STFTCB_RESET_OFF            GPIOC->ODR &= ~GPIO_ODR_OD4

// D/C | AO | RS
/* Выбор данных/команды. (некоторые ЖК-платы называют это постоянным током или D / C). При подаче высокого \
 * напряжения это означает отправку данных, при подаче низкого напряжения это означает отправку команды.
 *  B14 ---> D/C | AO | RS
 * */
#define STFTCB_DC_RCC               RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN
#define STFTCB_DC_MODER             GPIOB->MODER |= GPIO_MODER_MODER0_0
#define	STFTCB_DC_ON                GPIOB->ODR |= GPIO_ODR_OD0
#define	STFTCB_DC_OFF               GPIOB->ODR &= ~GPIO_ODR_OD0

// SPI_SS(CS)
/* Выбор микросхемы (некоторые ЖК-дисплеи называют это SS)
 *  B15 ---> SPI_SS(CS)
 * */
#define STFTCB_CS_RCC               RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN
#define STFTCB_CS_MODER             GPIOC->MODER |= GPIO_MODER_MODER5_0
#define	STFTCB_CS_ON                GPIOC->ODR |= GPIO_ODR_OD5
#define	STFTCB_CS_OFF               GPIOC->ODR &= ~GPIO_ODR_OD5

//// Текст
/* Возможны случаи когда нет надобности в том, чтобы выводить текст, для этого закомментировать строчку ниже
 * */
//#define STFTCB_TEXT

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
