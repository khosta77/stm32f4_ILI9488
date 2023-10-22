#ifndef SERIAL_TFT_CONTROL_BUS_H_
#define SERIAL_TFT_CONTROL_BUS_H_

#include "stftcb_reg.h"

// Объявление существования массива для передачи данных
extern uint16_t stftcb_array_tx_0[STFTCB_SIZE];
extern uint16_t stftcb_array_tx_1[STFTCB_SIZE];

// Переменная статуса
uint8_t stftcb_array_tx_status = 0x00;
uint8_t stftcb_array_tx_mxar = 0x00;

//// Функция инициализации
void STFTCB_init();

//// Отправка команды, либо данных настройки по SPI в обход DMA
// Одно байтовый формат
void stftcb_sendCmd1byte(uint8_t cmd);
void stftcb_sendData1byte(uint8_t dt);

// Дву байтовый формат
void stftcb_sendCmd2byte(uint16_t cmd);
void stftcb_sendData2byte(uint16_t dt);

//// Работа с кадром
// Задача размеров окна
#if (STFTCB_WIDTH < 0xFF)
void stftcb_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
#else
void stftcb_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
#endif
void stftcb_SetFullAddressWindow();

// Обоновление кадра
void stftcb_updateFrame();

//// Функции отрисовки объектов
void stftcb_DrawFillBackground(uint16_t color);
void stftcb_DrawPixel(uint16_t y, uint16_t x, uint16_t color);
uint8_t stftcb_DrawHorizonLine(uint16_t y, uint16_t x0, uint16_t x1, uint16_t color);
uint8_t stftcb_DrawVerticalLine(uint16_t x, uint16_t y0, uint16_t y1, uint16_t color);
void stftcb_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void stftcb_DrawNoFillRectangle(uint16_t x0, uint16_t y0, uint16_t x2, uint16_t y2, float alpha, uint16_t color);
void stftcb_DrawFillRectangle(uint16_t x0, uint16_t y0, uint16_t x2, uint16_t y2, float alpha, uint16_t color);
//void stftcb_DrawNoFillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
//                               float alpha, uint16_t color);
//void stftcb_DrawFillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
//                             float alpha, uint16_t color);
void stftcb_DrawNoFillCicle(int16_t x0, int16_t y0, int16_t R, uint16_t color);
void stftcb_DrawFillCicle(int16_t x0, int16_t y0, int16_t R, uint16_t color);

//// Вывод текста
void printt(uint16_t x0, uint16_t y0, const char *str);
void printT(uint16_t x0, uint16_t y0, const char *str);


/** @brief DMA2_Stream3_IRQHandler - прерывание при завершение передачи данных по SPI
 * */
void DMA2_Stream3_IRQHandler(void) {
    if (STFTCB_SPI_DMA_TCIF) {  // Прерывания по завершению передачи
	GPIOD->ODR ^= GPIO_ODR_OD15;
	stftcb_array_tx_status = 0x00;
	STFTCB_SPI_DMA_SxCR->CR &= ~DMA_SxCR_EN;
        STFTCB_SPI_DMA_CTCIF; 
	}
}

#endif  // SERIAL_TFT_CONTROL_BUS_H_
