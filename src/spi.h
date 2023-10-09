#ifndef SPI_H_
#define SPI_H_

#include "../system/include/cmsis/stm32f4xx.h"
#include "../system/include/stm32f4-hal/stm32f4xx_hal.h"

void SPI1_init();
static void SPI1_GPIO_init();
static void SPI1_SPI_init();
static void SPI1_DMA_init();

void SPI_1byte_mode_on();
void SPI_2byte_mode_on();

void SPI1_transmit(uint16_t dt);

void SPI1_init() {
    SPI1_GPIO_init();
    SPI1_SPI_init();
    SPI1_DMA_init();
}

static void SPI1_SPI_init() {
    // 1. Включаем тактирование
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    // *. Что то мутное, ни на что не влияет
//  SPI1->CRCPR = 10;
    // *. Сбросим биты настрой в CR1
    //SPI1->CR1 |= (SPI_CR1_BR_1 | SPI_CR1_BR_0);
    SPI1->CR1 &= ~(SPI_CR1_LSBFIRST | SPI_CR1_CPHA | SPI_CR1_CPOL);
    // *. Сбросим наверняка CR2
	SPI1->CR2 |= SPI_CR2_TXDMAEN;
    // 2. Настройка CR1
    // - SPI_CR1_MSTR - мастер мод
    // - SPI_CR1_SSM - Разрешает программное управление slave устройством
    // - SPI_CR1_SSI - Надо с SPI_CR1_SSM включать. Синхронизирует что то
    // - SPI_CR1_SPE - Запуск SPI
    // - SPI_CR1_DFF - 16-битный режим передачи, его включать после инициализации дисплея
	SPI1->CR1 |= (SPI_CR1_MSTR | /*SPI_CR1_DFF |*/ SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE);
}

/** @brief SPI1_GPIO_init - инициализация GPIO для SPI1 так как нам надо только отправлять данные в режиме \
 *                          Master, то надо инициализировать только две ножки, тактирование(SPI_SCK) и \
 *                          Master Out Slave In (SPI_MOSI).
 *                          PA5 ---> SPI1_SCK
 *                          PA7 ---> SPI1_MOSI
 * */
static void SPI1_GPIO_init() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= (GPIO_MODER_MODER5_1 | GPIO_MODER_MODER7_1);
	GPIOA->AFR[0] |= ((GPIO_AFRL_AFSEL5_2 | GPIO_AFRL_AFSEL5_0) | (GPIO_AFRL_AFSEL7_2 | GPIO_AFRL_AFSEL7_0));
	GPIOA->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR5_1 | GPIO_OSPEEDER_OSPEEDR7_1);
	GPIOA->PUPDR |= (GPIO_PUPDR_PUPD5_1 | GPIO_PUPDR_PUPD7_1);
}

static void SPI1_DMA_init() {
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    // Отключаем DMA, для передачи
	DMA2_Stream3->CR &= ~DMA_SxCR_EN;
	while ((DMA2_Stream3->CR) & DMA_SxCR_EN){;}
    // Настройка контрольных регистров
    // - (0x03 << 25)     - настройка DMA канала, для SP1_TX
    // - DMA_SxCR_MINC    - Memory INCrement mode
    // - DMA_SxCR_DIR_0   - память-периферия
    // // Так как SPI в режиме 16-бит, то и DMA тоже должен быть на это настроен
    // - DMA_SxCR_MSIZE_0 - полуслово (16 бит)
    // - DMA_SxCR_PSIZE_0 - полуслово (16 бит)
    // - DMA_SxCR_TCIE    - Прерывания по завершению передачи
    // // Дополнительные прерывания, не и использую
    // - DMA_SxCR_CIRC    - Режим кольцевого буфера разрешен
    // - DMA_SxCR_HTIE    -
    // - DMA_SxCR_TEIE    -
    // - DMA_SxCR_DMEIE   -
	DMA2_Stream3->CR = ((0x03 << 25) | DMA_SxCR_MINC | DMA_SxCR_DIR_0 | DMA_SxCR_MSIZE_0 | DMA_SxCR_PSIZE_0 | DMA_SxCR_TCIE);
	//DMA2_Stream3->FCR = 0;
	//DMA2_Stream3->FCR &= ~DMA_SxFCR_DMDIS;

    DMA2->LIFCR |= DMA_LIFCR_CTCIF3;  // (DMA_LIFCR_CTCIF3 | DMA_LIFCR_CHTIF3 | DMA_LIFCR_CTEIF3 | DMA_LIFCR_CDMEIF3 | DMA_LIFCR_CFEIF3);
	DMA2_Stream3->PAR = (uint32_t)&SPI1->DR;
//	DMA2_Stream3->M0AR = (uint32_t)&stftcb_array_tx[0];
//	DMA2_Stream3->NDTR = STFTCB_SIZE;
//	DMA2_Stream3->CR |= DMA_SxCR_EN;

	NVIC_EnableIRQ(DMA2_Stream3_IRQn);
    NVIC_SetPriority(DMA2_Stream3_IRQn, 2);
}

void SPI_1byte_mode_on() {
    SPI1->CR1 &= ~SPI_CR1_SPE;
    SPI1->CR1 &= ~SPI_CR1_DFF;
    SPI1->CR1 |= SPI_CR1_SPE;
}

void SPI_2byte_mode_on() {
    SPI1->CR1 &= ~SPI_CR1_SPE;
    SPI1->CR1 |= SPI_CR1_DFF;
    SPI1->CR1 |= SPI_CR1_SPE;
}

void SPI1_transmit(uint16_t dt) {
    while(SPI1->SR & SPI_SR_BSY);  // Ждем, пока не освободится буфер передатчика
    SPI1->DR = dt;                 // Заполняем буфер передатчика
}

#endif  // SPI_H_
