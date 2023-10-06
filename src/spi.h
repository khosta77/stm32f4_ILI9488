#ifndef SPI_H_
#define SPI_H_

#include "../system/include/cmsis/stm32f4xx.h"
#include "../system/include/stm32f4-hal/stm32f4xx_hal.h"

void SPI1_init();
void SPI1_GPIO_init();
void SPI1_SPI_init();

void SPI1_transmit(uint16_t dt);

void SPI1_init() {
    SPI1_GPIO_init();
    SPI1_SPI_init();
}

void SPI1_SPI_init() {
    // 1. Включаем тактирование
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    // *. Что то мутное, ни на что не влияет
//  SPI1->CRCPR = 10;
    // *. Сбросим биты настрой в CR1
    SPI1->CR1 &= ~(SPI_CR1_LSBFIRST | SPI_CR1_CPHA | SPI_CR1_CPOL);
    // *. Сбросим наверняка CR2
    SPI1->CR2 = 0x0000;
    // 2. Настройка CR1
    // - SPI_CR1_MSTR - мастер мод
    // - SPI_CR1_SSM - Разрешает программное управление slave устройством
    // - SPI_CR1_SSI - Надо с SPI_CR1_SSM включать. Синхронизирует что то
    // - SPI_CR1_SPE - Запуск SPI
	SPI1->CR1 |= (SPI_CR1_MSTR | /*SPI_CR1_DFF |*/ SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE);
}

/** @brief SPI1_GPIO_init - инициализация GPIO для SPI1 так как нам надо только отправлять данные в режиме \
 *                          Master, то надо инициализировать только две ножки, тактирование(SPI_SCK) и \
 *                          Master Out Slave In (SPI_MOSI).
 *                          PA5 ---> SPI1_SCK
 *                          PA7 ---> SPI1_MOSI
 * */
void SPI1_GPIO_init() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= (GPIO_MODER_MODER5_1 | GPIO_MODER_MODER7_1);
	GPIOA->AFR[0] |= ((GPIO_AFRL_AFSEL5_2 | GPIO_AFRL_AFSEL5_0) | (GPIO_AFRL_AFSEL7_2 | GPIO_AFRL_AFSEL7_0));
	GPIOA->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR5_1 | GPIO_OSPEEDER_OSPEEDR7_1);
	GPIOA->PUPDR |= (GPIO_PUPDR_PUPD5_1 | GPIO_PUPDR_PUPD7_1);
}

#if 1
void SPI2_GPIO_init();
void SPI2_SPI_init();
void SPI2_DMA_init();
#define SPI2_DMA1_SIZE 10 //20480

