#include "stftcb_spi.h"

static void SPI_GPIO_init();
static void SPI_SPI_init();
static void SPI_DMA_init();

void SPI_init() {
    SPI_GPIO_init();
    SPI_SPI_init();
    SPI_DMA_init();
}

static void SPI_SPI_init() {
    // 1. Включаем тактирование
    STFTCB_SPI_RCC;
    //RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    // 2. Настройка деления частоты
    STFTCB_SPI->CR1 |= STFTCB_SPI_BR;  // ();  // (SPI_CR1_BR_1 | SPI_CR1_BR_0);
    // 3. Сброс битов, которые могут испортить передачу
    STFTCB_SPI->CR1 &= ~(SPI_CR1_LSBFIRST | SPI_CR1_CPHA | SPI_CR1_CPOL);
    // 3. настрока DMA
	STFTCB_SPI->CR2 |= (SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);
    // 4. Настройка CR1
    // - SPI_CR1_MSTR - мастер мод
    // - SPI_CR1_SSM - Разрешает программное управление slave устройством
    // - SPI_CR1_SSI - Надо с SPI_CR1_SSM включать. Синхронизирует что то
    // - SPI_CR1_SPE - Запуск SPI
    // - SPI_CR1_DFF - 16-битный режим передачи, его включать после инициализации дисплея
	STFTCB_SPI->CR1 |= (SPI_CR1_MSTR | /*SPI_CR1_DFF |*/ SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE);
}

/** @brief SPI1_GPIO_init - инициализация GPIO для SPI
 * */
static void SPI_GPIO_init() {
    STFTCB_SPI_GPIO_SCK_RCC;
    STFTCB_SPI_GPIO_SCK_MODER;
    STFTCB_SPI_GPIO_SCK_AFR;

//    STFTCB_SPI_GPIO_MISO_RCC;
//    STFTCB_SPI_GPIO_MISO_MODER;
//    STFTCB_SPI_GPIO_MISO_AFR;

    STFTCB_SPI_GPIO_MOSI_RCC;
    STFTCB_SPI_GPIO_MOSI_MODER;
    STFTCB_SPI_GPIO_MOSI_AFR;
}

static void SPI_DMA_init() {
    STFTCB_SPI_DMA_RCC;
    //RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    // Отключаем DMA, для передачи
	STFTCB_SPI_DMA_SxCR->CR &= ~DMA_SxCR_EN;
	while ((STFTCB_SPI_DMA_SxCR->CR) & DMA_SxCR_EN){;}
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
	STFTCB_SPI_DMA_SxCR->CR = (STFTCB_SPI_DMA_SxCR_CH | DMA_SxCR_MINC | DMA_SxCR_DIR_0 |
                               DMA_SxCR_MSIZE_0 | DMA_SxCR_PSIZE_0 | DMA_SxCR_TCIE);
	//DMA2_Stream3->FCR = 0;
	//DMA2_Stream3->FCR &= ~DMA_SxFCR_DMDIS;

    STFTCB_SPI_DMA_CTCIF;  // Включаем прерывание после успешной передачи передачи
    //DMA2->LIFCR |= DMA_LIFCR_CTCIF3;  
	STFTCB_SPI_DMA_SxCR->PAR = (uint32_t)&STFTCB_SPI->DR;
	NVIC_EnableIRQ(STFTCB_SPI_DMA_IRQN);
    NVIC_SetPriority(STFTCB_SPI_DMA_IRQN, 2);
}

void SPI_1byte_mode_on() {
    STFTCB_SPI->CR1 &= ~SPI_CR1_SPE;
    STFTCB_SPI->CR1 &= ~SPI_CR1_DFF;
    STFTCB_SPI->CR1 |= SPI_CR1_SPE;
}

void SPI_2byte_mode_on() {
    STFTCB_SPI->CR1 &= ~SPI_CR1_SPE;
    STFTCB_SPI->CR1 |= SPI_CR1_DFF;
    STFTCB_SPI->CR1 |= SPI_CR1_SPE;
}

void SPI_transmit(uint16_t dt) {
    while(STFTCB_SPI->SR & SPI_SR_BSY);  // Ждем, пока не освободится буфер передатчика
    STFTCB_SPI->DR = dt;                 // Заполняем буфер передатчика
}


