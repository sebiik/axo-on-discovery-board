EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 11
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
L power:+5V #PWR03
U 1 1 5ECCC81A
P 6400 1300
AR Path="/5ECCC81A" Ref="#PWR03"  Part="1" 
AR Path="/5EFDA4FE/5ECCC81A" Ref="#PWR?"  Part="1" 
F 0 "#PWR03" H 6400 1150 50  0001 C CNN
F 1 "+5V" H 6415 1473 50  0000 C CNN
F 2 "" H 6400 1300 50  0001 C CNN
F 3 "" H 6400 1300 50  0001 C CNN
	1    6400 1300
	1    0    0    -1  
$EndComp
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
Text GLabel 4000 4450 0    50   Output ~ 0
WM8731_SCL
Text GLabel 4000 4550 0    50   Output ~ 0
WM8731_SDA
Text GLabel 4550 4650 0    50   Output ~ 0
I2S_LRCLK
Text GLabel 4550 4750 0    50   Output ~ 0
I2S_BCLK
Text GLabel 4550 5750 0    50   Output ~ 0
I2S_MCLK
Text GLabel 4550 5950 0    50   Output ~ 0
SDIO_D0
Wire Wire Line
	4550 5950 4750 5950
Text GLabel 4550 6050 0    50   Output ~ 0
SDIO_D1
Text GLabel 4550 6150 0    50   Output ~ 0
SDIO_D2
Text GLabel 4550 6250 0    50   Output ~ 0
SDIO_D3
Wire Wire Line
	4550 6050 4750 6050
Wire Wire Line
	4550 6150 4750 6150
Wire Wire Line
	4550 6250 4750 6250
Text GLabel 4550 6350 0    50   Output ~ 0
SDIO_CK
Text GLabel 6550 2150 2    50   Output ~ 0
SDIO_CMD
Wire Wire Line
	6550 2150 6350 2150
Wire Wire Line
	4550 6350 4750 6350
Text GLabel 4500 2350 0    50   Output ~ 0
DAC1
Text GLabel 4500 2450 0    50   Output ~ 0
DAC2
Wire Wire Line
	4500 2350 4750 2350
Wire Wire Line
	4750 2450 4500 2450
Text GLabel 4500 3250 0    50   Output ~ 0
SPIRAM_NSS
Wire Wire Line
	4500 3250 4750 3250
Text GLabel 4500 3750 0    50   Output ~ 0
SPIRAM_SCK
Text GLabel 4500 3850 0    50   Input ~ 0
SPIRAM_MISO
Text GLabel 4500 3950 0    50   Output ~ 0
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
$Comp
L STM32F4DISCOVERY:STM32F4DISCOVERY STM32F4
U 1 1 5ECCC823
P 5550 4050
AR Path="/5ECCC823" Ref="STM32F4"  Part="1" 
AR Path="/5EFDA4FE/5ECCC823" Ref="JB?"  Part="1" 
F 0 "STM32F4" H 5550 4150 50  0000 C CNN
F 1 "STM32F4DISCOVERY" H 5550 4050 50  0000 C CNN
F 2 "foots:STM32F4DISCOVERY" H 5550 4050 50  0001 L BNN
F 3 "6" H 5550 4050 50  0001 L BNN
F 4 "STMicroelectronics" H 5550 4050 50  0001 L BNN "Field4"
F 5 "Manufacturer Recommendations" H 5550 4050 50  0001 L BNN "Field5"
F 6 "-" H 5550 4050 50  0001 C CNN "LCSC"
	1    5550 4050
	1    0    0    -1  
$EndComp
$Sheet
S 7750 3550 950  950 
U 5EE2DB57
F0 "MIDI" 50
F1 "midi.sch" 50
$EndSheet
Text GLabel 6550 2850 2    50   Input ~ 0
MIDI_RX
Text GLabel 6550 2750 2    50   Output ~ 0
MIDI_TX
Wire Wire Line
	6550 2750 6350 2750
Wire Wire Line
	6550 2850 6350 2850
Wire Wire Line
	4000 4450 4750 4450
Wire Wire Line
	4000 4550 4750 4550
Text GLabel 4500 2050 0    50   Input ~ 0
ADC1
Text GLabel 4500 2150 0    50   Input ~ 0
ADC2
Text GLabel 4500 2250 0    50   Input ~ 0
ADC3
Wire Wire Line
	4500 2250 4750 2250
Wire Wire Line
	4750 2150 4500 2150
Wire Wire Line
	4500 2050 4750 2050
