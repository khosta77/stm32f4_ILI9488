#ifndef SERIAL_TFT_CONTROL_BUS_H_
#define SERIAL_TFT_CONTROL_BUS_H_

#include "stftcb_reg.h"

// Объявление существования массива для передачи данных
extern uint8_t stftcb_array_tx_0[1024];
extern uint8_t stftcb_array_tx_1[1024];

// Переменная статуса
extern uint8_t stftcb_array_tx_status;
extern uint8_t stftcb_array_tx_mxar;

extern uint16_t count_l;

/// Функция инициализации
void STFTCB_init();

//// Отправка команды, либо данных настройки по SPI в обход DMA
// Одно байтовый формат
void stftcb_sendCmd1byte(uint8_t cmd);
void stftcb_sendData1byte(uint8_t dt);

// Дву байтовый формат
void stftcb_sendCmd2byte(uint16_t cmd);
void stftcb_sendData2byte(uint16_t dt);

// Массив с настройкой
void stftcb_sendCmd(uint8_t address, uint8_t *data, uint16_t size);

//// Работа с кадром
// Задача размеров окна
void stftcb_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void stftcb_SetFullAddressWindow();

// Обоновление кадра
void stftcb_updateFrame();

//// Функции отрисовки объектов
void stftcb_FillBackground(uint16_t color);

//// Вывод текста
//void printt(uint16_t x0, uint16_t y0, const char *str);
//void printT(uint16_t x0, uint16_t y0, const char *str);

#endif  // SERIAL_TFT_CONTROL_BUS_H_
