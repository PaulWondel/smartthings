EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Espressiv_8266nodemcu:ESP8266NodeMCU U?
U 1 1 5F874528
P 5250 3450
F 0 "U?" H 5250 4517 50  0000 C CNN
F 1 "ESP8266NodeMCU" H 5250 4426 50  0000 C CNB
F 2 "smart_things_PCBv1:ESP8266_nodeMCU_V1" H 5250 2150 50  0001 C CNN
F 3 "" H 5350 2150 50  0001 C CNN
	1    5250 3450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Barrel_Jack J?
U 1 1 5F875BF7
P 3600 4150
F 0 "J?" H 3657 4475 50  0000 C CNN
F 1 "Barrel_Jack" H 3657 4384 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 3650 4110 50  0001 C CNN
F 3 "~" H 3650 4110 50  0001 C CNN
	1    3600 4150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J?
U 1 1 5F879B0C
P 7200 2950
F 0 "J?" H 7228 2926 50  0000 L CNN
F 1 "Conn_01x04_Female" H 7228 2835 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 7200 2950 50  0001 C CNN
F 3 "~" H 7200 2950 50  0001 C CNN
	1    7200 2950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Female J?
U 1 1 5F87805C
P 7200 3950
F 0 "J?" H 7228 3976 50  0000 L CNN
F 1 "Conn_01x03_Female" H 7228 3885 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Horizontal" H 7200 3950 50  0001 C CNN
F 3 "~" H 7200 3950 50  0001 C CNN
	1    7200 3950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Female J?
U 1 1 5F876A09
P 7200 3500
F 0 "J?" H 7228 3526 50  0000 L CNN
F 1 "Conn_01x03_Female" H 7228 3435 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Horizontal" H 7200 3500 50  0001 C CNN
F 3 "~" H 7200 3500 50  0001 C CNN
	1    7200 3500
	1    0    0    -1  
$EndComp
Text Notes 7000 2750 0    43   ~ 0
LCD 16x2
Text Notes 7000 3300 0    43   ~ 0
DHT11\n
Wire Wire Line
	3900 4250 4100 4250
Wire Wire Line
	4100 4250 4100 4050
Wire Wire Line
	4100 4050 4350 4050
Wire Wire Line
	3900 4050 4050 4050
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
	4250 4650 6650 4650
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
	7000 3150 6550 3150
Wire Wire Line
	6550 3150 6550 3600
Connection ~ 6550 4050
Wire Wire Line
	6550 4050 6150 4050
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
$EndSCHEMATC
