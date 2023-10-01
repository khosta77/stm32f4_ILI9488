#ifndef SPI_H_
#define SPI_H_

#include "../system/include/cmsis/stm32f4xx.h"

void MyDelay(uint32_t time) {
	for (uint32_t t = 0; t < time; t++);
}

SPI_HandleTypeDef hspi1;

void SPI_GPIO_init();

/* SPI1 init function */
void MX_SPI1_Init(void) {
    SPI_GPIO_init();
#if 0
    __HAL_RCC_SPI1_CLK_ENABLE();  //
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;  // SPI_CR1_MSTR
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;  // Нули за этим кроятся
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;  // По умолчанию ноль
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;  // Полярность, ноль
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;  // Clock PHAse, фаза тактов, 0
    hspi1.Init.NSS = SPI_NSS_SOFT;  // SPI_CR1_SSM
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;  // Прескейлер оставляем базовым
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;  // формат фрейма в контексте порядка следования старшинства бит, 0
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;  //  FRame Format, формат фрейма, 0
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;  // Hardware CRC calculation ENable, 0
    hspi1.Init.CRCPolynomial = 10;  //
    HAL_SPI_Init(&hspi1);
#else
    // 1. Включаем тактирование
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    // 2. Настройка CR1
    // - SPI_CR1_MSTR - мастер мод
    // - SPI_CR1_SSM - Разрешает программное управление slave устройством
	SPI1->CR1 |= (SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI);
    SPI1->CRCPR = 10;
	SPI1->CR1 &= ~(SPI_CR1_LSBFIRST | SPI_CR1_CPHA | SPI_CR1_CPOL);
	SPI1->CR2 = 0x0000;
   	SPI1->CR1 |= SPI_CR1_SPE;

#if 0
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;  // SPI_CR1_MSTR
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;  // Нули за этим кроятся
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;  // По умолчанию ноль
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;  // Полярность, ноль
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;  // Clock PHAse, фаза тактов, 0
    hspi1.Init.NSS = SPI_NSS_SOFT;  // SPI_CR1_SSM
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;  // Прескейлер оставляем базовым
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;  // формат фрейма в контексте порядка следования старшинства бит, 0
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;  //  FRame Format, формат фрейма, 0
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;  // Hardware CRC calculation ENable, 0
    hspi1.Init.CRCPolynomial = 10;  //
#endif
#endif
}

void SPI_GPIO_init() {
    /**SPI1 GPIO Configuration
    PA6     ------> SPI1_MISO  // Нету
    PA7     ------> SPI1_MOSI
    PA5     ------> SPI1_SCK
    */
#if 1
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= (GPIO_MODER_MODER5_1 | /*GPIO_MODER_MODER6_1 |*/ GPIO_MODER_MODER7_1);
	GPIOA->AFR[0] |= ((GPIO_AFRL_AFSEL5_2 | GPIO_AFRL_AFSEL5_0) |
					 /* (GPIO_AFRL_AFSEL6_2 | GPIO_AFRL_AFSEL6_0) |*/
					  (GPIO_AFRL_AFSEL7_2 | GPIO_AFRL_AFSEL7_0));
	GPIOA->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR5_1 |/* GPIO_OSPEEDER_OSPEEDR6_1 |*/ GPIO_OSPEEDER_OSPEEDR7_1);
	GPIOA->PUPDR |= (GPIO_PUPDR_PUPD5_1 |/* GPIO_PUPDR_PUPD6_1 |*/ GPIO_PUPDR_PUPD7_1);
#else
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif
}


void SPI_BeginTransmission() {
	while ((SPI1->SR & SPI_SR_BSY));
	while (!(SPI1->SR & SPI_SR_TXE));
	//GPIOC->ODR &= ~GPIO_ODR_OD3;
}

void SPI_Write(uint8_t data) {
    while ((SPI1->SR & SPI_SR_BSY));
	while (!(SPI1->SR & SPI_SR_TXE));
	SPI1->DR = data;
}

