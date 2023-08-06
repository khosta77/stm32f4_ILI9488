#pragma once
//#include "font_include.h" //���� ����� ����� �������������� � ���������� ������, �� �������� ��� ��� extern � font_include.h
//�������������� ���������� font_include.h � ��� ����
//#include "char_out.h"


#ifndef COLOR_DEF
#define COLOR_DEF
//������� ��� ����������� �� rgb 565 �����
#define mRGB(r, g, b) ((uint16_t)(r << (5 + 6)) | (uint16_t)(g << 5) | (uint16_t)b)
//0brrrr rggg gggb bbbb
//#define RGB_GET_R(r) ((uint16_t)((r&0xF800)>>(5+6)))
//#define RGB_GET_G(r) ((uint16_t)((r&0x07E0)>>5))
//#define RGB_GET_B(r) ((uint16_t)( r&0x001F))

#define RGB_GET_R(r) ((r >> (5 + 6)) & 0x1F)
#define RGB_GET_G(r) ((r >> 5) & 0x3F)
#define RGB_GET_B(r) (r & 0x1F)

//16-�� ������ ������� ������� (65536 ������)
#define BLACK 0x0000
#define WHITE 0xFFFF
#define GRAY 0xE79C
#define GREEN 0x07E0
#define BLUE 0x001F
#define RED 0xF800
#define SKY 0x5d1c
#define YELLOW 0xffe0
#define MAGENTA 0xf81f
#define CYAN 0x07ff
#define ORANGE 0xfca0
//#define    PINK                 0xF97F
#define BROWN 0x8200
#define VIOLET 0x9199
#define SILVER 0xa510
#define GOLD 0xa508
#define BEGH 0xf77b
#define NAVY 0x000F
#define DARK_GREEN 0x03E0
#define DARK_CYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHT_GREY 0xC618
#define DARK_GREY 0x7BEF

//---------------
/* ������������ ����� */
#define RGB16(color) (uint16_t)(((color & 0xF80000) >> 8) | ((color & 0x00FC00) >> 5) | ((color & 0x0000F8) >> 3))
//#define RGB(r,g,b)   (unsigned long)((r >> 3) |((g >> 2) << 5) |((b >> 3) << 11))

/* �������� ����� */
#define COL_BLACK RGB16(0)
#define COL_WHITE RGB16(0xffffff)
#define COL_RED RGB16(0xff0000)
#define COL_BLUE RGB16(0x0000ff)
#define COL_GREEN RGB16(0x00ff00)

#define COL_YELLOW RGB16(0xffff00)
#define COL_MAGENTA RGB16(0xff00ff)
#define COL_AQUA RGB16(0x00ffff)

#define COL_PURPLE RGB(160, 32, 240)
#define COL_REDPINK RGB(255, 50, 50)
#define COL_ORANGE RGB(255, 165, 0)
#define COL_BLUE_D RGB16(0x002db3)

#endif //

#ifndef FONT_15_H_
#define FONT_15_H_

//#include "../common_file/char_out.h"
// #include "df_msansserif_15.h"	//sDotMSansSerif_15

//���� �����

//**********************************************************
//��� ���� ��������� ���
//static const uint16_t fSansSerif_14_info[][2] PROGMEM =
//            |����� 16| ���!

//��� ������� ������
//static const uint8_t fSansSerif_14[] PROGMEM

// TSettingfontDot sDotSansSerif22={
	// fSansSerif_14, //font
	// &fSansSerif_14_info[0][0],//font_info
	// 22, //height
	// BLACK,//color
	// WHITE,//bgcolor
// };
//**********************************************************
 // !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
 //����������������������������������������������������������������
// 
//  Font information for Tahoma 9pt
// 


