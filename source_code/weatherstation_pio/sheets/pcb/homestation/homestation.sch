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
L MCU_Espressiv_8266nodemcu:ESP8266NodeMCU U1
U 1 1 5FB07934
P 5300 3250
F 0 "U1" H 5300 4317 50  0001 C CNN
F 1 "ESP8266NodeMCU" H 5300 4226 50  0000 C CNB
F 2 "esp8266_nodemcu:ESP8266_nodeMCU_V1" H 5300 1950 50  0001 C CNN
F 3 "" H 5400 1950 50  0001 C CNN
	1    5300 3250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Barrel_Jack J4
U 1 1 5FB128B3
P 4250 4800
F 0 "J4" V 4353 4620 50  0001 R CNN
F 1 "Barrel Jack Power Connecter (9 volt input)" V 4307 4620 50  0000 R CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 4300 4760 50  0001 C CNN
F 3 "~" H 4300 4760 50  0001 C CNN
	1    4250 4800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4150 3950 4400 3950
Wire Wire Line
	4350 3850 4400 3850
Text Label 4150 4400 1    50   ~ 0
Vcc(9v)
Text Label 4350 4400 1    50   ~ 0
GND
Wire Wire Line
	4150 4500 4150 3950
$Comp
L Device:R R2
U 1 1 5FB206BB
P 3500 4600
F 0 "R2" H 3570 4646 50  0000 L CNN
F 1 "1.5K ohm" H 3570 4555 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3430 4600 50  0001 C CNN
F 3 "~" H 3500 4600 50  0001 C CNN
	1    3500 4600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5FB2121B
P 3500 4100
F 0 "R1" H 3570 4146 50  0000 L CNN
F 1 "1.2K ohm" H 3570 4055 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3430 4100 50  0001 C CNN
F 3 "~" H 3500 4100 50  0001 C CNN
	1    3500 4100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Female J3
U 1 1 5FB17800
P 3600 3350
F 0 "J3" H 3492 3635 50  0001 C CNN
F 1 "DHT11" H 3492 3559 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 3600 3350 50  0001 C CNN
F 3 "~" H 3600 3350 50  0001 C CNN
	1    3600 3350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4350 3850 4350 4450
Wire Wire Line
	4150 3950 3500 3950
Connection ~ 4150 3950
Wire Wire Line
	3500 4750 4050 4750
Wire Wire Line
	4050 4450 4350 4450
Wire Wire Line
	4050 4450 4050 4750
Connection ~ 4350 4450
Wire Wire Line
	4350 4450 4350 4500
$Comp
L Connector:Conn_01x04_Female J1
U 1 1 5FB28744
P 2650 4300
F 0 "J1" H 2542 4585 50  0001 C CNN
F 1 "Converted Voltage" H 2542 4513 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 2650 4300 50  0001 C CNN
F 3 "~" H 2650 4300 50  0001 C CNN
	1    2650 4300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2900 4750 2900 4500
Wire Wire Line
	2900 4500 2850 4500
Connection ~ 3500 4750
Wire Wire Line
	2900 4500 2900 4400
Wire Wire Line
	2900 4400 2850 4400
Connection ~ 2900 4500
Wire Wire Line
	2900 4300 2900 4200
Wire Wire Line
	2900 4200 2850 4200
Connection ~ 2900 4300
Wire Wire Line
	2900 4300 2850 4300
Wire Notes Line
	4000 4900 4000 3850
Wire Notes Line
	2400 3850 2400 4900
Text Notes 2500 3800 0    50   ~ 0
9 volt to 5 volt converter
Text Label 2900 4300 0    50   ~ 0
Vcc(5v)
Wire Wire Line
	3500 4250 3500 4300
Connection ~ 3500 4300
Wire Wire Line
	3500 4300 3500 4450
Wire Wire Line
	2900 4750 3500 4750
Text Label 2900 4750 0    50   ~ 0
GND
Wire Wire Line
	4400 2850 3800 2850
Wire Wire Line
	4400 2950 4250 2950
Wire Wire Line
	4250 2950 4250 3350
Wire Wire Line
	4250 3350 3800 3350
Wire Wire Line
	2900 4300 3250 4300
Wire Wire Line
	3400 4300 3400 3900
Wire Wire Line
	3400 3900 3950 3900
Wire Wire Line
	3950 3900 3950 3250
Wire Wire Line
	3950 3250 3800 3250
Connection ~ 3400 4300
Wire Wire Line
	3400 4300 3500 4300
Wire Wire Line
	3950 3250 3950 2750
Wire Wire Line
	3950 2750 3800 2750
