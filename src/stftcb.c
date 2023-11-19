#include "stftcb.h"

uint8_t stftcb_array_tx_0[1024];
uint8_t stftcb_array_tx_1[1024];

uint8_t stftcb_array_tx_status;
uint8_t stftcb_array_tx_mxar;

uint16_t count_l = 0x0000;

const uint16_t STFTCB_ARRAY_SIZE = (3 * STFTCB_WIDTH);

static void STFTCB_GPIO_init();
static void STFTCB_memset0();
static void STFTCB_DMA_init();
static void STFTCB_TFT_init();

static void stftcb_setColAddress(uint16_t x0, uint16_t x1);
static void stftcb_setRawAddress(uint16_t y0, uint16_t y1);

static void stftcb_DrawLine0(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color,
                             const int16_t deltaX, const int16_t deltaY, const int16_t signX,
                             const int16_t signY, int16_t error, int16_t error2);
static void stftcb_DrawLine1(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color,
                             const int16_t deltaX, const int16_t deltaY, const int16_t signX,
                             const int16_t signY, int16_t error, int16_t error2);

#ifndef STFTCB_TEXT
  static uint16_t get_symbol_id(char c);

  #if STFTCB_TEXT_ORIENTATION
    static void draw_symbol_v(uint16_t id, const uint16_t y, const uint16_t x);
  #else
    static void draw_symbol_h(uint16_t id, const uint16_t y, const uint16_t x);
  #endif

  #if STFTCB_TEXT_ORIENTATION
    static void draw_symbol_V(uint16_t id, const uint16_t y, const uint16_t x);
  #else
    static void draw_symbol_H(uint16_t id, const uint16_t y, const uint16_t x);
  #endif

  #if STFTCB_TEXT_FLIP_VERTICAL
    static void reverse(char* str);
  #endif
#endif

/*=========================================================================================================*/
/*                    Функции инициализации serial tft control bus                                         */
/*=========================================================================================================*/
/** @brief STFTCB_init - инициализация интерфейса serial tft control bus
 * */
void STFTCB_init() {
    stftcb_array_tx_status = 0x00;
    stftcb_array_tx_mxar = 0x00;
    SPI_init();
    STFTCB_GPIO_init();

    STFTCB_memset0();
    STFTCB_DMA_init();
    STFTCB_TFT_init();

}

/** @brief STFTCB_GPIO_init - инициализация GPIO для различных команд
 * */
static void STFTCB_GPIO_init() {
    STFTCB_RESET_RCC;
    STFTCB_RESET_MODER;

    STFTCB_DC_RCC;
    STFTCB_DC_MODER;

    STFTCB_CS_RCC;
    STFTCB_CS_MODER;
}

/** @brief STFTCB_memset_0 - обнуление массива
 * */
static void STFTCB_memset0() {  // это приводило к ошибке памяти.
    //memset(&stftcb_array_tx_0[0], 0x00, (STFTCB_SIZE * sizeof(uint8_t)));
    //memset(&stftcb_array_tx_1[0], 0x00, (STFTCB_SIZE * sizeof(uint8_t)));
}

static void STFTCB_DMA_init() {
    STFTCB_SPI_DMA_SxCR->M0AR = (uint32_t)&stftcb_array_tx_0[0];
    STFTCB_SPI_DMA_SxCR->M1AR = (uint32_t)&stftcb_array_tx_1[0];
    STFTCB_SPI_DMA_SxCR->NDTR = STFTCB_ARRAY_SIZE;
}