const  uint8_t MSansSerif_10pt[] =
{
	/* Char:33 "!", Offset:14 Byte, Size of:14 Byte, Width:2 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x03,
	0x03,
	0x03,
	0x03, 
	0x03,
	0x03,
	0x00,
	0x03, 
	0x03,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__
	__
	__
	##
	##
	##
	##
	##
	##
	__
	##
	##
	__
	__
	*/

	/* Char:34 """, Offset:28 Byte, Size of:14 Byte, Width:5 pix, Height:14 pix */
	0x00,
	0x00,
	0x1B, 
	0x1B,
	0x1B, 
	0x00, 
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00, 
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____
	_____
	##_##
	##_##
	##_##
	_____
	_____
	_____
	_____
	_____
	_____
	_____
	_____
	_____
	*/

	/* Char:35 "#", Offset:42 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x48,
	0x48, 
	0xFE, 
	0xFE,
	0x24,
	0x7F,
	0x7F, 
	0x12, 
	0x12,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	___#__#_
	___#__#_
	_#######
	_#######
	__#__#__
	#######_
	#######_
	_#__#___
	_#__#___
	________
	________
	*/

	/* Char:36 "$", Offset:56 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x08,
	0x08, 
	0x3E,
	0x4B,
	0x0B,
	0x1E, 
	0x3C, 
	0x68, 
	0x69,
	0x3E,
	0x08, 
	0x08,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	___#___
	___#___
	_#####_
	##_#__#
	##_#___
	_####__
	__####_
	___#_##
	#__#_##
	_#####_
	___#___
	___#___
	*/

	/* Char:37 "%", Offset:70 Byte, Size of:28 Byte, Width:13 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00,
	0x0E,
	0x02,
	0x1B, 
	0x01, 
	0x9B, 
	0x00,
	0x9B,
	0x00,
	0x4E,
	0x0E,
	0x20, 
	0x1B,
	0x20,
	0x1B,
	0x10, 
	0x1B, 
	0x08, 
	0x0E,
	0x00,
	0x00,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____________
	_____________
	_____________
	_###_____#___
	##_##___#____
	##_##__#_____
	##_##__#_____
	_###__#__###_
	_____#__##_##
	_____#__##_##
	____#___##_##
	___#_____###_
	_____________
	_____________
	*/

	/* Char:38 "&", Offset:98 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x1E,
	0x33, 
	0x33, 
	0x1E, 
	0xCE,
	0xDB,
	0x73,
	0x73, 
	0xDE,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	_####___
	##__##__
	##__##__
	_####___
	_###__##
	##_##_##
	##__###_
	##__###_
	_####_##
	________
	________
	*/

	/* Char:39 "'", Offset:112 Byte, Size of:14 Byte, Width:2 pix, Height:14 pix */
	0x00,
	0x00,
	0x03, 
	0x03,
	0x03,
	0x00, 
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__
	__
	##
	##
	##
	__
	__
	__
	__
	__
	__
	__
	__
	__
	*/

	/* Char:40 "(", Offset:126 Byte, Size of:14 Byte, Width:4 pix, Height:14 pix */
	0x00, 
	0x00,
	0x0C,
	0x06, 
	0x06,
	0x03, 
	0x03,
	0x03,
	0x03,
	0x03, 
	0x03, 
	0x06, 
	0x06, 
	0x0C,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	____
	____
	__##
	_##_
	_##_
	##__
	##__
	##__
	##__
	##__
	##__
	_##_
	_##_
	__##
	*/

	/* Char:41 ")", Offset:140 Byte, Size of:14 Byte, Width:4 pix, Height:14 pix */
	0x00,
	0x00,
	0x03, 
	0x06, 
	0x06,
	0x0C,
	0x0C,
	0x0C,
	0x0C, 
	0x0C,
	0x0C,
	0x06,
	0x06, 
	0x03,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	____
	____
	##__
	_##_
	_##_
	__##
	__##
	__##
	__##
	__##
	__##
	_##_
	_##_
	##__
	*/

	/* Char:42 "*", Offset:154 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00, 
	0x0C,
	0x2D,
	0x1E, 
	0x2D,
	0x0C, 
	0x00,
	0x00,
	0x00, 
	0x00,
	0x00, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	__##__
	#_##_#
	_####_
	#_##_#
	__##__
	______
	______
	______
	______
	______
	______
	______
	*/

	/* Char:43 "+", Offset:168 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00, 
	0x00, 
	0x08,
	0x08,
	0x08,
	0x7F,
	0x08,
	0x08,
	0x08,
	0x00,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_______
	___#___
	___#___
	___#___
	#######
	___#___
	___#___
	___#___
	_______
	_______
	_______
	*/

	/* Char:44 ",", Offset:182 Byte, Size of:14 Byte, Width:2 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00, 
	0x00, 
	0x00,
	0x00, 
	0x00,
	0x00, 
	0x03, 
	0x03,
	0x03,
	0x01,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__
	__
	__
	__
	__
	__
	__
	__
	__
	__
	##
	##
	##
	#_
	*/

	/* Char:45 "-", Offset:196 Byte, Size of:14 Byte, Width:4 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00, 
	0x0F,
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00, 
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	____
	____
	____
	____
	____
	____
	####
	____
	____
	____
	____
	____
	____
	____
	*/

	/* Char:46 ".", Offset:210 Byte, Size of:14 Byte, Width:2 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00, 
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x00, 
	0x00, 
	0x03,
	0x03,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__
	__
	__
	__
	__
	__
	__
	__
	__
	__
	__
	##
	##
	__
	*/

	/* Char:47 "/", Offset:224 Byte, Size of:14 Byte, Width:5 pix, Height:14 pix */
	0x00,
	0x00, 
	0x10,
	0x10,
	0x08, 
	0x08,
	0x08, 
	0x04,
	0x04,
	0x02,
	0x02,
	0x02, 
	0x01, 
	0x01,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____
	_____
	____#
	____#
	___#_
	___#_
	___#_
	__#__
	__#__
	_#___
	_#___
	_#___
	#____
	#____
	*/

	/* Char:48 "0", Offset:238 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00, 
	0x3C,
	0x66,
	0xC3, 
	0xC3,
	0xC3, 
	0xC3, 
	0xC3,
	0xC3, 
	0xC3,
	0x66,
	0x3C,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	__####__
	_##__##_
	##____##
	##____##
	##____##
	##____##
	##____##
	##____##
	##____##
	_##__##_
	__####__
	________
	*/

	/* Char:49 "1", Offset:252 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00, 
	0x18,
	0x1E,
	0x18, 
	0x18,
	0x18, 
	0x18, 
	0x18,
	0x18,
	0x18, 
	0x18,
	0x7E, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	___##___
	_####___
	___##___
	___##___
	___##___
	___##___
	___##___
	___##___
	___##___
	___##___
	_######_
	________
	*/

	/* Char:50 "2", Offset:266 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00, 
	0x00,
	0x7E,
	0xC1, 
	0xC0, 
	0xC0,
	0x60, 
	0x30,
	0x18,
	0x0C, 
	0x06,
	0x03,
	0xFF, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	_######_
	#_____##
	______##
	______##
	_____##_
	____##__
	___##___
	__##____
	_##_____
	##______
	########
	________
	*/

	/* Char:51 "3", Offset:280 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x3E,
	0x63,
	0xC0,
	0xC0,
	0x60,
	0x3C, 
	0x60, 
	0xC0,
	0xC1,
	0x63,
	0x3E, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	_#####__
	##___##_
	______##
	______##
	_____##_
	__####__
	_____##_
	______##
	#_____##
	##___##_
	_#####__
	________
	*/

	/* Char:52 "4", Offset:294 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x63,
	0x63,
	0x63, 
	0x63,
	0x63, 
	0x63,
	0xFF,
	0x60, 
	0x60, 
	0x60,
	0x60, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	##___##_
	##___##_
	##___##_
	##___##_
	##___##_
	##___##_
	########
	_____##_
	_____##_
	_____##_
	_____##_
	________
	*/

	/* Char:53 "5", Offset:308 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0xFF,
	0x01,
	0x01,
	0x3F,
	0x63,
	0xC0,
	0xC0, 
	0xC0, 
	0xC1,
	0x63,
	0x3E,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	########
	#_______
	#_______
	######__
	##___##_
	______##
	______##
	______##
	#_____##
	##___##_
	_#####__
	________
	*/

	/* Char:54 "6", Offset:322 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x7C,
	0x06,
	0x03,
	0x03, 
	0x7F,
	0xC3, 
	0xC3,
	0xC3,
	0xC3, 
	0xC3,
	0x7E,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	__#####_
	_##_____
	##______
	##______
	#######_
	##____##
	##____##
	##____##
	##____##
	##____##
	_######_
	________
	*/

	/* Char:55 "7", Offset:336 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00, 
	0xFF,
	0x60,
	0x30,
	0x10, 
	0x18,
	0x08,
	0x0C,
	0x04,
	0x06,
	0x06, 
	0x06, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	########
	_____##_
	____##__
	____#___
	___##___
	___#____
	__##____
	__#_____
	_##_____
	_##_____
	_##_____
	________
	*/

	/* Char:56 "8", Offset:350 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x3C, 
	0x66,
	0xC3, 
	0xC3,
	0x66,
	0x3C,
	0x66, 
	0xC3, 
	0xC3,
	0x66,
	0x3C,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	__####__
	_##__##_
	##____##
	##____##
	_##__##_
	__####__
	_##__##_
	##____##
	##____##
	_##__##_
	__####__
	________
	*/

	/* Char:57 "9", Offset:364 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x3C,
	0x66,
	0xC3,
	0xC3,
	0xC3, 
	0xE6,
	0xFC, 
	0xC0,
	0x60,
	0x30,
	0x1E,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	__####__
	_##__##_
	##____##
	##____##
	##____##
	_##__###
	__######
	______##
	_____##_
	____##__
	_####___
	________
	*/

	/* Char:58 ":", Offset:378 Byte, Size of:14 Byte, Width:2 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00, 
	0x00,
	0x03,
	0x03, 
	0x00,
	0x00,
	0x00, 
	0x03,
	0x03, 
	0x00,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__
	__
	__
	__
	##
	##
	__
	__
	__
	##
	##
	__
	__
	__
	*/

	/* Char:59 ";", Offset:392 Byte, Size of:14 Byte, Width:2 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x00,
	0x00, 
	0x03,
	0x03,
	0x00, 
	0x00,
	0x00,
	0x03, 
	0x03,
	0x03, 
	0x01,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__
	__
	__
	__
	__
	##
	##
	__
	__
	__
	##
	##
	##
	#_
	*/

	/* Char:60 "<", Offset:406 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x00,
	0xC0, 
	0x30,
	0x0C,
	0x03, 
	0x03,
	0x0C,
	0x30, 
	0xC0,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	________
	______##
	____##__
	__##____
	##______
	##______
	__##____
	____##__
	______##
	________
	________
	*/

	/* Char:61 "=", Offset:420 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x7F,
	0x00, 
	0x00, 
	0x7F,
	0x00,
	0x00,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_______
	_______
	_______
	#######
	_______
	_______
	#######
	_______
	_______
	_______
	_______
	*/

	/* Char:62 ">", Offset:434 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00,
	0x03, 
	0x0C, 
	0x30,
	0xC0, 
	0xC0,
	0x30,
	0x0C, 
	0x03,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	________
	##______
	__##____
	____##__
	______##
	______##
	____##__
	__##____
	##______
	________
	________
	*/

	/* Char:63 "?", Offset:448 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00, 
	0x1E,
	0x31,
	0x30,
	0x18, 
	0x0C, 
	0x0C,
	0x00,
	0x0C,
	0x0C,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	_####_
	#___##
	____##
	___##_
	__##__
	__##__
	______
	__##__
	__##__
	______
	______
	*/

	/* Char:64 "@", Offset:462 Byte, Size of:28 Byte, Width:9 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x7C,
	0x00,
	0x82,
	0x00,
	0x79, 
	0x01,
	0x6D, 
	0x01,
	0x6D,
	0x01,
	0x6D, 
	0x01,
	0x6D,
	0x01, 
	0xD9,
	0x00, 
	0x02, 
	0x00,
	0x7C,
	0x00, 
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_________
	_________
	_________
	__#####__
	_#_____#_
	#__####_#
	#_##_##_#
	#_##_##_#
	#_##_##_#
	#_##_##_#
	#__##_##_
	_#_______
	__#####__
	_________
	*/

	/* Char:65 "A", Offset:490 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x18, 
	0x3C,
	0x3C,
	0x66, 
	0x66,
	0x66,
	0xFF, 
	0xC3,
	0xC3, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	___##___
	__####__
	__####__
	_##__##_
	_##__##_
	_##__##_
	########
	##____##
	##____##
	________
	________
	*/

	/* Char:66 "B", Offset:504 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x3F, 
	0x63,
	0x63,
	0x63,
	0x3F, 
	0x63, 
	0x63,
	0x63,
	0x3F,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	######_
	##___##
	##___##
	##___##
	######_
	##___##
	##___##
	##___##
	######_
	_______
	_______
	*/

	/* Char:67 "C", Offset:518 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x3E,
	0x43,
	0x43, 
	0x03,
	0x03, 
	0x03,
	0x43,
	0x43, 
	0x3E,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_#####_
	##____#
	##____#
	##_____
	##_____
	##_____
	##____#
	##____#
	_#####_
	_______
	_______
	*/

	/* Char:68 "D", Offset:532 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x3F,
	0x63,
	0xC3, 
	0xC3,
	0xC3, 
	0xC3,
	0xC3,
	0x63,
	0x3F, 
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	######__
	##___##_
	##____##
	##____##
	##____##
	##____##
	##____##
	##___##_
	######__
	________
	________
	*/

	/* Char:69 "E", Offset:546 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x3F, 
	0x03,
	0x03, 
	0x03, 
	0x3F,
	0x03,
	0x03,
	0x03, 
	0x3F,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	######
	##____
	##____
	##____
	######
	##____
	##____
	##____
	######
	______
	______
	*/

	/* Char:70 "F", Offset:560 Byte, Size of:14 Byte, Width:5 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00, 
	0x1F, 
	0x03,
	0x03,
	0x03,
	0x1F, 
	0x03,
	0x03,
	0x03,
	0x03,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____
	_____
	_____
	#####
	##___
	##___
	##___
	#####
	##___
	##___
	##___
	##___
	_____
	_____
	*/

	/* Char:71 "G", Offset:574 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x00,
	0x3E,
	0x43,
	0x43,
	0x03, 
	0x73, 
	0x63,
	0x63,
	0x63,
	0x7E, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_#####_
	##____#
	##____#
	##_____
	##__###
	##___##
	##___##
	##___##
	_######
	_______
	_______
	*/

	/* Char:72 "H", Offset:588 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0xC3, 
	0xC3, 
	0xC3,
	0xC3,
	0xFF,
	0xC3, 
	0xC3, 
	0xC3, 
	0xC3,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	##____##
	##____##
	##____##
	##____##
	########
	##____##
	##____##
	##____##
	##____##
	________
	________
	*/

	/* Char:73 "I", Offset:602 Byte, Size of:14 Byte, Width:4 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x0F,
	0x06,
	0x06,
	0x06,
	0x06, 
	0x06,
	0x06, 
	0x06,
	0x0F,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	____
	____
	____
	####
	_##_
	_##_
	_##_
	_##_
	_##_
	_##_
	_##_
	####
	____
	____
	*/

	/* Char:74 "J", Offset:616 Byte, Size of:14 Byte, Width:5 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x1E, 
	0x18, 
	0x18,
	0x18,
	0x18,
	0x18, 
	0x18, 
	0x18,
	0x0F,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____
	_____
	_____
	_####
	___##
	___##
	___##
	___##
	___##
	___##
	___##
	####_
	_____
	_____
	*/

	/* Char:75 "K", Offset:630 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x00,
	0x63,
	0x33,
	0x1B, 
	0x0F, 
	0x07, 
	0x0F,
	0x1B,
	0x33, 
	0x63, 
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	##___##
	##__##_
	##_##__
	####___
	###____
	####___
	##_##__
	##__##_
	##___##
	_______
	_______
	*/

	/* Char:76 "L", Offset:644 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x03, 
	0x03, 
	0x03,
	0x03,
	0x03, 
	0x03, 
	0x03,
	0x03, 
	0x3F,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	##____
	##____
	##____
	##____
	##____
	##____
	##____
	##____
	######
	______
	______
	*/

	/* Char:77 "M", Offset:658 Byte, Size of:28 Byte, Width:10 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x03, 
	0x03,
	0x87,
	0x03, 
	0xCF, 
	0x03,
	0x7D, 
	0x03,
	0x39,
	0x03,
	0x11, 
	0x03,
	0x01,
	0x03, 
	0x01, 
	0x03, 
	0x01,
	0x03,
	0x00,
	0x00, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__________
	__________
	__________
	##______##
	###____###
	####__####
	#_#####_##
	#__###__##
	#___#___##
	#_______##
	#_______##
	#_______##
	__________
	__________
	*/

	/* Char:78 "N", Offset:686 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x43, 
	0x47,
	0x47, 
	0x4D,
	0x59,
	0x59,
	0x71, 
	0x71, 
	0x61,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	##____#
	###___#
	###___#
	#_##__#
	#__##_#
	#__##_#
	#___###
	#___###
	#____##
	_______
	_______
	*/

	/* Char:79 "O", Offset:700 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x7E, 
	0xC3,
	0xC3,
	0xC3,
	0xC3, 
	0xC3, 
	0xC3,
	0xC3,
	0x7E, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	_######_
	##____##
	##____##
	##____##
	##____##
	##____##
	##____##
	##____##
	_######_
	________
	________
	*/

	/* Char:80 "P", Offset:714 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00, 
	0x3F,
	0x63, 
	0x63, 
	0x63,
	0x63,
	0x3F,
	0x03, 
	0x03, 
	0x03,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	######_
	##___##
	##___##
	##___##
	##___##
	######_
	##_____
	##_____
	##_____
	_______
	_______
	*/

	/* Char:81 "Q", Offset:728 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x7E, 
	0xC3, 
	0xC3,
	0xC3,
	0xC3,
	0xC3, 
	0xC3, 
	0xC3,
	0x7E,
	0x30,
	0xE0,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	_######_
	##____##
	##____##
	##____##
	##____##
	##____##
	##____##
	##____##
	_######_
	____##__
	_____###
	*/

	/* Char:82 "R", Offset:742 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x3F,
	0x63,
	0x63,
	0x63, 
	0x3F, 
	0x1B,
	0x33,
	0x63,
	0xC3, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	######__
	##___##_
	##___##_
	##___##_
	######__
	##_##___
	##__##__
	##___##_
	##____##
	________
	________
	*/

	/* Char:83 "S", Offset:756 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x3E, 
	0x43, 
	0x43,
	0x03,
	0x3E,
	0x60, 
	0x61,
	0x61, 
	0x3E,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_#####_
	##____#
	##____#
	##_____
	_#####_
	_____##
	#____##
	#____##
	_#####_
	_______
	_______
	*/

	/* Char:84 "T", Offset:770 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x3F,
	0x0C,
	0x0C, 
	0x0C, 
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C, 
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	######
	__##__
	__##__
	__##__
	__##__
	__##__
	__##__
	__##__
	__##__
	______
	______
	*/

	/* Char:85 "U", Offset:784 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x63,
	0x63, 
	0x63,
	0x63,
	0x63,
	0x63, 
	0x63,
	0x63, 
	0x3E, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	##___##
	##___##
	##___##
	##___##
	##___##
	##___##
	##___##
	##___##
	_#####_
	_______
	_______
	*/

	/* Char:86 "V", Offset:798 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x00,
	0x63, 
	0x63,
	0x63,
	0x36, 
	0x36,
	0x36,
	0x1C,
	0x1C,
	0x1C, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	##___##
	##___##
	##___##
	_##_##_
	_##_##_
	_##_##_
	__###__
	__###__
	__###__
	_______
	_______
	*/

	/* Char:87 "W", Offset:812 Byte, Size of:28 Byte, Width:11 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x23,
	0x06,
	0x73,
	0x06,
	0x73,
	0x06,
	0x53,
	0x06,
	0xDE,
	0x03, 
	0xDE,
	0x03,
	0xDE,
	0x03, 
	0x8C, 
	0x01,
	0x8C, 
	0x01, 
	0x00,
	0x00, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	___________
	___________
	___________
	##___#___##
	##__###__##
	##__###__##
	##__#_#__##
	_####_####_
	_####_####_
	_####_####_
	__##___##__
	__##___##__
	___________
	___________
	*/

	/* Char:88 "X", Offset:840 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x63, 
	0x63, 
	0x36,
	0x1C, 
	0x1C,
	0x1C,
	0x36,
	0x63, 
	0x63,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	##___##
	##___##
	_##_##_
	__###__
	__###__
	__###__
	_##_##_
	##___##
	##___##
	_______
	_______
	*/

	/* Char:89 "Y", Offset:854 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x33,
	0x33,
	0x33, 
	0x1E,
	0x1E, 
	0x0C,
	0x0C,
	0x0C,
	0x0C, 
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	##__##
	##__##
	##__##
	_####_
	_####_
	__##__
	__##__
	__##__
	__##__
	______
	______
	*/

	/* Char:90 "Z", Offset:868 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x3F,
	0x30, 
	0x30,
	0x18,
	0x0C,
	0x06,
	0x03, 
	0x03,
	0x3F,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	######
	____##
	____##
	___##_
	__##__
	_##___
	##____
	##____
	######
	______
	______
	*/

	/* Char:91 "[", Offset:882 Byte, Size of:14 Byte, Width:4 pix, Height:14 pix */
	0x00,
	0x00, 
	0x0F,
	0x03,
	0x03, 
	0x03, 
	0x03, 
	0x03,
	0x03,
	0x03,
	0x03,
	0x03, 
	0x03,
	0x0F,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	____
	____
	####
	##__
	##__
	##__
	##__
	##__
	##__
	##__
	##__
	##__
	##__
	####
	*/

	/* Char:92 "\", Offset:896 Byte, Size of:14 Byte, Width:5 pix, Height:14 pix */
	0x00,
	0x00,
	0x01,
	0x01, 
	0x02,
	0x02, 
	0x02,
	0x04,
	0x04, 
	0x08,
	0x08,
	0x08,
	0x10, 
	0x10,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____
	_____
	#____
	#____
	_#___
	_#___
	_#___
	__#__
	__#__
	___#_
	___#_
	___#_
	____#
	____#
	*/

	/* Char:93 "]", Offset:910 Byte, Size of:14 Byte, Width:4 pix, Height:14 pix */
	0x00,
	0x00,
	0x0F, 
	0x0C,
	0x0C, 
	0x0C,
	0x0C,
	0x0C, 
	0x0C,
	0x0C,
	0x0C, 
	0x0C,
	0x0C, 
	0x0F,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	____
	____
	####
	__##
	__##
	__##
	__##
	__##
	__##
	__##
	__##
	__##
	__##
	####
	*/

	/* Char:94 "^", Offset:924 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00, 
	0x18,
	0x24, 
	0x42,
	0x81,
	0x00, 
	0x00,
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	___##___
	__#__#__
	_#____#_
	#______#
	________
	________
	________
	________
	________
	________
	________
	*/

	/* Char:95 "_", Offset:938 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00, 
	0xFF,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	________
	________
	________
	________
	________
	________
	________
	________
	________
	________
	########
	*/

	/* Char:96 "`", Offset:952 Byte, Size of:14 Byte, Width:4 pix, Height:14 pix */
	0x00,
	0x06,
	0x09,
	0x09,
	0x06, 
	0x00,
	0x00,
	0x00, 
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	____
	_##_
	#__#
	#__#
	_##_
	____
	____
	____
	____
	____
	____
	____
	____
	____
	*/

	/* Char:97 "a", Offset:966 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00, 
	0x1C,
	0x32, 
	0x30,
	0x3E,
	0x33, 
	0x33,
	0x3E, 
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	______
	______
	__###_
	_#__##
	____##
	_#####
	##__##
	##__##
	_#####
	______
	______
	*/

	/* Char:98 "b", Offset:980 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x03,
	0x03, 
	0x03, 
	0x3B,
	0x67,
	0x63,
	0x63,
	0x63, 
	0x63,
	0x3F,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	##_____
	##_____
	##_____
	##_###_
	###__##
	##___##
	##___##
	##___##
	##___##
	######_
	_______
	_______
	*/

	/* Char:99 "c", Offset:994 Byte, Size of:14 Byte, Width:5 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x1E,
	0x03, 
	0x03, 
	0x03, 
	0x03,
	0x03, 
	0x1E, 
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____
	_____
	_____
	_____
	_____
	_####
	##___
	##___
	##___
	##___
	##___
	_####
	_____
	_____
	*/

	/* Char:100 "d", Offset:1008 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x60, 
	0x60,
	0x60, 
	0x7E,
	0x63,
	0x63, 
	0x63, 
	0x63, 
	0x73,
	0x6E,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_____##
	_____##
	_____##
	_######
	##___##
	##___##
	##___##
	##___##
	##__###
	_###_##
	_______
	_______
	*/

	/* Char:101 "e", Offset:1022 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00, 
	0x1E,
	0x33, 
	0x33,
	0x3F, 
	0x03,
	0x23,
	0x1E, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	______
	______
	_####_
	##__##
	##__##
	######
	##____
	##___#
	_####_
	______
	______
	*/

	/* Char:102 "f", Offset:1036 Byte, Size of:14 Byte, Width:5 pix, Height:14 pix */
	0x00,
	0x00,
	0x1C,
	0x06, 
	0x06,
	0x0F,
	0x06, 
	0x06,
	0x06,
	0x06, 
	0x06,
	0x06,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____
	_____
	__###
	_##__
	_##__
	####_
	_##__
	_##__
	_##__
	_##__
	_##__
	_##__
	_____
	_____
	*/

	/* Char:103 "g", Offset:1050 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00,
	0x7E, 
	0x63, 
	0x63,
	0x63,
	0x63,
	0x73,
	0x6E, 
	0x60, 
	0x3E,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_______
	_______
	_######
	##___##
	##___##
	##___##
	##___##
	##__###
	_###_##
	_____##
	_#####_
	*/

	/* Char:104 "h", Offset:1064 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x03,
	0x03,
	0x03, 
	0x3B,
	0x67,
	0x63,
	0x63,
	0x63,
	0x63,
	0x63, 
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	##_____
	##_____
	##_____
	##_###_
	###__##
	##___##
	##___##
	##___##
	##___##
	##___##
	_______
	_______
	*/

	/* Char:105 "i", Offset:1078 Byte, Size of:14 Byte, Width:2 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x00,
	0x03, 
	0x00,
	0x03,
	0x03, 
	0x03, 
	0x03,
	0x03,
	0x03,
	0x03,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__
	__
	__
	##
	__
	##
	##
	##
	##
	##
	##
	##
	__
	__
	*/

	/* Char:106 "j", Offset:1092 Byte, Size of:14 Byte, Width:3 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x06,
	0x00, 
	0x07,
	0x06, 
	0x06,
	0x06,
	0x06, 
	0x06, 
	0x06, 
	0x06,
	0x03,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	___
	___
	___
	_##
	___
	###
	_##
	_##
	_##
	_##
	_##
	_##
	_##
	##_
	*/

	/* Char:107 "k", Offset:1106 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x03,
	0x03, 
	0x03,
	0x33,
	0x1B, 
	0x0F,
	0x07, 
	0x0F,
	0x1B,
	0x33,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	##____
	##____
	##____
	##__##
	##_##_
	####__
	###___
	####__
	##_##_
	##__##
	______
	______
	*/

	/* Char:108 "l", Offset:1120 Byte, Size of:14 Byte, Width:2 pix, Height:14 pix */
	0x00, 
	0x00,
	0x03,
	0x03,
	0x03,
	0x03, 
	0x03, 
	0x03,
	0x03,
	0x03,
	0x03, 
	0x03,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__
	__
	##
	##
	##
	##
	##
	##
	##
	##
	##
	##
	__
	__
	*/

	/* Char:109 "m", Offset:1134 Byte, Size of:28 Byte, Width:10 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00, 
	0x00,
	0x00, 
	0x00, 
	0x00,
	0x00, 
	0x00,
	0xDF,
	0x01,
	0x33, 
	0x03, 
	0x33,
	0x03,
	0x33,
	0x03,
	0x33,
	0x03, 
	0x33, 
	0x03,
	0x33,
	0x03,
	0x00, 
	0x00, 
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__________
	__________
	__________
	__________
	__________
	#####_###_
	##__##__##
	##__##__##
	##__##__##
	##__##__##
	##__##__##
	##__##__##
	__________
	__________
	*/

	/* Char:110 "n", Offset:1162 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00, 
	0x00, 
	0x3B,
	0x67,
	0x63, 
	0x63, 
	0x63,
	0x63, 
	0x63,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_______
	_______
	##_###_
	###__##
	##___##
	##___##
	##___##
	##___##
	##___##
	_______
	_______
	*/

	/* Char:111 "o", Offset:1176 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00, 
	0x3E, 
	0x63, 
	0x63,
	0x63,
	0x63,
	0x63,
	0x3E,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_______
	_______
	_#####_
	##___##
	##___##
	##___##
	##___##
	##___##
	_#####_
	_______
	_______
	*/

	/* Char:112 "p", Offset:1190 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00, 
	0x3B,
	0x67,
	0x63, 
	0x63, 
	0x63,
	0x63, 
	0x3F,
	0x03, 
	0x03,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_______
	_______
	##_###_
	###__##
	##___##
	##___##
	##___##
	##___##
	######_
	##_____
	##_____
	*/

	/* Char:113 "q", Offset:1204 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00, 
	0x7E,
	0x63, 
	0x63,
	0x63,
	0x63, 
	0x73,
	0x6E, 
	0x60,
	0x60,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_______
	_______
	_######
	##___##
	##___##
	##___##
	##___##
	##__###
	_###_##
	_____##
	_____##
	*/

	/* Char:114 "r", Offset:1218 Byte, Size of:14 Byte, Width:4 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00, 
	0x00,
	0x0B,
	0x0F,
	0x03, 
	0x03, 
	0x03, 
	0x03,
	0x03,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	____
	____
	____
	____
	____
	##_#
	####
	##__
	##__
	##__
	##__
	##__
	____
	____
	*/

	/* Char:115 "s", Offset:1232 Byte, Size of:14 Byte, Width:5 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x00,
	0x00,
	0x0E,
	0x13, 
	0x03, 
	0x0E,
	0x18,
	0x19,
	0x0E,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____
	_____
	_____
	_____
	_____
	_###_
	##__#
	##___
	_###_
	___##
	#__##
	_###_
	_____
	_____
	*/

	/* Char:116 "t", Offset:1246 Byte, Size of:14 Byte, Width:5 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x06, 
	0x06, 
	0x1F,
	0x06,
	0x06, 
	0x06,
	0x06, 
	0x06,
	0x1C,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____
	_____
	_____
	_##__
	_##__
	#####
	_##__
	_##__
	_##__
	_##__
	_##__
	__###
	_____
	_____
	*/

	/* Char:117 "u", Offset:1260 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00,
	0x63,
	0x63, 
	0x63,
	0x63,
	0x63,
	0x73, 
	0x6E, 
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_______
	_______
	##___##
	##___##
	##___##
	##___##
	##___##
	##__###
	_###_##
	_______
	_______
	*/

	/* Char:118 "v", Offset:1274 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x33,
	0x33,
	0x33, 
	0x1E, 
	0x1E,
	0x0C, 
	0x0C, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	______
	______
	##__##
	##__##
	##__##
	_####_
	_####_
	__##__
	__##__
	______
	______
	*/

	/* Char:119 "w", Offset:1288 Byte, Size of:28 Byte, Width:10 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00,
	0x33, 
	0x03, 
	0x33,
	0x03,
	0xB6,
	0x01,
	0xB6, 
	0x01, 
	0xFE,
	0x01,
	0xCC,
	0x00, 
	0xCC,
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__________
	__________
	__________
	__________
	__________
	##__##__##
	##__##__##
	_##_##_##_
	_##_##_##_
	_########_
	__##__##__
	__##__##__
	__________
	__________
	*/

	/* Char:120 "x", Offset:1316 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x00,
	0x33, 
	0x33,
	0x1E,
	0x0C, 
	0x1E, 
	0x33, 
	0x33,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	______
	______
	##__##
	##__##
	_####_
	__##__
	_####_
	##__##
	##__##
	______
	______
	*/

	/* Char:121 "y", Offset:1330 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x33,
	0x33,
	0x33, 
	0x1E,
	0x1E,
	0x0C,
	0x0C,
	0x06,
	0x06,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	______
	______
	##__##
	##__##
	##__##
	_####_
	_####_
	__##__
	__##__
	_##___
	_##___
	*/

	/* Char:122 "z", Offset:1344 Byte, Size of:14 Byte, Width:5 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00, 
	0x1F, 
	0x18, 
	0x0C,
	0x06,
	0x03,
	0x03, 
	0x1F,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____
	_____
	_____
	_____
	_____
	#####
	___##
	__##_
	_##__
	##___
	##___
	#####
	_____
	_____
	*/

	/* Char:123 "{", Offset:1358 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
		0x00,
	0x00,
	0x38,
	0x0C, 
	0x0C,
	0x0C, 
	0x0C,
	0x07,
	0x0C, 
	0x0C,
	0x0C,
	0x0C,
	0x0C, 
	0x38,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	___###
	__##__
	__##__
	__##__
	__##__
	###___
	__##__
	__##__
	__##__
	__##__
	__##__
	___###
	*/

	/* Char:124 "|", Offset:1372 Byte, Size of:14 Byte, Width:2 pix, Height:14 pix */
	0x00, 
	0x00,
	0x03,
	0x03,
	0x03, 
	0x03,
	0x03,
	0x03,
	0x03,
	0x03,
	0x03, 
	0x03, 
	0x03, 
	0x03,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__
	__
	##
	##
	##
	##
	##
	##
	##
	##
	##
	##
	##
	##
	*/

	/* Char:125 "}", Offset:1386 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00,
	0x07,
	0x0C,
	0x0C, 
	0x0C, 
	0x0C,
	0x38,
	0x0C,
	0x0C, 
	0x0C,
	0x0C,
	0x0C, 
	0x07,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	###___
	__##__
	__##__
	__##__
	__##__
	___###
	__##__
	__##__
	__##__
	__##__
	__##__
	###___
	*/

	/* Char:126 "~", Offset:1400 Byte, Size of:28 Byte, Width:9 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00,
	0x00, 
	0x0E,
	0x01,
	0x1F,
	0x01,
	0xF1, 
	0x01, 
	0xE1,
	0x00,
	0x00,
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_________
	_________
	_________
	_________
	_________
	_________
	_###____#
	#####___#
	#___#####
	#____###_
	_________
	_________
	_________
	_________
	*/

	/* Char:192 "�", Offset:1428 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x00,
	0x18,
	0x3C,
	0x3C, 
	0x66,
	0x66, 
	0x66,
	0xFF,
	0xC3, 
	0xC3,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	___##___
	__####__
	__####__
	_##__##_
	_##__##_
	_##__##_
	########
	##____##
	##____##
	________
	________
	*/

	/* Char:193 "�", Offset:1442 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x3F,
	0x03,
	0x03,
	0x3F,
	0x63,
	0x63, 
	0x63, 
	0x63,
	0x3F,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	######_
	##_____
	##_____
	######_
	##___##
	##___##
	##___##
	##___##
	######_
	_______
	_______
	*/

	/* Char:194 "�", Offset:1456 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00, 
	0x3F,
	0x63,
	0x63,
	0x63, 
	0x3F,
	0x63, 
	0x63,
	0x63,
	0x3F, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	######_
	##___##
	##___##
	##___##
	######_
	##___##
	##___##
	##___##
	######_
	_______
	_______
	*/

	/* Char:195 "�", Offset:1470 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x3F, 
	0x03, 
	0x03,
	0x03,
	0x03,
	0x03, 
	0x03,
	0x03, 
	0x03,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	######
	##____
	##____
	##____
	##____
	##____
	##____
	##____
	##____
	______
	______
	*/

	/* Char:196 "�", Offset:1484 Byte, Size of:28 Byte, Width:9 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00, 
	0x00, 
	0xFC,
	0x00,
	0xCC,
	0x00,
	0xCC, 
	0x00, 
	0xCC,
	0x00,
	0xCC,
	0x00,
	0xCC,
	0x00, 
	0xC6,
	0x00, 
	0xC6,
	0x00,
	0xFF, 
	0x01,
	0x83,
	0x01, 
	0x83,
	0x01,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_________
	_________
	_________
	__######_
	__##__##_
	__##__##_
	__##__##_
	__##__##_
	__##__##_
	_##___##_
	_##___##_
	#########
	##_____##
	##_____##
	*/

	/* Char:197 "�", Offset:1512 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x3F,
	0x03,
	0x03,
	0x03, 
	0x3F,
	0x03,
	0x03,
	0x03,
	0x3F,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	######
	##____
	##____
	##____
	######
	##____
	##____
	##____
	######
	______
	______
	*/

	/* Char:198 "�", Offset:1526 Byte, Size of:28 Byte, Width:12 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x63,
	0x0C,
	0x66, 
	0x06, 
	0x6C,
	0x03,
	0x6C,
	0x03,
	0xFC,
	0x03, 
	0x6C, 
	0x03,
	0x66,
	0x06,
	0x66, 
	0x06,
	0x63,
	0x0C, 
	0x00,
	0x00, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	____________
	____________
	____________
	##___##___##
	_##__##__##_
	__##_##_##__
	__##_##_##__
	__########__
	__##_##_##__
	_##__##__##_
	_##__##__##_
	##___##___##
	____________
	____________
	*/

	/* Char:199 "�", Offset:1554 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x3E, 
	0x61,
	0x60,
	0x60,
	0x1C,
	0x60, 
	0x60, 
	0x61, 
	0x3E,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_#####_
	#____##
	_____##
	_____##
	__###__
	_____##
	_____##
	#____##
	_#####_
	_______
	_______
	*/

	/* Char:200 "�", Offset:1568 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x41, 
	0x61,
	0x71,
	0x79,
	0x5D, 
	0x4F,
	0x47,
	0x43, 
	0x41,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	#_____#
	#____##
	#___###
	#__####
	#_###_#
	####__#
	###___#
	##____#
	#_____#
	_______
	_______
	*/

	/* Char:201 "�", Offset:1582 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x22,
	0x1C,
	0x00,
	0x41, 
	0x61, 
	0x71,
	0x79,
	0x5D,
	0x4F,
	0x47, 
	0x43,
	0x41,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_#___#_
	__###__
	_______
	#_____#
	#____##
	#___###
	#__####
	#_###_#
	####__#
	###___#
	##____#
	#_____#
	_______
	_______
	*/

	/* Char:202 "�", Offset:1596 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x00,
	0x63,
	0x33,
	0x33, 
	0x1B, 
	0x0F,
	0x1B,
	0x33,
	0x33,
	0x63, 
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	##___##
	##__##_
	##__##_
	##_##__
	####___
	##_##__
	##__##_
	##__##_
	##___##
	_______
	_______
	*/

	/* Char:203 "�", Offset:1610 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0xFC, 
	0xCC,
	0xCC, 
	0xCC,
	0xCC,
	0xCC, 
	0xCC,
	0xC6,
	0xC3,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	__######
	__##__##
	__##__##
	__##__##
	__##__##
	__##__##
	__##__##
	_##___##
	##____##
	________
	________
	*/

	/* Char:204 "�", Offset:1624 Byte, Size of:28 Byte, Width:10 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x03,
	0x03, 
	0x87,
	0x03,
	0xCF,
	0x03,
	0x7D,
	0x03,
	0x39,
	0x03,
	0x11,
	0x03,
	0x01,
	0x03, 
	0x01, 
	0x03,
	0x01,
	0x03,
	0x00, 
	0x00,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__________
	__________
	__________
	##______##
	###____###
	####__####
	#_#####_##
	#__###__##
	#___#___##
	#_______##
	#_______##
	#_______##
	__________
	__________
	*/

	/* Char:205 "�", Offset:1652 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00, 
	0xC3, 
	0xC3,
	0xC3,
	0xC3,
	0xFF, 
	0xC3,
	0xC3, 
	0xC3,
	0xC3,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	##____##
	##____##
	##____##
	##____##
	########
	##____##
	##____##
	##____##
	##____##
	________
	________
	*/

	/* Char:206 "�", Offset:1666 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x7E, 
	0xC3, 
	0xC3,
	0xC3,
	0xC3,
	0xC3,
	0xC3, 
	0xC3, 
	0x7E,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	_######_
	##____##
	##____##
	##____##
	##____##
	##____##
	##____##
	##____##
	_######_
	________
	________
	*/

	/* Char:207 "�", Offset:1680 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0xFF,
	0xC3, 
	0xC3,
	0xC3,
	0xC3, 
	0xC3,
	0xC3,
	0xC3, 
	0xC3,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	########
	##____##
	##____##
	##____##
	##____##
	##____##
	##____##
	##____##
	##____##
	________
	________
	*/

	/* Char:208 "�", Offset:1694 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x3F,
	0x63,
	0x63, 
	0x63,
	0x63,
	0x3F,
	0x03,
	0x03,
	0x03,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	######_
	##___##
	##___##
	##___##
	##___##
	######_
	##_____
	##_____
	##_____
	_______
	_______
	*/

	/* Char:209 "�", Offset:1708 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00, 
	0x3E,
	0x43,
	0x43,
	0x03, 
	0x03, 
	0x03,
	0x43,
	0x43,
	0x3E,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_#####_
	##____#
	##____#
	##_____
	##_____
	##_____
	##____#
	##____#
	_#####_
	_______
	_______
	*/

	/* Char:210 "�", Offset:1722 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x3F,
	0x0C,
	0x0C, 
	0x0C, 
	0x0C,
	0x0C,
	0x0C,
	0x0C, 
	0x0C,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	######
	__##__
	__##__
	__##__
	__##__
	__##__
	__##__
	__##__
	__##__
	______
	______
	*/

	/* Char:211 "�", Offset:1736 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x63,
	0x63,
	0x36,
	0x36,
	0x1C, 
	0x1C, 
	0x18,
	0x0C,
	0x06,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	##___##
	##___##
	_##_##_
	_##_##_
	__###__
	__###__
	___##__
	__##___
	_##____
	_______
	_______
	*/

	/* Char:212 "�", Offset:1750 Byte, Size of:28 Byte, Width:10 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00, 
	0x30,
	0x00, 
	0xFE,
	0x01,
	0x33, 
	0x03,
	0x33, 
	0x03, 
	0x33,
	0x03,
	0x33, 
	0x03, 
	0x33,
	0x03,
	0xFE,
	0x01,
	0x30,
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__________
	__________
	__________
	____##____
	_########_
	##__##__##
	##__##__##
	##__##__##
	##__##__##
	##__##__##
	_########_
	____##____
	__________
	__________
	*/

	/* Char:213 "�", Offset:1778 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x63, 
	0x63,
	0x36,
	0x1C, 
	0x1C,
	0x1C,
	0x36,
	0x63,
	0x63, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	##___##
	##___##
	_##_##_
	__###__
	__###__
	__###__
	_##_##_
	##___##
	##___##
	_______
	_______
	*/

	/* Char:214 "�", Offset:1792 Byte, Size of:28 Byte, Width:9 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0xC3,
	0x00,
	0xC3, 
	0x00,
	0xC3,
	0x00, 
	0xC3, 
	0x00, 
	0xC3,
	0x00,
	0xC3,
	0x00,
	0xC3,
	0x00, 
	0xC3,
	0x00,
	0xFF,
	0x01,
	0x80, 
	0x01, 
	0x80,
	0x01,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_________
	_________
	_________
	##____##_
	##____##_
	##____##_
	##____##_
	##____##_
	##____##_
	##____##_
	##____##_
	#########
	_______##
	_______##
	*/

	/* Char:215 "�", Offset:1820 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00, 
	0xC3,
	0xC3, 
	0xC3,
	0xC3,
	0xC3, 
	0xFE,
	0xC0,
	0xC0,
	0xC0,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	##____##
	##____##
	##____##
	##____##
	##____##
	_#######
	______##
	______##
	______##
	________
	________
	*/

	/* Char:216 "�", Offset:1834 Byte, Size of:28 Byte, Width:12 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00, 
	0x00,
	0x63, 
	0x0C,
	0x63,
	0x0C, 
	0x63,
	0x0C,
	0x63,
	0x0C, 
	0x63,
	0x0C, 
	0x63,
	0x0C,
	0x63,
	0x0C,
	0x63, 
	0x0C, 
	0xFF,
	0x0F,
	0x00,
	0x00,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	____________
	____________
	____________
	##___##___##
	##___##___##
	##___##___##
	##___##___##
	##___##___##
	##___##___##
	##___##___##
	##___##___##
	############
	____________
	____________
	*/

	/* Char:217 "�", Offset:1862 Byte, Size of:28 Byte, Width:13 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00, 
	0x00,
	0x63,
	0x0C, 
	0x63,
	0x0C, 
	0x63,
	0x0C,
	0x63,
	0x0C,
	0x63,
	0x0C,
	0x63, 
	0x0C,
	0x63,
	0x0C,
	0x63,
	0x0C,
	0xFF,
	0x1F,
	0x00,
	0x18, 
	0x00, 
	0x18,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____________
	_____________
	_____________
	##___##___##_
	##___##___##_
	##___##___##_
	##___##___##_
	##___##___##_
	##___##___##_
	##___##___##_
	##___##___##_
	#############
	___________##
	___________##
	*/

	/* Char:218 "�", Offset:1890 Byte, Size of:28 Byte, Width:9 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x0F,
	0x00,
	0x0C,
	0x00,
	0x0C,
	0x00,
	0xFC,
	0x00,
	0x8C,
	0x01,
	0x8C, 
	0x01,
	0x8C, 
	0x01,
	0x8C,
	0x01, 
	0xFC,
	0x00,
	0x00, 
	0x00,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_________
	_________
	_________
	####_____
	__##_____
	__##_____
	__######_
	__##___##
	__##___##
	__##___##
	__##___##
	__######_
	_________
	_________
	*/

	/* Char:219 "�", Offset:1918 Byte, Size of:28 Byte, Width:10 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00, 
	0x00,
	0x03,
	0x03,
	0x03,
	0x03,
	0x03,
	0x03,
	0x3F,
	0x03,
	0x63,
	0x03,
	0x63,
	0x03, 
	0x63,
	0x03, 
	0x63,
	0x03,
	0x3F, 
	0x03,
	0x00,
	0x00, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__________
	__________
	__________
	##______##
	##______##
	##______##
	######__##
	##___##_##
	##___##_##
	##___##_##
	##___##_##
	######__##
	__________
	__________
	*/

	/* Char:220 "�", Offset:1946 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x03,
	0x03,
	0x03, 
	0x3F,
	0x63, 
	0x63,
	0x63, 
	0x63, 
	0x3F,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	##_____
	##_____
	##_____
	######_
	##___##
	##___##
	##___##
	##___##
	######_
	_______
	_______
	*/

	/* Char:221 "�", Offset:1960 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00, 
	0x3E,
	0x61,
	0x61,
	0x60,
	0x7C,
	0x60,
	0x61,
	0x61,
	0x3E,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_#####_
	#____##
	#____##
	_____##
	__#####
	_____##
	#____##
	#____##
	_#####_
	_______
	_______
	*/

	/* Char:222 "�", Offset:1974 Byte, Size of:28 Byte, Width:13 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00, 
	0x00,
	0xC3,
	0x0F,
	0x63, 
	0x18, 
	0x63,
	0x18,
	0x63,
	0x18,
	0x7F,
	0x18, 
	0x63,
	0x18, 
	0x63,
	0x18,
	0x63,
	0x18,
	0xC3,
	0x0F,
	0x00,
	0x00,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____________
	_____________
	_____________
	##____######_
	##___##____##
	##___##____##
	##___##____##
	#######____##
	##___##____##
	##___##____##
	##___##____##
	##____######_
	_____________
	_____________
	*/

	/* Char:223 "�", Offset:2002 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0xFC,
	0xC6,
	0xC6, 
	0xC6,
	0xFC,
	0xD8,
	0xCC,
	0xC6, 
	0xC3,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	__######
	_##___##
	_##___##
	_##___##
	__######
	___##_##
	__##__##
	_##___##
	##____##
	________
	________
	*/

	/* Char:224 "�", Offset:2016 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00, 
	0x00,
	0x00,
	0x1C,
	0x32, 
	0x30, 
	0x3E,
	0x33,
	0x33,
	0x3E,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	______
	______
	__###_
	_#__##
	____##
	_#####
	##__##
	##__##
	_#####
	______
	______
	*/

	/* Char:225 "�", Offset:2030 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00, 
	0x00,
	0x7C,
	0x06,
	0x03,
	0x3F, 
	0x63, 
	0x63,
	0x63,
	0x63,
	0x63, 
	0x3E,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	__#####
	_##____
	##_____
	######_
	##___##
	##___##
	##___##
	##___##
	##___##
	_#####_
	_______
	_______
	*/

	/* Char:226 "�", Offset:2044 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x1F,
	0x33,
	0x33,
	0x1F,
	0x33,
	0x33,
	0x1F,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	______
	______
	#####_
	##__##
	##__##
	#####_
	##__##
	##__##
	#####_
	______
	______
	*/

	/* Char:227 "�", Offset:2058 Byte, Size of:14 Byte, Width:5 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x00,
	0x1F, 
	0x03,
	0x03, 
	0x03,
	0x03, 
	0x03, 
	0x03,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____
	_____
	_____
	_____
	_____
	#####
	##___
	##___
	##___
	##___
	##___
	##___
	_____
	_____
	*/

	/* Char:228 "�", Offset:2072 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x00, 
	0x00,
	0x7C,
	0x6C,
	0x6C, 
	0x6C, 
	0x66, 
	0x66,
	0xFF,
	0xC3,
	0xC3,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	________
	________
	__#####_
	__##_##_
	__##_##_
	__##_##_
	_##__##_
	_##__##_
	########
	##____##
	##____##
	*/

	/* Char:229 "�", Offset:2086 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00, 
	0x00, 
	0x1E, 
	0x33,
	0x33,
	0x3F,
	0x03, 
	0x23, 
	0x1E,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	______
	______
	_####_
	##__##
	##__##
	######
	##____
	##___#
	_####_
	______
	______
	*/

	/* Char:230 "�", Offset:2100 Byte, Size of:28 Byte, Width:10 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00, 
	0x00,
	0x00,
	0x33, 
	0x03,
	0xB6, 
	0x01,
	0xB6,
	0x01,
	0xFC,
	0x00,
	0xB6,
	0x01,
	0xB6,
	0x01,
	0x33,
	0x03,
	0x00,
	0x00,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__________
	__________
	__________
	__________
	__________
	##__##__##
	_##_##_##_
	_##_##_##_
	__######__
	_##_##_##_
	_##_##_##_
	##__##__##
	__________
	__________
	*/

	/* Char:231 "�", Offset:2128 Byte, Size of:14 Byte, Width:5 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x00,
	0x00,
	0x0E,
	0x19,
	0x18,
	0x0E,
	0x18,
	0x19,
	0x0E,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____
	_____
	_____
	_____
	_____
	_###_
	#__##
	___##
	_###_
	___##
	#__##
	_###_
	_____
	_____
	*/

	/* Char:232 "�", Offset:2142 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00, 
	0x21, 
	0x31,
	0x39, 
	0x2D,
	0x27,
	0x23, 
	0x21,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	______
	______
	#____#
	#___##
	#__###
	#_##_#
	###__#
	##___#
	#____#
	______
	______
	*/

	/* Char:233 "�", Offset:2156 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x22, 
	0x1C,
	0x00,
	0x21,
	0x31,
	0x39, 
	0x2D, 
	0x27,
	0x23,
	0x21,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	_#___#
	__###_
	______
	#____#
	#___##
	#__###
	#_##_#
	###__#
	##___#
	#____#
	______
	______
	*/

	/* Char:234 "�", Offset:2170 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00,
	0x33,
	0x1B, 
	0x1B,
	0x0F, 
	0x1B,
	0x1B, 
	0x33, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	______
	______
	##__##
	##_##_
	##_##_
	####__
	##_##_
	##_##_
	##__##
	______
	______
	*/

	/* Char:235 "�", Offset:2184 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x00, 
	0x00,
	0x7E,
	0x66,
	0x66,
	0x66, 
	0x66,
	0x66, 
	0x63,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_______
	_______
	_######
	_##__##
	_##__##
	_##__##
	_##__##
	_##__##
	##___##
	_______
	_______
	*/

	/* Char:236 "�", Offset:2198 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00, 
	0x00,
	0xC3, 
	0xE7,
	0xE7,
	0xDB,
	0xDB,
	0xDB,
	0xC3,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	________
	________
	##____##
	###__###
	###__###
	##_##_##
	##_##_##
	##_##_##
	##____##
	________
	________
	*/

	/* Char:237 "�", Offset:2212 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x63,
	0x63,
	0x63,
	0x7F, 
	0x63,
	0x63,
	0x63, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_______
	_______
	##___##
	##___##
	##___##
	#######
	##___##
	##___##
	##___##
	_______
	_______
	*/

	/* Char:238 "�", Offset:2226 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00, 
	0x3E, 
	0x63,
	0x63,
	0x63,
	0x63,
	0x63, 
	0x3E,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_______
	_______
	_#####_
	##___##
	##___##
	##___##
	##___##
	##___##
	_#####_
	_______
	_______
	*/

	/* Char:239 "�", Offset:2240 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00, 
	0x7F,
	0x63,
	0x63, 
	0x63, 
	0x63,
	0x63,
	0x63,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_______
	_______
	#######
	##___##
	##___##
	##___##
	##___##
	##___##
	##___##
	_______
	_______
	*/

	/* Char:240 "�", Offset:2254 Byte, Size of:14 Byte, Width:7 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x00,
	0x3B,
	0x67, 
	0x63, 
	0x63,
	0x63,
	0x63,
	0x3F, 
	0x03,
	0x03,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_______
	_______
	_______
	_______
	_______
	##_###_
	###__##
	##___##
	##___##
	##___##
	##___##
	######_
	##_____
	##_____
	*/

	/* Char:241 "�", Offset:2268 Byte, Size of:14 Byte, Width:5 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x00, 
	0x00,
	0x1E,
	0x03,
	0x03, 
	0x03, 
	0x03,
	0x03,
	0x1E,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____
	_____
	_____
	_____
	_____
	_####
	##___
	##___
	##___
	##___
	##___
	_####
	_____
	_____
	*/

	/* Char:242 "�", Offset:2282 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x3F,
	0x0C,
	0x0C, 
	0x0C, 
	0x0C,
	0x0C,
	0x0C,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	______
	______
	######
	__##__
	__##__
	__##__
	__##__
	__##__
	__##__
	______
	______
	*/

	/* Char:243 "�", Offset:2296 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x00,
	0x00, 
	0x33,
	0x33,
	0x33,
	0x1E, 
	0x1E, 
	0x0C,
	0x0C,
	0x06,
	0x06,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	______
	______
	##__##
	##__##
	##__##
	_####_
	_####_
	__##__
	__##__
	_##___
	_##___
	*/

	/* Char:244 "�", Offset:2310 Byte, Size of:28 Byte, Width:10 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x00,
	0x30, 
	0x00, 
	0x30, 
	0x00,
	0x30,
	0x00,
	0xFE, 
	0x01, 
	0x33,
	0x03,
	0x33,
	0x03,
	0x33,
	0x03, 
	0x33, 
	0x03,
	0x33,
	0x03,
	0xFE, 
	0x01,
	0x30, 
	0x00,
	0x30,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__________
	__________
	____##____
	____##____
	____##____
	_########_
	##__##__##
	##__##__##
	##__##__##
	##__##__##
	##__##__##
	_########_
	____##____
	____##____
	*/

	/* Char:245 "�", Offset:2338 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00,
	0x33,
	0x33,
	0x1E,
	0x0C,
	0x1E,
	0x33,
	0x33, 
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	______
	______
	##__##
	##__##
	_####_
	__##__
	_####_
	##__##
	##__##
	______
	______
	*/

	/* Char:246 "�", Offset:2352 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00, 
	0x63, 
	0x63,
	0x63,
	0x63,
	0x63, 
	0x63,
	0xFF, 
	0xC0,
	0xC0,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	________
	________
	##___##_
	##___##_
	##___##_
	##___##_
	##___##_
	##___##_
	########
	______##
	______##
	*/

	/* Char:247 "�", Offset:2366 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00,
	0x33,
	0x33, 
	0x33,
	0x33, 
	0x3E,
	0x30,
	0x30, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	______
	______
	##__##
	##__##
	##__##
	##__##
	_#####
	____##
	____##
	______
	______
	*/

	/* Char:248 "�", Offset:2380 Byte, Size of:28 Byte, Width:10 pix, Height:14 pix */
	0x00,
	0x00, 
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x33,
	0x03,
	0x33,
	0x03,
	0x33,
	0x03,
	0x33,
	0x03,
	0x33,
	0x03,
	0x33, 
	0x03,
	0xFF,
	0x03, 
	0x00,
	0x00, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__________
	__________
	__________
	__________
	__________
	##__##__##
	##__##__##
	##__##__##
	##__##__##
	##__##__##
	##__##__##
	##########
	__________
	__________
	*/

	/* Char:249 "�", Offset:2408 Byte, Size of:28 Byte, Width:11 pix, Height:14 pix */
	0x00,
	0x00,
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00,
	0x00, 
	0x00,
	0x33,
	0x03,
	0x33,
	0x03,
	0x33,
	0x03, 
	0x33, 
	0x03,
	0x33,
	0x03, 
	0x33, 
	0x03,
	0xFF,
	0x07,
	0x00,
	0x06,
	0x00,
	0x06,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	___________
	___________
	___________
	___________
	___________
	##__##__##_
	##__##__##_
	##__##__##_
	##__##__##_
	##__##__##_
	##__##__##_
	###########
	_________##
	_________##
	*/

	/* Char:250 "�", Offset:2436 Byte, Size of:14 Byte, Width:8 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00, 
	0x00,
	0x0F,
	0x0C,
	0x7C,
	0xCC,
	0xCC, 
	0xCC,
	0x7C, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	________
	________
	________
	________
	________
	####____
	__##____
	__#####_
	__##__##
	__##__##
	__##__##
	__#####_
	________
	________
	*/

	/* Char:251 "�", Offset:2450 Byte, Size of:28 Byte, Width:9 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x00, 
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00,
	0x83,
	0x01, 
	0x83, 
	0x01,
	0x9F,
	0x01,
	0xB3,
	0x01, 
	0xB3,
	0x01, 
	0xB3,
	0x01,
	0x9F, 
	0x01,
	0x00,
	0x00,
	0x00, 
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_________
	_________
	_________
	_________
	_________
	##_____##
	##_____##
	#####__##
	##__##_##
	##__##_##
	##__##_##
	#####__##
	_________
	_________
	*/

	/* Char:252 "�", Offset:2478 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00, 
	0x00,
	0x00,
	0x00,
	0x00, 
	0x03, 
	0x03, 
	0x1F,
	0x33,
	0x33,
	0x33,
	0x1F, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	______
	______
	______
	______
	______
	##____
	##____
	#####_
	##__##
	##__##
	##__##
	#####_
	______
	______
	*/

	/* Char:253 "�", Offset:2492 Byte, Size of:14 Byte, Width:5 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x0F,
	0x18,
	0x18,
	0x1E, 
	0x18, 
	0x18, 
	0x0F,
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	_____
	_____
	_____
	_____
	_____
	####_
	___##
	___##
	_####
	___##
	___##
	####_
	_____
	_____
	*/

	/* Char:254 "�", Offset:2506 Byte, Size of:28 Byte, Width:10 pix, Height:14 pix */
	0x00, 
	0x00, 
	0x00,
	0x00,
	0x00, 
	0x00,
	0x00, 
	0x00,
	0x00,
	0x00,
	0xF3,
	0x01, 
	0x1B,
	0x03,
	0x1B,
	0x03,
	0x1F,
	0x03, 
	0x1B,
	0x03, 
	0x1B,
	0x03,
	0xF3,
	0x01, 
	0x00, 
	0x00, 
	0x00,
	0x00,
	/* Font:"Tahoma", Height:15 pix, Style:Bold
	__________
	__________
	__________
	__________
	__________
	##__#####_
	##_##___##
	##_##___##
	#####___##
	##_##___##
	##_##___##
	##__#####_
	__________
	__________
	*/

	/* Char:255 "�", Offset:2534 Byte, Size of:14 Byte, Width:6 pix, Height:14 pix */
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x3E,
	0x33, 
	0x33,
	0x33, 
	0x3E,
	0x36, 
	0x33,
	0x00,
	0x00
   /* Font:"Tahoma", Height:15 pix, Style:Bold
   ______
   ______
   ______
   ______
   ______
   _#####
   ##__##
   ##__##
   ##__##
   _#####
   _##_##
   ##__##
   ______
   ______
   */
};

