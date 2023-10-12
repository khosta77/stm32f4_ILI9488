#ifndef ST7735_H_
#define ST7735_H_

#include "./stftcb.h"
#include "./st7735_register.h"
#include "./st7735_font.h"
#include <stdbool.h>
#include <stdlib.h> 
// call before initializing any SPI devices

void MyDelay(uint32_t time) {
	for (uint32_t t = 0; t < time; t++);
}

void ST7735_Init();
//void ST7735_DrawPixel(uint8_t x, uint8_t y, uint16_t color);
//uint32_t ST7735_DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor);
//void ST7735_DrawCharS(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size);
//void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
//void ST7735_FillScreen(uint16_t color);
//void ST7735_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);
//void ST7735_InvertColors(bool invert);
//void ST7735_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
//void ST7735_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
//void ST7735_Drawaxes(uint16_t axisColor, uint16_t bgColor, char *xLabel,char *yLabel1, uint16_t label1Color, char *yLabel2, uint16_t label2Color,int32_t ymax, int32_t ymin);
//void ST7735_PlotIncrement(void);
//void ST7735_PlotPoint(int32_t data1, uint16_t color1);
 
void ST7735_Init_Command1();
void ST7735_Init_Command2();
void ST7735_Init_Command3();

#define DELAY 0x80
//int32_t Ymax, Ymin, X;        // X goes from 0 to 127
//int32_t Yrange; //YrangeDiv2;
//int TimeIndex;
//uint16_t PlotBGColor;

void ST7735_Init() {
	STFTCB_CS_OFF;
	STFTCB_RESET_OFF;
	MyDelay(7);
	STFTCB_RESET_ON;

	ST7735_Init_Command1();
	ST7735_Init_Command2();
	ST7735_Init_Command3();

	//STFTCB_CS_ON;

}

//%s/stftcb_sendCmd1byte(/stftcb_sendCmd1byte(/g
//%s/stftcb_sendData1byte(/stftcb_sendData1byte(/g

void ST7735_Init_Command1() {
	stftcb_sendCmd1byte(ST7735_SWRESET);    //  1: Software reset
	MyDelay(150);
	stftcb_sendCmd1byte(ST7735_SLPOUT);	    //  2: Out of sleep mode
	MyDelay(500);
	stftcb_sendCmd1byte(ST7735_FRMCTR1);    //  3: Frame rate ctrl - normal mode
	stftcb_sendData1byte(0x01);			    //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
	stftcb_sendData1byte(0x2C);
	stftcb_sendData1byte(0x2D);
	stftcb_sendCmd1byte(ST7735_FRMCTR2);    //  4: Frame rate control - idle mode
	stftcb_sendData1byte(0x01);		        //  Rate = fosc/(1x2+40) * (LINE+2C+2D)
	stftcb_sendData1byte(0x2C);
	stftcb_sendData1byte(0x2D);
	stftcb_sendCmd1byte(ST7735_FRMCTR3);    //  5: Frame rate ctrl - partial mode
	stftcb_sendData1byte(0x01);			    //     Dot inversion mode
	stftcb_sendData1byte(0x2C);
	stftcb_sendData1byte(0x2D);
	stftcb_sendData1byte(0x01);			    //     Line inversion mode
	stftcb_sendData1byte(0x2C);
	stftcb_sendData1byte(0x2D);
	stftcb_sendCmd1byte(ST7735_INVCTR);	    //  6: Display inversion ctrl
	stftcb_sendData1byte(0x07);			    //     No inversion
	stftcb_sendCmd1byte(ST7735_PWCTR1);	    //  7: Power control
	stftcb_sendData1byte(0xA2);
	stftcb_sendData1byte(0x02);			    //     -4.6V
	stftcb_sendData1byte(0x84);			    //     AUTO mode
	stftcb_sendCmd1byte(ST7735_PWCTR2);	    //  8: Power control
	stftcb_sendData1byte(0xC5);			    //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
	stftcb_sendCmd1byte(ST7735_PWCTR3);	    //  9: Power control
	stftcb_sendData1byte(0x0A);			    //     Opamp current small
	stftcb_sendData1byte(0x00);			    //     Boost frequency
	stftcb_sendCmd1byte(ST7735_PWCTR4);	    // 10: Power control
	stftcb_sendData1byte(0x8A);			    //     BCLK/2, Opamp current small & Medium low
	stftcb_sendData1byte(0x2A);
	stftcb_sendCmd1byte(ST7735_PWCTR5);	    // 11: Power control
	stftcb_sendData1byte(0x8A);
	stftcb_sendData1byte(0xEE);
	stftcb_sendCmd1byte(ST7735_VMCTR1);	    // 12: Power control
	stftcb_sendData1byte(0x0E);
	stftcb_sendCmd1byte(ST7735_INVOFF);	    // 13: Don't invert display
	stftcb_sendCmd1byte(ST7735_MADCTL);	    // 14: Memory access control (directions)
	stftcb_sendData1byte(ST7735_ROTATION);  //     row addr/col addr, bottom to top refresh
	stftcb_sendCmd1byte(ST7735_COLMOD);	    // 15: set color mode
	stftcb_sendData1byte(0x05);			    //     16-bit color
}