static void STFTCB_TFT_init() {
    STFTCB_CS_OFF;
    STFTCB_RESET_OFF;
    STFTCB_DELAY(7);
    STFTCB_RESET_ON;

#if 1
    stftcb_sendCmd1byte(STFTCB_SOFTRES);    //  0: Software reset
    STFTCB_DELAY(150000);
    
#if 1  // ILI9488
    //stftcb_sendCmd1byte(STFTCB_DION);
#if 0
    stftcb_sendCmd1byte(0xE0);
	stftcb_sendData1byte(0x00);
	stftcb_sendData1byte(0x03);
	stftcb_sendData1byte(0x09);
	stftcb_sendData1byte(0x08);
	stftcb_sendData1byte(0x16);
	stftcb_sendData1byte(0x0A);
	stftcb_sendData1byte(0x3F);
	stftcb_sendData1byte(0x78);
	stftcb_sendData1byte(0x4C);
	stftcb_sendData1byte(0x09);
	stftcb_sendData1byte(0x0A);
	stftcb_sendData1byte(0x08);
	stftcb_sendData1byte(0x16);
	stftcb_sendData1byte(0x1A);
	stftcb_sendData1byte(0x0F);

	stftcb_sendCmd1byte(0XE1);
	stftcb_sendData1byte(0x00);
	stftcb_sendData1byte(0x16);
	stftcb_sendData1byte(0x19);
	stftcb_sendData1byte(0x03);
	stftcb_sendData1byte(0x0F);
	stftcb_sendData1byte(0x05);
	stftcb_sendData1byte(0x32);
	stftcb_sendData1byte(0x45);
	stftcb_sendData1byte(0x46);
	stftcb_sendData1byte(0x04);
	stftcb_sendData1byte(0x0E);
	stftcb_sendData1byte(0x0D);
	stftcb_sendData1byte(0x35);
	stftcb_sendData1byte(0x37);
	stftcb_sendData1byte(0x0F);
#endif
#if 0
	stftcb_sendCmd1byte(0XC0); //Power Control 1
	stftcb_sendData1byte(0x17); //Vreg1out
	stftcb_sendData1byte(0x15); //Verg2out

	stftcb_sendCmd1byte(0xC1); //Power Control 2
	stftcb_sendData1byte(0x41); //VGH,VGL

	stftcb_sendCmd1byte(0xC5); //Power Control 3
	stftcb_sendData1byte(0x00);
	stftcb_sendData1byte(0x12); //Vcom
	stftcb_sendData1byte(0x80);

	stftcb_sendCmd1byte(0x36); //Memory Access
	stftcb_sendData1byte(0x48);
#endif
	stftcb_sendCmd1byte(0x3A); // Interface Pixel Format
	stftcb_sendData1byte(0x66); //18 bit
#if 0
	stftcb_sendCmd1byte(0XB0); // Interface Mode Control ПМРППРРТПОРО
	stftcb_sendData1byte(0x80); //SDO NOT USE

    stftcb_sendCmd1byte(0xB1); //Frame rate
	stftcb_sendData1byte(0xA0); //60Hz

	stftcb_sendCmd1byte(0xB4); //Display Inversion Control
	stftcb_sendData1byte(0x02); //2-dot

	stftcb_sendCmd1byte(0XB6); //Display Function Control  RGB/MCU Interface Control

	stftcb_sendCmd1byte(0x02); //MCU
	stftcb_sendData1byte(0x02); //Source,Gate scan dieection

	stftcb_sendCmd1byte(0XE9); // Set Image Functio
	stftcb_sendData1byte(0x00); // Disable 24 bit data

	stftcb_sendCmd1byte(0xF7); // Adjust Control
	stftcb_sendData1byte(0xA9);
	stftcb_sendData1byte(0x51);
	stftcb_sendData1byte(0x2C);
	stftcb_sendData1byte(0x82); // D7 stream, loose
#endif
#endif
    stftcb_sendCmd1byte(STFTCB_SLPOUT);     //  1: Out of sleep mode
    STFTCB_DELAY(500);
    stftcb_sendCmd1byte(STFTCB_DISPON);
    STFTCB_DELAY(100);
//    stftcb_sendCmd1byte(STFTCB_COLMODPFS);  //  2: set color mode
//    stftcb_sendData1byte(0x55);             //     16-bit color
//    stftcb_sendCmd1byte(0xE9); // Set Image Functio
//	stftcb_sendData1byte(0x00); // Disable 24 bit data
#endif
   // stftcb_updateFrame();
}

/*=========================================================================================================*/
/*                              Функции отправки данных на дисплей                                         */
/*=========================================================================================================*/
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

void stftcb_sendCmd(uint8_t address, uint8_t *data, uint16_t size) {
    stftcb_sendCmd1byte(address);
    for (uint16_t i = 0; i < size; ++i)
        stftcb_sendData1byte(data[i]);
}
/*=========================================================================================================*/
/*                      Функции объявления области выделения кадра                                         */
/*=========================================================================================================*/
static void stftcb_setColAddress(uint16_t x0, uint16_t x1) {
    uint8_t data_column[4] = { (uint8_t)((x0 >> 8) & 0xFF), (uint8_t)(x0 & 0xFF),
                               (uint8_t)((x1 >> 8) & 0xFF), (uint8_t)(x1 & 0xFF)};

    stftcb_sendCmd1byte(STFTCB_RAMAC);
    stftcb_sendCmd(STFTCB_CASET, &data_column[0], 4);
}

