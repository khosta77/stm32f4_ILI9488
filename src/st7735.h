#ifndef ST7735_H_
#define ST7735_H_

#include "./spi.h"
#include <stdbool.h>


/*** Redefine if necessary ***/
 
#define LCD_RST_Pin       GPIO_PIN_12
#define ST7735_RES_GPIO_Port GPIOB
#define LCD_CS_Pin        GPIO_PIN_15
#define ST7735_CS_GPIO_Port  GPIOB
#define LCD_RS_Pin        GPIO_PIN_14
#define ST7735_DC_GPIO_Port  GPIOB
 
// RESET | RST | RES
#define LCD_RST1  GPIOB->ODR |= GPIO_ODR_OD12;   // HAL_GPIO_WritePin(GPIOB, LCD_RST_Pin, GPIO_PIN_SET);
#define LCD_RST0  GPIOB->ODR &= ~GPIO_ODR_OD12;  // HAL_GPIO_WritePin(GPIOB, LCD_RST_Pin, GPIO_PIN_RESET);

// D/C | AO | RS
#define	LCD_DC1	GPIOB->ODR |= GPIO_ODR_OD14;  // HAL_GPIO_WritePin(GPIOB, LCD_RS_Pin, GPIO_PIN_SET)
#define	LCD_DC0 GPIOB->ODR &= ~GPIO_ODR_OD14;  // HAL_GPIO_WritePin(GPIOB, LCD_RS_Pin, GPIO_PIN_RESET)

// SPI_SS(CS)
#define	LCD_CS1	GPIOB->ODR |= GPIO_ODR_OD15;  // HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_SET);
#define	LCD_CS0	GPIOB->ODR &= ~GPIO_ODR_OD15;  // HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_RESET);
 
// AliExpress/eBay 1.8" display, default orientation
void MX_GPIO_Init() {
    RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOBEN);
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = LCD_RS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_CS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_RST_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
// call before initializing any SPI devices
void ST7735_Unselect();
 
void ST7735_Init();
void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
uint32_t ST7735_DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor);
void ST7735_DrawCharS(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size);
void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ST7735_FillScreen(uint16_t color);
void ST7735_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);
void ST7735_InvertColors(bool invert);
void ST7735_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void ST7735_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void ST7735_Drawaxes(uint16_t axisColor, uint16_t bgColor, char *xLabel,char *yLabel1, uint16_t label1Color, char *yLabel2, uint16_t label2Color,int32_t ymax, int32_t ymin);
void ST7735_PlotIncrement(void);
void ST7735_PlotPoint(int32_t data1, uint16_t color1);
 
void lcd7735_sendCmd(uint8_t cmd);
void lcd7735_sendData(uint8_t data);
//void lcd7735_senddata(uint8_t data);
void ST7735_Init_Command1();
void ST7735_Init_Command2();
void ST7735_Init_Command3();

#define DELAY 0x80
int32_t Ymax,Ymin,X;        // X goes from 0 to 127
int32_t Yrange; //YrangeDiv2;
int TimeIndex;
uint16_t PlotBGColor;

static void ST7735_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    lcd7735_sendCmd(ST7735_CASET);         // Column addr set
	lcd7735_sendData(0x00);                //        XS15 ~ XS8
	lcd7735_sendData(x0 + ST7735_XSTART);  // XSTART XS7 ~ XS0
	lcd7735_sendData(0x00);                //        XE15 ~ XE8
	lcd7735_sendData(x1 + ST7735_XSTART);  // XEND   XE7 ~ XE0

	lcd7735_sendCmd(ST7735_RASET);         // Row addr set
	lcd7735_sendData(0x00);
	lcd7735_sendData(y0 + ST7735_YSTART);  // YSTART
	lcd7735_sendData(0x00);
	lcd7735_sendData(y1 + ST7735_YSTART);  // YEND

	lcd7735_sendCmd(ST7735_RAMWR);
}
void ST7735_Init() {
    //ST7735_Select();
	LCD_CS0;
    //ST7735_Reset();
	LCD_RST0;
	MyDelay(7);
	LCD_RST1;

    //ST7735_ExecuteCommandList(init_cmds1);
	ST7735_Init_Command1();
    //ST7735_ExecuteCommandList(init_cmds2);
	ST7735_Init_Command2();
    //ST7735_ExecuteCommandList(init_cmds3);
	ST7735_Init_Command3();

    //ST7735_Unselect();
	LCD_CS1;
}

