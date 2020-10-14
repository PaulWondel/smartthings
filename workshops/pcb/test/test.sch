EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Smart Things - Home Weather Station"
Date "2020-10-14"
Rev "v1"
Comp "Hogeschool Rotterdam"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Espressiv_8266nodemcu:ESP8266NodeMCU U?
U 1 1 5F870337
P 5250 3800
F 0 "U?" H 5250 4867 50  0000 C CNN
F 1 "ESP8266NodeMCU" H 5250 4776 50  0000 C CNB
F 2 "smart_things_PCBv1:ESP8266_nodeMCU_V1" H 5250 2500 50  0001 C CNN
F 3 "" H 5350 2500 50  0001 C CNN
	1    5250 3800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Barrel_Jack J?
U 1 1 5F874605
P 2700 4850
F 0 "J?" H 2757 5175 50  0000 C CNN
F 1 "Barrel_Jack" H 2757 5084 50  0000 C CNN
F 2 "" H 2750 4810 50  0001 C CNN
F 3 "~" H 2750 4810 50  0001 C CNN
	1    2700 4850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J?
U 1 1 5F88065A
P 2150 2700
F 0 "J?" H 2178 2676 50  0000 L CNN
F 1 "Conn_01x04_Female" V 2178 2585 50  0000 L CNN
F 2 "" H 2150 2700 50  0001 C CNN
F 3 "~" H 2150 2700 50  0001 C CNN
	1    2150 2700
	0    -1   -1   0   
$EndComp
Text Notes 2100 2550 0    50   ~ 0
Oled
Wire Wire Line
	3000 4750 4350 4750
Wire Wire Line
	4350 4750 4350 4500
Wire Wire Line
	3000 4950 4000 4950
Wire Wire Line
	4000 4950 4000 4400
Wire Wire Line
	4000 4400 4350 4400
$EndSCHEMATC
