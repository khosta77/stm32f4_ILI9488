#include "./st7735.h"

uint16_t colors[] = {
    STFTCB_COLOR_BLACK,
    STFTCB_COLOR_WHITE,
    STFTCB_COLOR_BLUE,
    STFTCB_COLOR_RED,
    STFTCB_COLOR_GREEN,
    STFTCB_COLOR_MAGENTA,
    STFTCB_COLOR_YELLOW
};

const uint8_t COLORS_SIZE = (sizeof(colors) / sizeof(colors[0]));

#define RGB565(r, g, b) (((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3))

int main(void) { 
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER |= (GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0);
    GPIOD->ODR &= ~(GPIO_ODR_OD12 | GPIO_ODR_OD13 | GPIO_ODR_OD14 | GPIO_ODR_OD15);

    STFTCB_init();
    ST7735_Init();

    uint8_t color = 0x00;

	while(1) {
        if (color == COLORS_SIZE)
            color = 0x00;
        stftcb_DrawFillBackground(colors[color]);
        ++color;
	}
}