void ST7735_Init_Command1() {
	lcd7735_sendCmd(ST7735_SWRESET);		//  1: Software reset
	MyDelay(150);
	lcd7735_sendCmd(ST7735_SLPOUT);			//  2: Out of sleep mode
	MyDelay(500);
	lcd7735_sendCmd(ST7735_FRMCTR1);		//  3: Frame rate ctrl - normal mode
	lcd7735_sendData(0x01);							//     Rate = fosc/(1x2+40) * (LINE+2C+2D)
	lcd7735_sendData(0x2C);
	lcd7735_sendData(0x2D);
	lcd7735_sendCmd(ST7735_FRMCTR2);		//  4: Frame rate control - idle mode
	lcd7735_sendData(0x01);							//  Rate = fosc/(1x2+40) * (LINE+2C+2D)
	lcd7735_sendData(0x2C);
	lcd7735_sendData(0x2D);
	lcd7735_sendCmd(ST7735_FRMCTR3);		//  5: Frame rate ctrl - partial mode
	lcd7735_sendData(0x01);							//     Dot inversion mode
	lcd7735_sendData(0x2C);
	lcd7735_sendData(0x2D);
	lcd7735_sendData(0x01);							//     Line inversion mode
	lcd7735_sendData(0x2C);
	lcd7735_sendData(0x2D);
	lcd7735_sendCmd(ST7735_INVCTR);			//  6: Display inversion ctrl
	lcd7735_sendData(0x07);							//     No inversion
	lcd7735_sendCmd(ST7735_PWCTR1);			//  7: Power control
	lcd7735_sendData(0xA2);
	lcd7735_sendData(0x02);							//     -4.6V
	lcd7735_sendData(0x84);							//     AUTO mode
	lcd7735_sendCmd(ST7735_PWCTR2);			//  8: Power control
	lcd7735_sendData(0xC5);							//     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
	lcd7735_sendCmd(ST7735_PWCTR3);			//  9: Power control
	lcd7735_sendData(0x0A);							//     Opamp current small
	lcd7735_sendData(0x00);							//     Boost frequency
	lcd7735_sendCmd(ST7735_PWCTR4);			// 10: Power control
	lcd7735_sendData(0x8A);							//     BCLK/2, Opamp current small & Medium low
	lcd7735_sendData(0x2A);
	lcd7735_sendCmd(ST7735_PWCTR5);			// 11: Power control
	lcd7735_sendData(0x8A);
	lcd7735_sendData(0xEE);
	lcd7735_sendCmd(ST7735_VMCTR1);			// 12: Power control
	lcd7735_sendData(0x0E);
	lcd7735_sendCmd(ST7735_INVOFF);			// 13: Don't invert display
	lcd7735_sendCmd(ST7735_MADCTL);			// 14: Memory access control (directions)
	lcd7735_sendData(ST7735_ROTATION);	//     row addr/col addr, bottom to top refresh
	lcd7735_sendCmd(ST7735_COLMOD);			// 15: set color mode
	lcd7735_sendData(0x05);							//     16-bit color
}

void ST7735_Init_Command2(void)
{
	lcd7735_sendCmd(ST7735_CASET);			//  1: Column addr set
	lcd7735_sendData(0x00);							//     XSTART = 0
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x00);							//     XEND = 127
	lcd7735_sendData(0x7F);
	lcd7735_sendCmd(ST7735_RASET);			//  2: Row addr set
	lcd7735_sendData(0x00);							//     XSTART = 0
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x00);							//     XEND = 127
	lcd7735_sendData(0x7F);
}

