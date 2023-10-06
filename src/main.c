#include "../system/include/cmsis/stm32f4xx.h"
//#include "./spi.h"
//#include "./st7735.h"

#define ch3		(0x03<<25)


/*

	* @brief initialize SPI1 peripheral and required pins
  * @param  None
  * @retval None

*/
void spi1_init(void) {
	//enable clock for GPIOA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//set PA5, PA6 and PA7 to alternate function mode
	GPIOA->MODER |= (GPIO_MODER_MODE5_1 | GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);
	//set which type of alternate function is
	GPIOA->AFR[0] |= ((0x05<<20) | (0x05<<24) | (0x05<<28));
	//enable clock access to SPI1
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	//set software slave managment
	SPI1->CR1 |= SPI_CR1_SSM|SPI_CR1_SSI;
	//set SPI in master mode
	SPI1->CR1 |= SPI_CR1_MSTR;
	SPI1->CR1 |= SPI_CR1_BR_0;
	//enable DMA_TX buffer
	SPI1->CR2 |= SPI_CR2_TXDMAEN;
	//enable SPI peripheral
	SPI1->CR1 |= SPI_CR1_SPE;
}

/*
 * @brief intialize DMA2 Stream3 Channel 3
 * @param  None
 * @retval None
 */
void dma2_stream3_ch2_init(void) {
	RCC->AHB1ENR|=RCC_AHB1ENR_DMA2EN;
	DMA2_Stream3->CR&=~DMA_SxCR_EN;
	while((DMA2_Stream3->CR)&DMA_SxCR_EN){;}
	DMA2_Stream3->CR=ch3|DMA_SxCR_MINC|DMA_SxCR_DIR_0|DMA_SxCR_TCIE
	|DMA_SxCR_HTIE|DMA_SxCR_TEIE|DMA_SxCR_DMEIE;
	//DMA2_Stream3->FCR=0;
	DMA2_Stream3->FCR&=~DMA_SxFCR_DMDIS;
	NVIC_EnableIRQ(DMA2_Stream3_IRQn);
}

/*
 * @brief initiation DMA transfer
 * @param  uint32_t src for data source
 * @param  uint32_t length of data source
 * @retval None
 */
void spi_transfer_dma(uint32_t src,uint32_t len) {
	DMA2->LIFCR |=DMA_LIFCR_CTCIF3|DMA_LIFCR_CHTIF3|DMA_LIFCR_CTEIF3|DMA_LIFCR_CDMEIF3|DMA_LIFCR_CFEIF3;
	DMA2_Stream3->PAR= (uint32_t)&SPI1->DR;
	DMA2_Stream3->M0AR=src;
	DMA2_Stream3->NDTR=len;
	DMA2_Stream3->CR|=DMA_SxCR_EN;
}

#define	LED_red		(1U<<14)
#define LED_green  	(1U<<12)
#define LED_blue    (1U<<15)
#define LED_orange  (1U<<13)
#define	LED_PORT    GPIOD
void led_init();

#define GPIOD_CLOCK    (1<<3)
//bits of the pins
#define LED_red_BIT    (1U<<28)
#define LED_green_BIT  (1U<<24)
#define LED_orange_BIT (1U<<26)
#define LED_blue_BIT   (1U<<30)
//LED port
#define	LED_PORT		GPIOD
//bit possition for color
#define	LED_red		 		 (1U<<14)
#define LED_green  		 (1U<<12)
#define LED_blue       (1U<<15)
#define LED_orange     (1U<<13)

	/*
	* @brief initialize the built-in LED of STM32F407-DISCO
  * @param  None
  * @retval None

*/

void led_init()
	{
	RCC->AHB1ENR |=GPIOD_CLOCK;
	GPIOD->MODER |= LED_red_BIT|LED_green_BIT|LED_orange_BIT|LED_blue_BIT;

	}

char data[]={'A','B','C','D','E','F','G'};
volatile uint8_t finished=0;
void delayMs(int delay)

{

volatile int i;

for(; delay>0 ;delay--)

{

for(i =0; i<3195;i++);

}

}

int main(void)
	{
	//printf("system init\r\n");
	led_init();
	spi1_init();
	dma2_stream3_ch2_init();
	//printf("system init finished\r\n");

	while(1)

			{
			spi_transfer_dma((uint32_t)data,sizeof(data));
			while(finished==0){}
			finished=0;
			delayMs(10);

			}
	}
void DMA2_Stream3_IRQHandler(void)
		{

		if(DMA2->LISR&(DMA_LISR_TCIF3))
				{
					LED_PORT->ODR^=LED_blue;
					//printf("finished transfered\r\n");
					finished=1;
					DMA2_Stream3->CR&=~DMA_SxCR_EN;
					DMA2->LIFCR |=DMA_LIFCR_CTCIF3;
				}

		if(DMA2->LISR&(DMA_LISR_HTIF3))
				{
					LED_PORT->ODR^=LED_green;
					//printf("half transfered\r\n");
					DMA2->LIFCR |=DMA_LIFCR_CHTIF3;
				}


		if(DMA2->LISR&(DMA_LISR_TEIF3))
						{
						//printf("transfer error interrupt\r\n");
						DMA2->LIFCR|=(DMA_LIFCR_CTEIF3);
						}

		if(DMA2->LISR&(DMA_LISR_DMEIF3))
						{
					//	printf("Direct mode interrupt error\r\n");
						DMA2->LIFCR|=(DMA_LIFCR_CDMEIF3);
						}

		if(DMA2->LISR&(DMA_LISR_FEIF3))
						{
					//	printf("FIFO error interrupt\r\n");
						DMA2->LIFCR|=(DMA_LIFCR_CFEIF3);
						}

			NVIC_ClearPendingIRQ(DMA2_Stream3_IRQn);
		}




#if 0
int main(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER |= (GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0);
    GPIOD->ODR &= ~(GPIO_ODR_OD12 | GPIO_ODR_OD13 | GPIO_ODR_OD14 | GPIO_ODR_OD15);

    //STFTCB_init();
    //ST7735_Init();
    SPI2_SPI_init();
    GPIOD->ODR |= GPIO_ODR_OD12;
    while(1) {}
    uint8_t color = 0x00;
    uint16_t colors[9] = {ST7735_BLACK, ST7735_BLUE, ST7735_RED, ST7735_GREEN, ST7735_CYAN, ST7735_MAGENTA, ST7735_YELLOW, ST7735_ORANGE, ST7735_LIGHTGREEN};

	while(1) {
        if (color == 9)
            color = 0x00;
        ST7735_FillScreen(colors[color]);
        ++color;
#if 0
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
#endif
	}
}
#endif

