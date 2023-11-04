#include "stftcb.h"

uint16_t stftcb_array_tx_0[STFTCB_SIZE];
uint16_t stftcb_array_tx_1[STFTCB_SIZE];

uint8_t stftcb_array_tx_status;
uint8_t stftcb_array_tx_mxar;

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

#define STP_FLASH_WHILE_BSY()       { while (FLASH->SR & FLASH_SR_BSY){} }
#define START_ADDRESS   0x0800C000 	//	(FLASH_BASE + 48*1024)
#define BASE_ADDRESS    0x08010000
#define ADDRESS_MX0R    ((uint32_t)0x08020000)// + (uint32_t)STFTCB_SIZE)
#define ADDRESS_MX1R    ((uint32_t)0x08040000)// + (uint32_t)STFTCB_SIZE)// + (uint32_t)(2 * STFTCB_SIZE))

void stp_flash_init() {
	//// Конфигурация FLASH
	// 1. Очистка флагов
    FLASH->ACR = 0;
	
    // 2. Установка задержки (5 секунд)
	FLASH->ACR |= FLASH_ACR_LATENCY_5WS;  // (5 <<  0);
	
    // 3. Включаем кэш команд
    FLASH->ACR |= FLASH_ACR_ICEN;  //(1 <<  9);
	
    // 4. Включаем кэш данных
    FLASH->ACR |= FLASH_ACR_DCEN;  //(1 << 10);
	
    // 5. PLL Выбран в качестве системных часов \
    // если не работает, убрать макрос.
    //RCC->CFGR |= RCC_CFGR_SW_0;  //(2 <<  0);
	
    // 6. Ждем пока PLL включится
	for (uint8_t i = 0; i < 15; i++);
    //while ((RCC->CFGR & 0x0F) != 0x0A);
}

void stp_flash_unlock() {
    //// Разблокировка памяти
    if (FLASH->CR & FLASH_CR_LOCK) {
        FLASH->KEYR = 0x45670123;
        FLASH->KEYR = 0xCDEF89AB;
    }
}

void stp_flash_lock() {
    //// Блокировка памяти
    FLASH->CR |= FLASH_CR_LOCK;
}

static void stp_flash_write(uint32_t address, uint8_t data) {
    //// Запись данных в одну клетку
    // 1. Разрешаем программирование
    FLASH->CR |= FLASH_CR_PG;

    // 2. Записываем в ячейку данных один байт
    *(uint8_t *)address = data;

    // 3. Ждем пока запись завершится
    STP_FLASH_WHILE_BSY();
    
    // 4. Запрещаем программирование
    FLASH->CR &= ~FLASH_CR_PG;
}

static void stp_flash_write_buffer(uint32_t address, const uint8_t * dataBuffer, uint32_t size) {
    //// Запись данных в одну ячейку
	// 1. Разблокируем память для записи данных
    stp_flash_unlock();
    
    // 2. Подождем пока произойдет разблокировка
    STP_FLASH_WHILE_BSY();

    // 3. Цикл записи
    while (size >= sizeof(uint8_t)) {
    	stp_flash_write(address, *(const uint8_t *)dataBuffer);
        address += sizeof(uint8_t);
        dataBuffer += sizeof(uint8_t);
        size -= sizeof(uint8_t);
    }

    // 4. Заблокируем память. Признак хорошего тона
    stp_flash_lock();
}

// Запись данных во flash
void stp_flash_write_8(uint32_t address, const uint8_t *dataBuffer, uint32_t size) {
	stp_flash_write_buffer(address, dataBuffer, size);
}

void stp_flash_write_16(uint32_t address, const uint16_t *dataBuffer, uint32_t size) {
    uint8_t buffer[(sizeof(uint16_t) * size)];
    memcpy(buffer, dataBuffer, (sizeof(uint16_t) * size));
    stp_flash_write_buffer(address, buffer, (sizeof(uint16_t) * size));
}

void stp_flash_write_32(uint32_t address, const uint32_t *dataBuffer, uint32_t size) {
	uint8_t buffer[(sizeof(uint32_t) * size)];
	memcpy(buffer, dataBuffer, (sizeof(uint32_t) * size));
	stp_flash_write_buffer(address, buffer, (sizeof(uint32_t) * size));
}

void stp_flash_erase(uint32_t sector) {
    //// Очистка сектора
    // 1. Разблокировка памяти для работы с ней
	stp_flash_unlock();

    // 2. Ждем пока она разблокируется
	STP_FLASH_WHILE_BSY();

    // 3. Защита от дурака, если передали большое число
    sector = sector & 0x0F;

    // 4. Очистка сектора
    FLASH->CR |= FLASH_CR_SER;	// Sector Erase Flag
    FLASH->CR |= (sector << 3);	// Sector Number to SNB[3:0]
    FLASH->CR |= FLASH_CR_STRT;	// Sector Erase Start

    // 5. Ждем пока сектор очистится
    STP_FLASH_WHILE_BSY();

    // 6. Выключаем флаг работы с сектором
    FLASH->CR &= ~FLASH_CR_SER;

    // 7. Блокируем память
    stp_flash_lock();
}

