#include "../system/include/cmsis/stm32f4xx.h"

void MyDelay(uint32_t time) {
	for (uint32_t t = 0; t < time; t++);
}

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

//===========================================================================================================
#if 1
#include <math.h>
//#include "GPIO.h"
//#include "pin_settings.h"
//#include "sys.h"
#include "stdlib.h"
//#include "tdelay.h"

//#include "spi.h"
//#include "spim.h"
//#include <stm32f4xx_hal.h>


//#define LCD_DC 		GPIO_PIN_6
//#define LCD_RES 	    GPIO_PIN_4




//#include "tdelay.h"

#define STM32

#define CONST_READ	*	//для stm32
#define Delay_ms	delay_ms
#define ON_PIN	on
#define OFF_PIN	off
typedef uint32_t _uchar_;
typedef uint32_t _uint_;
typedef int32_t _int_;


//---Define LCD---------------


#define MAX_HEIGHT_P	320   //Высота
#define MAX_WIDTH_P		480	  //ШИРИНА

#define SINGLE_IO_MODE 1


#define MAX_HEIGHT_L	MAX_WIDTH_P
#define MAX_WIDTH_L		MAX_HEIGHT_P

	//*** ili9341 ***********************************************
#define NOP     	0x00
#define SWRESET 	0x01
#define RDDID   	0x04// Read display identification information (04h)
#define RDDST   	0x09

#define SLPIN   	0x10
#define SLPOUT  	0x11
#define PTLON   	0x12 // Partial Mode ON
#define NORON   	0x13 // Normal Display Mode ON

#define RDMODE  	0x0A
#define RDMADCTL  	0x0B
#define RDPIXFMT  	0x0C
#define RDIMGFMT  	0x0D
#define RDSELFDIAG	0x0F

#define INVOFF  	0x20
#define INVON   	0x21
#define GAMMASET 	0x26
#define DISPOFF 	0x28
#define DISPON  	0x29

#define CASET   	0x2A
#define PASET   	0x2B
#define RAMWR   	0x2C
#define RAMRD   	0x2E

#define PTLAR    	0x30
#define MADCTL   	0x36
#define VSCRSADD 	0x37
#define PIXFMT   	0x3A//COLMOD

#define FRMCTR1 	0xB1
#define FRMCTR2 	0xB2
#define FRMCTR3 	0xB3
#define INVCTR  	0xB4
#define DFUNCTR 	0xB6

#define PWCTR1  	0xC0
#define PWCTR2  	0xC1
#define PWCTR3  	0xC2
#define PWCTR4  	0xC3
#define PWCTR5  	0xC4
#define VMCTR1  	0xC5
#define VMCTR2  	0xC7

#define RDID1   	0xDA
#define RDID2   	0xDB
#define RDID3   	0xDC
#define RDID4   	0xDD

#define GMCTRP1 	0xE0
#define GMCTRN1 	0xE1
#define ILI9488_SLPOUT  0x11
#define ILI9488_DISPON  0x29

#define ILI9488_CASET   0x2A
#define ILI9488_PASET   0x2B
#define ILI9488_RAMWR   0x2C
#define ILI9488_RAMRD   0x2E
#define ILI9488_MADCTL  0x36
#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

//---------------------------
void write16BitColor(uint16_t color);

void lcd_init(void); //	Функция инициализации дисплея.
void lcd_wr_data(uint8_t data);
// задать область. Возвращает 0 если успешно
_uchar_ lcd_win(_uint_ x1, _uint_ y1, _uint_ x2, _uint_ y2); // Определение области экрана для заполнения

// закрасить пиксель
void lcd_wr_pixel(_uint_ x, _uint_ y, uint16_t color); // вывод пиксела

// закрашенный прямоугольник. Конечные координаты x2 y2 задавать на 1 меньше! //возвращает 0 при удачном выполнении
uint8_t lcd_fill_rect(_uint_ x1, _uint_ y1, _uint_ x2, _uint_ y2, uint16_t color); // Функция заполнения прямоугольной области экрана заданым цветом

// незакрашенный прямоугольник.Конечные координаты x2 y2 задавать на 1 меньше!  //возвращает 0 при удачном выполнении
uint8_t lcd_rect(_uint_ x1, _uint_ y1, _uint_ x2, _uint_ y2, uint16_t color);

// Закрасить весь экран цветом
void lcd_fill_screen(uint16_t color);

// нарисовать линию
// void lcd_line(_uint_ x0, _uint_ y0, _uint_ x1, _uint_ y1, uint16_t color);
void lcd_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

// нарисовать закрашенный круг
void lcd_fill_circle(_uint_ pos_x, _uint_ pos_y, _uint_ r, uint16_t color);

// нарисовать незакрашенный круг
void lcd_draw_circle(_uint_ pos_x, _uint_ pos_y, _uint_ r, uint16_t color);


void lcd_draw_progressbar_h(_uint_ x,
	_uint_ y,
	_uint_ w,
	_uint_ h, //горизонтальный прогрессбар
	uint16_t clVoid,
	uint16_t clFull,
	uint16_t clBorder,
	_int_ Min,
	_int_ Max,
	_int_ Val);
void lcd_draw_progressbar_v(_uint_ x,
	_uint_ y,
	_uint_ w,
	_uint_ h, //вертикальный прогрессбар
	uint16_t clVoid,
	uint16_t clFull,
	uint16_t clBorder,
	_int_ Min,
	_int_ Max,
	_int_ Val);

// вывести буфер из флеш содержащий 16 битный цвет, 2 байта на пиксель MSB LSB
void lcd_fill_buff(_uint_ x1, _uint_ y1, _uint_ x2, _uint_ y2, const uint8_t *b);

//-----------------------------------------------------------
enum RtScr { PORTRET0, PORTRET180, LANDSHAVT0, LANDSHAVT180 };

void 	lcd_init_width_height(void); //востанвить максимальную ширину и высоту экрана
void 	set_rotate_screen(_uchar_ Rotate);
_uchar_	get_rotate_screen(void);
_uint_	get_MaxWidth(void);
_uint_	get_MaxHeight(void);
void 	set_MaxWidth(_uint_ Width); //задать ширину экрана
void 	set_MaxHeight(_uint_ Height); //задать высоту экрана

