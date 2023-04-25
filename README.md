# axo-on-discovery-board
Axoloti on a ~~STM32F4 discovery board~~ Eurorack board using a WM8731 codec for audio in/out

The images show the first prototype using a STM32F4 discovery board (use what you have).


![image front](/images/v01_image_front.jpg)



![image side](/images/v01_image_side.jpg)



![image back](/images/v01_image_back.jpg)



~~Please note that the USB programming port is on the STM32F4 Discovery board, in other words it is on the back of the module and only accessible when the module is removed from the case. I didn't bother messing with the STM32F4's USB OTG ports as they are already laid out on the Discovery. This is okay for my personal use case as I don't reflash the unit often.~~

Turns out the USB programming port pins are not even accessible on the Discovery board. I plan to get rid of the Discovery altogether and design a custom Core board carrying an STM32F427, SDRAM and whatever (which will bring us MUCH closer to the original Axoloti).

~~No plans to add an USB host port so far as there are TRS MIDI jacks already on the board.~~

# Features:

* 20hp Eurorack module, "upgradeable" Core board plugs into the back
* 2 audio inputs (24bit, 48khz, +/-5V or +/-10V with a simple modification)
* 2 audio outputs (24bit, 48khz, +/-5V)
* 8 pots
* 4 unattenuated CV inputs (+/-5V) getting summed with pots 1-4
* 4 attenuated CV inputs (+/-5V) patchable as objects
* 4 unattenuated CV inputs (+/-5V) patchable as objects
* 2 protected gate inputs
* 2 gate outputs (+10V)
* 2 CV outputs (12bit resolution, +/-5V)
* 4 momentary switches
* 4 dimmable dual-colour LEDs
* Micro SD card slot on panel
* USB programming port on panel (talk to Axoloti Patcher)
* USB host port on panel (connect USB MIDI keyboard directly)


# Frontend board & panel progress:

* Feature set [✓]
* Schematic [75%]
* PCB layout [10%]


# Core board progress:

* Feature set [✓]
* Schematic [✓]
* PCB layout [99%]


# Wishlist:
* expansion header, expansion module with OLED, encoder, menu buttons?