uint32_t stp_flash_sector_size(uint32_t sector) {
    //// получить какой то адрес сектора, честно хз за чем эта функция (Legacy)
    if (sector >= 0 && sector <= 3) {
        return (16 * 1024);
    } else if (sector == 4) {
        return (64 * 1024);
    } else if (sector >= 5 && sector <= 11) {
        return (128 * 1024);
    }
    return 0;
}

static void stftcb_flash_draw_color(uint32_t address, const uint16_t color, uint32_t i) {
    // 3. Цикл записи
//    uint8_t clr[2] = {0xFF, 0xFF}; //{(uint8_t)((color >> 8) & 0xFF), (uint8_t)(color & 0xFF)};
//    address += (1 + (i * sizeof(uint8_t)));
//    stp_flash_write(address, clr[0]);
//    address += 1;
//    stp_flash_write(address, clr[1]);

}


void stp_flash_read_8(uint32_t address, uint8_t *buffer, uint32_t size) {
    memcpy(buffer, (uint8_t*) address, size);
}

void stp_flash_read_16(uint32_t address, uint16_t *buffer, uint32_t size) {
	uint8_t char_buffer[(sizeof(uint16_t) * size)];
	memcpy(char_buffer, (uint8_t*) address, (sizeof(uint16_t) * size));
	memcpy(buffer, char_buffer, (size * sizeof(uint16_t)));
}

void stp_flash_read_32(uint32_t address, uint32_t *buffer, uint32_t size) {
	uint8_t char_buffer[(sizeof(uint32_t) * size)];
	memcpy(char_buffer, (uint8_t*) address, (sizeof(uint32_t) * size));
	memcpy(buffer, char_buffer, (size * sizeof(uint32_t)));
}


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
    GPIOD->ODR |= GPIO_ODR_OD12;

    stp_flash_init();
    stp_flash_erase(5);
    stp_flash_erase(6);
    //stp_flash_unlock();
    //STP_FLASH_WHILE_BSY();
        GPIOD->ODR |= GPIO_ODR_OD13;

    //STFTCB_memset0();
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
static void STFTCB_memset0() {
    memset(&stftcb_array_tx_0[0], 0x0000, (STFTCB_SIZE * sizeof(uint16_t)));
    memset(&stftcb_array_tx_1[0], 0x0000, (STFTCB_SIZE * sizeof(uint16_t)));
}

static void STFTCB_DMA_init() {
    STFTCB_SPI_DMA_SxCR->M0AR = (uint32_t)&stftcb_array_tx_0[0];
    STFTCB_SPI_DMA_SxCR->M1AR = (uint32_t)&stftcb_array_tx_1[0];
    STFTCB_SPI_DMA_SxCR->NDTR = STFTCB_SIZE;
}

static void STFTCB_TFT_init() {
    STFTCB_CS_OFF;
    STFTCB_RESET_OFF;
    STFTCB_DELAY(7);
    STFTCB_RESET_ON;

#if 1
    stftcb_sendCmd1byte(STFTCB_SOFTRES);    //  0: Software reset
    STFTCB_DELAY(150000);
    stftcb_sendCmd1byte(STFTCB_SLPOUT);     //  1: Out of sleep mode
    STFTCB_DELAY(500);
    stftcb_sendCmd1byte(STFTCB_DISPON);
    STFTCB_DELAY(100);
    stftcb_sendCmd1byte(STFTCB_COLMODPFS);  //  2: set color mode
    stftcb_sendData1byte(0x55);             //     16-bit color
#endif
    stftcb_updateFrame();
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
    stftcb_SetFullAddressWindow();

    SPI_2byte_mode_on();
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
    STFTCB_SPI_DMA_SxCR->NDTR = STFTCB_SIZE;
    STFTCB_SPI_DMA_SxCR->CR |= DMA_SxCR_MINC;
    STFTCB_SPI_DMA_SxCR->CR |= DMA_SxCR_EN;
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

static void stftcb_Draw_FillBackground0(uint16_t color) {
    for (uint32_t i = 0; i < STFTCB_SIZE; i++)
        stftcb_array_tx_0[i] = color;
}

static void stftcb_Draw_FillBackground1(uint16_t color) {
    for (uint32_t i = 0; i < STFTCB_SIZE; i++)
        stftcb_array_tx_1[i] = color;
}

/* @brief stftcb_DrawFillBackground - закрашивает в выбранный цвет задний фон
 * */
void stftcb_DrawFillBackground(uint16_t color) {
    while (stftcb_array_tx_status != 0x00) {;}  // Ждем пока предыдущая передача не закончится
    if (stftcb_array_tx_mxar == 0) {
        stftcb_Draw_FillBackground0(color);
        stp_flash_erase(5);
        stp_flash_write_16(ADDRESS_MX0R, &stftcb_array_tx_0[0], STFTCB_SIZE);
        stftcb_Draw_FillBackground0(0xFFFF);
        stp_flash_read_16(ADDRESS_MX0R, &stftcb_array_tx_0[0], STFTCB_SIZE);
    } else {
        stftcb_Draw_FillBackground1(color);
        stp_flash_erase(6);
        stp_flash_write_16(ADDRESS_MX1R, &stftcb_array_tx_1[0], STFTCB_SIZE);
        stftcb_Draw_FillBackground1(0xFFFF);
        stp_flash_read_16(ADDRESS_MX1R, &stftcb_array_tx_1[0], STFTCB_SIZE);
    }
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


