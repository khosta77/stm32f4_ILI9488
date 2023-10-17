#include "./st7735.h"

//uint16_t tft_display[STFTCB_SIZE];

void rainbow();
void drawPoints();
void drawLine_0();
void drawLine_1();
void drawRectangleNoFill();
void drawRectangleFill();
void drawCicleNoFill();
void drawCicleFill();




uint16_t colors[] = {
//    STFTCB_COLOR_BLACK,
    STFTCB_COLOR_WHITE,
    STFTCB_COLOR_BLUE,
    STFTCB_COLOR_RED,
    STFTCB_COLOR_GREEN,
    STFTCB_COLOR_MAGENTA,
    STFTCB_COLOR_YELLOW
};

const uint8_t COLORS_SIZE = (sizeof(colors) / sizeof(colors[0]));

#define RGB565(r, g, b) (((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3))
#define CHECK_C(c) { if (c == COLORS_SIZE) c = 0x00; \
                     else ++c;}

void SystemClockConfig() {
	// Prescaler Configrations
	RCC->CFGR 	|= (5 << 10);			// APB1 Prescaler = 4
	RCC->CFGR 	|= (0x5 << 13);			// APB2 Prescaler = 3

	RCC->CR 	|= (1 << 16);			// HSE Clock Enable - HSEON
	while(!(RCC->CR & 0x00020000));		// Wait until HSE Clock Ready - HSERDY

	// PLL Configrations
	RCC->PLLCFGR = 0;					// Clear all PLLCFGR register
	RCC->PLLCFGR |=  (8		<<  0);		// PLLM = 8;
	RCC->PLLCFGR |=  (336 	<<  6);		// PLLN = 336;
	RCC->PLLCFGR &= ~(3 	<< 16);		// PLLP = 2; // For 2, Write 0
	RCC->PLLCFGR |=  (1 	<< 22);		// HSE Oscillator clock select as PLL
	RCC->PLLCFGR |=  (7 	<< 24);		// PLLQ = 7;

	RCC->CR 		|=  (1 		<< 24); // PLL Clock Enable - PLLON
	while(!(RCC->CR & 0x02000000)); 	// Wait until PLL Clock Ready - PLLRDY

	// Flash Configrations
	FLASH->ACR = 0;						// Clear all ACR register (Access Control Register)
	FLASH->ACR 		|= (5 <<  0); 		// Latency - 5 Wait State
	FLASH->ACR 		|= (1 <<  9);		// Instruction Cache Enable
	FLASH->ACR 		|= (1 << 10);		// Data Cache Enable

	RCC->CFGR 		|= (2 <<  0);		// PLL Selected as System Clock
	while((RCC->CFGR & 0x0F) != 0x0A); 	// Wait PLL On
}

int main(void) {
    //SystemClockConfig();
    SystemCoreClockUpdate();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER |= (GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0);
    GPIOD->ODR &= ~(GPIO_ODR_OD12 | GPIO_ODR_OD13 | GPIO_ODR_OD14 | GPIO_ODR_OD15);

//    if (SystemCoreClock == 16000000/*168000000*/)
//        GPIOD->ODR |= GPIO_ODR_OD12;
    STFTCB_init();
    ST7735_Init();

    char *c = "890";
//    printt(0,0, &c[0]);
//    stftcb_updateFrame();

	while(1) {
        printT(0,0, &c[0]);
        stftcb_updateFrame();
        //stftcb_DrawFillBackground(0x0000);
	}
}

void rainbow() {
    static uint16_t color = 0x00;
    if (color == COLORS_SIZE)
            color = 0x00;
    stftcb_DrawFillBackground(colors[color]);
    ++color;
}

void drawPoints() {
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

void drawLine_0() {
    static uint16_t color = 0x00;
    
    CHECK_C(color);
    for (uint16_t i = 0, I = 0; i < STFTCB_HEIGHT; i++, I += STFTCB_WIDTH) {
        stftcb_DrawLine(0, 0, (STFTCB_WIDTH - 1), i, colors[color]);
        stftcb_updateFrame();
    }

    CHECK_C(color);
    for (uint16_t i = 0, I = 0; i < STFTCB_HEIGHT; i++, I += STFTCB_WIDTH) {
        stftcb_DrawLine((STFTCB_WIDTH - 1), 0, 0, i, colors[color]);
        stftcb_updateFrame();
    }

    CHECK_C(color);
    for (uint16_t i = 0, I = 0; i < STFTCB_HEIGHT; i++, I += STFTCB_WIDTH) {
        stftcb_DrawLine((STFTCB_WIDTH - 1), (STFTCB_HEIGHT - 1), 0, i, colors[color]);
        stftcb_updateFrame();
    }

    CHECK_C(color);
    for (uint16_t i = 0, I = 0; i < STFTCB_HEIGHT; i++, I += STFTCB_WIDTH) {
        stftcb_DrawLine(0, (STFTCB_HEIGHT - 1), (STFTCB_WIDTH - 1), i, colors[color]);
        stftcb_updateFrame();
    }
}

void drwwLine_1() {
    static uint16_t color = 0x00;

    CHECK_C(color);
    for (uint16_t i = 0; i < STFTCB_HEIGHT; i++)
        stftcb_DrawLine(0, 0, (STFTCB_WIDTH - 1), i, colors[color]);
    stftcb_updateFrame();

    
    CHECK_C(color);
    for (uint16_t i = 0; i < STFTCB_HEIGHT; i++)
        stftcb_DrawLine((STFTCB_WIDTH - 1), 0, 0, i, colors[color]);
    stftcb_updateFrame();

    CHECK_C(color);
    for (uint16_t i = 0; i < STFTCB_HEIGHT; i++)
        stftcb_DrawLine((STFTCB_WIDTH - 1), (STFTCB_HEIGHT - 1), 0, i, colors[color]);
    stftcb_updateFrame();

    CHECK_C(color);
    for (uint16_t i = 0; i < STFTCB_HEIGHT; i++)
        stftcb_DrawLine(0, (STFTCB_HEIGHT - 1), (STFTCB_WIDTH - 1), i, colors[color]);
    stftcb_updateFrame();
}

void drawRectangleNoFill() {
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

void drawRectangleFill() {
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

void drawCicleNoFill() {
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

void drawCicleFill() {
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

// stftcb_DrawNoFillCicle
