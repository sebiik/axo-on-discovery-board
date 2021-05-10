EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 3100 3550 0    50   Input ~ 0
SPIRAM_NSS
Text GLabel 7150 3750 2    50   Input ~ 0
SPIRAM_SCK
Text GLabel 3100 3650 0    50   Input ~ 0
SPIRAM_MISO
Text GLabel 7150 3850 2    50   Input ~ 0
SPIRAM_MOSI-VGA_PIXEL
$Comp
L 23LC1024:23LC1024-I_SN U2
U 1 1 5ECDC1BB
P 3700 3550
AR Path="/5ECDA234/5ECDC1BB" Ref="U2"  Part="1" 
AR Path="/5ED86ED4/5ECDC1BB" Ref="U?"  Part="1" 
AR Path="/5EE2DB57/5ECDC1BB" Ref="U?"  Part="1" 
F 0 "U2" H 5300 3937 60  0000 C CNN
F 1 "23LC1024-I_SN" H 5300 3831 60  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5300 3790 60  0001 C CNN
F 3 "" H 3700 3550 60  0000 C CNN
	1    3700 3550
	1    0    0    -1  
$EndComp
$Comp
L axof4_base_board-rescue:+3.3V-power #PWR026
U 1 1 5EE51592
P 7150 3400
AR Path="/5ECDA234/5EE51592" Ref="#PWR026"  Part="1" 
AR Path="/5ED86ED4/5EE51592" Ref="#PWR?"  Part="1" 
AR Path="/5EE2DB57/5EE51592" Ref="#PWR?"  Part="1" 
F 0 "#PWR026" H 7150 3250 50  0001 C CNN
F 1 "+3.3V" H 7165 3573 50  0000 C CNN
F 2 "" H 7150 3400 50  0001 C CNN
F 3 "" H 7150 3400 50  0001 C CNN
	1    7150 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 3850 7150 3850
Wire Wire Line
	3100 3650 3700 3650
Wire Wire Line
	6900 3750 7150 3750
$Comp
L axof4_base_board-rescue:GND-power #PWR024
U 1 1 5EDD81C1
P 3500 4050
AR Path="/5ECDA234/5EDD81C1" Ref="#PWR024"  Part="1" 
AR Path="/5ED86ED4/5EDD81C1" Ref="#PWR?"  Part="1" 
AR Path="/5EE2DB57/5EDD81C1" Ref="#PWR?"  Part="1" 
F 0 "#PWR024" H 3500 3800 50  0001 C CNN
F 1 "GND" H 3505 3877 50  0000 C CNN
F 2 "" H 3500 4050 50  0001 C CNN
F 3 "" H 3500 4050 50  0001 C CNN
	1    3500 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 3850 3500 3850
Wire Wire Line
	3500 3850 3500 4050
Wire Wire Line
	6900 3650 7150 3650
Wire Wire Line
	7150 3650 7150 3550
Connection ~ 7150 3550
$Comp
L axof4_base_board-rescue:R-Device R24
U 1 1 5ECDE811
P 3500 3300
AR Path="/5ECDA234/5ECDE811" Ref="R24"  Part="1" 
AR Path="/5ED86ED4/5ECDE811" Ref="R?"  Part="1" 
AR Path="/5EE2DB57/5ECDE811" Ref="R?"  Part="1" 
F 0 "R24" H 3350 3250 50  0000 C CNN
F 1 "10k" V 3500 3300 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3430 3300 50  0001 C CNN
F 3 "~" H 3500 3300 50  0001 C CNN
	1    3500 3300
	-1   0    0    1   
$EndComp
$Comp
L axof4_base_board-rescue:+3.3V-power #PWR023
U 1 1 5EDD81C2
P 3500 3100
AR Path="/5ECDA234/5EDD81C2" Ref="#PWR023"  Part="1" 
AR Path="/5ED86ED4/5EDD81C2" Ref="#PWR?"  Part="1" 
AR Path="/5EE2DB57/5EDD81C2" Ref="#PWR?"  Part="1" 
F 0 "#PWR023" H 3500 2950 50  0001 C CNN
F 1 "+3.3V" H 3500 3250 50  0000 C CNN
F 2 "" H 3500 3100 50  0001 C CNN
F 3 "" H 3500 3100 50  0001 C CNN
	1    3500 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3550 3500 3550
$Comp
L axof4_base_board-rescue:C_Small-Device C23
U 1 1 5EE51593
P 6950 3300
AR Path="/5ECDA234/5EE51593" Ref="C23"  Part="1" 
AR Path="/5ED86ED4/5EE51593" Ref="C?"  Part="1" 
AR Path="/5EE2DB57/5EE51593" Ref="C?"  Part="1" 
F 0 "C23" H 7100 3250 50  0000 R CNN
F 1 "100n" H 7150 3350 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 6950 3300 50  0001 C CNN
F 3 "~" H 6950 3300 50  0001 C CNN
	1    6950 3300
	-1   0    0    1   
$EndComp
$Comp
L axof4_base_board-rescue:GND-power #PWR025
U 1 1 5ECE192A
P 6600 3100
AR Path="/5ECDA234/5ECE192A" Ref="#PWR025"  Part="1" 
AR Path="/5ED86ED4/5ECE192A" Ref="#PWR?"  Part="1" 
AR Path="/5EE2DB57/5ECE192A" Ref="#PWR?"  Part="1" 
F 0 "#PWR025" H 6600 2850 50  0001 C CNN
F 1 "GND" H 6605 2927 50  0000 C CNN
F 2 "" H 6600 3100 50  0001 C CNN
F 3 "" H 6600 3100 50  0001 C CNN
	1    6600 3100
	1    0    0    -1  
$EndComp
Connection ~ 3500 3550
Wire Wire Line
	3500 3550 3700 3550