Text GLabel 4500 2550 0    50   Input ~ 0
ADC4
Text GLabel 4500 2650 0    50   Input ~ 0
ADC5
Wire Wire Line
	4500 2550 4750 2550
Wire Wire Line
	4750 2650 4500 2650
Text GLabel 4550 5250 0    50   Input ~ 0
ADC6
Text GLabel 4550 5350 0    50   Input ~ 0
ADC7
Text GLabel 4550 5450 0    50   Input ~ 0
ADC8
Wire Wire Line
	4550 5250 4750 5250
Wire Wire Line
	4750 5350 4550 5350
Wire Wire Line
	4550 5450 4750 5450
NoConn ~ 4750 1950
NoConn ~ 4750 1750
Text GLabel 6550 3650 2    50   Input ~ 0
BUTT1
Text GLabel 6550 3750 2    50   Input ~ 0
BUTT2
Text GLabel 6550 3850 2    50   Input ~ 0
BUTT3
Text GLabel 6550 3950 2    50   Input ~ 0
BUTT4
Text GLabel 6550 2550 2    50   Input ~ 0
GATE_IN1
Text GLabel 6550 2650 2    50   Input ~ 0
GATE_IN2
Wire Wire Line
	6400 1300 6400 1350
Wire Wire Line
	6400 1350 6350 1350
Wire Wire Line
	6400 1350 6400 1450
Wire Wire Line
	6400 1450 6350 1450
Connection ~ 6400 1350
$Comp
L power:GND #PWR02
U 1 1 61D397F8
P 5100 7250
F 0 "#PWR02" H 5100 7000 50  0001 C CNN
F 1 "GND" H 5105 7077 50  0000 C CNN
F 2 "" H 5100 7250 50  0001 C CNN
F 3 "" H 5100 7250 50  0001 C CNN
	1    5100 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 7150 5100 7200
Wire Wire Line
	5100 7200 5200 7200
Wire Wire Line
	6000 7150 6000 7200
Wire Wire Line
	6000 7200 5900 7200
Wire Wire Line
	5200 7150 5200 7200
Connection ~ 5200 7200
Wire Wire Line
	5200 7200 5300 7200
Wire Wire Line
	5300 7200 5300 7150
Connection ~ 5300 7200
Wire Wire Line
	5300 7200 5400 7200
Wire Wire Line
	5400 7150 5400 7200
Connection ~ 5400 7200
Wire Wire Line
	5400 7200 5500 7200
Wire Wire Line
	5500 7200 5500 7150
Connection ~ 5500 7200
Wire Wire Line
	5600 7150 5600 7200
Connection ~ 5600 7200
Wire Wire Line
	5700 7200 5700 7150
Connection ~ 5700 7200
Wire Wire Line
	5700 7200 5600 7200
Wire Wire Line
	5800 7150 5800 7200
Connection ~ 5800 7200
Wire Wire Line
	5800 7200 5700 7200
Wire Wire Line
	5900 7200 5900 7150
Connection ~ 5900 7200
Wire Wire Line
	5900 7200 5800 7200
NoConn ~ 6350 5350
NoConn ~ 6350 5450
NoConn ~ 6350 2350
NoConn ~ 6350 2450
NoConn ~ 4750 5850
NoConn ~ 4750 5150
NoConn ~ 4750 2950
NoConn ~ 4750 2850
NoConn ~ 4750 3050
NoConn ~ 4750 3150
NoConn ~ 4750 3650
NoConn ~ 4750 6450
NoConn ~ 4750 6550
NoConn ~ 4750 6650
Text Notes 4675 6800 1    50   ~ 0
weak pins
Text GLabel 6550 3150 2    50   Output ~ 0
LED1A
Text GLabel 6550 3250 2    50   Output ~ 0
LED1B
Text GLabel 6550 3350 2    50   Output ~ 0
LED2A
Text GLabel 6550 3450 2    50   Output ~ 0
LED2B
Text GLabel 6550 4550 2    50   Output ~ 0
LED3A
Text GLabel 6550 4750 2    50   Output ~ 0
LED3B
Text GLabel 6550 4950 2    50   Output ~ 0
LED4A
Text GLabel 6550 5050 2    50   Output ~ 0
LED4B
Wire Wire Line
	6350 5050 6550 5050
Wire Wire Line
	6550 4950 6350 4950
Wire Wire Line
	6350 4750 6550 4750
Wire Wire Line
	6550 4550 6350 4550
Wire Wire Line
	6350 3450 6550 3450
Wire Wire Line
	6550 3350 6350 3350
Wire Wire Line
	6350 3250 6550 3250
Wire Wire Line
	6550 3150 6350 3150