// Character descriptors for Microsoft Sans Serif 14pt
// { [Char width in bits], [Offset into microsoftSansSerif_14ptCharBitmaps in bytes] }
const  uint16_t MSansSerif_10pt_info[][2]  =
//const FONT_CHAR_INFO microsoftSansSerif_14ptDescriptors[] = 
{
	//Width (X pix), Offset (Start Byte)
	{ 2, 0 },
	/*!*/
	{ 5, 14 },
	/*"*/
	{ 8, 28 },
	/*#*/
	{ 7, 42 },
	/*$*/
	{ 13, 56 },
	/*%*/
	{ 8, 84 },
	/*&*/
	{ 2, 98 },
	/*'*/
	{ 4, 112 },
	/*(*/
	{ 4, 126 },
	/*)*/
	{ 6, 140 },
	/***/
	{ 7, 154 },
	/*+*/
	{ 2, 168 },
	/*,*/
	{ 4, 182 },
	/*-*/
	{ 2, 196 },
	/*.*/
	{ 5, 210 },
	/* / */
	{ 8, 224 },
	/*0*/
	{ 8, 238 },
	/*1*/
	{ 8, 252 },
	/*2*/
	{ 8, 266 },
	/*3*/
	{ 8, 280 },
	/*4*/
	{ 8, 294 },
	/*5*/
	{ 8, 308 },
	/*6*/
	{ 8, 322 },
	/*7*/
	{ 8, 336 },
	/*8*/
	{ 8, 350 },
	/*9*/
	{ 2, 364 },
	/*:*/
	{ 2, 378 },
	/*;*/
	{ 8, 392 },
	/*<*/
	{ 7, 406 },
	/*=*/
	{ 8, 420 },
	/*>*/
	{ 6, 434 },
	/*?*/
	{ 9, 448 },
	/*@*/
	{ 8, 476 },
	/*A*/
	{ 7, 490 },
	/*B*/
	{ 7, 504 },
	/*C*/
	{ 8, 518 },
	/*D*/
	{ 6, 532 },
	/*E*/
	{ 5, 546 },
	/*F*/
	{ 7, 560 },
	/*G*/
	{ 8, 574 },
	/*H*/
	{ 4, 588 },
	/*I*/
	{ 5, 602 },
	/*J*/
	{ 7, 616 },
	/*K*/
	{ 6, 630 },
	/*L*/
	{ 10, 644 },
	/*M*/
	{ 7, 672 },
	/*N*/
	{ 8, 686 },
	/*O*/
	{ 7, 700 },
	/*P*/
	{ 8, 714 },
	/*Q*/
	{ 8, 728 },
	/*R*/
	{ 7, 742 },
	/*S*/
	{ 6, 756 },
	/*T*/
	{ 7, 770 },
	/*U*/
	{ 7, 784 },
	/*V*/
	{ 11, 798 },
	/*W*/
	{ 7, 826 },
	/*X*/
	{ 6, 840 },
	/*Y*/
	{ 6, 854 },
	/*Z*/
	{ 4, 868 },
	/*[*/
	{ 5, 882 },
	/*\*/
	{ 4, 896 },
	/*]*/
	{ 8, 910 },
	/*^*/
	{ 8, 924 },
	/*_*/
	{ 4, 938 },
	/*`*/
	{ 6, 952 },
	/*a*/
	{ 7, 966 },
	/*b*/
	{ 5, 980 },
	/*c*/
	{ 7, 994 },
	/*d*/
	{ 6, 1008 },
	/*e*/
	{ 5, 1022 },
	/*f*/
	{ 7, 1036 },
	/*g*/
	{ 7, 1050 },
	/*h*/
	{ 2, 1064 },
	/*i*/
	{ 3, 1078 },
	/*j*/
	{ 6, 1092 },
	/*k*/
	{ 2, 1106 },
	/*l*/
	{ 10, 1120 },
	/*m*/
	{ 7, 1148 },
	/*n*/
	{ 7, 1162 },
	/*o*/
	{ 7, 1176 },
	/*p*/
	{ 7, 1190 },
	/*q*/
	{ 4, 1204 },
	/*r*/
	{ 5, 1218 },
	/*s*/
	{ 5, 1232 },
	/*t*/
	{ 7, 1246 },
	/*u*/
	{ 6, 1260 },
	/*v*/
	{ 10, 1274 },
	/*w*/
	{ 6, 1302 },
	/*x*/
	{ 6, 1316 },
	/*y*/
	{ 5, 1330 },
	/*z*/
	{ 6, 1344 },
	/*{*/
	{ 2, 1358 },
	/*|*/
	{ 6, 1372 },
	/*}*/
	{ 9, 1386 },
	/*~*/
	{ 8, 1414 },
	/*�*/
	{ 7, 1428 },
	/*�*/
	{ 7, 1442 },
	/*�*/
	{ 6, 1456 },
	/*�*/
	{ 9, 1470 },
	/*�*/
	{ 6, 1498 },
	/*�*/
	{ 12, 1512 },
	/*�*/
	{ 7, 1540 },
	/*�*/
	{ 7, 1554 },
	/*�*/
	{ 7, 1568 },
	/*�*/
	{ 7, 1582 },
	/*�*/
	{ 8, 1596 },
	/*�*/
	{ 10, 1610 },
	/*�*/
	{ 8, 1638 },
	/*�*/
	{ 8, 1652 },
	/*�*/
	{ 8, 1666 },
	/*�*/
	{ 7, 1680 },
	/*�*/
	{ 7, 1694 },
	/*�*/
	{ 6, 1708 },
	/*�*/
	{ 7, 1722 },
	/*�*/
	{ 10, 1736 },
	/*�*/
	{ 7, 1764 },
	/*�*/
	{ 9, 1778 },
	/*�*/
	{ 8, 1806 },
	/*�*/
	{ 12, 1820 },
	/*�*/
	{ 13, 1848 },
	/*�*/
	{ 9, 1876 },
	/*�*/
	{ 10, 1904 },
	/*�*/
	{ 7, 1932 },
	/*�*/
	{ 7, 1946 },
	/*�*/
	{ 13, 1960 },
	/*�*/
	{ 8, 1988 },
	/*�*/
	{ 6, 2002 },
	/*�*/
	{ 7, 2016 },
	/*�*/
	{ 6, 2030 },
	/*�*/
	{ 5, 2044 },
	/*�*/
	{ 8, 2058 },
	/*�*/
	{ 6, 2072 },
	/*�*/
	{ 10, 2086 },
	/*�*/
	{ 5, 2114 },
	/*�*/
	{ 6, 2128 },
	/*�*/
	{ 6, 2142 },
	/*�*/
	{ 6, 2156 },
	/*�*/
	{ 7, 2170 },
	/*�*/
	{ 8, 2184 },
	/*�*/
	{ 7, 2198 },
	/*�*/
	{ 7, 2212 },
	/*�*/
	{ 7, 2226 },
	/*�*/
	{ 7, 2240 },
	/*�*/
	{ 5, 2254 },
	/*�*/
	{ 6, 2268 },
	/*�*/
	{ 6, 2282 },
	/*�*/
	{ 10, 2296 },
	/*�*/
	{ 6, 2324 },
	/*�*/
	{ 8, 2338 },
	/*�*/
	{ 6, 2352 },
	/*�*/
	{ 10, 2366 },
	/*�*/
	{ 11, 2394 },
	/*�*/
	{ 8, 2422 },
	/*�*/
	{ 9, 2436 },
	/*�*/
	{ 6, 2464 },
	/*�*/
	{ 5, 2478 },
	/*�*/
	{ 10, 2492 },
	/*�*/
	{ 6, 2520 } /*�*/
	
};

/* Font information for Microsoft Sans Serif 10pt */
// const FONT_INFO microsoftSansSerif_10ptFontInfo =
// {
	// 15, /*  Character height */
	// '!', /*  Start character */
	// 1103, /*  End character */
	// 2, /*  Width, in pixels, of space character */
	// microsoftSansSerif_10ptBlockLookup, /*  Character block lookup */
	// NULL, /*  Character descriptor array */
	// microsoftSansSerif_10ptBitmaps, /*  Character bitmap array */
// };

TSettingfontDot sDotFONT_15 = {
	MSansSerif_10pt,
	&MSansSerif_10pt_info[0][0],
	8,
	14,
	YELLOW,
	BLACK  //GOLD
};




#endif /* FONT_15_H_ */
