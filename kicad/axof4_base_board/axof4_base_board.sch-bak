EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 5
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
Text Notes 2000 4500 0    50   ~ 0
TODO add header for external i2c devices
Text GLabel 4000 4450 0    50   Input ~ 0
I2C_SCL
Text GLabel 4000 4550 0    50   Input ~ 0
I2C_SDA
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
Text Notes 2350 3250 0    50   ~ 0
TODO add header for external spi device
Text GLabel 4500 3750 0    50   Input ~ 0
SPIRAM_SCK
Text GLabel 4500 3850 0    50   Input ~ 0
SPIRAM_MISO
Text GLabel 4500 3950 0    50   Input ~ 0
SPIRAM_MOSI-VGA_PIXEL
Wire Wire Line
	4500 3750 4750 3750
Wire Wire Line
	4750 3850 4500 3850
Wire Wire Line
	4500 3950 4750 3950
Text GLabel 4500 2050 0    50   Input ~ 0
VGA_VSYNC
Wire Wire Line
	4500 2050 4750 2050
Text GLabel 4500 2750 0    50   Input ~ 0
VGA_HSYNC
Wire Wire Line
	4500 2750 4750 2750
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
P 3100 4200
AR Path="/5EDF8C2D" Ref="R23"  Part="1" 
AR Path="/5EFC127A/5EDF8C2D" Ref="R?"  Part="1" 
F 0 "R23" H 3050 4100 50  0000 R CNN
F 1 "4.7k" V 3100 4300 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3030 4200 50  0001 C CNN
F 3 "~" H 3100 4200 50  0001 C CNN
	1    3100 4200
	-1   0    0    1   
$EndComp
$Comp
L axof4_base_board-rescue:+3.3V-power #PWR021
U 1 1 5EDF8C33
P 3100 4000
AR Path="/5EDF8C33" Ref="#PWR021"  Part="1" 
AR Path="/5EFC127A/5EDF8C33" Ref="#PWR?"  Part="1" 
F 0 "#PWR021" H 3100 3850 50  0001 C CNN
F 1 "+3.3V" H 3115 4173 50  0000 C CNN
F 2 "" H 3100 4000 50  0001 C CNN
F 3 "" H 3100 4000 50  0001 C CNN
	1    3100 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 4000 3100 4050
Connection ~ 3100 4050
Wire Wire Line
	2900 4050 3100 4050
$Comp
L axof4_base_board-rescue:R-Device R21
U 1 1 5EDF8C3C
P 2900 4200
AR Path="/5EDF8C3C" Ref="R21"  Part="1" 
AR Path="/5EFC127A/5EDF8C3C" Ref="R?"  Part="1" 
F 0 "R21" H 3100 4100 50  0000 R CNN
F 1 "4.7k" V 2900 4300 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 2830 4200 50  0001 C CNN
F 3 "~" H 2900 4200 50  0001 C CNN
	1    2900 4200
	-1   0    0    1   
$EndComp
Wire Wire Line
	3100 4350 4050 4350
Wire Wire Line
	4050 4350 4050 4450
Connection ~ 4050 4450
Wire Wire Line
	4050 4450 4000 4450
Wire Wire Line
	2900 4350 2900 4650
Wire Wire Line
	2900 4650 4050 4650
Wire Wire Line
	4050 4650 4050 4550
Connection ~ 4050 4550
Wire Wire Line
	4050 4550 4750 4550
$EndSCHEMATC
