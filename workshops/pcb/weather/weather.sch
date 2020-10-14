EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Smart Things - Home Weather Station"
Date "2020-10-14"
Rev "v1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Espressiv_8266nodemcu:ESP8266NodeMCU U1
U 1 1 5F874528
P 5250 3450
F 0 "U1" H 5250 4517 50  0000 C CNN
F 1 "ESP8266NodeMCU" H 5250 4426 50  0000 C CNB
F 2 "Module:ESP8266_nodeMCU_V1" H 5250 2150 50  0001 C CNN
F 3 "" H 5350 2150 50  0001 C CNN
	1    5250 3450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Barrel_Jack J1
U 1 1 5F875BF7
P 3600 4150
F 0 "J1" H 3657 4475 50  0000 C CNN
F 1 "Barrel_Jack" H 3657 4384 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 3650 4110 50  0001 C CNN
F 3 "~" H 3650 4110 50  0001 C CNN
	1    3600 4150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J2
U 1 1 5F879B0C
P 7200 2950
F 0 "J2" H 7228 2926 50  0000 L CNN
F 1 "Conn_01x04_Female" H 7228 2835 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 7200 2950 50  0001 C CNN
F 3 "~" H 7200 2950 50  0001 C CNN
	1    7200 2950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Female J4
U 1 1 5F87805C
P 7200 3950
F 0 "J4" H 7228 3976 50  0000 L CNN
F 1 "Conn_01x03_Female" H 7228 3885 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7200 3950 50  0001 C CNN
F 3 "~" H 7200 3950 50  0001 C CNN
	1    7200 3950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Female J3
U 1 1 5F876A09
P 7200 3500
F 0 "J3" H 7228 3526 50  0000 L CNN
F 1 "Conn_01x03_Female" H 7228 3435 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7200 3500 50  0001 C CNN
F 3 "~" H 7200 3500 50  0001 C CNN
	1    7200 3500
	1    0    0    -1  
$EndComp
Text Notes 7000 2750 0    43   ~ 0
LCD 16x2
Text Notes 7000 3300 0    43   ~ 0
DHT11\n
Wire Wire Line
	4100 4250 4100 4050
Wire Wire Line
	4100 4050 4350 4050
Wire Wire Line
	3900 4050 4000 4050
Wire Wire Line
	4050 4050 4050 4150
Wire Wire Line
	4050 4150 4250 4150
Wire Wire Line
	6150 2850 7000 2850
Wire Wire Line
	6150 2950 7000 2950
Text Notes 7250 2850 0    43   ~ 0
SCL\n
Text Notes 7250 2950 0    43   ~ 0
SDA
Text Notes 7250 3050 0    43   ~ 0
VCC
Text Notes 7250 3150 0    43   ~ 0
GND
Text Notes 7250 3400 0    43   ~ 0
VCC
Text Notes 7250 3500 0    43   ~ 0
DATA
Text Notes 7250 3600 0    43   ~ 0
GND
Text Notes 7000 3750 0    43   ~ 0
HC-SR501 PIR Sensor
Text Notes 7250 3850 0    43   ~ 0
VCC
Text Notes 7250 3950 0    43   ~ 0
DATA
Text Notes 7250 4050 0    43   ~ 0
GND
Connection ~ 4250 4150
Wire Wire Line
	4250 4150 4350 4150
Wire Wire Line
	4250 4150 4250 4650
Wire Wire Line
	6650 4650 6650 3850
Wire Wire Line
	6650 3050 7000 3050
Wire Wire Line
	7000 3400 6650 3400
Connection ~ 6650 3400
Wire Wire Line
	6650 3400 6650 3050
Wire Wire Line
	7000 3850 6650 3850
Connection ~ 6650 3850
Wire Wire Line
	6650 3850 6650 3400
Wire Wire Line
	7000 4050 6550 4050
Wire Wire Line
	6550 3150 6550 3600
Connection ~ 6550 4050
Wire Wire Line
	7000 3600 6550 3600
Connection ~ 6550 3600
Wire Wire Line
	6550 3600 6550 4050
Wire Wire Line
	7000 3500 6350 3500
Wire Wire Line
	6350 3500 6350 3450
Wire Wire Line
	6350 3450 6150 3450
Wire Wire Line
	7000 3950 6350 3950
Wire Wire Line
	6350 3950 6350 3550
Wire Wire Line
	6350 3550 6150 3550
Wire Wire Line
	4000 4050 4050 4050
Wire Wire Line
	6550 4050 6400 4050
Wire Wire Line
	7000 3150 6550 3150
$Comp
L power:GND #PWR0102
U 1 1 5F8888C5
P 6400 4050
F 0 "#PWR0102" H 6400 3800 50  0001 C CNN
F 1 "GND" H 6405 3877 50  0000 C CNN
F 2 "" H 6400 4050 50  0001 C CNN
F 3 "" H 6400 4050 50  0001 C CNN
	1    6400 4050
	1    0    0    -1  
