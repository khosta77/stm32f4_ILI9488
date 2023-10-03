#include "../system/include/cmsis/stm32f4xx.h"
#include "./spi.h"
#include "./st7735.h"


int main(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER |= (GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0);
    GPIOD->ODR &= ~(GPIO_ODR_OD12 | GPIO_ODR_OD13 | GPIO_ODR_OD14 | GPIO_ODR_OD15);
    STFTCB_init();
    ST7735_Init();

    uint8_t color = 0x00;
    uint16_t colors[9] = {ST7735_BLACK, ST7735_BLUE, ST7735_RED, ST7735_GREEN, ST7735_CYAN, ST7735_MAGENTA, ST7735_YELLOW, ST7735_ORANGE, ST7735_LIGHTGREEN};
    GPIOD->ODR |= GPIO_ODR_OD12;
	while(1) {
        if (color == 9)
            color = 0x00;
        ST7735_FillScreen(colors[color]);
        ++color;
        while (1) {
            if (color == 9)
                color = 0x01;
            for (uint16_t i = 0; i < 360; i++) {
                stftcb_DrawFillRectangle(40, 40, 90, 90, i, ST7735_BLUE);
           //     stftcb_DrawFillRectangle(35, 60, 60, 100, (i + 10), ST7735_RED);

        //    ST7735_DrawFillEasyRectangle(20, 20, 100, 100, colors[color]);
             //   MyDelay(10000);
                stftcb_DrawFillRectangle(40, 40, 90, 90, i, ST7735_BLACK);
             //   stftcb_DrawFillRectangle(35, 60, 60, 100, (i + 10), ST7735_BLACK);


            }
/*
            for (uint8_t y = 0; y < ST7735_HEIGHT; ++y) {
                    ST7735_DrawLine(0, 0, (ST7735_WIDTH), y, colors[color]);
                    MyDelay(1000);
            }
            for (uint8_t x = (ST7735_WIDTH); x >= 0 && x != 0xFF; --x) {
                    ST7735_DrawLine(0, 0, x, (ST7735_HEIGHT), colors[color]);
                    MyDelay(1000);
            }
*/
            ++color;
          //  while(1){}
        }
        //while (1) {
          //  GPIOD->ODR &= ~(GPIO_ODR_OD12 | GPIO_ODR_OD13 | GPIO_ODR_OD14);
        //}
	}
}


