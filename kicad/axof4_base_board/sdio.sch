EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 2350 2100 0    50   Input ~ 0
SDIO_D0
Text GLabel 2350 2200 0    50   Input ~ 0
SDIO_D1
Text GLabel 2350 2300 0    50   Input ~ 0
SDIO_D2
Text GLabel 2350 2400 0    50   Input ~ 0
SDIO_D3
Text GLabel 2400 2700 0    50   Input ~ 0
SDIO_CMD
$Comp
L Connector:SD_Card J6
U 1 1 5F740056
P 5750 2900
F 0 "J6" H 5750 3565 50  0000 C CNN
F 1 "SD_Card" H 5750 3474 50  0000 C CNN
F 2 "Connector_Card:SD_TE_2041021" H 5750 2900 50  0001 C CNN
F 3 "http://portal.fciconnect.com/Comergent//fci/drawing/10067847.pdf" H 5750 2900 50  0001 C CNN
	1    5750 2900
	1    0    0    -1  
$EndComp
Text GLabel 2350 3000 0    50   Input ~ 0
SDIO_CK
Wire Wire Line
	2350 3000 4850 3000
Wire Wire Line
	2400 2700 3900 2700
Wire Wire Line
	2350 2100 2850 2100
Wire Wire Line
	2850 2100 2850 3200
Wire Wire Line
	2850 3200 4150 3200
Wire Wire Line
	2350 2200 2750 2200
Wire Wire Line
	2750 2200 2750 3300
Wire Wire Line
	2750 3300 4400 3300
Wire Wire Line
	2350 2300 2650 2300
Wire Wire Line
	2650 2300 2650 2500
Wire Wire Line
	2350 2400 2550 2400
Wire Wire Line
	2550 2400 2550 2600
Wire Wire Line
	2550 2600 3650 2600
$Comp
L axof4_base_board-rescue:+3.3V-power #PWR0103
U 1 1 5F743FB7
P 1350 2700
F 0 "#PWR0103" H 1350 2550 50  0001 C CNN
F 1 "+3.3V-power" H 1365 2873 50  0000 C CNN
F 2 "" H 1350 2700 50  0001 C CNN
F 3 "" H 1350 2700 50  0001 C CNN
	1    1350 2700
	1    0    0    -1  
$EndComp
$Comp
L axof4_base_board-rescue:GND-power #PWR0104
U 1 1 5F744B0D
P 1700 3300
F 0 "#PWR0104" H 1700 3050 50  0001 C CNN
F 1 "GND-power" H 1705 3127 50  0000 C CNN
F 2 "" H 1700 3300 50  0001 C CNN
F 3 "" H 1700 3300 50  0001 C CNN
	1    1700 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 3300 1700 3200
Wire Wire Line
	1700 2800 4850 2800
Wire Wire Line
	1350 2700 1350 2900
Wire Wire Line
	1350 2900 4850 2900
NoConn ~ 6650 2700
NoConn ~ 6650 2800
NoConn ~ 6650 3000
NoConn ~ 6650 3100
$Comp
L Device:CP C40
U 1 1 5F750B90
P 1350 3050
F 0 "C40" H 1468 3096 50  0000 L CNN
F 1 "10u" H 1468 3005 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_4x5.4" H 1388 2900 50  0001 C CNN
F 3 "~" H 1350 3050 50  0001 C CNN
	1    1350 3050
	1    0    0    -1  
$EndComp
Connection ~ 1350 2900
Wire Wire Line
	1350 3200 1700 3200
Connection ~ 1700 3200
Wire Wire Line
	1700 2800 1700 3200
Wire Wire Line
	1700 3200 2500 3200
Wire Wire Line
	2500 3200 2500 3100
Wire Wire Line
	2500 3100 4850 3100
$Comp
L Device:R R30
U 1 1 5F753A6C
P 3400 2150
F 0 "R30" H 3470 2196 50  0000 L CNN
F 1 "47k" H 3470 2105 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3330 2150 50  0001 C CNN
F 3 "~" H 3400 2150 50  0001 C CNN
	1    3400 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R31
U 1 1 5F757136
P 3650 2150
F 0 "R31" H 3720 2196 50  0000 L CNN
F 1 "47k" H 3720 2105 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3580 2150 50  0001 C CNN
F 3 "~" H 3650 2150 50  0001 C CNN
	1    3650 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R32
U 1 1 5F75727F
P 3900 2150
F 0 "R32" H 3970 2196 50  0000 L CNN
F 1 "47k" H 3970 2105 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3830 2150 50  0001 C CNN
F 3 "~" H 3900 2150 50  0001 C CNN
	1    3900 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R33
U 1 1 5F757554
P 4150 2150
F 0 "R33" H 4220 2196 50  0000 L CNN
F 1 "47k" H 4220 2105 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 4080 2150 50  0001 C CNN
F 3 "~" H 4150 2150 50  0001 C CNN
	1    4150 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R34
U 1 1 5F7577B3
P 4400 2150
F 0 "R34" H 4470 2196 50  0000 L CNN
F 1 "47k" H 4470 2105 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 4330 2150 50  0001 C CNN
F 3 "~" H 4400 2150 50  0001 C CNN
	1    4400 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 2300 3650 2600
Connection ~ 3650 2600
Wire Wire Line
	3650 2600 4850 2600
Wire Wire Line
	2650 2500 3400 2500
Wire Wire Line
	3400 2300 3400 2500
Connection ~ 3400 2500
Wire Wire Line
	3400 2500 4850 2500
Wire Wire Line
	3900 2300 3900 2700
Connection ~ 3900 2700
Wire Wire Line
	3900 2700 4850 2700
Wire Wire Line
	4150 2300 4150 3200
Connection ~ 4150 3200
Wire Wire Line
	4150 3200 4850 3200
Wire Wire Line
	4400 2300 4400 3300
Connection ~ 4400 3300
Wire Wire Line
	4400 3300 4850 3300
$Comp
L axof4_base_board-rescue:+3.3V-power #PWR0105
U 1 1 5F75AFEC
P 3900 1750
F 0 "#PWR0105" H 3900 1600 50  0001 C CNN
F 1 "+3.3V-power" H 3915 1923 50  0000 C CNN
F 2 "" H 3900 1750 50  0001 C CNN
F 3 "" H 3900 1750 50  0001 C CNN
	1    3900 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 2000 3400 1850
Wire Wire Line
	3400 1850 3650 1850
Wire Wire Line
	3900 1850 3900 1750
Wire Wire Line
	3900 1850 4150 1850
Wire Wire Line
	4400 1850 4400 2000
Connection ~ 3900 1850
Wire Wire Line
	3650 2000 3650 1850
Connection ~ 3650 1850
Wire Wire Line
	3650 1850 3900 1850
Wire Wire Line
	3900 2000 3900 1850
Wire Wire Line
	4150 2000 4150 1850
Connection ~ 4150 1850
Wire Wire Line
	4150 1850 4400 1850
$EndSCHEMATC
