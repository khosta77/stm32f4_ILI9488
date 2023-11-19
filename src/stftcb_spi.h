#ifndef SERIAL_TFT_CONTROL_BUS_SPI_H_
#define SERIAL_TFT_CONTROL_BUS_SPI_H_

#include "stftcb_reg.h"

void SPI_init();

void SPI_1byte_mode_on();
void SPI_2byte_mode_on();

void SPI_transmit(uint16_t dt);
void SPI_receiving(uint8_t *dt);

#endif  // SERIAL_TFT_CONTROL_BUS_SPI_H_
