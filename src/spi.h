#ifndef SPI_H_
#define SPI_H_

#include "../system/include/cmsis/stm32f4xx.h"

void MyDelay(uint32_t time) {
	for (uint32_t t = 0; t < time; t++);
}

SPI_HandleTypeDef hspi1;

/* SPI1 init function */
void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
 //   Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
    PB3     ------> SPI1_SCK
    */
    GPIO_InitStruct.Pin = /*GPIO_PIN_6;|*/GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
    PB3     ------> SPI1_SCK
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_6|GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3);
  }
}

/*
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_4
#define LCD_CS_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define LCD_NRST_Pin GPIO_PIN_13
#define LCD_NRST_GPIO_Port GPIOB
#define LCD_LED_Pin GPIO_PIN_14
#define LCD_LED_GPIO_Port GPIOB
#define LCD_D_C_Pin GPIO_PIN_15
#define LCD_D_C_GPIO_Port GPIOB
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
*/

#if 0

void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_CS_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_NRST_Pin|LCD_LED_Pin|LCD_D_C_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = LCD_CS_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = LCD_NRST_Pin|LCD_LED_Pin|LCD_D_C_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}
#endif
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