Wire Wire Line
	7150 3400 7150 3550
Wire Wire Line
	6950 3400 6950 3550
Wire Wire Line
	6900 3550 6950 3550
Connection ~ 6950 3550
Wire Wire Line
	6950 3550 7150 3550
Wire Wire Line
	6950 3200 6950 3050
Wire Wire Line
	6950 3050 6600 3050
Wire Wire Line
	6600 3050 6600 3100
$Comp
L axof4_base_board-rescue:+3.3V-power #PWR022
U 1 1 5ECE6440
P 3150 3900
AR Path="/5ECDA234/5ECE6440" Ref="#PWR022"  Part="1" 
AR Path="/5ED86ED4/5ECE6440" Ref="#PWR?"  Part="1" 
AR Path="/5EE2DB57/5ECE6440" Ref="#PWR?"  Part="1" 
F 0 "#PWR022" H 3150 3750 50  0001 C CNN
F 1 "+3.3V" H 3150 4050 50  0000 C CNN
F 2 "" H 3150 3900 50  0001 C CNN
F 3 "" H 3150 3900 50  0001 C CNN
	1    3150 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 3750 3300 3750
Wire Wire Line
	3300 3750 3300 4000
Wire Wire Line
	3300 4000 3150 4000
Wire Wire Line
	3150 4000 3150 3900
Wire Wire Line
	3500 3450 3500 3550
Wire Wire Line
	3500 3100 3500 3150
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J?
U 1 1 603C4C1A
P 4950 5500
AR Path="/603C4C1A" Ref="J?"  Part="1" 
AR Path="/5ECDA234/603C4C1A" Ref="J8"  Part="1" 
F 0 "J8" H 5000 5817 50  0000 C CNN
F 1 "SPI2_HEADER" H 5000 5726 50  0000 C CNN
F 2 "" H 4950 5500 50  0001 C CNN
F 3 "~" H 4950 5500 50  0001 C CNN
	1    4950 5500
	1    0    0    -1  
$EndComp
$Comp
L axof4_base_board-rescue:+3.3V-power #PWR?
U 1 1 603C4C20
P 5350 5250
AR Path="/603C4C20" Ref="#PWR?"  Part="1" 
AR Path="/5EFC127A/603C4C20" Ref="#PWR?"  Part="1" 
AR Path="/5ECDA234/603C4C20" Ref="#PWR044"  Part="1" 
F 0 "#PWR044" H 5350 5100 50  0001 C CNN
F 1 "+3.3V" H 5365 5423 50  0000 C CNN
F 2 "" H 5350 5250 50  0001 C CNN
F 3 "" H 5350 5250 50  0001 C CNN
	1    5350 5250
	1    0    0    -1  
$EndComp
Text GLabel 4700 5500 0    50   Input ~ 0
SPIRAM_SCK
Text GLabel 4700 5400 0    50   Input ~ 0
SPIRAM_MISO
Text GLabel 5300 5500 2    50   Input ~ 0
SPIRAM_MOSI-VGA_PIXEL
Wire Wire Line
	5250 5500 5300 5500
$Comp
L power:GND #PWR?
U 1 1 603C4C3C
P 5300 5650
AR Path="/603C4C3C" Ref="#PWR?"  Part="1" 
AR Path="/5ECDA234/603C4C3C" Ref="#PWR043"  Part="1" 
F 0 "#PWR043" H 5300 5400 50  0001 C CNN
F 1 "GND" H 5305 5477 50  0000 C CNN
F 2 "" H 5300 5650 50  0001 C CNN
F 3 "" H 5300 5650 50  0001 C CNN
	1    5300 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 5650 5300 5600
Wire Wire Line
	5300 5600 5250 5600
Text GLabel 4000 5600 0    50   Input ~ 0
SPI2_SOFT_NSS
Wire Wire Line
	4700 5400 4750 5400
Wire Wire Line
	4750 5500 4700 5500
Wire Wire Line
	4000 5600 4050 5600
$Comp
L axof4_base_board-rescue:R-Device R35
U 1 1 603CF6F9
P 4050 5250
AR Path="/5ECDA234/603CF6F9" Ref="R35"  Part="1" 
AR Path="/5ED86ED4/603CF6F9" Ref="R?"  Part="1" 
AR Path="/5EE2DB57/603CF6F9" Ref="R?"  Part="1" 
AR Path="/603CF6F9" Ref="R?"  Part="1" 
F 0 "R35" H 3900 5200 50  0000 C CNN
F 1 "10k" V 4050 5250 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3980 5250 50  0001 C CNN
F 3 "~" H 4050 5250 50  0001 C CNN
	1    4050 5250
	-1   0    0    1   
$EndComp
$Comp
L axof4_base_board-rescue:+3.3V-power #PWR042
U 1 1 603CF6FF
P 4050 5050
AR Path="/5ECDA234/603CF6FF" Ref="#PWR042"  Part="1" 
AR Path="/5ED86ED4/603CF6FF" Ref="#PWR?"  Part="1" 
AR Path="/5EE2DB57/603CF6FF" Ref="#PWR?"  Part="1" 
AR Path="/603CF6FF" Ref="#PWR?"  Part="1" 
F 0 "#PWR042" H 4050 4900 50  0001 C CNN
F 1 "+3.3V" H 4050 5200 50  0000 C CNN
F 2 "" H 4050 5050 50  0001 C CNN
F 3 "" H 4050 5050 50  0001 C CNN
	1    4050 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 5050 4050 5100
Wire Wire Line
	4050 5400 4050 5600
Connection ~ 4050 5600
Wire Wire Line
	4050 5600 4750 5600
Wire Wire Line
	5350 5250 5350 5400
Wire Wire Line
	5350 5400 5250 5400
$EndSCHEMATC
