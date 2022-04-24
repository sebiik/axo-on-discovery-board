# axo-on-discovery-board
Axoloti on STM32F4 discovery board using a WM8731 codec for audio in/out



Please note that the USB programming port is on the STM32F4 Discovery board, in other words it is on the back of the module and only accessible when the module is removed from the case. I didn't bother messing with the STM32F4's USB OTG ports as they are already laid out on the Discovery. This is okay for my personal use case as I don't reflash the unit often.


# Features:
* 20hp Eurorack module, STM32F4 Discovery board plugs into the back
* 2 audio inputs (24bit, 48khz, +/-5V or +/-10V with a simple modification)
* 2 audio outputs (24bit, 48khz, +/-5V)
* 8 pots
* 4 protected CV inputs with attenuverter (+/-5V) corresponding to pots 1-4
* 4 unattenuated protected CV inputs (+/-5V) corresponding to pots 5-8
* 2 gate inputs with protection
* 2 gate outputs (+10V)
* 2 CV outputs (12bit resolution, +/-5V)
* 4 momentary switches
* 4 dimmable dual-color LEDs
* Micro SD card slot on panel
* 1024kbit SRAM (23LC1024 like on Teensy Audio Board)

# Progress:

Feature set [✓]

Schematic [✓]

PCB layout [75%]



Please note that the USB programming port is on the STM32F4 Discovery board, in other words it is on the back of the module and only accessible when the module is removed from the case. This is okay for my personal usecase as I don't reflash the unit often.
