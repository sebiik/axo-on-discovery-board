EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 7750 1150 950  900 
U 5EFC127A
F0 "Audio Codec" 50
F1 "codec.sch" 50
$EndSheet
$Comp
L axof4_base_board-rescue:+3.3V-power #PWR03
U 1 1 5ECCC814
P 6600 1000
AR Path="/5ECCC814" Ref="#PWR03"  Part="1" 
AR Path="/5EFDA4FE/5ECCC814" Ref="#PWR?"  Part="1" 
F 0 "#PWR03" H 6600 850 50  0001 C CNN
F 1 "+3.3V" H 6615 1173 50  0000 C CNN
F 2 "" H 6600 1000 50  0001 C CNN
F 3 "" H 6600 1000 50  0001 C CNN
	1    6600 1000
	1    0    0    -1  
$EndComp
$Comp
L axof4_base_board-rescue:+5V-power #PWR01
U 1 1 5ECCC81A
P 6350 1000
AR Path="/5ECCC81A" Ref="#PWR01"  Part="1" 
AR Path="/5EFDA4FE/5ECCC81A" Ref="#PWR?"  Part="1" 
F 0 "#PWR01" H 6350 850 50  0001 C CNN
F 1 "+5V" H 6365 1173 50  0000 C CNN
F 2 "" H 6350 1000 50  0001 C CNN
F 3 "" H 6350 1000 50  0001 C CNN
	1    6350 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 1000 6350 1250
Wire Wire Line
	4000 4550 4050 4550
Wire Wire Line
	4750 4450 4050 4450
Wire Wire Line
	4550 4650 4750 4650
Wire Wire Line
	4550 4750 4750 4750
Wire Wire Line
	4550 4850 4750 4850
Wire Wire Line
	4550 4950 4750 4950
Wire Wire Line
	4550 5750 4750 5750
Text GLabel 4000 4450 0    50   Input ~ 0
WM8731_SCL
Text GLabel 4000 4550 0    50   Input ~ 0
WM8731_SDA
Text GLabel 4550 4650 0    50   Input ~ 0
I2S_LRCLK
Text GLabel 4550 4750 0    50   Input ~ 0
I2S_BCLK
Text GLabel 4550 4850 0    50   Input ~ 0
I2S_RX
Text GLabel 4550 4950 0    50   Input ~ 0
I2S_TX
Text GLabel 4550 5750 0    50   Input ~ 0
I2S_MCLK
$Comp
L axof4_base_board-rescue:GND-power #PWR?
U 1 1 5ECCC838
P 6350 6950
AR Path="/5EFDA4FE/5ECCC838" Ref="#PWR?"  Part="1" 
AR Path="/5ECCC838" Ref="#PWR02"  Part="1" 
F 0 "#PWR02" H 6350 6700 50  0001 C CNN
F 1 "GND" H 6355 6777 50  0000 C CNN
F 2 "" H 6350 6950 50  0001 C CNN
F 3 "" H 6350 6950 50  0001 C CNN
	1    6350 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 6950 6350 6850
Text GLabel 4550 5950 0    50   Input ~ 0
SDIO_D0
Wire Wire Line
	4550 5950 4750 5950
Text GLabel 4550 6050 0    50   Input ~ 0
SDIO_D1
Text GLabel 4550 6150 0    50   Input ~ 0
SDIO_D2
Text GLabel 4550 6250 0    50   Input ~ 0
SDIO_D3
Wire Wire Line
	4550 6050 4750 6050
Wire Wire Line
	4550 6150 4750 6150
Wire Wire Line
	4550 6250 4750 6250
Text GLabel 4550 6350 0    50   Input ~ 0
SDIO_CK
Text GLabel 6550 2150 2    50   Input ~ 0
SDIO_CMD
Wire Wire Line
	6550 2150 6350 2150
Wire Wire Line
	4550 6350 4750 6350
Text GLabel 4500 2350 0    50   Input ~ 0
DAC1
Text GLabel 4500 2450 0    50   Input ~ 0
DAC2
Wire Wire Line
	4500 2350 4750 2350
Wire Wire Line
	4750 2450 4500 2450
Text GLabel 4500 3250 0    50   Input ~ 0
SPIRAM_NSS
Wire Wire Line
	4500 3250 4750 3250
Text GLabel 4500 3750 0    50   Input ~ 0
SPIRAM_SCK
Text GLabel 4500 3850 0    50   Input ~ 0
SPIRAM_MISO
Text GLabel 4500 3950 0    50   Input ~ 0
SPIRAM_MOSI
Wire Wire Line
	4500 3750 4750 3750
