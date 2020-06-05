EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
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
L axof4_base_board-rescue:GND-power #PWR024
U 1 1 5ECDDAD6
P 5300 4600
AR Path="/5ECDA234/5ECDDAD6" Ref="#PWR024"  Part="1" 
AR Path="/5ED86ED4/5ECDDAD6" Ref="#PWR027"  Part="1" 
F 0 "#PWR027" H 5300 4350 50  0001 C CNN
F 1 "GND" H 5305 4427 50  0000 C CNN
F 2 "" H 5300 4600 50  0001 C CNN
F 3 "" H 5300 4600 50  0001 C CNN
	1    5300 4600
	1    0    0    -1  
$EndComp
$Comp
L axof4_base_board-rescue:+3.3V-power #PWR023
U 1 1 5ECDF67F
P 8000 3100
AR Path="/5ECDA234/5ECDF67F" Ref="#PWR023"  Part="1" 
AR Path="/5ED86ED4/5ECDF67F" Ref="#PWR029"  Part="1" 
F 0 "#PWR029" H 8000 2950 50  0001 C CNN
F 1 "+3.3V" H 8000 3250 50  0000 C CNN
F 2 "" H 8000 3100 50  0001 C CNN
F 3 "" H 8000 3100 50  0001 C CNN
	1    8000 3100
	1    0    0    -1  
$EndComp
$Comp
L dk_PMIC-Voltage-Regulators-Linear:L7805CV U3
U 1 1 5ED8BF7B
P 4700 3350
F 0 "U3" H 4700 3637 60  0000 C CNN
F 1 "L7805CV" H 4700 3531 60  0000 C CNN
F 2 "digikey-footprints:TO-220-3" H 4900 3550 60  0001 L CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 4900 3650 60  0001 L CNN
F 4 "497-1443-5-ND" H 4900 3750 60  0001 L CNN "Digi-Key_PN"
F 5 "L7805CV" H 4900 3850 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 4900 3950 60  0001 L CNN "Category"
F 7 "PMIC - Voltage Regulators - Linear" H 4900 4050 60  0001 L CNN "Family"
F 8 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 4900 4150 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/stmicroelectronics/L7805CV/497-1443-5-ND/585964" H 4900 4250 60  0001 L CNN "DK_Detail_Page"
F 10 "IC REG LINEAR 5V 1.5A TO220AB" H 4900 4350 60  0001 L CNN "Description"
F 11 "STMicroelectronics" H 4900 4450 60  0001 L CNN "Manufacturer"
F 12 "Active" H 4900 4550 60  0001 L CNN "Status"
	1    4700 3350
	1    0    0    -1  
$EndComp
$Comp
L axof4_base_board-rescue:+5V-power #PWR028
U 1 1 5ED8D0B0
P 5500 3150
F 0 "#PWR028" H 5500 3000 50  0001 C CNN
F 1 "+5V-power" H 5515 3323 50  0000 C CNN
F 2 "" H 5500 3150 50  0001 C CNN
F 3 "" H 5500 3150 50  0001 C CNN
	1    5500 3150
	1    0    0    -1  
$EndComp
$Comp
L dk_PMIC-Voltage-Regulators-Linear:LM1117MPX-3_3_NOPB U4
U 1 1 5ED8D948
P 7200 3350
F 0 "U4" H 7150 3637 60  0000 C CNN
F 1 "LM1117MPX-3_3_NOPB" H 7150 3531 60  0000 C CNN
F 2 "digikey-footprints:SOT-223" H 7400 3550 60  0001 L CNN
F 3 "http://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Flm1117" H 7400 3650 60  0001 L CNN
F 4 "LM1117MPX-3.3/NOPBCT-ND" H 7400 3750 60  0001 L CNN "Digi-Key_PN"
F 5 "LM1117MPX-3.3/NOPB" H 7400 3850 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 7400 3950 60  0001 L CNN "Category"
F 7 "PMIC - Voltage Regulators - Linear" H 7400 4050 60  0001 L CNN "Family"
F 8 "http://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Flm1117" H 7400 4150 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/texas-instruments/LM1117MPX-3.3-NOPB/LM1117MPX-3.3-NOPBCT-ND/1010516" H 7400 4250 60  0001 L CNN "DK_Detail_Page"
F 10 "IC REG LIN 3.3V 800MA SOT223-4" H 7400 4350 60  0001 L CNN "Description"
F 11 "Texas Instruments" H 7400 4450 60  0001 L CNN "Manufacturer"
F 12 "Active" H 7400 4550 60  0001 L CNN "Status"
	1    7200 3350
	1    0    0    -1  