void ST7735_Init_Command3(void)
{
	lcd7735_sendCmd(ST7735_GMCTRP1);  //  1: Magical unicorn dust
	lcd7735_sendData(0x02);
	lcd7735_sendData(0x1C);
	lcd7735_sendData(0x07);
	lcd7735_sendData(0x12);
	lcd7735_sendData(0x37);
	lcd7735_sendData(0x32);
	lcd7735_sendData(0x29);
	lcd7735_sendData(0x2D);
	lcd7735_sendData(0x29);
	lcd7735_sendData(0x25);
	lcd7735_sendData(0x2B);
	lcd7735_sendData(0x39);
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x01);
	lcd7735_sendData(0x03);
	lcd7735_sendData(0x10);
	lcd7735_sendCmd(ST7735_GMCTRN1);  //  2: Sparkles and rainbows
	lcd7735_sendData(0x03);
	lcd7735_sendData(0x1D);
	lcd7735_sendData(0x07);
	lcd7735_sendData(0x06);
	lcd7735_sendData(0x2E);
	lcd7735_sendData(0x2C);
	lcd7735_sendData(0x29);
	lcd7735_sendData(0x2D);
	lcd7735_sendData(0x2E);
	lcd7735_sendData(0x2E);
	lcd7735_sendData(0x37);
	lcd7735_sendData(0x3F);
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x02);
	lcd7735_sendData(0x10);
	lcd7735_sendCmd(ST7735_NORON);
	MyDelay(10);
	lcd7735_sendCmd(ST7735_DISPON);
	MyDelay(100);
}


void ST7735_PlotPoint(int32_t data1, uint16_t color1){
  data1 = ((data1 - Ymin)*100)/Yrange;
  if(data1 > 98){
    data1 = 98;
    color1 = ST7735_RED;
  }
  if(data1 < 0){
    data1 = 0;
    color1 = ST7735_RED;
  }
  ST7735_DrawPixel(TimeIndex + 11, 116 - data1, color1);
  ST7735_DrawPixel(TimeIndex + 11, 115 - data1, color1);
}

void ST7735_PlotIncrement(void){
  TimeIndex = TimeIndex + 1;
  if(TimeIndex > 99){
    TimeIndex = 0;
  }
  ST7735_DrawFastVLine(TimeIndex + 11, 17, 100, PlotBGColor);
}

void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
        return;

    LCD_CS0;

    ST7735_SetAddressWindow(x, y, x+1, y+1);
    uint8_t data[2];
		data[0] = color >> 8;
		data[1] = color & 0xFF;
		lcd7735_sendData(data[0]);
		lcd7735_sendData(data[1]);

    LCD_CS1;  //unselect
}
uint32_t ST7735_DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor){
  uint32_t count = 0;
  if(y>15) return 0;
  while(*pt){
    ST7735_DrawCharS(x*6, y*10, *pt, textColor, ST7735_BLACK, 1);
    pt++;
    x = x+1;
    if(x>20) return count;  // number of characters printed
    count++;
  }
  return count;  // number of characters printed
}
void ST7735_DrawCharS(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size){
  uint8_t line;
  int32_t i, j;
  if((x >= ST7735_WIDTH)            ||
     (y >= ST7735_HEIGHT)           ||
     ((x + 5 * size - 1) < 0) ||
     ((y + 8 * size - 1) < 0))
    return;

  for (i=0; i<6; i++ ) {
    if (i == 5)
      line = 0x0;
    else
      line = Font[(c*5)+i];
    for (j = 0; j<8; j++) {
      if (line & 0x1) {
        if (size == 1)
          ST7735_DrawPixel(x+i, y+j, textColor);
        else {
          ST7735_FillRectangle(x+(i*size), y+(j*size), size, size, textColor);
        }
      } else if (bgColor != textColor) {
        if (size == 1) // default size
          ST7735_DrawPixel(x+i, y+j, bgColor);
        else {  // big size
         ST7735_FillRectangle(x+i*size, y+j*size, size, size, bgColor);
        }
      }
      line >>= 1;
    }
  }
}

