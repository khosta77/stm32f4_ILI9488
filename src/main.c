#include "stftcb.h"


/** @brief DMA2_Stream3_IRQHandler - прерывание при завершение передачи данных по SPI
 * */
void DMA2_Stream3_IRQHandler(void) {
    if (STFTCB_SPI_DMA_TCIF) {  // Прерывания по завершению передачи
        GPIOD->ODR ^= GPIO_ODR_OD15;
        stftcb_array_tx_status = 0x00;
        STFTCB_SPI_DMA_SxCR->CR &= ~DMA_SxCR_EN;
        STFTCB_SPI_DMA_CTCIF; 
    }
}

static void rainbow();
static void drawPoints();
static void drawLine_0();
static void drawLine_1();
static void drawRectangleNoFill();
static void drawRectangleFill();
static void drawCicleNoFill();
static void drawCicleFill();

uint16_t colors[] = {
    STFTCB_COLOR_BLACK,
    STFTCB_COLOR_WHITE,
    STFTCB_COLOR_BLUE,
    STFTCB_COLOR_RED,
    STFTCB_COLOR_GREEN,
    STFTCB_COLOR_MAGENTA,
    STFTCB_COLOR_YELLOW
};

const uint8_t COLORS_SIZE = 7;//(sizeof(colors) / sizeof(colors[0]));

#define RGB565(r, g, b) (((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3))
#define CHECK_C(c) { if (c == COLORS_SIZE) c = 0x00; \
                     else ++c;}

int main(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER |= (GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0);
    GPIOD->ODR &= ~(GPIO_ODR_OD12 | GPIO_ODR_OD13 | GPIO_ODR_OD14 | GPIO_ODR_OD15);

    STFTCB_init();

    //char *c = "890";

    while(1) {
		drawLine_0();
        //printT(0,0, &c[0]);
        //stftcb_updateFrame();
    }
}

static void rainbow() {
    static uint16_t color = 0x00;
    if (color == COLORS_SIZE)
            color = 0x00;
    stftcb_DrawFillBackground(colors[color]);
    for (uint32_t t = 0; t < 0xAFFFF; t++);
    stftcb_updateFrame();
    ++color;
}

static void drawPoints() {
    static uint16_t color = 0x00;
    if (color == COLORS_SIZE)
            color = 0x00;
    for (uint16_t i = 0, I = 0; i < STFTCB_HEIGHT; i++, I += STFTCB_WIDTH) {
        for (uint16_t j = 0; j < STFTCB_WIDTH; j++) {
            stftcb_DrawPixel(i, j, colors[color]);
        }
    }
    stftcb_updateFrame();
    ++color;
}

static void drawLine_0() {
    static uint16_t color = 0x00;
    for (uint32_t t = 0; t < 0xAFFFF; t++);  
    CHECK_C(color);
    for (uint16_t i = 0, I = 0; i < STFTCB_HEIGHT; i++, I += STFTCB_WIDTH) {
        stftcb_DrawLine(0, 0, (STFTCB_WIDTH - 1), i, colors[color]);
        stftcb_updateFrame();
    }
    for (uint32_t t = 0; t < 0xAFFFF; t++);

    CHECK_C(color);
    for (uint16_t i = 0, I = 0; i < STFTCB_HEIGHT; i++, I += STFTCB_WIDTH) {
        stftcb_DrawLine((STFTCB_WIDTH - 1), 0, 0, i, colors[color]);
        stftcb_updateFrame();
    }
    for (uint32_t t = 0; t < 0xAFFFF; t++);

    CHECK_C(color);
    for (uint16_t i = 0, I = 0; i < STFTCB_HEIGHT; i++, I += STFTCB_WIDTH) {
        stftcb_DrawLine((STFTCB_WIDTH - 1), (STFTCB_HEIGHT - 1), 0, i, colors[color]);
        stftcb_updateFrame();
    }
    for (uint32_t t = 0; t < 0xAFFFF; t++);

    CHECK_C(color);
    for (uint16_t i = 0, I = 0; i < STFTCB_HEIGHT; i++, I += STFTCB_WIDTH) {
        stftcb_DrawLine(0, (STFTCB_HEIGHT - 1), (STFTCB_WIDTH - 1), i, colors[color]);
        stftcb_updateFrame();
    }
}

static void drawLine_1() {
    static uint16_t color = 0x00;
    for (uint32_t t = 0; t < 0xAFFFF; t++);

    CHECK_C(color);
    for (uint16_t i = 0; i < STFTCB_HEIGHT; i++)
        stftcb_DrawLine(0, 0, (STFTCB_WIDTH - 1), i, colors[color]);
    stftcb_updateFrame();
    stftcb_updateFrame();
    for (uint32_t t = 0; t < 0xAFFFF; t++);

    
    CHECK_C(color);
    for (uint16_t i = 0; i < STFTCB_HEIGHT; i++)
        stftcb_DrawLine((STFTCB_WIDTH - 1), 0, 0, i, colors[color]);
    stftcb_updateFrame();
    stftcb_updateFrame();
    for (uint32_t t = 0; t < 0xAFFFF; t++);

    CHECK_C(color);
    for (uint16_t i = 0; i < STFTCB_HEIGHT; i++)
        stftcb_DrawLine((STFTCB_WIDTH - 1), (STFTCB_HEIGHT - 1), 0, i, colors[color]);
    stftcb_updateFrame();
    stftcb_updateFrame();
    for (uint32_t t = 0; t < 0xAFFFF; t++);

    CHECK_C(color);
    for (uint16_t i = 0; i < STFTCB_HEIGHT; i++)
        stftcb_DrawLine(0, (STFTCB_HEIGHT - 1), (STFTCB_WIDTH - 1), i, colors[color]);
    stftcb_updateFrame();
    stftcb_updateFrame();
}

