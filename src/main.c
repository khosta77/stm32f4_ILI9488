#include "../system/include/cmsis/stm32f4xx.h"
 #include "../system/include/stm32f4-hal/stm32f4xx_hal.h"
#include "./spi.h"
#include "./st7735.h"


int main(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER |= (GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0);
    GPIOD->ODR &= ~(GPIO_ODR_OD12 | GPIO_ODR_OD13 | GPIO_ODR_OD14 | GPIO_ODR_OD15);
    MX_GPIO_Init();
    GPIOD->ODR |= GPIO_ODR_OD12;
    MX_SPI1_Init();
    GPIOD->ODR |= GPIO_ODR_OD13;
    Lcd_Init();
    GPIOD->ODR |= GPIO_ODR_OD14;
	//lv_port_disp_init();
	//lv_demo_benchmark(LV_DEMO_BENCHMARK_MODE_RENDER_AND_DRIVER);

	while(1) {
        for (uint8_t y = 0; y < (LCD_H - 2); y++) {
            for (uint8_t x = 0; x < (LCD_W - 2); x++) {
                Lcd_DrawLine(0, 0, x, y);
                //MyDelay(10000);
                //GPIOD->ODR ^= GPIO_ODR_OD15;
            }
        }
        while (1) {
            GPIOD->ODR |= GPIO_ODR_OD15;
        }
	}
}