void ST7735_Drawaxes(uint16_t axisColor, uint16_t bgColor, char *xLabel,char *yLabel1, uint16_t label1Color, char *yLabel2, uint16_t label2Color,int32_t ymax, int32_t ymin)
	{
  int i;

  Ymax = ymax;
  Ymin = ymin;
  Yrange = Ymax - Ymin;
  TimeIndex = 0;
  PlotBGColor = bgColor;
	LCD_CS0;
  ST7735_FillRectangle(0, 0, 128, 160, bgColor);
  ST7735_DrawFastHLine(10, 140, 101, axisColor);
  ST7735_DrawFastVLine(10, 17, 124, axisColor);
  for(i=20; i<=110; i=i+10){
    ST7735_DrawPixel(i, 141, axisColor);
  }
  for(i=17; i<120; i=i+10){
    ST7735_DrawPixel(9, i, axisColor);
  }
  i = 50;
  while((*xLabel) && (i < 100)){
    ST7735_DrawCharS(i, 145, *xLabel, axisColor, bgColor, 1);
    i = i + 6;
    xLabel++;
  }
  if(*yLabel2){ // two labels
    i = 26;
    while((*yLabel2) && (i < 50)){
      ST7735_DrawCharS(0, i, *yLabel2, label2Color, bgColor, 1);
      i = i + 8;
      yLabel2++;
    }
    i = 82;
  }else{ // one label
    i = 42;
  }
  while((*yLabel1) && (i < 120)){
   ST7735_DrawCharS(0, i, *yLabel1, label1Color, bgColor, 1);
    i = i + 8;
    yLabel1++;
  }
	LCD_CS1;
}

void ST7735_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
  uint8_t hi = color >> 8, lo = color;

	LCD_CS0;
  // Rudimentary clipping
  if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
  if((x+w-1) >= ST7735_WIDTH)  w = ST7735_WIDTH-x;
  ST7735_SetAddressWindow(x, y, x+w-1, y);

  while (w--) {
    lcd7735_sendData(hi);
    lcd7735_sendData(lo);
  }
	LCD_CS1;
}

void ST7735_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
  uint8_t hi = color >> 8, lo = color;
	LCD_CS0;

  // Rudimentary clipping
  if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
  if((y+h-1) >= ST7735_HEIGHT) h = ST7735_HEIGHT-y;
  ST7735_SetAddressWindow(x, y, x, y+h-1);

  while (h--) {
    lcd7735_sendData(hi);
    lcd7735_sendData(lo);
  }
	LCD_CS1;
}

void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    // clipping
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
    if((x + w - 1) >= ST7735_WIDTH) w = ST7735_WIDTH - x;
    if((y + h - 1) >= ST7735_HEIGHT) h = ST7735_HEIGHT - y;

    LCD_CS0;
    ST7735_SetAddressWindow(x, y, x+w-1, y+h-1);
    LCD_DC1;
    for(y = h; y > 0; y--) {
        for(x = w; x > 0; x--) {
					lcd7735_sendData(color>>8);
					lcd7735_sendData(color);
        }
    }

		LCD_CS1;  //Unselect
}
void ST7735_FillScreen(uint16_t color) {
    ST7735_FillRectangle(0, 0, ST7735_WIDTH, ST7735_HEIGHT, color);
}
void ST7735_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data) {
int16_t skipC = 0;
  int16_t originalWidth = w;
  int i = w*(h - 1);

  if((x >= ST7735_WIDTH) || ((y - h + 1) >= ST7735_HEIGHT) || ((x + w) <= 0) || (y < 0)){
    return;
  }
  if((w > ST7735_WIDTH) || (h > ST7735_HEIGHT)){

    return;
  }
  if((x + w - 1) >= ST7735_WIDTH){
    skipC = (x + w) - ST7735_WIDTH;
    w = ST7735_WIDTH - x;
  }
  if((y - h + 1) < 0){
    i = i - (h - y - 1)*originalWidth;
    h = y + 1;
  }
  if(x < 0){
    w = w + x;
    skipC = -1*x;
    i = i - x;
    x = 0;
  }
  if(y >= ST7735_HEIGHT){
    h = h - (y - ST7735_HEIGHT + 1);
    y = ST7735_HEIGHT - 1;
  }

	LCD_CS0;  //Select

  ST7735_SetAddressWindow(x, y-h+1, x+w-1, y);

  for(y=0; y<h; y=y+1){
    for(x=0; x<w; x=x+1){

      lcd7735_sendData((uint8_t)(data[i] >> 8));

      lcd7735_sendData((uint8_t)data[i]);
      i = i + 1;
    }
    i = i + skipC;
    i = i - 2*originalWidth;
  }
	LCD_CS1;  //Unselect
}

