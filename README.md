# Creating a computer interface device for analog measurement eqipment using ATmega168 microcontroller
[РУССКАЯ ВЕРСИЯ НИЖЕ](https://github.com/Tyomix/university-EPR#Изготовление-устройства-сопряжения-с-компьютером-для-аналоговых-измерительных-приборов-на-базе-микроконтроллера-ATmega168)

The purpose of this project is the development of an analog-to-digital converter module for RE-1301 electron paramagnetic resonance (EPR) spectrometer. The development of ADC device is based on Atmel ATmega168-20PU 8-bit microcontroller, which has numerous features and a very reasonable price.

This microcontroller has all the features which are needed for this project such as 16-bit timer, 16 kB ROM, 1 kB RAM and 10-bit successive-approximation ADC with sampling rate up to 200 kHz and 6 channel multiplication opportunity.  More than that there is a free software implementation of USB 1.1 interface called V-USB which makes possible data connection between PC and microcontroller via USB. Using USB interface makes  this device more usable as compared with analogs which use simpler but obsolete interfaces. 

![](https://github.com/Tyomix/university-EPR/blob/main/1.png?raw=true)

_Figure 1. Circuit diagram of the device._

Figure 1 shows the circuit diagram of the designed device. The microcontroller IC1 is powered directly from USB port of PC. VD1 and VD2 zener diodes are used for adapting 5V output signals of the microcontroller with USB standard D+ and D- signal voltage which is 3.3V. The R3 and R4 resistors form a voltage divider which provides 3.3V at D-  line in the absence of a signal. This allows the computer to recognize USB protocol version. The microcontroller is clocked by Z1 quartz resonator.  IC2 operational amplifier is powered by +12 and -12 lines of a computer power supply unit. This chip is needed to control the level of the signal applied to the input of the microcontroller (using R8 potentiometer) and to adjust the null point (using R7 potentiometer). The output of the operational amplifier is connected to the microcontroller through R6 resistor and diodes VD3-VD6. They protect the input of the ADC from negative and very high voltage. ADC uses an internal reference voltage of 1.1V. C5 capacitor smoothes pulses of this reference voltage. The assembled device was mounted inside a computer case and connected through internal USB port. 
To accomplish this project we had to write a firmware for ATmega168. Atmel AVR Studio 4 with AVR GCC Toolchain add-on was used for developing the firmware. The source code of the firmware is written in C programming language. The microcontroller acts using USB human interface device class (USB HID) in our system. Windows operating systems already have required drivers to host such devices.

The data processing software for PC was written in order to operate with the microcontroller and to process the data obtained.  Figure 2 shows a user interface of this software. The program processes the received data in real time. The collected data is stores in a physical memory and are shown in a text field. There is an opportunity to preview a graph plotted according to the data of selected ADC channel. After making all the measurements a user can save the data in a text file for further working.

![](https://github.com/Tyomix/university-EPR/blob/main/2.png?raw=true)

_Figure 2. User interface of the data processing software._

Thus the system has the following characteristics:
- 4 ADC channels: one with preamplifier intended to work with output signal of EPR spectrometer and three others may be used for additional related experimental equipment (e.g. temperature sensors);
- ADC resolution: 8 bit; 
- Maximum sampling frequency: 100 Hz;
- Noise level: 2% max.


# Изготовление устройства сопряжения с компьютером для аналоговых измерительных приборов на базе микроконтроллера ATmega168

Цель работы заключалась в разработке и изготовлении модуля аналого-цифрового преобразователя для радиоспектрометра РЭ1301. Одним из наиболее экономичных вариантов является АЦП на базе 8-битного микроконтроллера архитектуры AVR – ATmega168-20PU, производимого фирмой Atmel.
Рассматриваемый микроконтроллер имеет все возможности, необходимые для данного проекта – 10-битный АЦП последовательного приближения с частотой преобразования до 200 кГц и возможностью мультиплексирования до 6 каналов; 16-битный таймер; 16 кБ ПЗУ для программы и 1 кБ оперативной памяти. Кроме того, для данного микроконтроллера существует свободно распространяемая  программная реализация low-speed USB 1.1 – V-USB, которая позволяет осуществить обмен данными с компьютером через порт USB. Именно использование USB выгодно отличает данное устройство от аналогов с более простыми, но устаревшими интерфейсами, поскольку порты USB имеются на любом современном ПК.
На основе микроконтроллера ATmega168 была разработана следующая принципиальная схема:

![](https://github.com/Tyomix/university-EPR/blob/main/1.png?raw=true)

_Рис. 1. Принципиальная схема устройства._

Питание на микроконтроллер IC1 (5В) подается непосредственно с USB порта ЭВМ (рис. 1). Поскольку в USB уровень сигнала на линиях D+ и D- составляет 3.3В, а схему подключили к 5В, для согласования установлены стабилитроны VD1 и VD2, которые уменьшают сигнал с микроконтроллера на гасящих резисторах R1, R2 до уровня необходимого по стандарту. Для определения версии протокола в схеме задействован делитель напряжения на резисторах R3 и R4, который обеспечивает 3.4В для линии D- при отсутствии сигнала. Тактовая частота микроконтроллера задается кварцевым резонатором Z1. Операционный усилитель К553УД1, который питается от линий +12В и -12В блока питания ЭВМ, включен по инвертирующей схеме. Он служит для регулировки уровня сигнала на входе АЦП микроконтроллера (при помощи резистора R8), а также смещения нулевой точки (при помощи резистора R7). Вход операционного усилителя через разъём подключен к усилителю сигнала У5-11. Выход К553УД1 подключен к 3 каналу АЦП микроконтроллера через резистор R6 и диоды VD3-VD6, которые защищают вход АЦП от отрицательного или слишком высокого напряжения. АЦП использует внутренний источник опорного напряжения 1.1В. Для сглаживания пульсаций опорного напряжения служит конденсатор C5.

Программное обеспечение (ПО), используемое в данном проекте включает следующее:
- управляющая микропрограмма для микроконтроллера ATmega168,
- программа для обработки данных.

Для написания программы микроконтроллера была использована среда разработки от Atmel – AVR Studio 4 с дополнением AVR GCC Toolchain, которое представляет собой свободный (GNU GPL version 2) C++ компилятор.

В разрабатываемом приборе микроконтроллер работает с ЭВМ (хостом) через USB, представляясь устройством USB HID (human interface device) класса, т.е. устройством ввода. Для работы с такими устройствами в системе Windows уже имеется стандартный драйвер, который и будет использоваться программой.
Для связи с микроконтроллером и обработки полученных данных была разработана специальная программа. Ее интерфейс показан на рис. 2. В задачу данного ПО входит обнаружение устройства и подключение к нему, а затем получение данных измерений и показаний таймера.

Программа в реальном времени обрабатывает полученные данные и показания таймера. Собранные данные программа хранит в оперативной памяти ПК и выводит их в поле для просмотра. Также для выбранного канала данных программа строит график, позволяющий наблюдать зависимость напряжения на входе АЦП от времени. Непосредственно во время измерения пользователь может изменять параметры графика. После измерения полученные данные можно сохранить в текстовом файле для осуществления их дальнейшей обработки.

![](https://github.com/Tyomix/university-EPR/blob/main/2.png?raw=true)

_Рис. 2. Интерфейс программы обработки данных_

Таким образом, полученный блок сопряжения обладает следующими характеристиками:
- Количество каналов: 4 – один с внешним предусилителем и регулировкой нулевой точки, три – без предусилителя (диапазон измерений 0 – 1.1 В).
- Разрядность АЦП: 8 бит.
- Максимальная частота преобразования: 100 Гц.
- Уровень шумов относительно предела измерений: не более 2%.