#include "stdlib.h"

//#include "delay.h"	 
//#include "SPI.h"

	   
_uint_ MaxWidth = MAX_WIDTH_P - 1, MaxHeight = MAX_HEIGHT_P - 1;
_uchar_ RotateScreen;


static void spi_init(void)  {
    SPI_Init();
#if 0
	SPI1->CR1 =
		(0 * SPI_CR1_CPHA) |        // Clock Phase
		(0 * SPI_CR1_CPOL) |        // Clock Polarity
		(1 * SPI_CR1_MSTR) |        // Master Selection

		(0 * SPI_CR1_BR) |          // BR[2:0] bits (Baud Rate Control)
		(0 * SPI_CR1_BR_0) |        // Bit 0
		(0 * SPI_CR1_BR_1) |        // Bit 1
		(0 * SPI_CR1_BR_2) |        // Bit 2

		(1 * SPI_CR1_SPE) |         // SPI Enable
		(0 * SPI_CR1_LSBFIRST) |    // Frame Format
		(1 * SPI_CR1_SSI) |         // Internal slave select				//программно на выводе NSS=1, режим мастера
		(1 * SPI_CR1_SSM) |         // Software slave management			//программное упр
		(0 * SPI_CR1_RXONLY) |      // Receive only
		(0 * SPI_CR1_DFF) |         // Data Frame Format
		(0 * SPI_CR1_CRCNEXT) |     // Transmit CRC next
		(0 * SPI_CR1_CRCEN) |       // Hardware CRC calculation enable
		(0 * SPI_CR1_BIDIOE) |      // Output enable in bidirectional mode	//
		(0 * SPI_CR1_BIDIMODE); // Bidirectional data mode enable		//прием/передача по одному проводу

	SPI1->CR2 =
		(0 * SPI_CR2_RXDMAEN) |   // Rx Buffer DMA Enable
		(0 * SPI_CR2_TXDMAEN) |   // Tx Buffer DMA Enable
		(0 * SPI_CR2_SSOE) |      // SS Output Enable
		(0 * SPI_CR2_ERRIE) |     // Error Interrupt Enable
		(0 * SPI_CR2_RXNEIE) |    // RX buffer Not Empty Interrupt Enable
		(0 * SPI_CR2_TXEIE); // Tx buffer Empty Interrupt Enable
#endif
}


static void spiGPIO_init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    GPIOC->MODER |= GPIO_MODER_MODER0_0;  // D/C
	GPIOC->MODER |= GPIO_MODER_MODER2_0;  // RESET

	GPIOC->ODR |= GPIO_ODR_OD0;
	GPIOC->ODR &= ~GPIO_ODR_OD2;