void ST7735_InvertColors(bool invert) {
  //ST7735_Select();
	LCD_CS0;
  //ST7735_WriteCommand(invert ? ST7735_INVON : ST7735_INVOFF);
	lcd7735_sendCmd(invert ? ST7735_INVON : ST7735_INVOFF);
  LCD_CS1;  //Unselect
}

void lcd7735_sendCmd(uint8_t cmd) {  //uint8_t       //unsigned char
   LCD_DC0; //Set DC low
   SPI1_transmit(cmd);
}


void lcd7735_sendData(uint8_t data) {  //uint8_t      //unsigned char
   LCD_DC1;//Set DC HIGH
   SPI1_transmit(data);
}
/*
void lcd7735_senddata(uint8_t data) {
    SPI1_transmit(data);
}
*/
#if 0
//画笔颜色 rgb565
#define WHITE       0xFFFF
#define BLACK      	0x0000
#define BLUE       	0x001F
#define BRED        0xF81F
#define GRED 		0xFFE0
#define GBLUE		0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 		0xBC40 //棕色
#define BRRED 		0xFC07 //棕红色
#define GRAY  		0x8430 //灰色
#define GRAY0       0xEF7D
#define GRAY1       0x8410      	//灰色1      00000 000000 00000
#define GRAY2       0x4208
//GUI颜色

#define DARKBLUE      	 0x01CF	//深蓝色
#define LIGHTBLUE      	 0x7D7C	//浅蓝色
#define GRAYBLUE       	 0x5458 //灰蓝色
//以上三色为PANEL的颜色

#define LIGHTGREEN     	0x841F //浅绿色
#define LIGHTGRAY     0xEF5B //浅灰色(PANNEL)
#define LGRAY 			 		0xC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE      	0xA651 //浅灰蓝色(中间层颜色)
#define LBBLUE          0x2B12 //浅棕蓝色(选择条目的反色)

//定义LCD的尺寸
#define LCD_W 128
#define LCD_H 128

//定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转
#define USE_VERTICAL    0   /* 竖屏，排针在下面，左上角为坐标原点 */
#define USE_HORIZONTAL  1   /* 横屏，排针在右边，左上角为坐标原点 */

typedef struct
{
	uint8_t  width;			//LCD 宽度
	uint8_t  height;			//LCD 高度
	uint8_t  dir;			  //横屏还是竖屏控制：0，竖屏；1，横屏。
	uint8_t  wramcmd;		//开始写gram指令
	uint8_t  setxcmd;		//设置x坐标指令
	uint8_t  setycmd;		//设置y坐标指令
  uint8_t  xoffset;
  uint8_t	 yoffset;
	uint16_t id;				  //LCD ID
	uint16_t point_color;
	uint16_t back_color;
}_lcd_dev;


void Lcd_Init(void);
void Lcd_On(void);
void Lcd_Off(void);
void Lcd_Reset(void);
void Lcd_Clear(uint16_t Color);
void LCD_Fill(uint8_t sx, uint8_t sy, uint8_t ex, uint8_t ey, uint16_t color);
void LCD_Fill_lvgl(uint8_t sx, uint8_t sy, uint8_t ex, uint8_t ey, uint16_t *color);
void Lcd_WriteData(uint8_t Data);
void Lcd_WriteCmd(uint8_t Cmd);
void Lcd_WriteReg(uint8_t reg, uint8_t Data);
void Lcd_SetXY(uint8_t x, uint8_t y);
void Lcd_SetRegion(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end);
void Lcd_WriteData_16Bit(uint16_t Data);
void Lcd_Direction(uint8_t direction);

void Lcd_DrawPoint(uint8_t x, uint8_t y);
void Lcd_DrawPix(uint8_t x, uint8_t y, uint16_t color);
void Lcd_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

//创建一个LCD对象
_lcd_dev lcddev = {
	.setxcmd=0x2A,
	.setycmd=0x2B,
	.wramcmd=0x2C, 
	.point_color = RED,
	.back_color  = BLUE
};