static void drawRectangleNoFill() {
    for (float a = 0.0; a < 360.0; a += 5) {
        GPIOD->ODR &= ~GPIO_ODR_OD12;
            GPIOD->ODR &= ~GPIO_ODR_OD13;
        stftcb_DrawNoFillRectangle(50, 50, 90, 90, a, STFTCB_COLOR_RED);
        stftcb_DrawNoFillRectangle(20, 70, 30, 80, (a + 10), STFTCB_COLOR_GREEN);
        stftcb_DrawNoFillRectangle(48, 60, 80, 100, (a - 5), STFTCB_COLOR_YELLOW);
        stftcb_DrawNoFillRectangle(70, 100, 85, 120, (a + 3.2), STFTCB_COLOR_WHITE);
            GPIOD->ODR |= GPIO_ODR_OD13;
            GPIOD->ODR &= ~GPIO_ODR_OD14;
        stftcb_updateFrame();
            GPIOD->ODR |= GPIO_ODR_OD14;
        stftcb_DrawNoFillRectangle(50, 50, 90, 90, a, 0x0000);
        stftcb_DrawNoFillRectangle(20, 70, 30, 80, (a + 10), 0x0000);
        stftcb_DrawNoFillRectangle(48, 60, 80, 100, (a - 5), 0x0000);
        stftcb_DrawNoFillRectangle(70, 100, 85, 120, (a + 3.2), 0x0000);
        GPIOD->ODR |= GPIO_ODR_OD12;
    }
}

static void drawRectangleFill() {
    for (float a = 0.0; a < 360.0; a += 5) {
        GPIOD->ODR &= ~GPIO_ODR_OD12;
            GPIOD->ODR &= ~GPIO_ODR_OD13;
        stftcb_DrawFillRectangle(50, 50, 90, 90, a, STFTCB_COLOR_RED);
        stftcb_DrawFillRectangle(20, 70, 30, 80, (a + 10), STFTCB_COLOR_GREEN);
        stftcb_DrawFillRectangle(48, 60, 80, 100, (a - 5), STFTCB_COLOR_YELLOW);
        stftcb_DrawFillRectangle(70, 100, 100, 130, (a + 3.2), STFTCB_COLOR_WHITE);
            GPIOD->ODR |= GPIO_ODR_OD13;
            GPIOD->ODR &= ~GPIO_ODR_OD14;
        stftcb_updateFrame();
            GPIOD->ODR |= GPIO_ODR_OD14;
        stftcb_DrawFillBackground(0x0000);
        GPIOD->ODR |= GPIO_ODR_OD12;
    }
}

static void drawCicleNoFill() {
    for (int a = 6; a < 16; a++) {
        GPIOD->ODR &= ~GPIO_ODR_OD12;
            GPIOD->ODR &= ~GPIO_ODR_OD13;
        stftcb_DrawNoFillCicle((STFTCB_WIDTH / 2), (STFTCB_HEIGHT / 2), 20, STFTCB_COLOR_RED);
        stftcb_DrawNoFillCicle(20, 70, (a + 10), STFTCB_COLOR_GREEN);
        stftcb_DrawNoFillCicle(48, 60, (a - 5), STFTCB_COLOR_YELLOW);
        stftcb_DrawNoFillCicle(70, 100, (a + 3.2), STFTCB_COLOR_WHITE);
            GPIOD->ODR |= GPIO_ODR_OD13;
            GPIOD->ODR &= ~GPIO_ODR_OD14;
        stftcb_updateFrame();
            GPIOD->ODR |= GPIO_ODR_OD14;
        stftcb_DrawFillBackground(0x0000);
        GPIOD->ODR |= GPIO_ODR_OD12;
    }  
}

static void drawCicleFill() {
    for (int a = 6; a < 16; a++) {
        GPIOD->ODR &= ~GPIO_ODR_OD12;
            GPIOD->ODR &= ~GPIO_ODR_OD13;
        stftcb_DrawFillCicle((STFTCB_WIDTH / 2), (STFTCB_HEIGHT / 2), 20, STFTCB_COLOR_RED);
        stftcb_DrawFillCicle(20, 70, (a + 10), STFTCB_COLOR_GREEN);
        stftcb_DrawFillCicle(48, 60, (a - 5), STFTCB_COLOR_YELLOW);
        stftcb_DrawFillCicle(70, 100, (a + 3.2), STFTCB_COLOR_WHITE);
            GPIOD->ODR |= GPIO_ODR_OD13;
            GPIOD->ODR &= ~GPIO_ODR_OD14;
        stftcb_updateFrame();
        for (uint16_t i = 0; i < 0xFFFD; i++);
            GPIOD->ODR |= GPIO_ODR_OD14;
        stftcb_DrawFillBackground(0x0000);
        GPIOD->ODR |= GPIO_ODR_OD12;
    }
}


