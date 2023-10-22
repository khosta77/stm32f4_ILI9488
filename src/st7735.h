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
    //ST7735_Init_Command2();
    ST7735_Init_Command3();

    //STFTCB_CS_ON;
    stftcb_updateFrame();
}

//%s/stftcb_sendCmd1byte(/stftcb_sendCmd1byte(/g
//%s/stftcb_sendData1byte(/stftcb_sendData1byte(/g

void ST7735_Init_Command1() {
    stftcb_sendCmd1byte(ST7735_SWRESET);    //  1: Software reset
    MyDelay(150);
    stftcb_sendCmd1byte(ST7735_SLPOUT);     //  2: Out of sleep mode
    MyDelay(500);
    stftcb_sendCmd1byte(ST7735_FRMCTR1);    //  3: Frame rate ctrl - normal mode	
    stftcb_sendData1byte(0x01);             //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    stftcb_sendData1byte(0x2C);
    stftcb_sendData1byte(0x2D);
    stftcb_sendCmd1byte(ST7735_FRMCTR2);    //  4: Frame rate control - idle mode
    stftcb_sendData1byte(0x01);             //  Rate = fosc/(1x2+40) * (LINE+2C+2D)
    stftcb_sendData1byte(0x2C);
    stftcb_sendData1byte(0x2D);
    stftcb_sendCmd1byte(ST7735_FRMCTR3);    //  5: Frame rate ctrl - partial mode
    stftcb_sendData1byte(0x01);             //     Dot inversion mode
    stftcb_sendData1byte(0x2C);
    stftcb_sendData1byte(0x2D);
    stftcb_sendData1byte(0x01);             //     Line inversion mode
    stftcb_sendData1byte(0x2C);
    stftcb_sendData1byte(0x2D);
    stftcb_sendCmd1byte(ST7735_INVCTR);     //  6: Display inversion ctrl
    stftcb_sendData1byte(0x07);             //     No inversion
    stftcb_sendCmd1byte(ST7735_PWCTR1);     //  7: Power control
    stftcb_sendData1byte(0xA2);
    stftcb_sendData1byte(0x02);             //     -4.6V
    stftcb_sendData1byte(0x84);             //     AUTO mode
    stftcb_sendCmd1byte(ST7735_PWCTR2);     //  8: Power control
    stftcb_sendData1byte(0xC5);             //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
    stftcb_sendCmd1byte(ST7735_PWCTR3);     //  9: Power control
    stftcb_sendData1byte(0x0A);             //     Opamp current small
    stftcb_sendData1byte(0x00);             //     Boost frequency
    stftcb_sendCmd1byte(ST7735_PWCTR4);     // 10: Power control
    stftcb_sendData1byte(0x8A);             //     BCLK/2, Opamp current small & Medium low
    stftcb_sendData1byte(0x2A);
    stftcb_sendCmd1byte(ST7735_PWCTR5);     // 11: Power control
    stftcb_sendData1byte(0x8A);
    stftcb_sendData1byte(0xEE);
    stftcb_sendCmd1byte(ST7735_VMCTR1);     // 12: Power control
    stftcb_sendData1byte(0x0E);
    stftcb_sendCmd1byte(ST7735_INVOFF);     // 13: Don't invert display
    stftcb_sendCmd1byte(ST7735_MADCTL);     // 14: Memory access control (directions)
    stftcb_sendData1byte(ST7735_ROTATION);  //     row addr/col addr, bottom to top refresh
    stftcb_sendCmd1byte(ST7735_COLMOD);     // 15: set color mode
    stftcb_sendData1byte(0x05);             //     16-bit color
}

void ST7735_Init_Command2(void) {
    stftcb_sendCmd1byte(ST7735_CASET);  //  1: Column addr set
    stftcb_sendData1byte(0x00);         //     XSTART = 0
    stftcb_sendData1byte(0x00);
    stftcb_sendData1byte(0x00);         //     XEND = 127
    stftcb_sendData1byte(0x7F);
    stftcb_sendCmd1byte(ST7735_RASET);  //  2: Row addr set
    stftcb_sendData1byte(0x00);         //     XSTART = 0
    stftcb_sendData1byte(0x00);
    stftcb_sendData1byte(0x00);         //     XEND = 127
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

#endif  // ST7735_H_