Wire Wire Line
	4750 3850 4500 3850
Wire Wire Line
	4500 3950 4750 3950
$Sheet
S 8900 1150 1000 900 
U 5ECD8B86
F0 "SDIO" 50
F1 "sdio.sch" 50
$EndSheet
$Sheet
S 7750 2400 950  950 
U 5ECDA234
F0 "SPI RAM" 50
F1 "spiram.sch" 50
$EndSheet
$Sheet
S 8900 2400 950  950 
U 5ED86ED4
F0 "Power" 50
F1 "power.sch" 50
$EndSheet
Wire Wire Line
	6350 1450 6600 1450
Wire Wire Line
	6600 1000 6600 1450
$Comp
L STM32F4DISCOVERY:STM32F4DISCOVERY JB1
U 1 1 5ECCC823
P 5550 4050
AR Path="/5ECCC823" Ref="JB1"  Part="1" 
AR Path="/5EFDA4FE/5ECCC823" Ref="JB?"  Part="1" 
F 0 "JB1" H 5550 7117 50  0000 C CNN
F 1 "STM32F4DISCOVERY" H 5550 7026 50  0000 C CNN
F 2 "lib:MODULE_STM32F4DISCOVERY" H 5550 4050 50  0001 L BNN
F 3 "6" H 5550 4050 50  0001 L BNN
F 4 "STMicroelectronics" H 5550 4050 50  0001 L BNN "Field4"
F 5 "Manufacturer Recommendations" H 5550 4050 50  0001 L BNN "Field5"
	1    5550 4050
	1    0    0    -1  
$EndComp
$Comp
L axof4_base_board-rescue:R-Device R23
U 1 1 5EDF8C2D
P 3350 4150
AR Path="/5EDF8C2D" Ref="R23"  Part="1" 
AR Path="/5EFC127A/5EDF8C2D" Ref="R?"  Part="1" 
F 0 "R23" H 3300 4050 50  0000 R CNN
F 1 "4.7k" V 3350 4250 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3280 4150 50  0001 C CNN
F 3 "~" H 3350 4150 50  0001 C CNN
	1    3350 4150
	-1   0    0    1   
$EndComp
$Comp
L axof4_base_board-rescue:+3.3V-power #PWR021
U 1 1 5EDF8C33
P 3350 3950
AR Path="/5EDF8C33" Ref="#PWR021"  Part="1" 
AR Path="/5EFC127A/5EDF8C33" Ref="#PWR?"  Part="1" 
F 0 "#PWR021" H 3350 3800 50  0001 C CNN
F 1 "+3.3V" H 3365 4123 50  0000 C CNN
F 2 "" H 3350 3950 50  0001 C CNN
F 3 "" H 3350 3950 50  0001 C CNN
	1    3350 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3950 3350 4000
Connection ~ 3350 4000
$Comp
L axof4_base_board-rescue:R-Device R21
U 1 1 5EDF8C3C
P 3150 4150
AR Path="/5EDF8C3C" Ref="R21"  Part="1" 
AR Path="/5EFC127A/5EDF8C3C" Ref="R?"  Part="1" 
F 0 "R21" H 3350 4050 50  0000 R CNN
F 1 "4.7k" V 3150 4250 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3080 4150 50  0001 C CNN
F 3 "~" H 3150 4150 50  0001 C CNN
	1    3150 4150
	-1   0    0    1   
$EndComp
Wire Wire Line
	4050 4350 4050 4450
Connection ~ 4050 4450
Wire Wire Line
	4050 4450 4000 4450
Wire Wire Line
	4050 4650 4050 4550
Connection ~ 4050 4550
Wire Wire Line
	4050 4550 4750 4550
$Sheet
S 7750 3700 950  950 
U 5EE2DB57
F0 "MIDI" 50
F1 "midi.sch" 50
$EndSheet
Text GLabel 3150 1350 0    50   Input ~ 0
MIDI_RX
Text GLabel 3150 1500 0    50   Input ~ 0
MIDI_TX
$Sheet
S 8900 3700 950  950 
U 5F736ED6
F0 "USB" 50
F1 "usb.sch" 50
$EndSheet
$Comp
L Connector_Generic:Conn_02x04_Odd_Even J7
U 1 1 602901E8
P 1300 4250
F 0 "J7" H 1350 4567 50  0000 C CNN
F 1 "I2C1_HEADER" H 1350 4476 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x04_P2.54mm_Vertical" H 1300 4250 50  0001 C CNN
F 3 "~" H 1300 4250 50  0001 C CNN
	1    1300 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 4150 1100 4150