static void stftcb_setRawAddress(uint16_t y0, uint16_t y1) {
    uint8_t data_row[4] = { (uint8_t)(y0 >> 8), (uint8_t)(y0 & 0xFF),
                            (uint8_t)(y1 >> 8), (uint8_t)(y1 & 0xFF)};
    stftcb_sendCmd(STFTCB_RASET, &data_row[0], 4);
    stftcb_sendCmd1byte(STFTCB_RAMWR);
}

void stftcb_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    SPI_1byte_mode_on();
    stftcb_setColAddress(x0, x1);
    stftcb_setRawAddress(y0, y1);
}

void stftcb_SetFullAddressWindow() {
    stftcb_SetAddressWindow(0, 0, (STFTCB_WIDTH - 1), (STFTCB_HEIGHT - 1));
}
/*=========================================================================================================*/
/*                              Функция обновления кадра                                                   */
/*=========================================================================================================*/
/** @brief stftcb_updateFrame - функция обновления кадра
 * */
void stftcb_updateFrame() {
    while (stftcb_array_tx_status != 0x00) {;}  // Ждем пока предыдущая передача не закончится
    stftcb_SetAddressWindow(0, count_l, STFTCB_WIDTH, count_l);
    ++count_l;
    //if (count_l == STFTCB_HEIGHT)
      //  count_l = 0;
    //stftcb_SetFullAddressWindow();

    SPI_1byte_mode_on();
    STFTCB_DC_ON;
    STFTCB_SPI_DMA_SxCR->CR &= ~DMA_SxCR_EN;
    while ((STFTCB_SPI_DMA_SxCR->CR) & DMA_SxCR_EN){;}

    if (stftcb_array_tx_mxar == 0) {
        STFTCB_SPI_DMA_SxCR->CR &= ~DMA_SxCR_CT;
        stftcb_array_tx_mxar = 0x01;
    } else {
        STFTCB_SPI_DMA_SxCR->CR |= DMA_SxCR_CT;
        stftcb_array_tx_mxar = 0x00;
    }

    stftcb_array_tx_status = 0x11;
    STFTCB_SPI_DMA_SxCR->NDTR = STFTCB_ARRAY_SIZE;
    STFTCB_SPI_DMA_SxCR->CR |= DMA_SxCR_MINC;
    STFTCB_SPI_DMA_SxCR->CR |= DMA_SxCR_EN;
}

/*=========================================================================================================*/
/*                              Функции отрисовки объектов в кадре                                         */
/*=========================================================================================================*/
static void stftcb_fullpoint8_0(const uint16_t i, const uint8_t r, const uint8_t g, const uint8_t b) {
    stftcb_array_tx_0[i]       = r;
    stftcb_array_tx_0[(i + 1)] = g;
    stftcb_array_tx_0[(i + 2)] = b;
}

static void stftcb_fullpoint8_1(const uint16_t i, const uint8_t r, const uint8_t g, const uint8_t b) {
    stftcb_array_tx_1[i]       = r;
    stftcb_array_tx_1[(i + 1)] = g;
    stftcb_array_tx_1[(i + 2)] = b;
}

static void stftcb_fullpoint8(const uint16_t i, const uint8_t r, const uint8_t g, const uint8_t b) {
    if (stftcb_array_tx_mxar == 0)
        stftcb_fullpoint8_0(i, r, g, b);
    else
        stftcb_fullpoint8_1(i, r, g, b);
}

void stftcb_FillBackground(uint16_t color) {
    const uint8_t rgb[3] = { (uint8_t)(((color & 0xF800) >> 11) << 3), 
                             (uint8_t)(((color & 0x07E0) >> 5) << 2), (uint8_t)((color & 0x001F) << 3)};
    count_l = 0;

    for (uint16_t i = 0; i < STFTCB_HEIGHT; ++i) {
        for (uint16_t j = 0; j < STFTCB_ARRAY_SIZE; j += 3)
            stftcb_fullpoint8(j, rgb[0], rgb[1], rgb[2]);
        //for (uint32_t t = 0; t < 0xFFF; t++);
        stftcb_updateFrame();
        ++count_l;
    }
}