$EndComp
$Comp
L dk_PMIC-Voltage-Regulators-Linear:LM1117MPX-3_3_NOPB U5
U 1 1 5ED8E22F
P 7200 4700
F 0 "U5" H 7150 4987 60  0000 C CNN
F 1 "LM1117MPX-3_3_NOPB" H 7150 4881 60  0000 C CNN
F 2 "digikey-footprints:SOT-223" H 7400 4900 60  0001 L CNN
F 3 "http://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Flm1117" H 7400 5000 60  0001 L CNN
F 4 "LM1117MPX-3.3/NOPBCT-ND" H 7400 5100 60  0001 L CNN "Digi-Key_PN"
F 5 "LM1117MPX-3.3/NOPB" H 7400 5200 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 7400 5300 60  0001 L CNN "Category"
F 7 "PMIC - Voltage Regulators - Linear" H 7400 5400 60  0001 L CNN "Family"
F 8 "http://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Flm1117" H 7400 5500 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/texas-instruments/LM1117MPX-3.3-NOPB/LM1117MPX-3.3-NOPBCT-ND/1010516" H 7400 5600 60  0001 L CNN "DK_Detail_Page"
F 10 "IC REG LIN 3.3V 800MA SOT223-4" H 7400 5700 60  0001 L CNN "Description"
F 11 "Texas Instruments" H 7400 5800 60  0001 L CNN "Manufacturer"
F 12 "Active" H 7400 5900 60  0001 L CNN "Status"
	1    7200 4700
	1    0    0    -1  
$EndComp
$Comp
L axof4_base_board-rescue:+3.3VA-power #PWR030
U 1 1 5ED8E8BF
P 8000 4450
F 0 "#PWR030" H 8000 4300 50  0001 C CNN
F 1 "+3.3VA-power" H 8015 4623 50  0000 C CNN
F 2 "" H 8000 4450 50  0001 C CNN
F 3 "" H 8000 4450 50  0001 C CNN
	1    8000 4450
	1    0    0    -1  
$EndComp
$Comp
L dk_Diodes-Rectifiers-Single:1N4001-G D1
U 1 1 5ED90192
P 3500 3350
F 0 "D1" H 3500 3587 60  0000 C CNN
F 1 "1N4001-G" H 3500 3481 60  0000 C CNN
F 2 "digikey-footprints:DO-41" H 3700 3550 60  0001 L CNN
F 3 "http://www.comchiptech.com/admin/files/product/1N4001-G%20Thru.%201N4007-G%20RevB.pdf" H 3700 3650 60  0001 L CNN
F 4 "641-1310-1-ND" H 3700 3750 60  0001 L CNN "Digi-Key_PN"
F 5 "1N4001-G" H 3700 3850 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 3700 3950 60  0001 L CNN "Category"
F 7 "Diodes - Rectifiers - Single" H 3700 4050 60  0001 L CNN "Family"
F 8 "http://www.comchiptech.com/admin/files/product/1N4001-G%20Thru.%201N4007-G%20RevB.pdf" H 3700 4150 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/comchip-technology/1N4001-G/641-1310-1-ND/1979675" H 3700 4250 60  0001 L CNN "DK_Detail_Page"
F 10 "DIODE GEN PURP 50V 1A DO41" H 3700 4350 60  0001 L CNN "Description"
F 11 "Comchip Technology" H 3700 4450 60  0001 L CNN "Manufacturer"
F 12 "Active" H 3700 4550 60  0001 L CNN "Status"
	1    3500 3350
	1    0    0    -1  
