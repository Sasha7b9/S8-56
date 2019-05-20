/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \page page1 Межпроцессорные коммуникации

    \tableofcontents

    \section section1 Межплатный шлейф

    \code
    +----+-------+--------------+----+-------+-------------+----+
    | №  | Наим. |    437ZIT         |       |   429VIT6        |
    |конт|       |     FPGA          |       |   Панель         |
    +----+-------+--------------+----+-------+-------------+----+
    |    |       | 43  PA7      | O  | MODE0 | 8  PC14     | I  |
    |    |       | 44  PC4      | O  | MODE1 | 9  PC15     | I  |
    |    |       | 127 PG12     | I  | READY | 7  PC13     | O  |
    |    |       | 119 PD5  WR  | IO | FL0   | 86 PD5  WR  | IO |
    |    |       | 118 PD4  RD  | IO |       | 85 PD4  RD  | IO |    
    |    |       |              |    |       |             |    |
    |    | AD0   | 85  PD14 D0  | IO | D0    | 97 PE0  DA0 | IO |
    |    | AD1   | 86  PD15 D1  | IO | D1    | 98 PE1  DA1 | IO |
    |    | AD2   | 114 PD0  D2  | IO | D2    | 1  PE2  DA2 | IO |
    |    | AD3   | 115 PD1  D3  | IO | D3    | 2  PE3  DA3 | IO |
    |    | AD4   | 58  PE7  D4  | IO | D4    | 3  PE4  DA4 | IO |
    |    | AD5   | 59  PE8  D5  | IO | D5    | 4  PE5  DA5 | IO |
    |    | AD6   | 60  PE9  D6  | IO | D6    | 5  PE6  DA6 | IO |
    |    | AD7   | 63  PE10 D7  | IO | D7    | 38 PE7  DA7 | IO |
    +----+-------+--------------+----+-------+-------------+----+
    
    M0, M1 означают режим, в котором находится устройство.
    
    +----+----+---------------------------------------------------------------------------+---------------------------------------------------------------------------------+
    | M0 | M1 | Алгоритм работы устройства                                                | Алгоритм работы панели                                                          |
    +----+----+---------------------------------------------------------------------------+---------------------------------------------------------------------------------+
    | 1  | 1  | ***** Обмен запрещён *****                                                |                                                                                 |
    |    |    |                                                                           |                                                                                 |
    | 0  | 1  | ***** Передача данных в панель *****                                      |                                                                                 |
    |    |    | 1. Настроить сигналы:                                                     | Обнаружив такое состояние M0M1, панель выполняет следующие действия:            |
    |    |    |    FL0 - out                                                              | 1. Считывает данные c D0...D7.                                                  |
    |    |    |    D0...D7 - out                                                          | 2. Устанавливает READY в "0".                                                   |
    |    |    | 2. Установить FL0 в "1".                                                  | 3. Ожидает появления на FL0 "0".                                                |
    |    |    | 3. Установить D0...D7.                                                    | 4. Устанавливает READY в "1".                                                   |
    |    |    | 3. Установить M0M1 в состояние "01"                                       | 5. Если M0M1 в состоянии 00 - переход к п.1.                                    |
    |    |    | 4. Дождаться "0" на READY (панель прочитала данные).                      | 5. Выход из процедуры чтения                                                    |
    |    |    | 5. Если данных больше нет - установить 11 на M0M1                         |                                                                                 |
    |    |    | 6. Установить "0" на FL0.                                                 |                                                                                 |
    |    |    | 7. Если есть данные для передачи - перейти к п.3.                         |                                                                                 |
    |    |    | 8. Установить M0M1 в "11".                                                |                                                                                 |
    |    |    |                                                                           |                                                                                 |
    | 1  | 0  | ***** Чтение данных из панели *****                                       |                                                                                 |
    |    |    | 1. Настроить сигналы:                                                     | Обнаружив такое состояние M0M1, панель выполняет следующие действия:            |
    |    |    |    D0...D7 - in                                                           | 1. Переводит D0...D7 в состояние out                                            |
    |    |    | 2. Установить M0M1 в состояние "10".                                      | 2. Устанавливает D0...D7 (если данных для передачи нет, передаёт 0).            |
    |    |    | 3. Дождаться "0" на READY (панель установила данные).                     | 3. Установить READY в "0".                                                      |
    |    |    | 4. Установить M0M1 в "11". Это запрещает дальнейший обмен и даёт панеи    | 4. Дождаться появления "11" на M0M1.                                            |
    |    |    |    понять, что данные прочитаны.                                          | 5. Установить D0...D7 в состояние in, READY в состояние "1".                    |
    +----+----+---------------------------------------------------------------------------+---------------------------------------------------------------------------------+

    \endcode
       

    \section section2 Работа с тестер-компонентом

    \code
    +----+----------+------+-----+--------------------------------------------------------+
    | №  |          |      |     |                                                        |
    |конт|          |      |     |                                                        |
    +----+----------+------+-----+--------------------------------------------------------+
    | 41 | DAC_TEST | PA5  | ЦАП | Сюда подаём напряжение в соотвествии с выбранным шагом |
    | 53 | TEST_ON  | PF13 | OUT | Включение тестер-компонента. Активный уровень - 0      |
    | 54 | PNP      | PF14 | OUT | Отрицательная полярность - 1, положительная - 0        |
    | 55 | U        | PF15 | OUT | 1 - управление напряжением, 0 - управление током       |
    | 56 | I        | PG0  | OUT | 1 - управление током, 0 - управление напряжением       |
    | 99 | TEST_STR | PC9  | IN  | Тактовые имульсы                                       |
    +----+----------+------+-----+--------------------------------------------------------+
    \endcode
    
    Примечания.
    *ШД - шина данных.
*/