Connection ~ 1600 4150
$Comp
L power:GND #PWR040
U 1 1 602A0F05
P 900 4300
F 0 "#PWR040" H 900 4050 50  0001 C CNN
F 1 "GND" H 905 4127 50  0000 C CNN
F 2 "" H 900 4300 50  0001 C CNN
F 3 "" H 900 4300 50  0001 C CNN
	1    900  4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	900  4300 900  4250
Wire Wire Line
	900  4250 1100 4250
Wire Wire Line
	1100 4450 1600 4450
Wire Wire Line
	3150 4300 3150 4650
Wire Wire Line
	3350 4350 3350 4300
Wire Wire Line
	1600 4350 1100 4350
Wire Wire Line
	1600 3850 1600 4150
Wire Wire Line
	1100 4250 1600 4250
Connection ~ 1100 4250
Text Notes 1650 4250 0    50   ~ 0
VCC\nGND
Wire Wire Line
	4100 1450 4150 1450
Wire Wire Line
	4700 1450 4700 1650
Wire Wire Line
	4700 1650 4750 1650
$Comp
L axof4_base_board-rescue:+3.3V-power #PWR048
U 1 1 602C979F
P 4150 950
AR Path="/602C979F" Ref="#PWR048"  Part="1" 
AR Path="/5EFC127A/602C979F" Ref="#PWR?"  Part="1" 
F 0 "#PWR048" H 4150 800 50  0001 C CNN
F 1 "+3.3V" H 4165 1123 50  0000 C CNN
F 2 "" H 4150 950 50  0001 C CNN
F 3 "" H 4150 950 50  0001 C CNN
	1    4150 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 950  4150 1000
Wire Wire Line
	4150 1000 4100 1000
$Comp
L Device:R R36
U 1 1 602CD2A4
P 4150 1600
F 0 "R36" H 4220 1646 50  0000 L CNN
F 1 "10k" H 4220 1555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4080 1600 50  0001 C CNN
F 3 "~" H 4150 1600 50  0001 C CNN
	1    4150 1600
	1    0    0    -1  
$EndComp
Connection ~ 4150 1450
Wire Wire Line
	4150 1450 4700 1450
$Comp
L power:GND #PWR047
U 1 1 602CE2E4
P 4050 1800
F 0 "#PWR047" H 4050 1550 50  0001 C CNN
F 1 "GND" H 4055 1627 50  0000 C CNN
F 2 "" H 4050 1800 50  0001 C CNN
F 3 "" H 4050 1800 50  0001 C CNN
	1    4050 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 1800 4050 1750
Wire Wire Line
	4050 1750 4150 1750
Text GLabel 1600 4350 2    50   Input ~ 0
I2C1_SCL
Text GLabel 1600 4450 2    50   Input ~ 0
I2C1_SDA
Wire Wire Line
	3150 4000 3350 4000
Wire Wire Line
	3350 4350 4050 4350
Wire Wire Line
	3150 4650 4050 4650
Text GLabel 4500 4050 0    50   Input ~ 0
I2C1_SCL
Text GLabel 4500 4350 0    50   Input ~ 0
I2C1_SDA
Wire Wire Line
	4500 4350 4750 4350
Wire Wire Line
	4500 4050 4750 4050
Text GLabel 4500 3450 0    50   Input ~ 0
SPI2_SOFT_NSS
Wire Wire Line
	4500 3450 4750 3450
$Comp
L axof4_base_board-rescue:+3.3V-power #PWR041
U 1 1 603DAAD6
P 1600 3850
AR Path="/603DAAD6" Ref="#PWR041"  Part="1" 
AR Path="/5EFC127A/603DAAD6" Ref="#PWR?"  Part="1" 
F 0 "#PWR041" H 1600 3700 50  0001 C CNN
F 1 "+3.3V" H 1615 4023 50  0000 C CNN
F 2 "" H 1600 3850 50  0001 C CNN
F 3 "" H 1600 3850 50  0001 C CNN
	1    1600 3850
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 6102CCB9
P 4100 1200
F 0 "SW1" V 4146 1152 50  0000 R CNN
F 1 "BOOT" V 4055 1152 50  0000 R CNN
F 2 "Button_Switch_SMD:SW_Push_1P1T_NO_6x6mm_H9.5mm" H 4100 1400 50  0001 C CNN
F 3 "~" H 4100 1400 50  0001 C CNN
	1    4100 1200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4100 1450 4100 1400
$EndSCHEMATC