Wire Wire Line
	6550 2650 6350 2650
Wire Wire Line
	6350 2550 6550 2550
Wire Wire Line
	6550 3950 6350 3950
Wire Wire Line
	6350 3650 6550 3650
Wire Wire Line
	6350 3750 6550 3750
Wire Wire Line
	6550 3850 6350 3850
$Sheet
S 10100 2400 975  950 
U 622BE327
F0 "CV Inputs" 50
F1 "cv_in.sch" 50
$EndSheet
$Sheet
S 10100 1150 975  900 
U 6222B616
F0 "Audio I/O" 50
F1 "audio_io.sch" 50
$EndSheet
Wire Wire Line
	5500 7200 5600 7200
Wire Wire Line
	5100 7250 5100 7200
Connection ~ 5100 7200
Wire Wire Line
	6350 1650 6400 1650
Wire Wire Line
	6350 1750 6400 1750
Wire Wire Line
	6400 1750 6400 1650
Connection ~ 6400 1650
Text Notes 2225 5975 0    50   ~ 0
8 pots\n4 attenuverters\n4 buttons\n4 duo-color LEDs\n2 gate in\n2 gate out\n8 CV in\n2 CV out
Text GLabel 6550 2950 2    50   Output ~ 0
GATE_OUT1
Text GLabel 6550 3050 2    50   Output ~ 0
GATE_OUT2
Wire Wire Line
	6550 2950 6350 2950
Wire Wire Line
	6350 3050 6550 3050
NoConn ~ 6350 2250
NoConn ~ 6350 1950
NoConn ~ 4750 4150
NoConn ~ 4750 4250
NoConn ~ 6350 5150
NoConn ~ 6350 4850
NoConn ~ 6350 4650
NoConn ~ 6350 4450
Text GLabel 4550 4950 0    50   Output ~ 0
I2S_TX
Text GLabel 4550 4850 0    50   Input ~ 0
I2S_RX
Text Notes 8125 1600 0    50   ~ 0
done
Text Notes 9325 1600 0    50   ~ 0
done
Text Notes 10525 1600 0    50   ~ 0
done
$Sheet
S 10100 4725 975  950 
U 620487DC
F0 "Gate I/O" 50
F1 "gate_io.sch" 50
$EndSheet
NoConn ~ 5450 950 
NoConn ~ 5550 950 
NoConn ~ 5650 950 
Text Notes 8125 2875 0    50   ~ 0
done
Wire Wire Line
	6575 1600 6575 1650
Wire Wire Line
	6400 1650 6575 1650
$Sheet
S 10100 3550 975  950 
U 62AE40E0
F0 "CV outputs" 50
F1 "cv_out.sch" 50
$EndSheet
$Sheet
S 8900 3550 950  950 
U 61D5C679
F0 "LEDs and Buttons" 50
F1 "led_out.sch" 50
$EndSheet
Text Notes 8125 4025 0    50   ~ 0
done
Text Notes 9275 2875 0    50   ~ 0
done
$Comp
L power:+3V0 #PWR04
U 1 1 62AD02F9
P 6575 1600
F 0 "#PWR04" H 6575 1450 50  0001 C CNN
F 1 "+3V0" H 6590 1773 50  0000 C CNN
F 2 "" H 6575 1600 50  0001 C CNN
F 3 "" H 6575 1600 50  0001 C CNN
	1    6575 1600
	1    0    0    -1  
$EndComp
Text Notes 10500 2875 0    50   ~ 0
done
NoConn ~ 4750 3550
NoConn ~ 4750 5550
NoConn ~ 4750 5650
NoConn ~ 6350 4050
NoConn ~ 6350 4150
NoConn ~ 6350 4250
NoConn ~ 6350 4350
NoConn ~ 6350 2050
NoConn ~ 4750 3450
$Comp
L power:PWR_FLAG #FLG01
U 1 1 61E88C70
P 6575 1650
F 0 "#FLG01" H 6575 1725 50  0001 C CNN
F 1 "PWR_FLAG" V 6575 1778 50  0001 L CNN
F 2 "" H 6575 1650 50  0001 C CNN
F 3 "~" H 6575 1650 50  0001 C CNN
	1    6575 1650
	0    1    1    0   
$EndComp
Connection ~ 6575 1650
NoConn ~ 4750 1650
Text Notes 9275 4025 0    50   ~ 0
done
NoConn ~ 4750 4350
NoConn ~ 4750 4050
NoConn ~ 4750 2750
Text Notes 10525 4025 0    50   ~ 0
done
Text Notes 10475 5225 0    50   ~ 0
done
$EndSCHEMATC
