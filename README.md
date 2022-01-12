# axo-on-discovery-board
Axoloti on STM32F4 discovery board using a WM8731 codec for audio in/out



# Features:
* 20hp Eurorack module, STM32F4 Discovery board plugs into the back
* WM8731 codec with

  2 audio inputs (24bit, 48khz, +/-5V or +/-10V with a simple modification)

  2 audio outputs (24bit, 48khz, +/-5V)

* 8 pots
* 4 CV inputs with attenuverter (+/-5V) corresponding to pots 1-4
* 4 unattenuated CV inputs (+/-5V) corresponding to pots 5-8
* 2 gate inputs
* 2 gate outputs
* 2 CV outputs (12bit, +/-5V)
* 4 momentary switches
* 4 dual-color LEDs, PWM-able
* Micro SD card slot on panel
* 1024kbit SRAM (23LC1024 like on Teensy Audio Board)

# Progress:
Schematic [✓]
PCB layout [75%]

Please note that the USB programming port is on the STM32F4 Discovery board, in other words it is on the back of the module this not accessible when theodile is mounted. This is okay for my personal isecase as I don't reflash the unit often. 
