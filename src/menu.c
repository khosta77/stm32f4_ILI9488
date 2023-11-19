#include "./menu.h"

/*=========================================================================================================*/
/*                                          MENU_00_NOP                                                    */
/*=========================================================================================================*/
uint8_t nop() {
    GPIOD->ODR |= GPIO_ODR_OD12;
    for (uint32_t t = 0; t < 0xFFFFFF; t++);
    GPIOD->ODR &= ~GPIO_ODR_OD12;
    return 0x00;
}
/*=========================================================================================================*/
/*                                      MENU_01_SEND_DISPLAY_INFO                                          */
/*=========================================================================================================*/
uint8_t send_display_info() {
    char disinfo[] = "ST7735 128x160 RGB565;ILI9341-240x320-RGB565";
    memcpy(&usart2_tx_array[0], disinfo, strlen(disinfo) + 1);
    usart2_mrk = 0x00;
    DMA1_Stream6->NDTR = 128;
    DMA1_Stream6->CR |= DMA_SxCR_EN;
    return 0x00;
}
/*=========================================================================================================*/
/*                                      MENU_02_SEND_DISPLAY_RANGE                                         */
/*=========================================================================================================*/
static void write_display_range() {
    uint16_t x = STFTCB_WIDTH;
    uint16_t y = STFTCB_HEIGHT;
    uint8_t range[4] = { (uint8_t)((x >> 8) & 0xFF), (uint8_t)(x & 0xFF),
                         (uint8_t)((y >> 8) & 0xFF), (uint8_t)(y & 0xFF)};
    usart2_tx_array[0] = range[1];
    usart2_tx_array[1] = range[0];
    usart2_tx_array[2] = range[3];
    usart2_tx_array[3] = range[2];
}

uint8_t send_display_range() {
    write_display_range();
    usart2_mrk = 0x00;
    DMA1_Stream6->NDTR = 4;
    DMA1_Stream6->CR |= DMA_SxCR_EN;
    return 0x00;
}
/*=========================================================================================================*/
/*                                          MENU_03_PRINT_IMAGE                                            */
/*=========================================================================================================*/
static void memcpy_from_usart2arraytx_to_stftcbarraytxX() {
    if (stftcb_array_tx_mxar == 0)
        for (uint16_t i = 0; i < STFTCB_ARRAY_SIZE; ++i)
            stftcb_array_tx_0[i] = usart2_rx_array[i];
    else
        for (uint16_t i = 0; i < STFTCB_ARRAY_SIZE; ++i)
            stftcb_array_tx_1[i] = usart2_rx_array[i];
}

static void line_printer_init() {
    count_l            = 0;          // Сбрасываем размер выведенного кадра
    usart2_tx_array[0] = 0xFF;       // Команда подтверждающая передачу
    usart2_mrk         = USART_NOP;  // Сброс состояния USART2

    DMA1_Stream6->CR &= ~DMA_SxCR_EN;
    while ((DMA1_Stream6->CR) & DMA_SxCR_EN){;}
    DMA1_Stream6->CR |= DMA_SxCR_MINC;
    DMA1_Stream6->NDTR = 1;

    DMA1_Stream5->CR &= ~DMA_SxCR_EN;
    while ((DMA1_Stream5->CR) & DMA_SxCR_EN){;}
    DMA1_Stream5->CR |= DMA_SxCR_MINC;
    DMA1_Stream5->NDTR = STFTCB_ARRAY_SIZE;

    DMA1_Stream6->CR |= DMA_SxCR_EN;
}

static void line_rx_draw_frame() {
    if (usart2_mrk == USART_RX_ACTIVE) {
        memcpy_from_usart2arraytx_to_stftcbarraytxX();
        stftcb_updateFrame();
        usart2_mrk = 0x00;
        DMA1_Stream6->CR |= DMA_SxCR_EN;  // Подтверждаем, что считали массив. Отправив 0xFF на ПК
    }
}

static void line_tx_info_to_PC() {
    if (usart2_mrk == USART_TX_ACTIVE) {
        usart2_mrk = 0x00;
        DMA1_Stream5->CR |= DMA_SxCR_EN;  // Открываем канал записи, для новой строки.
    }
}

static void line_loop_tx_A_rx() {
    while (count_l != STFTCB_HEIGHT) {
        line_rx_draw_frame();
        line_tx_info_to_PC();
    }
}

uint8_t print_lines() {
    line_printer_init();
    line_loop_tx_A_rx();
    return message_out();
}
/*=========================================================================================================*/
/*                      Функции объявления области выделения кадра                                         */
/*=========================================================================================================*/
uint16_t colors[] = {
    STFTCB_COLOR_BLACK,
    STFTCB_COLOR_WHITE,
    STFTCB_COLOR_BLUE,
    STFTCB_COLOR_RED,
    STFTCB_COLOR_GREEN,
    STFTCB_COLOR_MAGENTA,
    STFTCB_COLOR_YELLOW
};
const uint8_t COLORS_SIZE = 7;//(sizeof(colors) / sizeof(colors[0]));

static void rainbow() {
    static uint16_t color = 0x00;
    if (color == COLORS_SIZE)
            color = 0x00;
    GPIOD->ODR |= GPIO_ODR_OD12;
    stftcb_FillBackground(colors[color]);
    GPIOD->ODR &= ~GPIO_ODR_OD12;
    ++color;
}

uint8_t rainbows() {
    rainbow();
    return 0x00;
}
/*=========================================================================================================*/
/*                      Меню выбора действия по USART2                                                     */
/*=========================================================================================================*/
static uint8_t message_in_menu() {
    switch (usart2_rx_array[0]) {
        case MENU_00_NOP:
            return nop();
        case MENU_01_SEND_DISPLAY_INFO:
            return send_display_info();
        case MENU_02_SEND_DISPLAY_RANGE:
            return send_display_range();
        case MENU_03_PRINT_IMAGE:
            return print_lines();
        case MENU_04_RAINBOWS:
            return rainbows();
        default:
            message_out();
    }
}

void message_in() {
    uint8_t msg_loop = message_in_menu();
}

uint8_t message_out() {
    DMA1_Stream5->CR &= ~DMA_SxCR_EN;
    while ((DMA1_Stream5->CR) & DMA_SxCR_EN){;}
    usart2_mrk = 0x00;
    DMA1_Stream5->NDTR = SIZE_CMD;
    DMA1_Stream5->CR |= DMA_SxCR_EN;
    return 0x00;
}