$EndComp
$Comp
L dk_Barrel-Power-Connectors:PJ-102A J2
U 1 1 5ED93FD0
P 2950 3350
F 0 "J2" H 2883 3575 50  0000 C CNN
F 1 "PJ-102A" H 2883 3484 50  0000 C CNN
F 2 "digikey-footprints:Barrel_Jack_5.5mmODx2.1mmID_PJ-102A" H 3150 3550 60  0001 L CNN
F 3 "https://www.cui.com/product/resource/digikeypdf/pj-102a.pdf" H 3150 3650 60  0001 L CNN
F 4 "CP-102A-ND" H 3150 3750 60  0001 L CNN "Digi-Key_PN"
F 5 "PJ-102A" H 3150 3850 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 3150 3950 60  0001 L CNN "Category"
F 7 "Barrel - Power Connectors" H 3150 4050 60  0001 L CNN "Family"
F 8 "https://www.cui.com/product/resource/digikeypdf/pj-102a.pdf" H 3150 4150 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/cui-inc/PJ-102A/CP-102A-ND/275425" H 3150 4250 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN PWR JACK 2X5.5MM SOLDER" H 3150 4350 60  0001 L CNN "Description"
F 11 "CUI Inc." H 3150 4450 60  0001 L CNN "Manufacturer"
F 12 "Active" H 3150 4550 60  0001 L CNN "Status"
	1    2950 3350
	1    0    0    -1  
$EndComp
Text Notes 2600 3700 0    50   ~ 0
DC 9-12V IN
Wire Wire Line
	3050 3350 3300 3350
$Comp
L axof4_base_board-rescue:C_Small-Device C25
U 1 1 5ED96746
P 4100 3450
F 0 "C25" H 4192 3496 50  0000 L CNN
F 1 "330n" H 4192 3405 50  0000 L CNN
F 2 "" H 4100 3450 50  0001 C CNN
F 3 "" H 4100 3450 50  0001 C CNN
	1    4100 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 3350 4100 3350
Wire Wire Line
	3050 3550 3250 3550
Wire Wire Line
	3250 3550 3250 3700
Wire Wire Line
	3250 3700 3700 3700
Wire Wire Line
	4100 3700 4100 3550
Wire Wire Line
	4100 3350 4400 3350
Connection ~ 4100 3350
Wire Wire Line
	4100 3700 4700 3700
Wire Wire Line
	4700 3700 4700 3650
Connection ~ 4100 3700
$Comp
L axof4_base_board-rescue:C_Small-Device C26
U 1 1 5ED987BF
P 5300 3500
F 0 "C26" H 5392 3546 50  0000 L CNN
F 1 "100n" H 5392 3455 50  0000 L CNN
F 2 "" H 5300 3500 50  0001 C CNN
F 3 "" H 5300 3500 50  0001 C CNN
	1    5300 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3350 5300 3350
Wire Wire Line
	5300 3350 5300 3400
Wire Wire Line
	5300 3350 5500 3350
Wire Wire Line
	5500 3350 5500 3150
Connection ~ 5300 3350
Wire Wire Line
	4700 3700 5300 3700
Wire Wire Line
	5300 3700 5300 3600
Connection ~ 4700 3700
Wire Wire Line
	5300 4600 5300 3700
Connection ~ 5300 3700
$Comp
L axof4_base_board-rescue:CP1_Small-Device C27
U 1 1 5ED9C001
P 5750 3500
F 0 "C27" H 5841 3546 50  0000 L CNN
F 1 "1u" H 5841 3455 50  0000 L CNN
F 2 "" H 5750 3500 50  0001 C CNN
F 3 "" H 5750 3500 50  0001 C CNN
	1    5750 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 3350 5750 3350
Wire Wire Line
	5750 3350 5750 3400
Connection ~ 5500 3350
Wire Wire Line
	5300 3700 5750 3700
Wire Wire Line
	5750 3700 5750 3600
$Comp
L axof4_base_board-rescue:R-Device R25
U 1 1 5EDA1E36
P 6200 3350
F 0 "R25" V 6100 3350 50  0000 C CNN
F 1 "4.7" V 6200 3350 50  0000 C CNN
F 2 "" V 6130 3350 50  0001 C CNN
F 3 "" H 6200 3350 50  0001 C CNN
	1    6200 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	5750 3350 6000 3350
Connection ~ 5750 3350
$Comp
L axof4_base_board-rescue:CP1_Small-Device C28
U 1 1 5EDA2BEA
P 6500 3500
F 0 "C28" H 6591 3546 50  0000 L CNN
F 1 "10u" H 6591 3455 50  0000 L CNN
F 2 "" H 6500 3500 50  0001 C CNN
F 3 "" H 6500 3500 50  0001 C CNN
	1    6500 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3350 6500 3350
