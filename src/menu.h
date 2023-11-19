#ifndef MENU_H_
#define MENU_H_

#include "../system/include/cmsis/stm32f4xx.h"

#include "./stftcb.h"
#include "./usart2.h"

#include <string.h>

#define MENU_00_NOP                0x00
#define MENU_01_SEND_DISPLAY_INFO  0x01
#define MENU_02_SEND_DISPLAY_RANGE 0x02
#define MENU_03_PRINT_IMAGE        0x03
#define MENU_04_RAINBOWS           0x04

uint8_t nop();
uint8_t send_display_info();
uint8_t send_display_range();
uint8_t print_lines();
uint8_t rainbows();

void message_in();
uint8_t message_out();

#endif  // MENU_H_
