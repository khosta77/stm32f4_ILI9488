#include "main.h"

/** @brief DMA2_Stream3_IRQHandler - прерывание при завершение передачи данных по SPI
 * */
void DMA2_Stream3_IRQHandler(void) {
    if (STFTCB_SPI_DMA_TCIF) {  // Прерывания по завершению передачи
        stftcb_array_tx_status = 0x00;
        STFTCB_SPI_DMA_SxCR->CR &= ~DMA_SxCR_EN;
        STFTCB_SPI_DMA_CTCIF; 
    }
}


void DMA1_Stream6_IRQHandler(void) {  // TX
    if ((DMA1->HISR & DMA_HISR_TCIF6) == DMA_HISR_TCIF6) {
        usart2_mrk = 0xA0;
        DMA1_Stream6->CR &= ~DMA_SxCR_EN;
        DMA1->HIFCR |= DMA_HIFCR_CTCIF6;
    }
}

void DMA1_Stream5_IRQHandler(void) {  // RX
    if ((DMA1->HISR & DMA_HISR_TCIF5) == DMA_HISR_TCIF5) {
        usart2_mrk = 0x0A;
        DMA1_Stream5->CR &= ~DMA_SxCR_EN;
        while ((DMA1_Stream5->CR) & DMA_SxCR_EN){;}
        DMA1->HIFCR |= DMA_HIFCR_CTCIF5;
    }
}

void SystemClockConfig();
void init();
void loop();

void init() {
    SystemClockConfig();
    USART2_init();
    STFTCB_init();
}

void loop() {
#if 1

    if (usart2_mrk == USART_RX_ACTIVE)
        message_in();
    if (usart2_mrk == USART_TX_ACTIVE)
        message_out();
#else
    for (uint16_t i = 0; i < 1000; i++)
        usart2_tx_array[i] = i;
    DMA1_Stream6->CR &= ~DMA_SxCR_EN;
    while ((DMA1_Stream6->CR) & DMA_SxCR_EN){;}
    DMA1_Stream6->CR |= DMA_SxCR_MINC;
    DMA1_Stream6->NDTR = 1000;
    DMA1_Stream6->CR |= DMA_SxCR_EN;
    while (usart2_mrk == 0x00) {;}
    usart2_mrk = 0x00;
#endif
}

void SystemClockConfig() {	
	// Prescaler Configrations
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;  // APB1 Prescaler = 4
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;  // APB2 Prescaler = 2
	RCC->CR   |= RCC_CR_HSEON;         // HSE Clock Enable - HSEON
	while(!(RCC->CR & 0x00020000));    // Wait until HSE Clock Ready - HSERDY

	// PLL Configrations
	RCC->PLLCFGR = 0;                         // Clear all PLLCFGR register
	RCC->PLLCFGR |=  (8 << 0);                // PLLM = 8;
	RCC->PLLCFGR |=  (336 << 6);              // PLLN = 336;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;        // PLLP = 2; // For 2, Write 0
	RCC->PLLCFGR |=  RCC_PLLCFGR_PLLSRC_HSE;  // HSE Oscillator clock select as PLL
	RCC->PLLCFGR |=  (7 << 24);               // PLLQ = 7;
	RCC->CR      |=  RCC_CR_PLLON;            // PLL Clock Enable - PLLON
	while(!(RCC->CR & 0x02000000));           // Wait until PLL Clock Ready - PLLRDY

	// Flash Configrations
	FLASH->ACR = 0;                       // Clear all ACR register (Access Control Register)
	FLASH->ACR |= FLASH_ACR_LATENCY_5WS;  // Latency - 5 Wait State
	FLASH->ACR |= FLASH_ACR_ICEN;         // Instruction Cache Enable
	FLASH->ACR |= FLASH_ACR_DCEN;         // Data Cache Enable
	RCC->CFGR  |= RCC_CFGR_SW_1;          // PLL Selected as System Clock
	while((RCC->CFGR & 0x0F) != 0x0A); 	  // Wait PLL On
}

int main(void) {
    init();
    usart2_tx_array[0] = usart2_tx_array[1] = 0x11;
    while(1) {
        loop();
    }
}