uint8_t sp1_dma1_tx_buffer_0[SPI2_DMA1_SIZE] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void SPI2_init() {
#if 0
    SPI2_GPIO_init();
    SPI2_SPI_init();
    SPI2_DMA_init();
#elif 0
        //DMA1 Stream 5 SPI3_TX channel 0
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    
    // GPIO
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
    
    // PC10 - SCK - Выход
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    // PC11 - MISO - Вход
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    // PC12 - MOSI - Выход
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    uint8_t data[] = {1,2,3};
    uint8_t len = 3;
        
    DMA1_Stream5->CR = 0;
    
    DMA1_Stream5->PAR = (uint32_t)(&SPI3->DR);
    DMA1_Stream5->M0AR = (uint32_t)data;
    DMA1_Stream5->NDTR = len;
    DMA1_Stream5->FCR = 0;							// Настройка FIFO буфера
    
    DMA1_Stream5->CR = 
     (0x00) << DMA_SxCR_CHSEL_Pos       // Выбор канала
    |(0x00) << DMA_SxCR_MBURST_Pos      //
    |(0x00) << DMA_SxCR_PBURST_Pos      //
    |0      << DMA_SxCR_CT_Pos          // Текущий буфер
    |0      << DMA_SxCR_DBM_Pos         // Двойной буфер
    |(0x03) << DMA_SxCR_PL_Pos          // Приоритет
    |0      << DMA_SxCR_PINCOS_Pos      // Инкремент адреса периферии
    |(0x00) << DMA_SxCR_MSIZE_Pos       // Размер данных в памяти 8 бит
    |(0x00) << DMA_SxCR_PSIZE_Pos       // Размер данных в периферии 8 бит
    |1      << DMA_SxCR_MINC_Pos        // Инкремент адреса памяти
    |0      << DMA_SxCR_PINC_Pos        // Инкремент адреса периферии
    |1      << DMA_SxCR_CIRC_Pos        // Циркуляционный режим
    |(0x01) << DMA_SxCR_DIR_Pos         // Направление данных из памяти в периферию
    |0      << DMA_SxCR_PFCTRL_Pos      // DMA управляет процессом
    |0      << DMA_SxCR_TCIE_Pos        // Прерывание по окончанию передачи
    |0      << DMA_SxCR_HTIE_Pos        // Прерывание по половине передачи
    |0      << DMA_SxCR_TEIE_Pos        // Прерывание по ошибке передачи
    |0      << DMA_SxCR_DMEIE_Pos       // Прерывание по 
    |1      << DMA_SxCR_EN_Pos;         // Активация DMA
    
    SPI3->CR2 = 1<<SPI_CR2_TXDMAEN_Pos
    | 1<<SPI_CR2_SSOE_Pos;
   
    SPI3->CR1 = 0<<SPI_CR1_DFF_Pos  //Размер кадра 8 бит
    | 0<<SPI_CR1_LSBFIRST_Pos     //MSB first
    | 1<<SPI_CR1_SSM_Pos          //Программное управление SS
    | 1<<SPI_CR1_SSI_Pos          //SS в высоком состоянии
    | 0x04<<SPI_CR1_BR_Pos        //Скорость передачи: F_PCLK/32
    | 1<<SPI_CR1_MSTR_Pos         //Режим Master (ведущий)
    | 0<<SPI_CR1_CPOL_Pos | 0<<SPI_CR1_CPHA_Pos //Режим работы SPI: 0
    | 1<<SPI_CR1_SPE_Pos; //Включаем SPI
#else
    			//enable clock for GPIOA
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
			//set PA5, PA6 and PA7 to alternate function mode
		GPIOA->MODER|=GPIO_MODER_MODE5_1|GPIO_MODER_MODE6_1|GPIO_MODER_MODE7_1;
			//set which type of alternate function is
		GPIOA->AFR[0]|=(0x05<<20)|(0x05<<24)|(0x05<<28);
			//enable clock access to SPI1
		RCC->APB2ENR|=RCC_APB2ENR_SPI1EN;
			//set software slave managment
		SPI1->CR1|=SPI_CR1_SSM|SPI_CR1_SSI;
			//set SPI in master mode
		SPI1->CR1|=SPI_CR1_MSTR;
		SPI1->CR1|=SPI_CR1_BR_0;
			//enable DMA_TX buffer
		SPI1->CR2|=SPI_CR2_TXDMAEN;
			//enable SPI peripheral
		SPI1->CR1|=SPI_CR1_SPE;

        	RCC->AHB1ENR|=RCC_AHB1ENR_DMA2EN;
	DMA2_Stream3->CR&=~DMA_SxCR_EN;
	while((DMA2_Stream3->CR)&DMA_SxCR_EN){;}
	DMA2_Stream3->CR=(0x03 << 25)|DMA_SxCR_MINC|DMA_SxCR_DIR_0|DMA_SxCR_TCIE
	|DMA_SxCR_HTIE|DMA_SxCR_TEIE|DMA_SxCR_DMEIE;
	//DMA2_Stream3->FCR=0;
	DMA2_Stream3->FCR&=~DMA_SxFCR_DMDIS;
	NVIC_EnableIRQ(DMA2_Stream3_IRQn);

    DMA2->LIFCR |=DMA_LIFCR_CTCIF3|DMA_LIFCR_CHTIF3|DMA_LIFCR_CTEIF3|DMA_LIFCR_CDMEIF3|DMA_LIFCR_CFEIF3;
				DMA2_Stream3->PAR= (uint32_t)&SPI1->DR;
				//DMA2_Stream3->M0AR=src;
    DMA2_Stream3->M0AR = (uint32_t)&sp1_dma1_tx_buffer_0[0];

				DMA2_Stream3->NDTR=SPI2_DMA1_SIZE;
				DMA2_Stream3->CR|=DMA_SxCR_EN;
#endif
}

void DMA2_Stream3_IRQHandler(void) {		
	if(DMA2->LISR&(DMA_LISR_TCIF3)) {
//		LED_PORT->ODR^=LED_blue;
//		printf("finished transfered\r\n");
//		finished=1;
		DMA2_Stream3->CR&=~DMA_SxCR_EN;
		DMA2->LIFCR |=DMA_LIFCR_CTCIF3;
	}
				
    if(DMA2->LISR&(DMA_LISR_HTIF3)) {
//		LED_PORT->ODR^=LED_green;
//		printf("half transfered\r\n");
		DMA2->LIFCR |=DMA_LIFCR_CHTIF3;
	}
					
	if(DMA2->LISR&(DMA_LISR_TEIF3)) {
//		printf("transfer error interrupt\r\n");
		DMA2->LIFCR|=(DMA_LIFCR_CTEIF3);
	}
						
	if(DMA2->LISR&(DMA_LISR_DMEIF3)) {
//		printf("Direct mode interrupt error\r\n");
		DMA2->LIFCR|=(DMA_LIFCR_CDMEIF3);
	}
						
	if(DMA2->LISR&(DMA_LISR_FEIF3)) {
//		printf("FIFO error interrupt\r\n");
		DMA2->LIFCR|=(DMA_LIFCR_CFEIF3);
	}

	NVIC_ClearPendingIRQ(DMA2_Stream3_IRQn);
}