#ifdef STFTCB_TEXT
/*=========================================================================================================*/
/*                                              Шрифты                                                     */
/*=========================================================================================================*/
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
#endif

/* Код ниже я бы хотел временно где-нибудь сохранить
 * */
#if 0
#define ST7735_MADCTL_MY  0x80
#define ST7735_MADCTL_MX  0x40
#define ST7735_MADCTL_MV  0x20
#define ST7735_MADCTL_ML  0x10
#define ST7735_MADCTL_RGB 0x00
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH  0x04


#define ST7735_IS_160X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 160
#define ST7735_XSTART 0
#define ST7735_YSTART 0
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MY)

#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13

#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E

#define ST7735_PTLAR   0x30
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD

#define ST7735_PWCTR6  0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// Color definitions
#define	ST7735_BLACK   0x0000
#define	ST7735_BLUE    0x001F
#define	ST7735_RED     0xF800
#define	ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW  0xFFE0
#define ST7735_WHITE   0xFFFF
#define ST7735_ORANGE  0xFD60
#define ST7735_LIGHTGREEN 0x07EF
#define ST7735_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

#define BGCOLOR     	ST7735_BLACK
#define AXISCOLOR   	ST7735_ORANGE
#define LIGHTCOLOR    ST7735_LIGHTGREEN

static void ST7735_Init_Command1();
static void ST7735_Init_Command2();
static void ST7735_Init_Command3();

static void ST7735_Init() {
    STFTCB_CS_OFF;
    STFTCB_RESET_OFF;
    STFTCB_DELAY(7);
    STFTCB_RESET_ON;

#if 1
    stftcb_sendCmd1byte(STFTCB_SOFTRES);    //  1: Software reset
    STFTCB_DELAY(150000);
    //STFTCB_DELAY(120);
    stftcb_sendCmd1byte(STFTCB_SLPOUT);     //  2: Out of sleep mode
    STFTCB_DELAY(500);
    stftcb_sendCmd1byte(STFTCB_DISPON);
    STFTCB_DELAY(100);
    stftcb_sendCmd1byte(STFTCB_COLMODPFS);     // 15: set color mode
    stftcb_sendData1byte(0x55);             //     16-bit color
#endif
    //STFTCB_CS_ON;
    stftcb_updateFrame();
}

//%s/stftcb_sendCmd1byte(/stftcb_sendCmd1byte(/g
//%s/stftcb_sendData1byte(/stftcb_sendData1byte(/g

static void ST7735_Init_Command1() {
#if 1
    stftcb_sendCmd1byte(ST7735_SWRESET);    //  1: Software reset
    STFTCB_DELAY(150);
#endif
#if 1
    stftcb_sendCmd1byte(ST7735_SLPOUT);     //  2: Out of sleep mode
    STFTCB_DELAY(500);
#endif
#if 0
#if 1
    stftcb_sendCmd1byte(ST7735_FRMCTR1);    //  3: Frame rate ctrl - normal mode
    stftcb_sendData1byte(0x01);             //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    stftcb_sendData1byte(0x2C);
    stftcb_sendData1byte(0x2D);
#endif
#if 1
    stftcb_sendCmd1byte(ST7735_FRMCTR2);    //  4: Frame rate control - idle mode
    stftcb_sendData1byte(0x01);             //  Rate = fosc/(1x2+40) * (LINE+2C+2D)
    stftcb_sendData1byte(0x2C);
    stftcb_sendData1byte(0x2D);
#endif
#if 1
    stftcb_sendCmd1byte(ST7735_FRMCTR3);    //  5: Frame rate ctrl - partial mode
    stftcb_sendData1byte(0x01);             //     Dot inversion mode
    stftcb_sendData1byte(0x2C);
    stftcb_sendData1byte(0x2D);
    stftcb_sendData1byte(0x01);             //     Line inversion mode
    stftcb_sendData1byte(0x2C);
    stftcb_sendData1byte(0x2D);
#endif
#endif
#if 0
    stftcb_sendCmd1byte(ST7735_INVCTR);     //  6: Display inversion ctrl
    stftcb_sendData1byte(0x07);             //     No inversion
#endif
#if 0
#if 1
    stftcb_sendCmd1byte(ST7735_PWCTR1);     //  7: Power control
    stftcb_sendData1byte(0xA2);
    stftcb_sendData1byte(0x02);             //     -4.6V
    stftcb_sendData1byte(0x84);             //     AUTO mode
#endif
#if 1
    stftcb_sendCmd1byte(ST7735_PWCTR2);     //  8: Power control
    stftcb_sendData1byte(0xC5);             //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
#endif
#if 1
    stftcb_sendCmd1byte(ST7735_PWCTR3);     //  9: Power control
    stftcb_sendData1byte(0x0A);             //     Opamp current small
    stftcb_sendData1byte(0x00);             //     Boost frequency
#endif
#if 1
    stftcb_sendCmd1byte(ST7735_PWCTR4);     // 10: Power control
    stftcb_sendData1byte(0x8A);             //     BCLK/2, Opamp current small & Medium low
    stftcb_sendData1byte(0x2A);
#endif
#if 1
    stftcb_sendCmd1byte(ST7735_PWCTR5);     // 11: Power control
    stftcb_sendData1byte(0x8A);
    stftcb_sendData1byte(0xEE);
#endif
#if 1
    stftcb_sendCmd1byte(ST7735_VMCTR1);     // 12: Power control
    stftcb_sendData1byte(0x0E);
#endif
#endif
//    stftcb_sendCmd1byte(ST7735_INVOFF);     // 13: Don't invert display
//    stftcb_sendCmd1byte(ST7735_MADCTL);     // 14: Memory access control (directions)
//    stftcb_sendData1byte(ST7735_ROTATION);  //     row addr/col addr, bottom to top refresh
    stftcb_sendCmd1byte(ST7735_COLMOD);     // 15: set color mode
    stftcb_sendData1byte(0x05);             //     16-bit color
}