Connection ~ 3950 3250
Wire Wire Line
	4400 3450 4150 3450
Wire Wire Line
	3800 2950 4150 2950
Wire Wire Line
	4150 2950 4150 3450
Connection ~ 4150 3450
Wire Wire Line
	4150 3450 3800 3450
Wire Notes Line
	2400 4900 4000 4900
Wire Notes Line
	2400 3850 4000 3850
$Comp
L Connector:Conn_01x03_Female J6
U 1 1 5FB39652
P 7400 3450
F 0 "J6" H 7428 3476 50  0001 L CNN
F 1 "Hal Effect Sensor" H 7192 3705 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7400 3450 50  0001 C CNN
F 3 "~" H 7400 3450 50  0001 C CNN
	1    7400 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 4300 3250 5150
Wire Wire Line
	3250 5150 6850 5150
Connection ~ 3250 4300
Wire Wire Line
	3250 4300 3400 4300
Wire Wire Line
	7200 3450 6200 3450
Wire Wire Line
	6200 3150 6550 3150
Wire Wire Line
	7000 3150 7000 3350
Wire Wire Line
	7000 3350 7200 3350
Wire Wire Line
	6200 3850 7200 3850
Wire Wire Line
	6200 3550 6300 3550
Wire Wire Line
	6300 3550 6300 4050
Wire Wire Line
	6300 4050 7200 4050
Wire Wire Line
	6200 3350 6400 3350
Wire Wire Line
	6400 3350 6400 3950
Wire Wire Line
	6400 3950 7200 3950
Wire Wire Line
	7200 3750 6500 3750
Wire Wire Line
	6500 3750 6500 3250
Wire Wire Line
	6500 3250 6200 3250
Text Label 7400 2650 0    50   ~ 0
SCL
$Comp
L Connector:Conn_01x04_Female J5
U 1 1 5FB3F774
P 7400 2750
F 0 "J5" H 7428 2726 50  0001 L CNN
F 1 "LCD 16x2 I2C" H 7192 2989 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 7400 2750 50  0001 C CNN
F 3 "~" H 7400 2750 50  0001 C CNN
	1    7400 2750
	1    0    0    -1  
$EndComp
Text Label 7400 2750 0    50   ~ 0
SDA
Text Label 6550 5150 0    50   ~ 0
Vcc(5v)
Wire Wire Line
	6850 3550 6850 5150
Wire Wire Line
	6850 3550 7200 3550
Wire Wire Line
	7200 2650 6200 2650
Wire Wire Line
	7200 2750 6200 2750
Wire Wire Line
	6850 3550 6850 2950
Wire Wire Line
	6850 2950 7200 2950
Connection ~ 6850 3550
Wire Wire Line
	7200 2850 6550 2850
Wire Wire Line
	6550 2850 6550 3150
Connection ~ 6550 3150
Wire Wire Line
	6550 3150 7000 3150
Text Label 7400 2850 0    50   ~ 0
GND
Text Label 7400 3550 0    50   ~ 0
Vcc(5v)
Text Label 7400 3850 0    50   ~ 0
GND
Text Label 7400 3750 0    50   ~ 0
RED
Text Label 7400 3950 0    50   ~ 0
GREEN
$Comp
L Connector:Conn_01x04_Female J7
U 1 1 5FB3E07B
P 7400 3850
F 0 "J7" H 7428 3826 50  0001 L CNN
F 1 "RGB" H 7192 3544 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 7400 3850 50  0001 C CNN
F 3 "~" H 7400 3850 50  0001 C CNN
	1    7400 3850
	1    0    0    -1  
$EndComp
Text Label 7400 4050 0    50   ~ 0
BLUE
Text Label 7400 2950 0    50   ~ 0
Vcc(5v)
Text Label 7400 3350 0    50   ~ 0
GND
Text Label 7400 3450 0    50   ~ 0
Data
Text Label 3400 3350 0    50   ~ 0
Data
Text Label 3400 2850 0    50   ~ 0
Data
Text Label 3300 3250 0    50   ~ 0
Vcc(5v)
Text Label 3300 2750 0    50   ~ 0
Vcc(5v)
Text Label 3450 3450 0    50   ~ 0
GND
Text Label 3450 2950 0    50   ~ 0
GND
$Comp
L Connector:Conn_01x03_Female J2
U 1 1 5FB1DA1E
P 3600 2850
F 0 "J2" H 3492 3135 50  0001 C CNN
F 1 "PIR Sensor" H 3492 3067 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 3600 2850 50  0001 C CNN
F 3 "~" H 3600 2850 50  0001 C CNN
	1    3600 2850
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