/* LCD初始化 */
void Lcd_Init(void)
{	
	Lcd_Reset(); //LCD初始化之前先硬件复位
	Lcd_WriteCmd(0x11);//退出睡眠
	MyDelay(120);
	//ST7735R Frame Rate
	Lcd_WriteCmd(0xB1); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteCmd(0xB2); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteCmd(0xB3); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	
	Lcd_WriteCmd(0xB4); //Column inversion 
	Lcd_WriteData(0x07); 
	
	//ST7735R Power Sequence
	Lcd_WriteCmd(0xC0); 
	Lcd_WriteData(0xA2); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x84);
	
	Lcd_WriteCmd(0xC1); 
	Lcd_WriteData(0xC5); 

	Lcd_WriteCmd(0xC2); 
	Lcd_WriteData(0x0A); 
	Lcd_WriteData(0x00); 

	Lcd_WriteCmd(0xC3); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0x2A); 
	
	Lcd_WriteCmd(0xC4); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0xEE); 
	
	Lcd_WriteCmd(0xC5); //VCOM 
	Lcd_WriteData(0x0E); 	

	//ST7735R Gamma Sequence
	Lcd_WriteCmd(0xe0); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1a); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x18); 
	Lcd_WriteData(0x2f); 
	Lcd_WriteData(0x28); 
	Lcd_WriteData(0x20); 
	Lcd_WriteData(0x22); 
	Lcd_WriteData(0x1f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x23); 
	Lcd_WriteData(0x37); 
	Lcd_WriteData(0x00); 	
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x10); 

	Lcd_WriteCmd(0xe1); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x17); 
	Lcd_WriteData(0x33); 
	Lcd_WriteData(0x2c); 
	Lcd_WriteData(0x29); 
	Lcd_WriteData(0x2e); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x39); 
	Lcd_WriteData(0x3f); 
	Lcd_WriteData(0x00); 
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x03); 
	Lcd_WriteData(0x10);  
	
	Lcd_WriteCmd(0x2a);  //Column address set
	Lcd_WriteData(0x00); //X address start
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00); //X address end
	Lcd_WriteData(0x7f);  //127

	Lcd_WriteCmd(0x2b);  //Row address set
	Lcd_WriteData(0x00); //Y address start
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00); //Y address end
	Lcd_WriteData(0x9f);  //159
	
	Lcd_WriteCmd(0xF0); //Enable test command  
	Lcd_WriteData(0x01); 
	Lcd_WriteCmd(0xF6); //Disable ram power save mode 
	Lcd_WriteData(0x00); 
	
	Lcd_WriteCmd(0x3A); //65k mode  rgb:565
	Lcd_WriteData(0x05); 
	
	Lcd_Direction(USE_HORIZONTAL);  
  Lcd_Clear(lcddev.back_color);	
	Lcd_On();	
	MyDelay(100);
}

/* 亮屏 */
void Lcd_On(void)
{
  HAL_GPIO_WritePin(LCD_LED_GPIO_Port, LCD_LED_Pin, GPIO_PIN_SET);  /* 开启背光 */	
	Lcd_WriteCmd(0x29);
}

/* 息屏 */
void Lcd_Off(void)
{
	HAL_GPIO_WritePin(LCD_LED_GPIO_Port, LCD_LED_Pin, GPIO_PIN_RESET);  /* 关闭背光 */
	Lcd_WriteCmd(0x28);
}

/* LCD复位 */
void Lcd_Reset(void)
{
	/* 硬件复位 */
	HAL_GPIO_WritePin(LCD_NRST_GPIO_Port, LCD_NRST_Pin, GPIO_PIN_RESET);
	MyDelay(100);
	HAL_GPIO_WritePin(LCD_NRST_GPIO_Port, LCD_NRST_Pin, GPIO_PIN_SET);
	MyDelay(50);
	/* 软件复位 */
	Lcd_WriteCmd(0x01);
	MyDelay(50);
}

/* LCD使用指定颜色清屏 */
void Lcd_Clear(uint16_t Color)
{
	uint8_t i,m;
  Lcd_SetRegion(0,0,lcddev.width-1,lcddev.height-1);
  Lcd_WriteCmd(lcddev.wramcmd);
	for(i=0;i<lcddev.height;i++)
	{
		for(m=0;m<lcddev.width;m++)
		{	
			Lcd_WriteData_16Bit(Color);
		} 
	}	
}