#if 0
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__GPIOA_CLK_ENABLE();	 
	__HAL_RCC_SPI1_CLK_ENABLE(); /* Peripheral clock enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = LCD_DC | LCD_RES; //pin : PA6 PA4
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA, LCD_RES, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LCD_DC, GPIO_PIN_SET);
#endif
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
 
//ili 9488 
void lcd_init(void) //set up display using predefined command sequence
{
	
	spiGPIO_init();
	spi_init();
	
	MyDelay(2);       //Delay_ms(1); 
	// Аппаратный сброс дисплея
    GPIOC->ODR |= GPIO_ODR_OD2;
	// HAL_GPIO_WritePin(GPIOA, LCD_RES, GPIO_PIN_RESET); // ON_PIN(LCD_RES);
	MyDelay(120);  //Delay_ms(120);

    GPIOC->ODR &= ~GPIO_ODR_OD2;
	//HAL_GPIO_WritePin(GPIOA, LCD_RES, GPIO_PIN_SET); //	OFF_PIN(LCD_RES);
	//HAL_Delay(120);  //Delay_ms(120);

	/// Программный сброс дисплея
	//lcd_wr_cmd(SWRESET);
	MyDelay(120);

	lcd_wr_cmd(0xE0);
	lcd_wr_data(0x00);
	lcd_wr_data(0x03);
	lcd_wr_data(0x09);
	lcd_wr_data(0x08);
	lcd_wr_data(0x16);
	lcd_wr_data(0x0A);
	lcd_wr_data(0x3F);
	lcd_wr_data(0x78);
	lcd_wr_data(0x4C);
	lcd_wr_data(0x09);
	lcd_wr_data(0x0A);
	lcd_wr_data(0x08);
	lcd_wr_data(0x16);
	lcd_wr_data(0x1A);
	lcd_wr_data(0x0F);

	lcd_wr_cmd(0XE1);
	lcd_wr_data(0x00);
	lcd_wr_data(0x16);
	lcd_wr_data(0x19);
	lcd_wr_data(0x03);
	lcd_wr_data(0x0F);
	lcd_wr_data(0x05);
	lcd_wr_data(0x32);
	lcd_wr_data(0x45);
	lcd_wr_data(0x46);
	lcd_wr_data(0x04);
	lcd_wr_data(0x0E);
	lcd_wr_data(0x0D);
	lcd_wr_data(0x35);
	lcd_wr_data(0x37);
	lcd_wr_data(0x0F);

	lcd_wr_cmd(0XC0); //Power Control 1
	lcd_wr_data(0x17); //Vreg1out
	lcd_wr_data(0x15); //Verg2out

	lcd_wr_cmd(0xC1); //Power Control 2
	lcd_wr_data(0x41); //VGH,VGL

	lcd_wr_cmd(0xC5); //Power Control 3
	lcd_wr_data(0x00);
	lcd_wr_data(0x12); //Vcom
	lcd_wr_data(0x80);

	lcd_wr_cmd(0x36); //Memory Access
	lcd_wr_data(0x48);

	lcd_wr_cmd(0x3A); // Interface Pixel Format
	lcd_wr_data(0x66); //18 bit

	lcd_wr_cmd(0XB0); // Interface Mode Control ПМРППРРТПОРО
	lcd_wr_data(0x80); //SDO NOT USE

	lcd_wr_cmd(0xB1); //Frame rate
	lcd_wr_data(0xA0); //60Hz

	lcd_wr_cmd(0xB4); //Display Inversion Control
	lcd_wr_data(0x02); //2-dot

	lcd_wr_cmd(0XB6); //Display Function Control  RGB/MCU Interface Control

	lcd_wr_data(0x02); //MCU
	lcd_wr_data(0x02); //Source,Gate scan dieection

	lcd_wr_cmd(0XE9); // Set Image Functio
	lcd_wr_data(0x00); // Disable 24 bit data

	lcd_wr_cmd(0xF7); // Adjust Control
	lcd_wr_data(0xA9);
	lcd_wr_data(0x51);
	lcd_wr_data(0x2C);
	lcd_wr_data(0x82); // D7 stream, loose

	lcd_wr_cmd(ILI9488_SLPOUT); //Exit Sleep

	MyDelay(110); //Delay_ms(110);

	lcd_wr_cmd(ILI9488_DISPON); //Display on
	 
//	// ************************************
//		// Sleep Out
//	lcd_wr_cmd(SLPOUT);
//	Delay_ms(100);
//
//	lcd_wr_cmd(DISPON);


}
 

 

void lcd_init_width_height(void) 
{
	if (RotateScreen < LANDSHAVT0) {
		MaxWidth = MAX_WIDTH_P - 1;
		MaxHeight = MAX_HEIGHT_P - 1;
	}
	else {
		MaxWidth = MAX_WIDTH_L - 1;
		MaxHeight = MAX_HEIGHT_L - 1;
	}
}

void write16BitColor(uint16_t color)
{
		
	uint8_t r = (color & 0xF800) >> 11;
	uint8_t g = (color & 0x07E0) >> 5;
	uint8_t b = color & 0x001F;
		
	r = (r * 255) / 31;
	g = (g * 255) / 63;
	b = (b * 255) / 31;
	if (SINGLE_IO_MODE)
	{
		lcd_wr_data(r);
		lcd_wr_data(g);
		lcd_wr_data(b);
	}
			 
		
}

//-------------------------------------------------------------------------
// Задать вращение дисплея
//-------------------------------------------------------------------------
void set_rotate_screen(_uchar_ r) 
{
	//_uchar_ madctl;
	
	_uchar_ rotation;
	//RotateScreen = Rotate;
	lcd_init_width_height();
	
	lcd_wr_cmd(ILI9488_MADCTL);
	
	rotation = r % 4; // can't be higher than 3
	
	switch (rotation) 
	{
	case 0:
		lcd_wr_data(MADCTL_MX | MADCTL_BGR);
		MaxWidth = MAX_WIDTH_P;
		MaxHeight = MAX_HEIGHT_P;
		break;
	case 1:
		lcd_wr_data(MADCTL_MV | MADCTL_BGR);
		MaxWidth = MAX_WIDTH_P;
		MaxHeight = MAX_HEIGHT_P;
		break;
	case 2:
		lcd_wr_data(MADCTL_MY | MADCTL_BGR);
		MaxWidth = MAX_WIDTH_P;
		MaxHeight = MAX_HEIGHT_P; //Высота
		break;
	case 3:
		lcd_wr_data(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
		MaxWidth = MAX_WIDTH_P;
		MaxHeight = MAX_HEIGHT_P;
		break;
	}
	
 
}

_uchar_ get_rotate_screen(void) {
	return RotateScreen;
}

_uint_ get_MaxWidth(void) {
	return MaxWidth;
}
_uint_ get_MaxHeight(void) {
	return MaxHeight;
}
void set_MaxHeight(_uint_ Height) {
	MaxHeight = Height;
}
void set_MaxWidth(_uint_ Width) {
	MaxWidth = Width;
}


// void check_win(_uint_ *x1, _uint_ *y1, _uint_ *x2, _uint_ *y2){
// _uint_
	// tmp=*x1;
	// if ( *x1 > *x2 ) {
		// *x1=*x2;
		// *x2=tmp;
	// }
	// tmp=*y1;
	// if ( *y1 > *y2 ) {
		// *y1=*y2;
		// *y2=tmp;
	// }	
// }
//-------------------------------------------------------------------------
// Определение области экрана для заполнения
// для задания области в 10 пикселей надо указываить 9, так как счет от нуля 10=0..9
_uchar_ lcd_win(_uint_ x1, _uint_ y1, _uint_ x2, _uint_ y2)
{

	// if (x1 > MaxWidth) return 1;
   // if (y1 > MaxHeight) return 1;
	if (x2 > MaxWidth) return 1;
	if (y2 > MaxHeight) return 1;
	
	lcd_wr_cmd(CASET);
	lcd_wr_data((uint8_t)((x1 & 0xFF00) >> 8));
	lcd_wr_data((uint8_t)(x1 & 0x00FF));
	lcd_wr_data((uint8_t)((x2 & 0xFF00) >> 8));
	lcd_wr_data((uint8_t)(x2 & 0x00FF));
	
	lcd_wr_cmd(PASET);
	lcd_wr_data((uint8_t)((y1 & 0xFF00) >> 8));
	lcd_wr_data((uint8_t)(y1 & 0x00FF));
	lcd_wr_data((uint8_t)((y2 & 0xFF00) >> 8));
	lcd_wr_data((uint8_t)(y2 & 0x00FF));

	lcd_wr_cmd(RAMWR);
	
	return 0;
}

//-------------------------------------------------------------------------
// вывод пиксела
void lcd_wr_pixel(_uint_ x, _uint_ y, uint16_t color)
{
	if (lcd_win(x, y, x, y)) return;
	
	//write16BitColor(color);
	lcd_wr_data((uint8_t)((color & 0xFF00) >> 8));
	lcd_wr_data((uint8_t)(color & 0x00FF));
}

//-------------------------------------------------------------------------
//нарисовать линию. Для вертикальных и горизонтальных использовать lcd_fill_rect
void lcd_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{

	int x = x1 - x0;
	int y = y1 - y0;
	int dx = abs(x), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;
	for (;;) {
		lcd_wr_pixel(x0, y0, color);
		e2 = 2*err;
		if (e2 >= dy) {
			if (x0 == x1) break;
			err += dy; x0 += sx;
		}
		if (e2 <= dx) {
			if (y0 == y1) break;
			err += dx; y0 += sy;
		}
	}
}

//-------------------------------------------------------------------------
// Функция заполнения прямоугольной области экрана заданным цветом
//Конечные координаты x2 y2 задавать на 1 меньше!
//возвращает 0 при удачном выполнении
uint8_t lcd_fill_rect(_uint_ x1, _uint_ y1, _uint_ x2, _uint_ y2, uint16_t color)
{
	// check_win(&x1, &y1, &x2, &y2);
	
	_uint_	tmp = x1;
	if (x1 > x2) {
		x1 = x2;
		x2 = tmp;
	}
	tmp = y1;
	if (y1 > y2) {
		y1 = y2;
		y2 = tmp;
	}
	
	if (lcd_win(x1, y1, x2, y2)) return 1;
#ifdef STM32
	for (uint32_t r = 0; r < (1 + y2 - y1)*(1 + x2 - x1); r++)
#else
		_uint_ y;
	_uint_ x;
	for (y = y1; y < y2 + 1; y++)
		for (x = x1; x < x2 + 1; x++)
			//for (uint16_t r=0; r<(1+y2-y1)*(1+x2-x1);r++)
#endif	
	{
		 
		//lcd_wr_data((uint8_t)((color & 0xFF00) >> 8));
		//lcd_wr_data((uint8_t)(color & 0x00FF));
		write16BitColor(color);
	
	}
	//Delay_ms(400);	
	return 0;
}

//-------------------------------------------------------------------------
// Рисование прямоугольника (не заполненного)
//
//-------------------------------------------------------------------------
/* MADCTL=0<<MADCTL_MV 		MADCTL=1<<MADCTL_MV
	0.0						0.0
	 -----> X				-----> Y
	|						|
	|						|
	v Y						v X

 */