void SPI_EndTransmission() {
	while ((SPI1->SR & SPI_SR_BSY));
	while (!(SPI1->SR & SPI_SR_TXE));
	//GPIOC->ODR |= GPIO_ODR_OD3;
}

void lcd_wr_data(uint8_t data) {
    // Ждем, пока не освободится буфер передатчика
    //while(!(SPI1->SR & SPI_SR_TXE));
    while(SPI1->SR & SPI_SR_BSY);
    // заполняем буфер передатчика
    SPI1->DR = data;
  /*
    if ((SPI1->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)  SPI1->CR1 |= SPI_CR1_SPE;
   // }


//	while (SPI1->SR & SPI_SR_BSY);  // ждать окончания передачи   
//	while (!(SPI1->SR & SPI_SR_TXE));

//    SPI_BeginTransmission();

//	while ((SPI1->SR & SPI_SR_TXE) == 0) ;//ждать освобождения буфера на передачу
	SPI1->DR = data; //запустить передачу байта
	//while ((SPI1->SR & SPI_SR_TXE) != 1);  // ждать освобождения буфера на передачу
	while ((SPI1->SR & SPI_SR_BSY) != 0);  // ждать окончания передачи  
    SPI1->CR1 &= ~SPI_CR1_SPE;
//	while ((SPI1->SR & SPI_SR_RXNE) == 0) ;//ждать "Receive buffer Not Empty" окончание приема
//	SPI1->DR; //reset SPI_SR_RXNE flag
//    SPI_EndTransmission();
*/
}

void SPI_WriteMulti(uint8_t* data, uint32_t size) {
	for (uint32_t i = 0; i < size; i++) {
		while ((SPI1->SR & SPI_SR_BSY));
		while (!(SPI1->SR & SPI_SR_TXE));
		SPI1->DR = data[i];
	}
}

uint8_t SPI_Read() {
	while ((SPI1->SR & SPI_SR_BSY));
	while (!(SPI1->SR & SPI_SR_RXNE));
	return (SPI1->DR);
}

#if 0
static void GPIO_Init() {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODER3_0;
	GPIOC->ODR |= GPIO_ODR_OD3;

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER |= GPIO_MODER_MODER12_0;
    GPIOD->ODR &= ~GPIO_ODR_OD12;
    GPIOD->MODER |= GPIO_MODER_MODER13_0;
    GPIOD->ODR &= ~GPIO_ODR_OD13;
}

#define SPI_PRESCALER 2

void SPI_Init() {
	//// GPIO
    GPIO_Init();
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= (GPIO_MODER_MODER5_1 | GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1);
	GPIOA->AFR[0] |= ((GPIO_AFRL_AFSEL5_2 | GPIO_AFRL_AFSEL5_0) |
					  (GPIO_AFRL_AFSEL6_2 | GPIO_AFRL_AFSEL6_0) |
					  (GPIO_AFRL_AFSEL7_2 | GPIO_AFRL_AFSEL7_0));
	GPIOA->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR5_1 | GPIO_OSPEEDER_OSPEEDR6_1 | GPIO_OSPEEDER_OSPEEDR7_1);
	GPIOA->PUPDR |= (GPIO_PUPDR_PUPD5_1 | GPIO_PUPDR_PUPD6_1 | GPIO_PUPDR_PUPD7_1);

	//// SPI
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	SPI1->CR1 |= SPI_CR1_MSTR;
	SPI1->CR1 |= (SPI_CR1_SSI | SPI_CR1_SSM);

    if(SPI_PRESCALER == 2) SPI1->CR1 &= ~(SPI_CR1_BR);
	if(SPI_PRESCALER == 4) SPI1->CR1 |= SPI_CR1_BR_0;
	if(SPI_PRESCALER == 8) SPI1->CR1 |= SPI_CR1_BR_1;
	if(SPI_PRESCALER == 16) SPI1->CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1;
	if(SPI_PRESCALER == 32) SPI1->CR1 |= SPI_CR1_BR_2;
	if(SPI_PRESCALER == 64) SPI1->CR1 |= SPI_CR1_BR_2 | SPI_CR1_BR_0;
	if(SPI_PRESCALER == 128) SPI1->CR1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1;
	if(SPI_PRESCALER == 256) SPI1->CR1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0;

	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;
	SPI1->CR1 &= ~SPI_CR1_CPHA;
	SPI1->CR2 = 0x0000;
	SPI1->CR1 |= SPI_CR1_SPE;
}

