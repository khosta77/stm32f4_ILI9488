# stm32f4_STFTCB

## Сборка
```
$ make all; sudo openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c \
"init; reset halt; flash write_image erase main.hex; "\  
"reset; exit"
```

## todo

* [ ] SPI
    * [ ] Настроить возможность считывать данных с дисплея
* [X] DMA
    * [X] Запись данных с разных массивов
* [ ] Алгоритмы
    * [X] Реализовать различные алгоритмы для работы с дисплеем
        * [X] Точка
        * [X] Горизонтальная прямая
        * [X] Вертикальная прямая
        * [X] Диагональ
        * [X] Прямоугольник не закрашенный
        * [X] Прямоугольник закрашенный
        * [X] Окружность не закрашенная
        * [X] Окружность закрашенная
        * [ ] ~Треугольник не закрашеный~
        * [ ] ~Треугольник закрашенный~
    * [ ] Возможность выводить текст на экран
        * [ ] Англиский 8x8
        * [ ] Русский 8x8
        * [ ] Масштабирование шрифта
* [ ] ST7735
    * [ ] Применить все полученные функции