$EndComp
Connection ~ 6400 4050
Wire Wire Line
	6400 4050 6150 4050
$Comp
L power:+9V #PWR0101
U 1 1 5F885573
P 4000 4050
F 0 "#PWR0101" H 4000 3900 50  0001 C CNN
F 1 "+9V" H 4015 4223 50  0000 C CNN
F 2 "" H 4000 4050 50  0001 C CNN
F 3 "" H 4000 4050 50  0001 C CNN
	1    4000 4050
	1    0    0    -1  
$EndComp
Connection ~ 4000 4050
Wire Wire Line
	4250 4650 6650 4650
Wire Wire Line
	3900 4250 4100 4250
$Comp
L Connector:Conn_01x05_Female J8
U 1 1 5F882423
P 5700 1950
F 0 "J8" V 5592 1662 50  0001 R CNN
F 1 "Conn_01x05_Female" V 5547 1662 50  0001 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 5700 1950 50  0001 C CNN
F 3 "~" H 5700 1950 50  0001 C CNN
	1    5700 1950
	0    -1   -1   0   
$EndComp
Text Notes 5400 1900 0    43   ~ 0
D0, D3, D4, D7, D8
Wire Wire Line
	6150 2750 5900 2750
Wire Wire Line
	5900 2750 5900 2150
Wire Wire Line
	6150 3050 5800 3050
Wire Wire Line
	5800 3050 5800 2150
Wire Wire Line
	6150 3150 5700 3150
Wire Wire Line
	5700 3150 5700 2150
Wire Wire Line
	6150 3650 5600 3650
Wire Wire Line
	5600 3650 5600 2150
Wire Wire Line
	6150 3750 5500 3750
Wire Wire Line
	5500 3750 5500 2150
$Comp
L Connector:Conn_01x02_Female J7
U 1 1 5F889B2E
P 5100 1950
F 0 "J7" V 4992 1762 50  0001 R CNN
F 1 "Conn_01x02_Female" V 4947 1762 50  0001 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5100 1950 50  0001 C CNN
F 3 "~" H 5100 1950 50  0001 C CNN
	1    5100 1950
	0    -1   -1   0   
$EndComp
Text Notes 5050 1900 0    43   ~ 0
TX,RX
Wire Wire Line
	6150 3850 5200 3850
Wire Wire Line
	5200 3850 5200 2150
Wire Wire Line
	6150 3950 5100 3950
Wire Wire Line
	5100 3950 5100 2150
$Comp
L Connector:Conn_01x01_Female J6
U 1 1 5F88DFE0
P 4900 1950
F 0 "J6" V 4838 1862 50  0001 R CNN
F 1 "Conn_01x01_Female" V 4792 1862 50  0001 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4900 1950 50  0001 C CNN
F 3 "~" H 4900 1950 50  0001 C CNN
	1    4900 1950
	0    -1   -1   0   
$EndComp
Text Notes 4850 1900 0    43   ~ 0
A0
Wire Wire Line
	4900 2150 4900 2750
Wire Wire Line
	4900 2750 4350 2750
$Comp
L Connector:Conn_01x08_Female J5
U 1 1 5F890933
P 3400 3050
F 0 "J5" H 3292 3443 50  0001 C CNN
F 1 "Conn_01x08_Female" H 3292 3444 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 3400 3050 50  0001 C CNN
F 3 "~" H 3400 3050 50  0001 C CNN
	1    3400 3050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4350 3950 3600 3950
Wire Wire Line
	3600 3950 3600 3450
Wire Wire Line
	4350 3850 3700 3850
Wire Wire Line
	3700 3850 3700 3350
Wire Wire Line
	3700 3350 3600 3350
Wire Wire Line
	4350 3550 3750 3550
Wire Wire Line
	3750 3550 3750 3250
Wire Wire Line
	3750 3250 3600 3250
Wire Wire Line
	4350 3450 3800 3450
Wire Wire Line
	3800 3450 3800 3150
Wire Wire Line
	3800 3150 3600 3150
Wire Wire Line
	4350 3350 3850 3350
Wire Wire Line
	3850 3350 3850 3050
Wire Wire Line
	3850 3050 3600 3050
Wire Wire Line
	4350 3250 3900 3250
Wire Wire Line
	3900 3250 3900 2950
Wire Wire Line
	3900 2950 3600 2950
Wire Wire Line
	4350 3150 4000 3150
Wire Wire Line
	4000 3150 4000 2850
Wire Wire Line
	4000 2850 3600 2850
Wire Wire Line
	4350 3050 4050 3050
Wire Wire Line
	4050 3050 4050 2750
Wire Wire Line
	4050 2750 3600 2750
$EndSCHEMATC
