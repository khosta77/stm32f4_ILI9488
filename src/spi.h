#ifndef SPI_H_
#define SPI_H_

#include "../system/include/cmsis/stm32f4xx.h"

void SPI1_init();
void SPI1_GPIO_init();
void SPI1_SPI_init();

void SPI1_transmit(uint8_t dt);

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
	SPI1->CR1 |= (SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE);
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

void SPI1_transmit(uint8_t dt) {
    while(SPI1->SR & SPI_SR_BSY);  // Ждем, пока не освободится буфер передатчика
    SPI1->DR = dt;                 // Заполняем буфер передатчика
}

#endif  // SPI_H_