//Конечные координаты x2 y2 задавать на 1 меньше! 
//возвращает 0 при удачном выполнении
uint8_t lcd_rect(_uint_ x1, _uint_ y1, _uint_ x2, _uint_ y2, uint16_t color)
{
	_uint_	tmp = x1;
	uint8_t err = 0;
	if (x1 > x2) {
		x1 = x2;
		x2 = tmp;
	}
	tmp = y1;
	if (y1 > y2) {
		y1 = y2;
		y2 = tmp;
	}
	
	err += lcd_fill_rect(x1, y1, x2, y1, color);
	err += lcd_fill_rect(x1, y2, x2, y2, color);
	err += lcd_fill_rect(x1, y1, x1, y2, color);
	err += lcd_fill_rect(x2, y1, x2, y2, color);
	return err;
}
 

//-------------------------------------------------------------------------
// Заполнение всего экрана одним цветом 
void lcd_fill_screen(uint16_t color)
{
	lcd_fill_rect(0, 0, MaxWidth, MaxHeight, color);
} 

//вывести буфер содержащий 16 битный цвет, 2 байта на пиксель MSB LSB
/* 
пример:
uint16_t y1[25] PROGMEM={
	GREEN,GREEN,GREEN,GREEN,GREEN,
	RED,RED,RED,RED,RED,
	BLUE,BLUE,BLUE,BLUE,BLUE,
	PURPLE,PURPLE,PURPLE,PURPLE,PURPLE,
	ORANGE,ORANGE,ORANGE,ORANGE,ORANGE
};
lcd_fill_buff(0,0,5,5, (const uint8_t *)&y1[0]);
 */
void lcd_fill_buff(_uint_ x1, _uint_ y1, _uint_ x2, _uint_ y2, const uint8_t *b)
{
	_uint_ y;
	_uint_ x;

	if (lcd_win(x1, y1, x2 - 1, y2 - 1)) return;
	lcd_wr_cmd(RAMWR);
	
	for (x = x1; x < x2 + 0; x++)
		for (y = y1; y < y2 + 0; y++)
		{
			//lcd_wr_data(CONST_READ(b + 1));
		   // lcd_wr_data(CONST_READ(b));
			write16BitColor(CONST_READ(b));
			write16BitColor(CONST_READ(b + 1));
			b += 2;
		}

}


// void TFT_Draw_Vertical_Line( uint16_t x, uint16_t y, uint16_t length,uint16_t color)
// {
	// TFT_Set_Column(x,x);
	// TFT_Set_Page(y,y+length);
	// lcd_wr_cmd(0x2c);
	// for(int i=0; i<length; i++)
	// lcd_wr_data16(color);
// }

void lcd_fill_circle(_uint_ pos_x, _uint_ pos_y, _uint_ r, uint16_t color)
{
	int x = -r, y = 0, err = 2 - 2*r, e2;
	do {

		// TFT_Draw_Vertical_Line(pos_x-x, pos_y-y, 2*y, color);
		// TFT_Draw_Vertical_Line(pos_x+x, pos_y-y, 2*y, color);
		
		lcd_rect(pos_x - x, pos_y - y, pos_x - x, pos_y - y + 2*y, color);
		lcd_rect(pos_x + x, pos_y - y, pos_x + x, pos_y - y + 2*y, color);

		e2 = err;
		if (e2 <= y) {
			err += ++y * 2 + 1;
			if (-x == y && e2 <= x) e2 = 0;
		}
		if (e2 > x) err += ++x * 2 + 1;
	} while (x <= 0);

}

void lcd_draw_circle(_uint_ pos_x, _uint_ pos_y, _uint_ r, uint16_t color)
{
	int x = -r, y = 0, err = 2 - 2*r, e2;
	do {
		lcd_wr_pixel(pos_x - x, pos_y + y, color);
		lcd_wr_pixel(pos_x + x, pos_y + y, color);
		lcd_wr_pixel(pos_x + x, pos_y - y, color);
		lcd_wr_pixel(pos_x - x, pos_y - y, color);
		e2 = err;
		if (e2 <= y) {
			err += ++y * 2 + 1;
			if (-x == y && e2 <= x) e2 = 0;
		}
		if (e2 > x) err += ++x * 2 + 1;
	} while (x <= 0);
}