void SPI2_GPIO_init() {
    RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOBEN);
    GPIOB->MODER |= GPIO_MODER_MODER13_1;  // SPI2_SCK
    GPIOB->AFR[1] | (GPIO_AFRH_AFSEL13_2 | GPIO_AFRH_AFSEL13_1);
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_1;
    GPIOB->PUPDR | GPIO_PUPDR_PUPD13_1;

    GPIOC->MODER |= GPIO_MODER_MODER3_1;  // SPI2_MOSI
    GPIOC->AFR[0] | (GPIO_AFRL_AFSEL3_2 | GPIO_AFRL_AFSEL3_1);
    GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_1;
    GPIOC->PUPDR | GPIO_PUPDR_PUPD3_1;
}

void SPI2_SPI_init() {
    // 1. Включаем тактирование
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
    // *. Что то мутное, ни на что не влияет
//  SPI2->CRCPR = 10;
    // *. Сбросим биты настрой в CR1
    SPI2->CR1 &= ~(SPI_CR1_LSBFIRST | SPI_CR1_CPHA | SPI_CR1_CPOL);
    // *. Сбросим наверняка CR2
    SPI2->CR2 |= (SPI_CR2_SSOE |  SPI_CR2_TXDMAEN);
    // 2. Настройка CR1
    // - SPI_CR1_MSTR - мастер мод
    // - SPI_CR1_SSM - Разрешает программное управление slave устройством
    // - SPI_CR1_SSI - Надо с SPI_CR1_SSM включать. Синхронизирует что то
    // - SPI_CR1_SPE - Запуск SPI
	SPI2->CR1 |= (SPI_CR1_MSTR |/* SPI_CR1_DFF |*/ SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE);
}

// uint16_t sp1_dma2_tx_buffer_1[SIZE];

void DMA1_Stream4_IRQHandler(void) {
    if ((DMA1->LISR & DMA_LISR_TCIF2) == DMA_LISR_TCIF2) {
//        GPIOD->ODR ^= GPIO_ODR_OD13;
        DMA1->LIFCR |= DMA_LIFCR_CTCIF2;
    }
}

void SPI2_DMA_init() {
    // 0. Включили тактирование DMA
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

    DMA1_Stream4->CR &= ~DMA_SxCR_MSIZE;
    DMA1_Stream4->CR &= ~DMA_SxCR_PSIZE;
    // 2. Устанавливаем размер ячейки (8-бит(можно 16-бит, 32-бит))
    // - DMA_SxCR_MSIZE_0 - 16 бит
    // - DMA_SxCR_PSIZE_0 - 16 бит
    // - DMA_SxCR_MINC - инкримент
    // - (0x1 << 6) - из памяти в переферию 
    // - DMA_SxCR_CIRC - цикличная запись
    // - DMA_SxCR_TCIE - прерывания
    DMA1_Stream4->CR |= (/*DMA_SxCR_MSIZE_0 | DMA_SxCR_PSIZE_0 |*/ DMA_SxCR_MINC | (0x1 << 6)/* | DMA_SxCR_CIRC*/ | DMA_SxCR_TCIE);
	DMA1_Stream4->CR &= ~DMA_SxCR_HTIE;

    // 8. Количество элементов данных, подлежащих передаче	
    DMA1_Stream4->NDTR = SPI2_DMA1_SIZE;

    // 9. Задаем адрес переферии
    DMA1_Stream4->PAR = (uint32_t)(&SPI2->DR);

    // 10. Задаем адрес памяти
    DMA1_Stream4->M0AR = (uint32_t)&sp1_dma1_tx_buffer_0[0];

    // 11. Настройка прерываний
    NVIC_EnableIRQ(DMA1_Stream4_IRQn);
    NVIC_SetPriority(DMA1_Stream4_IRQn, 2);

    // 12. Включаем DMA
    DMA1_Stream4->CR |= DMA_SxCR_EN;
    // Включение DMA происходит только после того, как мы инициализировали GPIO и USART
    // И не надо его выключать и включать после, он уже работает в цикле.
}
#endif

void SPI1_transmit(uint16_t dt) {
    while(SPI1->SR & SPI_SR_BSY);  // Ждем, пока не освободится буфер передатчика
    SPI1->DR = dt;                 // Заполняем буфер передатчика
}

#endif  // SPI_H_