static void ST7735_Init_Command2(void) {
    stftcb_sendCmd1byte(ST7735_CASET);  //  1: Column addr set
    stftcb_sendData1byte(0x00);         //     XSTART = 0
    stftcb_sendData1byte(0x00);
    stftcb_sendData1byte(0x00);         //     XEND = 127
    stftcb_sendData1byte(0x7F);
    stftcb_sendCmd1byte(ST7735_RASET);  //  2: Row addr set
    stftcb_sendData1byte(0x00);         //     XSTART = 0
    stftcb_sendData1byte(0x00);
    stftcb_sendData1byte(0x00);         //     XEND = 127
    stftcb_sendData1byte(0x7F);
}

static void ST7735_Init_Command3(void) {
#if 0
#if 1
    stftcb_sendCmd1byte(ST7735_GMCTRP1);  //  1: Magical unicorn dust
    stftcb_sendData1byte(0x02);
    stftcb_sendData1byte(0x1C);
    stftcb_sendData1byte(0x07);
    stftcb_sendData1byte(0x12);
    stftcb_sendData1byte(0x37);
    stftcb_sendData1byte(0x32);
    stftcb_sendData1byte(0x29);
    stftcb_sendData1byte(0x2D);
    stftcb_sendData1byte(0x29);
    stftcb_sendData1byte(0x25);
    stftcb_sendData1byte(0x2B);
    stftcb_sendData1byte(0x39);
    stftcb_sendData1byte(0x00);
    stftcb_sendData1byte(0x01);
    stftcb_sendData1byte(0x03);
    stftcb_sendData1byte(0x10);
#endif
#if 1
    stftcb_sendCmd1byte(ST7735_GMCTRN1);  //  2: Sparkles and rainbows
    stftcb_sendData1byte(0x03);
    stftcb_sendData1byte(0x1D);
    stftcb_sendData1byte(0x07);
    stftcb_sendData1byte(0x06);
    stftcb_sendData1byte(0x2E);
    stftcb_sendData1byte(0x2C);
    stftcb_sendData1byte(0x29);
    stftcb_sendData1byte(0x2D);
    stftcb_sendData1byte(0x2E);
    stftcb_sendData1byte(0x2E);
    stftcb_sendData1byte(0x37);
    stftcb_sendData1byte(0x3F);
    stftcb_sendData1byte(0x00);
    stftcb_sendData1byte(0x00);
    stftcb_sendData1byte(0x02);
    stftcb_sendData1byte(0x10);
#endif
#endif
//    stftcb_sendCmd1byte(ST7735_NORON);
//    STFTCB_DELAY(10);
    stftcb_sendCmd1byte(ST7735_DISPON);
    STFTCB_DELAY(100);
}
#endif