void SPI_BeginTransmission() {
	while ((SPI1->SR & SPI_SR_BSY));
	while (!(SPI1->SR & SPI_SR_TXE));
	GPIOC->ODR &= ~GPIO_ODR_OD3;
}

void SPI_Write(uint8_t data) {
    while ((SPI1->SR & SPI_SR_BSY));
	while (!(SPI1->SR & SPI_SR_TXE));
	SPI1->DR = data;
}

void SPI_WriteMulti(uint8_t* data, uint32_t size) {
	for (uint32_t i = 0; i < size; i++) {
		while ((SPI1->SR & SPI_SR_BSY));
		while (!(SPI1->SR & SPI_SR_TXE));
		SPI1->DR = data[i];
	}
}

void SPI_EndTransmission() {
	while ((SPI1->SR & SPI_SR_BSY));
	while (!(SPI1->SR & SPI_SR_TXE));
	GPIOC->ODR |= GPIO_ODR_OD3;
}

uint8_t SPI_Read() {
	while ((SPI1->SR & SPI_SR_BSY));
	while (!(SPI1->SR & SPI_SR_RXNE));
	return (SPI1->DR);
}

// CS – выбор чипа. Активный уровень низкий.
// DC – данные (1) или команда(0). Возможны и иные обозначения этого вывода – A0, RS.
// смотреть Figure 240. 
// TXE/RXNE/BSY behavior in Master / full-duplex mode (BIDIMODE=0 and RXONLY=0) in case of continuous transfers
void lcd_wr_cmd(uint8_t command) {
	//  while((SPI1->SR & SPI_SR_TXE)==0);//ждать освобождения буфера на передачу
	while (SPI1->SR & SPI_SR_BSY) ;//ждать окончания передачи   
	//задержки нужны , чтобы не дать off(LCD_DC) на незаконченную передачу
    SPI_BeginTransmission();

	//off(LCD_DC); 
	//HAL_GPIO_WritePin(GPIOA, LCD_DC, GPIO_PIN_RESET); //отправляем команду
    GPIOC->ODR &= ~GPIO_ODR_OD0;	
	
	SPI1->DR; //pre clear SPI_SR_RXNE flag
	SPI1->DR = command; //запустить передачу байта

	while ((SPI1->SR & SPI_SR_RXNE) == 0) ;//ждать "Receive buffer Not Empty" окончание приема
	SPI1->DR; //clear SPI_SR_RXNE flag

    SPI_EndTransmission();
	//HAL_GPIO_WritePin(GPIOA, LCD_DC, GPIO_PIN_SET); //on(LCD_DC); //переключаем на данные	
	GPIOC->ODR |= GPIO_ODR_OD0;
}

//inline
void lcd_wr_data(uint8_t data) {
	while (SPI1->SR & SPI_SR_BSY) ;//ждать окончания передачи   
    SPI_BeginTransmission();

	while ((SPI1->SR & SPI_SR_TXE) == 0) ;//ждать освобождения буфера на передачу
	SPI1->DR = data; //запустить передачу байта

	while ((SPI1->SR & SPI_SR_RXNE) == 0) ;//ждать "Receive buffer Not Empty" окончание приема
	SPI1->DR; //reset SPI_SR_RXNE flag
    SPI_EndTransmission();
}
#endif

#endif  // SPI_H_
