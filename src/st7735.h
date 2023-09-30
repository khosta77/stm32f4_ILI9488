#ifndef ST7735_H_
#define ST7735_H_

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

#endif  // ST7735_H_