void LCD_Fill(uint8_t sx, uint8_t sy, uint8_t ex, uint8_t ey, uint16_t color)
{  	
	uint8_t i,j;			
	uint8_t width=ex-sx+1;
	uint8_t height=ey-sy+1;
	Lcd_SetRegion(sx,sy,ex,ey);
	Lcd_WriteCmd(lcddev.wramcmd);
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		Lcd_WriteData_16Bit(color);
	}
}

void LCD_Fill_lvgl(uint8_t sx, uint8_t sy, uint8_t ex, uint8_t ey, uint16_t *color)
{
	uint8_t i,j;			
	uint8_t width=ex-sx+1;
	uint8_t height=ey-sy+1;
	Lcd_SetRegion(sx,sy,ex,ey);
	Lcd_WriteCmd(lcddev.wramcmd);
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			Lcd_WriteData_16Bit(*color);
      color++;
		}				
	}
}


void Lcd_WriteData(uint8_t Data)
{
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D_C_GPIO_Port, LCD_D_C_Pin, GPIO_PIN_SET);
	HAL_SPI_Transmit(&hspi1, &Data, 1, 0xff);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}


void Lcd_WriteData_16Bit(uint16_t Data)
{
	uint8_t high = 0;
	uint8_t low = 0;
	
	high = Data>>8;
	low = Data;
	
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D_C_GPIO_Port, LCD_D_C_Pin, GPIO_PIN_SET);
	HAL_SPI_Transmit(&hspi1, &high, 1, 0xff);                   
	HAL_SPI_Transmit(&hspi1, &low, 1, 0xff); 
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);  
}

void Lcd_WriteCmd(uint8_t Cmd)
{
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);   
	HAL_GPIO_WritePin(LCD_D_C_GPIO_Port, LCD_D_C_Pin, GPIO_PIN_RESET); 
	HAL_SPI_Transmit(&hspi1, &Cmd, 1, 0xff);                       
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

void Lcd_WriteReg(uint8_t reg, uint8_t Data)
{
	Lcd_WriteCmd(reg);
	Lcd_WriteData(Data);
}

void Lcd_SetXY(uint8_t x, uint8_t y)
{
	Lcd_SetRegion(x, y, x, y);
}

void Lcd_SetRegion(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end)
{
	Lcd_WriteCmd(lcddev.setxcmd);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start + lcddev.xoffset);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end + lcddev.xoffset);

	Lcd_WriteCmd(lcddev.setycmd);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start + lcddev.yoffset);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end + lcddev.yoffset);
}

void Lcd_Direction(uint8_t direction)
{
	switch(direction){		  
		case 0:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;	
			lcddev.xoffset=2;
			lcddev.yoffset=3;
			Lcd_WriteReg(0x36,(1<<3)|(1<<6)|(1<<7));//Memory data access control：BGR==1,MY==0,MX==0,MV==0   0xc0
		break;
		case 1:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			lcddev.xoffset=3;
			lcddev.yoffset=2;
			Lcd_WriteReg(0x36,(1<<3)|(1<<7)|(1<<5));//Memory data access control：BGR==1,MY==1,MX==0,MV==1   0xa0
		break;
		case 2:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;
      lcddev.xoffset=2;
			lcddev.yoffset=1;			
			Lcd_WriteReg(0x36,(1<<3)|(0<<6)|(0<<7));//Memory data access control：BGR==1,MY==0,MX==0,MV==0   0x00
		break;
		case 3:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			lcddev.xoffset=1;
			lcddev.yoffset=2;
			Lcd_WriteReg(0x36,(1<<3)|(0<<7)|(1<<6)|(1<<5));//Memory data access control：BGR==1,MY==1,MX==0,MV==1   0x60
		break;	
		default:break;
	}	
}

void Lcd_DrawPoint(uint8_t x, uint8_t y)
{
	Lcd_SetXY(x, y);
	Lcd_WriteCmd(lcddev.wramcmd);
	Lcd_WriteData_16Bit(lcddev.point_color);
}

void Lcd_DrawPix(uint8_t x, uint8_t y, uint16_t color)
{
	Lcd_SetXY(x, y);
	Lcd_WriteCmd(lcddev.wramcmd);
	Lcd_WriteData_16Bit(color);
}

void Lcd_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; 
	else if(delta_x==0)incx=0; 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ ) 
	{  
		Lcd_DrawPoint(uRow,uCol);
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}
#endif
#endif  // ST7735_H_