void lcd_draw_progressbar_h(_uint_ x, _uint_ y, _uint_ w, _uint_ h, uint16_t clVoid, uint16_t clFull, 
                            uint16_t clBorder, _int_ Min, _int_ Max, _int_ Val) {
	_int_ scaleVal = ((Val - Min) * 100 + (Val - Min) / 2) / (Max - Min);
	_uint_ scale = (w*scaleVal + w / 2) / 100 + x;
	_uint_ xw = x + w;
	if (scaleVal > 0) {
		if (scale > xw) 
            scale = xw;
		lcd_fill_rect(x, y, scale, y + h, clFull);
		if (scale < xw)
			lcd_fill_rect(scale + 1, y, xw, y + h, clVoid);
	}
	else
		lcd_fill_rect(x, y, xw, y + h, clVoid);

	lcd_rect(x - 1, y - 1, x + w + 1, y + h + 1, clBorder);
}

void lcd_draw_progressbar_v(_uint_ x, _uint_ y, _uint_ w, _uint_ h, uint16_t clVoid, uint16_t clFull, 
                            uint16_t clBorder, _int_ Min, _int_ Max, _int_ Val) {
	_int_ scaleVal = ((Val - Min) * 100 + (Val - Min) / 2) / (Max - Min);
	_uint_ scale = (h*scaleVal + h / 2) / 100;
	if (scaleVal > 0) {
		if (scale > h) 
            scale = h;
		scale = h - scale;
		lcd_fill_rect(x, y + scale, x + w, y + h, clFull);
		if (scale)
			lcd_fill_rect(x, y, x + w, y + scale - 1, clVoid);
	}
	else
		lcd_fill_rect(x, y, x + w, y + h, clVoid);
	
	lcd_rect(x - 1, y - 1, x + w + 1, y + h + 1, clBorder);
}

#endif
//===========================================================================================================
#if 1
#define MENU_ITEM_STORAGE const
#define _RD(x) (x)
typedef uint32_t _uchar;
typedef uint32_t _uint;

// extern TSettingfontDot *LastFont;
extern _uint LastHeight; //последняя высота шрифта

// #define SPACE_CHAR_IN_FONT//Символ пробела есть в шрифте

#define WIDE_SPACE_CHAR 1
#define WIDE_SPACE 3

#define ALIGN_L 0 //вывод шрифта слева-направо
#define ALIGN_R 1 //вывод шрифта справо-налево

//шрифт генерируется программой GLCD Font Creator
typedef struct
{
	const uint8_t *font;
	uint8_t Width; //ширина
	uint8_t Height; //высота
	uint16_t Color;
	uint16_t BgColor;
	//uint8_t ofsetChar;//кол-во байт в вертикальной линии(Height/8+1)*на кол-во линий(Width)
} TSettingfont;

//шрифт генерируется программой TheDotFactory-0.1.4
typedef struct
{
	const uint8_t *font; //битовое представление символа
	const uint16_t *fontInfo; //0х_FF(width)_FF(ofset) ширина символа и его смещение(нач. поз.) в массиве const uint8_t *font
	uint8_t WidthNum; //макс ширина символа цифры
	uint8_t Height; //Высота
	uint16_t Color;
	uint16_t BgColor;
} TSettingfontDot;

// Определения для шрифта цифр
// .0123456789
#define CHAR_THK 10

/*
// Определения для шрифта "только цифры"
// .0123456789AVWm
#define	CHAR_THK	14
#define	CHAR_A		10
#define	CHAR_V		11
#define	CHAR_W		12
#define	CHAR_m		13
*/

//uint8_t char_cdot_out(uint16_t x, uint16_t y, uint8_t ch, uint8_t Width, TSettingfontDot *sF);
//-----------------------------------------------------------
//вывод строки из ОЗУ
//x y координаты
//*s буфер на вывод
//Size сколько символов вывести из буфера *s
//Width - для цифр, фиксированная ширина. Цифры меньше этой ширины будут дополнены до Width BgColor. Выключить дополнение Width=0.
//Align - 0 выравнивание по левому краю, 1 выравнивание по правому краю (задавать крайнюю правую координату)
//возвращает последнюю позицию по х
uint16_t str_dot_out(uint16_t x, uint16_t y, char *s, uint8_t Size, uint8_t Width, uint8_t Align, TSettingfontDot *sF);

// вывод строки из ОЗУ с завершающим символом \0. Возвращает последнюю ПОЗИЦИЮ ПО Х
uint16_t str_dot_out_n(uint16_t x, uint16_t y, char *s, uint8_t Width, uint8_t Align, TSettingfontDot *sF);

// вывод строки из флеш с завершающим символом \0. Возвращает последнюю ПОЗИЦИЮ ПО Х
uint16_t str_dot_out_pgm(uint16_t x, uint16_t y, const char *s, uint8_t Width, TSettingfontDot *sF);

// закрасить область высотой и BgColor цветом шрифта, возвращает  Width+1
uint16_t draw_space(uint16_t x, uint16_t y, uint16_t Width, TSettingfontDot *sF);

//-----------------------------------------------------------
// вывод символа, возвращает ширину символа в пикселях sF->Width
// для определения шрифт/"шрифт только цифры" вызывает ch_kod(ch)
int8_t char_dot_out(uint16_t x, uint16_t y, uint8_t ch, uint8_t Width, uint8_t aling, TSettingfontDot *sF);

// вывод символа, возвращает ширину символа sF->Width в пикселях (GLCDFontCreator.exe для моноширных шрифтов)
uint8_t char_out_vh(uint16_t x, uint16_t y, uint8_t ch, TSettingfont *sF);

//-----------------------------------------------------------
//узнать конечную позицию по х строки из ОЗУ
int16_t get_poz_x_str(uint16_t x, char *s, uint8_t Size, uint8_t Width, uint8_t Align, TSettingfontDot *sF);

//узнать конечную позицию по х строки из ОЗУ с завершающим символом \0.
int16_t get_poz_x_str_n(uint16_t x, char *s, uint8_t Width, uint8_t Align, TSettingfontDot *sF);