void ST7735_Init_Command2(void) {
	stftcb_sendCmd1byte(ST7735_CASET);  //  1: Column addr set
	stftcb_sendData1byte(0x00);			//     XSTART = 0
	stftcb_sendData1byte(0x00);
	stftcb_sendData1byte(0x00);			//     XEND = 127
	stftcb_sendData1byte(0x7F);
	stftcb_sendCmd1byte(ST7735_RASET);	//  2: Row addr set
	stftcb_sendData1byte(0x00);			//     XSTART = 0
	stftcb_sendData1byte(0x00);
	stftcb_sendData1byte(0x00);			//     XEND = 127
	stftcb_sendData1byte(0x7F);
}

void ST7735_Init_Command3(void) {
	stftcb_sendCmd1byte(ST7735_GMCTRP1);  //  1: Magical unicorn dust
	stftcb_sendData1byte(0x02);
	stftcb_sendData1byte(0x1C);
	stftcb_sendData1byte(0x07);
	stftcb_sendData1byte(0x12);
	stftcb_sendData1byte(0x37);
	stftcb_sendData1byte(0x32);
	stftcb_sendData1byte(0x29);
	stftcb_sendData1byte(0x2D);
	stftcb_sendData1byte(0x29);
	stftcb_sendData1byte(0x25);
	stftcb_sendData1byte(0x2B);
	stftcb_sendData1byte(0x39);
	stftcb_sendData1byte(0x00);
	stftcb_sendData1byte(0x01);
	stftcb_sendData1byte(0x03);
	stftcb_sendData1byte(0x10);
	stftcb_sendCmd1byte(ST7735_GMCTRN1);  //  2: Sparkles and rainbows
	stftcb_sendData1byte(0x03);
	stftcb_sendData1byte(0x1D);
	stftcb_sendData1byte(0x07);
	stftcb_sendData1byte(0x06);
	stftcb_sendData1byte(0x2E);
	stftcb_sendData1byte(0x2C);
	stftcb_sendData1byte(0x29);
	stftcb_sendData1byte(0x2D);
	stftcb_sendData1byte(0x2E);
	stftcb_sendData1byte(0x2E);
	stftcb_sendData1byte(0x37);
	stftcb_sendData1byte(0x3F);
	stftcb_sendData1byte(0x00);
	stftcb_sendData1byte(0x00);
	stftcb_sendData1byte(0x02);
	stftcb_sendData1byte(0x10);
	stftcb_sendCmd1byte(ST7735_NORON);
	MyDelay(10);
	stftcb_sendCmd1byte(ST7735_DISPON);
	MyDelay(100);
}

#if 0
/**
 *  Тут он что то рисует, но я не очень понимаю что. Закоментирую. Возможно не пригодится
 * */