Wire Wire Line
	6500 3350 6500 3400
Wire Wire Line
	5750 3700 6100 3700
Wire Wire Line
	6500 3700 6500 3600
Connection ~ 5750 3700
Wire Wire Line
	6500 3350 6800 3350
Connection ~ 6500 3350
Wire Wire Line
	6500 3700 6500 3850
Wire Wire Line
	6500 3850 7100 3850
Wire Wire Line
	7100 3850 7100 3750
Connection ~ 6500 3700
Wire Wire Line
	7500 3450 7500 3350
Connection ~ 7500 3350
$Comp
L axof4_base_board-rescue:C_Small-Device C31
U 1 1 5EDADB63
P 8000 3450
F 0 "C31" H 8092 3496 50  0000 L CNN
F 1 "100n" H 8092 3405 50  0000 L CNN
F 2 "" H 8000 3450 50  0001 C CNN
F 3 "" H 8000 3450 50  0001 C CNN
	1    8000 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3850 7700 3850
Wire Wire Line
	7700 3850 7700 3550
Connection ~ 7100 3850
Wire Wire Line
	7700 3850 8000 3850
Wire Wire Line
	8000 3850 8000 3550
Connection ~ 7700 3850
Wire Wire Line
	8000 3100 8000 3350
Connection ~ 8000 3350
Wire Wire Line
	6000 3350 6000 4700
Wire Wire Line
	6000 4700 6800 4700
Connection ~ 6000 3350
Wire Wire Line
	6000 3350 6050 3350
$Comp
L axof4_base_board-rescue:CP1_Small-Device C30
U 1 1 5EDBC007
P 7700 4800
F 0 "C30" H 7791 4846 50  0000 L CNN
F 1 "10u" H 7791 4755 50  0000 L CNN
F 2 "" H 7700 4800 50  0001 C CNN
F 3 "" H 7700 4800 50  0001 C CNN
	1    7700 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 4700 7700 4700
$Comp
L axof4_base_board-rescue:C_Small-Device C32
U 1 1 5EDBC00E
P 8000 4800
F 0 "C32" H 8092 4846 50  0000 L CNN
F 1 "100n" H 8092 4755 50  0000 L CNN
F 2 "" H 8000 4800 50  0001 C CNN
F 3 "" H 8000 4800 50  0001 C CNN
	1    8000 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 4700 8000 4700
Connection ~ 7700 4700
Wire Wire Line
	7100 5200 7700 5200
Wire Wire Line
	7700 5200 7700 4900
Wire Wire Line
	7700 5200 8000 5200
Wire Wire Line
	8000 5200 8000 4900
Connection ~ 7700 5200
Wire Wire Line
	8000 4450 8000 4700
Connection ~ 8000 4700
Wire Wire Line
	7500 4800 7500 4700
Connection ~ 7500 4700
Wire Wire Line
	7100 5200 7100 5100
Connection ~ 7100 5200
$Comp
L axof4_base_board-rescue:CP1_Small-Device C24
U 1 1 5EDC119E
P 3700 3500
F 0 "C24" H 3791 3546 50  0000 L CNN
F 1 "10u" H 3791 3455 50  0000 L CNN
F 2 "" H 3700 3500 50  0001 C CNN
F 3 "" H 3700 3500 50  0001 C CNN
	1    3700 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 3400 3700 3350
Connection ~ 3700 3350
Wire Wire Line
	3700 3600 3700 3700
Connection ~ 3700 3700
Wire Wire Line
	3700 3700 4100 3700
Wire Wire Line
	6100 5200 6100 3700
Wire Wire Line
	6100 5200 7100 5200
Connection ~ 6100 3700
Wire Wire Line
	6100 3700 6500 3700
Connection ~ 7700 3350
Wire Wire Line
	7700 3350 8000 3350
Wire Wire Line
	7500 3350 7700 3350
$Comp
L axof4_base_board-rescue:CP1_Small-Device C29
U 1 1 5EDA7B97
P 7700 3450
F 0 "C29" H 7791 3496 50  0000 L CNN
F 1 "10u" H 7791 3405 50  0000 L CNN
F 2 "" H 7700 3450 50  0001 C CNN
F 3 "" H 7700 3450 50  0001 C CNN
	1    7700 3450
	1    0    0    -1  
$EndComp
$EndSCHEMATC