//узнать конечную позицию по х строки из флеш
uint16_t get_poz_x_str_pgm(uint16_t x, const char *s, uint8_t Width, TSettingfontDot *sF);
//-----------------------------------------------------------

// узнать ширину символа в пикселях (читается из шрифта)
uint8_t get_width_font_chr(uint8_t C, TSettingfontDot *sF);

// TSettingfontDot *LastFont;
_uint LastHeight; //последняя высота символа

//********************************************************************************
//внутренняя функция
//получить код символа для поиска в таблице
//шрифты начинаются с символа "!" Символа пробела нет.
#ifdef SPACE_CHAR_IN_FONT
#define _OF_SP 0
#else
#define _OF_SP 1
#endif

uint8_t ch_kod(uint8_t C)
{
	// if (C>32 && C<127) //если енглиш
	// C-=33;
	if (C >= 32 + _OF_SP && C < 127) //если енглиш
	C -= 32 + _OF_SP;
	else if(C >= 192) //русский
		// C-=98;
		C -= 97 + _OF_SP;
	else
	{
		//для набора символов ".0123456789"
		// C++;
		// if (C==CHAR_THK+1) C=0;

		if (C < CHAR_THK)
			C++;
		else if (C == CHAR_THK)
			C = 0;
	}
	return C;
}

//********************************************************************************

//закрасить область высотой и BgColor цветом шрифта
//Width == 0  - ширина 1 пиксель
//возвращает Width+1
uint16_t draw_space(uint16_t x, uint16_t y, uint16_t Width, TSettingfontDot *Sf)
{
	lcd_fill_rect(x, y, x + Width - 1, y + Sf->Height - 1, Sf->BgColor); //
	return Width;
}

/* 
// ********************************************************************************
//шрифт генерируется программой TheDotFactory-0.1.4
//шрифт уложен так - обход по высоте(столбцу) сверу вниз, слева на право 
// | /| /| вывод по столбцам (colum) сверху вниз, слева на право
// |/ |/ | сначало LSB
// v  v  v
//возвращает текущую ширину символа
uint8_t char_cdot_out(uint16_t x, uint16_t y, uint8_t ch, uint8_t Width, TSettingfontDot *sF){
uint8_t colum; 
uint8_t wlim;//ширина из таблицы инфо
uint16_t n;//смещение из таблицы инфо

	if (ch==CHAR_THK) Width=0;//если набор символов ".0123456789AVWm" то точку выводить не моноширно
	if (ch=='.') Width=0;//если полный набор символов то точку выводить не моноширно
	ch=ch_kod(ch);
	
	wlim=pgm_read_word(&sF->fontInfo[ch*2]);
	n=pgm_read_word(&sF->fontInfo[ch*2+1]);;
	LastHeight=sF->Height;
	if (lcd_win(x,y,  x+wlim-1, y+sF->Height-1)) return 0;

	for (uint8_t w=0; w<wlim;w++)	
		for (uint8_t i=0, b; i<sF->Height;i++){
			if (i%8==0) {
				colum=pgm_read_byte(&(sF->font[n++]));//читаем вертикальную линию
				b=1;
			}
			if (b & colum) {
				lcd_wr_data((uint8_t)((sF->Color & 0xFF00)>>8));
				lcd_wr_data((uint8_t) (sF->Color & 0x00FF));
			}
			else{
				lcd_wr_data((uint8_t)((sF->BgColor & 0xFF00)>>8));
				lcd_wr_data((uint8_t) (sF->BgColor & 0x00FF));
			}
			b<<=1;
		}
	
	if (wlim<Width){
		lcd_fill_rect(x+wlim,y,  x+wlim+(Width-(wlim-1)), y+sF->Height-1,sF->BgColor);
		wlim+=Width-wlim;
	}
	
	return wlim;
}
*/

//********************************************************************************
//ОСНОВНОЙ ШРИФТ
//шрифт генерируется программой TheDotFactory-0.1.4
//вывод символа
//шрифт уложен так - обход по строкам(row)  слева на право, сверу вниз
// ---> вывод по строкам (row) слева направо
//   /  сверху вниз
//  /   lsb first
// --->
//для программы от mrFox
//http://radiokot.ru/forum/viewtopic.php?p=3165151#p3165151
//обход байт горизонтально lsb, слева на право, сверу вниз

//Width - для цифр, фиксированная ширина. Цифры меньше этой ширины будут дополнены до Width BgColor. Выключить дополнение Width=0.
//Align - 0 выравнивание по левому краю, 1 выравнивание по правому краю (задавать крайнюю правую координату)
//возвращает текущую ширину СИМВОЛА
// volatile uint16_t vx[3];
int8_t char_dot_out(uint16_t x, uint16_t y, uint8_t ch, uint8_t Width, uint8_t aling, TSettingfontDot *sF)
{
	_uchar b, w, h, wlim, row = 0;
	_uint n;

	if (sF->fontInfo == 0)
	{
		//NULL если при инициализации fontInfo=0, то моноширный шрифт
		wlim = sF->WidthNum; //ширина символа
		n = (((sF->WidthNum - 1) / 8) + 1) * sF->Height * ch; //код символа в смещение в массиве sF->font
															  //например ширина 9 бит- 8бит+1бит =2байта (занимает горизонтальная строчка)
	}
	else
	{
		//шрифт генерируется программой TheDotFactory-0.1.4
		if (ch == CHAR_THK)
			Width = 0; //если набор символов ".0123456789AVWm" то точку выводить не моноширно
		if (ch == '.')
			Width = 0; //точку выводить не моноширно, иначе некрасиво)

		ch = ch_kod(ch);
		wlim = _RD(sF->fontInfo[ch * 2]); //ширина символа
		n = _RD(sF->fontInfo[ch * 2 + 1]); //код символа в смещение в массиве sF->font
	}

	LastHeight = sF->Height;

	if (aling == ALIGN_L)
	{
		if (lcd_win(x, y, x + wlim - 1, y + sF->Height - 1))
			return 0;
	}
	else
	{
		if (lcd_win(x - wlim + 1, y, x, y + sF->Height - 1))
			return 0;
	}

	for (h = 0; h < sF->Height; h++)
		for (w = 0, b = 1; w < wlim; w++)
		{
			if (w % 8 == 0)
			{
				row = _RD(sF->font[n++]); //читаем горизонтальную линию
				b = 1;
			}
			if (b & row)
			{
				write16BitColor(sF->Color);
				//lcd_wr_data((uint8_t)((sF->Color & 0xFF00) >> 8));
				//lcd_wr_data((uint8_t)(sF->Color & 0x00FF));
			}
			else
			{
				write16BitColor(sF->BgColor);
				//lcd_wr_data((uint8_t)((sF->BgColor & 0xFF00) >> 8));
				//lcd_wr_data((uint8_t)(sF->BgColor & 0x00FF));
			}
			b <<= 1;
		}

	if (aling == ALIGN_L)
	{
		if (wlim < Width)
		{
			if (!lcd_fill_rect(x + wlim, y, x + wlim + (Width - wlim) - 1, y + sF->Height - 1, sF->BgColor))
				wlim += Width - wlim;
		}
		return wlim;
	}
	else
	{
		if (wlim < Width)
		{
			if (!lcd_fill_rect((x - wlim) - (Width - wlim), y, (x - wlim), y + sF->Height - 1, sF->BgColor)) //GREEN//
			wlim += Width - wlim;
		}
		return -wlim;
	}
}
 
