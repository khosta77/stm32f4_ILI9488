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
* [ ] ~DMA.~
    * [ ] ~Запись данных с разных массивов~
* [ ] Алгоритмы
    * [ ] Реализовать различные алгоритмы для работы с дисплеем
        * [X] Точка
        * [X] Горизонтальная прямая
        * [X] Вертикальная прямая
        * [X] Диагональ
        * [X] Прямоугольник не закрашенный
        * [ ] Прямоугольник закрашенный
        * [ ] Окружность 
        * [ ] Треугольник
    * [ ] Возможность выводить текст на экран
        * [ ] Англиский 8x8
        * [ ] Русский 8x8
        * [ ] Масштабирование шрифта
* [ ] ST7735
    * [ ] Применить все полученные функции