void ST7735_PlotPoint(int32_t data1, uint16_t color1) {
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
#endif

#if 0
void ST7735_DrawPixel(uint8_t x, uint8_t y, uint16_t color) {
    //STFTCB_CS_OFF;
    stftcb_DrawPixel(x, y, color);
    //STFTCB_CS_ON;
}

void ST7735_DrawHorizonLine(uint8_t x, uint8_t y, uint8_t _wight, uint16_t color) {
    stftcb_DrawHorizonLine(x, y, _wight, color, ST7735_WIDTH);
}

void ST7735_DrawVerticalLine(uint8_t x, uint8_t y, uint8_t _height, uint16_t color) {
    stftcb_DrawVerticalLine(x, y, _height, color, ST7735_HEIGHT);
}

void ST7735_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color) {
    stftcb_DrawLine(x0, y0, x1, y1, color); 
}

void ST7735_DrawFillEasyRectangle(uint16_t x, uint16_t y, uint16_t _wight, uint16_t _height, uint16_t color) {
    stftcb_DrawFillEasyRectangle(x, y, _wight, _height, color);
}
#endif

//void ST7735_FillScreen(uint16_t color) {
  //  stftcb_DrawFillEasyRectangle(0, 0, ST7735_WIDTH, ST7735_HEIGHT, color);
//}

#if 0
/** Отрисовка букв
 * */
uint32_t ST7735_DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor) {
    uint32_t count = 0;
    if (y > 15) 
        return 0;
    while (*pt) {
        ST7735_DrawCharS(x * 6, y * 10, *pt, textColor, ST7735_BLACK, 1);
        pt++;
        x = x + 1;
        if(x > 20) 
            return count;  // number of characters printed
        count++;
    }
    return count;  // number of characters printed
}

void ST7735_DrawCharS(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size) {
    uint8_t line;
    int32_t i, j;
    if ((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT) || ((x + 5 * size - 1) < 0) || ((y + 8 * size - 1) < 0))
        return;
    for (i = 0; i < 6; i++) {
        if (i == 5)
            line = 0x0;
        else
            line = Font[(c*5)+i];

        for (j = 0; j<8; j++) {
            if (line & 0x1) {
                if (size == 1)
                    ST7735_DrawPixel(x+i, y+j, textColor);
                else
                    ST7735_FillRectangle(x+(i*size), y+(j*size), size, size, textColor);
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
#endif

#if 0
void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    // clipping
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
    if((x + w - 1) >= ST7735_WIDTH) w = ST7735_WIDTH - x;
    if((y + h - 1) >= ST7735_HEIGHT) h = ST7735_HEIGHT - y;

    STFTCB_CS_OFF;
    stftcb_SetAddressWindow(x, y, x+w-1, y+h-1);
    STFTCB_DC_ON;
    for(y = h; y > 0; y--) {
        for(x = w; x > 0; x--) {
					stftcb_sendData1byte(color>>8);
					stftcb_sendData1byte(color);
        }
    }

		STFTCB_CS_ON;  //Unselect
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

	STFTCB_CS_OFF;  //Select

    stftcb_SetAddressWindow(x, y-h+1, x+w-1, y);

    for(y=0; y<h; y=y+1){
        for(x=0; x<w; x=x+1){

        stftcb_sendData1byte((uint8_t)(data[i] >> 8));

        stftcb_sendData1byte((uint8_t)data[i]);
        i = i + 1;
        }
        i = i + skipC;
        i = i - 2*originalWidth;
    }
	STFTCB_CS_ON;  //Unselect
}

void ST7735_InvertColors(bool invert) {
    //ST7735_Select();
	STFTCB_CS_OFF;
    //ST7735_WriteCommand(invert ? ST7735_INVON : ST7735_INVOFF);
	stftcb_sendCmd1byte(invert ? ST7735_INVON : ST7735_INVOFF);
    STFTCB_CS_ON;  //Unselect
}
#endif

#if 0  // функции которые надо реализовать будет
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
#endif

#if 0  // цвета
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
#endif

#endif  // ST7735_H_