//************************
//используется - ОСНОВНОЙ ШРИФТ
//вывод строки с завершающим символом \0, шрифт читается из флеш
//Width ограничение мин ширины шрифта
//возвращает последнюю ПОЗИЦИЮ ПО Х
uint16_t str_dot_out_pgm(uint16_t x, uint16_t y, const char *s, uint8_t Width, TSettingfontDot *sF)
{
	uint8_t C;
#ifdef STM32
	C = *s++;
#else
	C = pgm_read_word(s++);
#endif
	while (C)
	{
		//cp_1251
#ifndef SPACE_CHAR_IN_FONT //в шрифтах нет символа пробела
		if (C == 32)
		{
			if (!lcd_fill_rect(x, y, x + WIDE_SPACE - 1, sF->Height - 1 + y, sF->BgColor)) //вывести пробел
			x += WIDE_SPACE; //задать ширину пробела
		}
		else
#endif
		{
			// x+=char_dot_out(x,y,C,Width,ALIGN_L,sF)+WIDE_SPACE_CHAR;
			// lcd_fill_rect(x-WIDE_SPACE_CHAR-0,y,x,sF->Height-1+y,sF->BgColor);//
			x += char_dot_out(x, y, C, Width, ALIGN_L, sF);
			if (!lcd_fill_rect(x, y, x + WIDE_SPACE_CHAR - 1, sF->Height - 1 + y, sF->BgColor))
				x += WIDE_SPACE_CHAR; //задать ширину между символами
		}
#ifdef STM32
		C = *s++;
#else
		C = pgm_read_word(s++);
#endif
	}

	return x;
}

//для строк с нулевым символом в конце
uint16_t str_dot_out_n(uint16_t x, uint16_t y, char *s, uint8_t Width, uint8_t Align, TSettingfontDot *sF)
{
	_uchar z = 0;
	while (s[z++]) ;
	return str_dot_out(x, y, s, z - 1, Width, Align, sF);
}
  

//вывод строки из ОЗУ
//x y координаты
//*s буфер на вывод
//Size сколько символов вывести из буфера *s
//Width - для цифр, фиксированная ширина. Цифры меньше этой ширины будут дополнены до Width BgColor. Выключить дополнение Width=0.
//Align - 0 выравнивание по левому краю, 1 выравнивание по правому краю (задавать крайнюю правую координату)
//возвращает последнюю позицию по х
uint16_t str_dot_out(uint16_t x, uint16_t y, char *s, uint8_t Size, uint8_t Width, uint8_t Align, TSettingfontDot *sF)
{
	uint8_t C;
	for (; Size; Size--)
	{
		if (Align == ALIGN_L)
		{
			C = *s++;
		}
		else
		{
			C = s[Size - 1];
		}
		//cp_1251
#ifndef SPACE_CHAR_IN_FONT //в шрифтах нет символа пробела
		if (C == 32)
		{
			if (Align == ALIGN_L)
			{
				if (!lcd_fill_rect(x, y, x + WIDE_SPACE - 1, sF->Height - 1 + y, sF->BgColor))
					x += WIDE_SPACE; //задать ширину пробела
			}
			else
			{
				if (!lcd_fill_rect(x - WIDE_SPACE + 1, y, x, sF->Height - 1 + y, sF->BgColor)) //GREEN
				x -= WIDE_SPACE; //задать ширину пробела
			}
		}
		else
#endif
		{
			x += char_dot_out(x, y, C, Width, Align, sF); //+WIDE_SPACE_CHAR;
			if (Align == ALIGN_L)
			{
				if (!lcd_fill_rect(x, y, x + WIDE_SPACE_CHAR - 1, sF->Height - 1 + y, sF->BgColor))
					x += WIDE_SPACE_CHAR; //задать ширину между символами
			}
			else
			{
				if (!lcd_fill_rect(x - WIDE_SPACE_CHAR + 1, y, x, sF->Height - 1 + y, sF->BgColor))
					x -= WIDE_SPACE_CHAR; //задать ширину между символами
			}
		}
	}

	return x;
}

//узнать ширину символа
uint8_t get_width_font_chr(uint8_t C, TSettingfontDot *sF)
{
	C = ch_kod(C);
	return _RD(sF->fontInfo[C * 2]);
}

