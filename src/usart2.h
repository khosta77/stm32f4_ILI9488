#ifndef USART2_H_
#define USART2_H_

#include "../system/include/cmsis/stm32f4xx.h"

#include "./stftcb.h"

#define USART_SIZE 1024
#define SIZE_CMD 2
#define CPU_CLOCK SystemCoreClock
#define MY_BDR 460900  // На ПК отношение 1 к 4
#define MYBRR (CPU_CLOCK / (16 * MY_BDR))

#define USART_NOP       0x00
#define USART_TX_ACTIVE 0xA0
#define USART_RX_ACTIVE 0x0A

extern uint8_t usart2_mrk;
extern uint8_t usart2_rx_array[USART_SIZE];
extern uint8_t usart2_tx_array[USART_SIZE];

void USART2_init();

#endif  // USART2_H_
