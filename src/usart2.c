#include "./usart2.h"

uint8_t usart2_mrk = 0x00;
uint8_t usart2_rx_array[USART_SIZE];
uint8_t usart2_tx_array[USART_SIZE];

static void GPIO_init() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= (GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1);
    GPIOA->AFR[0] |= (0x77 << 8);
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER |= (GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0);
}

static void USART_init() {
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    USART2->BRR = MYBRR;
    USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE);
    USART2->CR3 |= (USART_CR3_DMAR | USART_CR3_DMAT);
    USART2->CR1 |= USART_CR1_UE;
}


static void DMA_init() {
    // 0. Включили тактирование DMA
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

    DMA1_Stream6->CR &= ~DMA_SxCR_EN;
    while ((DMA1_Stream6->CR) & DMA_SxCR_EN){;}
    DMA1_Stream5->CR &= ~DMA_SxCR_EN;
    while ((DMA1_Stream5->CR) & DMA_SxCR_EN){;}

    // 1. Задание настройки
    // - (0x4 << 25) - 4-ый канал
    // - DMA_SxCR_MINC - увеличенный объем памяти
    // - DMA_SxCR_TCIE - прерывания по приему/передачи
    // - DMA_SxCR_CIRC (for rx) - циклическая работа
    DMA1_Stream6->CR |= ((0x4 << 25) | DMA_SxCR_MINC | DMA_SxCR_TCIE);
    DMA1_Stream5->CR |= ((0x4 << 25) | DMA_SxCR_MINC | DMA_SxCR_TCIE | DMA_SxCR_CIRC);

    // 2. Устанавливаем размер ячейки 8-бит и периферийных данных 8-бит
    DMA1_Stream6->CR &= ~(DMA_SxCR_MSIZE | DMA_SxCR_PSIZE);
    DMA1_Stream5->CR &= ~(DMA_SxCR_MSIZE | DMA_SxCR_PSIZE);

    // 3. Включаем режим работы
    DMA1_Stream6->CR |= (0x01<<6);  // Из памяти в перефирию
    DMA1_Stream5->CR &= ~(3UL<<6);  // Из переферии в память

    // 4. Количество элементов данных, подлежащих передаче
    DMA1_Stream6->NDTR = SIZE_CMD;
    DMA1_Stream5->NDTR = SIZE_CMD;

    // 5. Задаем адрес переферии
    DMA1_Stream6->PAR = (uint32_t)(&USART2->DR);
    DMA1_Stream5->PAR = (uint32_t)(&USART2->DR);

    // 6. Задаем адрес памяти
    DMA1_Stream6->M0AR = (uint32_t)&usart2_tx_array[0];
    DMA1_Stream5->M0AR = (uint32_t)&usart2_rx_array[0];

    // 7. Настройка прерываний
    NVIC_EnableIRQ(DMA1_Stream6_IRQn);
    NVIC_SetPriority(DMA1_Stream6_IRQn, 5);
    NVIC_EnableIRQ(DMA1_Stream5_IRQn);
    NVIC_SetPriority(DMA1_Stream5_IRQn, 4);

    // 8. Включаем DMA на прием данных
    DMA1_Stream5->CR |= DMA_SxCR_EN;
}

void USART2_init() {
    SystemCoreClockUpdate();
    GPIO_init();
    USART_init();
    DMA_init();
}