//узнать ширину символа
int8_t get_width_ch(uint8_t C, uint8_t Width, uint8_t Align, TSettingfontDot *sF)
{
	uint8_t wlim;
	int8_t x = 0;
	//cp_1251
#ifndef SPACE_CHAR_IN_FONT //в шрифтах нет символа пробела
	if (C == 32)
	{
		if (Align == ALIGN_L)
			x += WIDE_SPACE; //задать ширину пробела
		else
			x -= WIDE_SPACE; //задать ширину пробела
	}
	else
#endif
	{
		if (C == CHAR_THK)
			Width = 0; //если набор символов ".0123456789AVWm" то точку выводить не моноширно
		if (C == '.')
			Width = 0; //если набор символов ".0123456789AVWm" то точку выводить не моноширно
		C = ch_kod(C);

		wlim = _RD(sF->fontInfo[C * 2]); //	wlim=pgm_read_word(&sF->fontInfo[C*2]);
		if (wlim < Width)
			wlim += Width - wlim;

		if (Align == ALIGN_L)
			x += WIDE_SPACE_CHAR + wlim; //задать ширину между символами
		else
			x -= WIDE_SPACE_CHAR + wlim; //задать ширину между символами
	}

	return x;
}

//узнать конечную позицию по х строки из ОЗУ (х+1 - область за строкой)
int16_t get_poz_x_str(uint16_t x, char *s, uint8_t Size, uint8_t Width, uint8_t Align, TSettingfontDot *sF)
{
	uint8_t C;
	for (; Size; Size--)
	{
		if (Align == ALIGN_L)
		{
			C = *s++;
		}
		else
		{
			C = s[Size - 1];
		}
		x += get_width_ch(C, Width, Align, sF);
	}

	return x;
}

//узнать конечную позицию по х строки из ОЗУ с завершающим символом \0.
int16_t get_poz_x_str_n(uint16_t x, char *s, uint8_t Width, uint8_t Align, TSettingfontDot *sF)
{
	_uchar z = 0;
	while (s[z++]) ;
	return get_poz_x_str(x, s, z - 1, Width, Align, sF);
}

//узнать конечную позицию по х строки из флеш (х+1 - область за строкой)
uint16_t get_poz_x_str_pgm(uint16_t x, const char *s, uint8_t Width, TSettingfontDot *sF)
{
	uint8_t C;
	while (1)
	{
#ifdef STM32
		C = *s++;
#else
		C = pgm_read_word(s++);
#endif
		if (C == '\0')
			break;
		x += get_width_ch(C, Width, ALIGN_L, sF);
	}

	return x;
}

/*/узнать ширину строки
uint16_t get_width_str2(uint16_t x, char *s, uint8_t Size, uint8_t Width, uint8_t Align, TSettingfontDot *sF){
uint8_t	wlim, C;	
	for (;Size; Size--)
	{
		if (Align==ALIGN_L) {
			C=*s++; 
		}else{
			C=s[Size-1];
			
		} 
		//cp_1251
		if (C==32) {
			if (Align==ALIGN_L) 
				x+=WIDE_SPACE; //задать ширину пробела
			else
				x-=WIDE_SPACE; //задать ширину пробела
		}
		else
		{
			if (C==CHAR_THK) Width=0;//если набор символов ".0123456789AVWm" то точку выводить не моноширно
			if (C=='.') Width=0;//если набор символов ".0123456789AVWm" то точку выводить не моноширно
			C=ch_kod(C);

			wlim=_RD(sF->fontInfo[C*2]);//	wlim=pgm_read_word(&sF->fontInfo[C*2]);
			if (wlim<Width)
				wlim+=Width-wlim;
			
			if (Align==ALIGN_L) 
				x+=WIDE_SPACE_CHAR+wlim; //задать ширину между символами
			else
				x-=WIDE_SPACE_CHAR+wlim; //задать ширину между символами
		}
	}

	return x;
}
*/

/*  GLCDFontCreator.exe для моноширных шрифтов
шрифты укладываются по столбцам, сверху вниз, например шрифт 5х17 Width=5 Height=17	
Width->		0   1   2   3   4
			v
1byte		|  /|  /|  /|  /|
2byte		| / | / | / | / |
3byte		|/  |/  |/  |/  |
			v	v	v	v	v
в третьем байте используется всего 3*8-17=1бит

а читать и выводить будем так	
		01234
1byte	----->
		   /	последовательное сканирование бит  
	      /		в каждом байте столбца
2byte	----->
		   /
	      /
3byte	----->	
читается 1 байт в нем 1 бит, 2ой байт 1 бит и т.д.
читается 1 байт в нем 2 бит, 2ой байт 2 бит и т.д.
читается 1 байт в нем 8 бит, 2ой байт 8 бит и т.д.
*/
// *
uint8_t char_out_vh(uint16_t x, uint16_t y, uint8_t ch, TSettingfont *sF)
{
	uint8_t ofw;
	if (sF->Height < 9)
		ofw = 1;
	else
		ofw = (sF->Height / 8 + 1);
	uint8_t ofset = ofw * sF->Width;
	uint8_t colum;
	uint16_t n = ch * ofset;

	uint8_t h, b, byte, w;

	if (lcd_win(x, y, x + sF->Width - 1, y + sF->Height - 1))
		return 0;
	LastHeight = sF->Height;

	for (h = 0, b = 1, byte = 255; h < sF->Height; h++)
	{
		if (h % 8 == 0)
		{
			b = 1;
			byte++;
		}
		for (w = 0; w < sF->Width; w++)
		{
			colum = _RD(sF->font[n + ofw * w + byte]); //читаем
			if (b & colum)
			{
				
				//write16BitColor(sF->Color);
				lcd_wr_data((uint8_t)((sF->Color & 0xFF00) >> 8));
				lcd_wr_data((uint8_t)(sF->Color & 0x00FF));
			}
			else
			{
				//write16BitColor(sF->BgColor);
				lcd_wr_data((uint8_t)((sF->BgColor & 0xFF00) >> 8));
				lcd_wr_data((uint8_t)(sF->BgColor & 0x00FF));
			}
		}
		b <<= 1;
	}
	return sF->Width;
}
// */
#endif
//===========================================================================================================
#if 1
#include "./font_15.h"
#endif
//===========================================================================================================

int main(void) {

    lcd_init();

    uint16_t color = 0x0000;
	while(1) {
        if (color == 0xFFFF)
            color = 0x0000;
        lcd_fill_screen(color);
        ++color;
	}
}


