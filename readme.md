# ffinterface

![ffinterface](docs/bigButton.jpg)

*In the world of GUI, less mouse pointers, more fat fingers buttons.* 

A button box to interface with web-based GUI, when you want to just push on buttons to do repetitive tasks. This replaces the need for the small buttons of a keyboard, or *worse*, a MOUSE.

* Keyboard Maintainer: [Eliott CHOMARD](https://github.com/Totile)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

This project is based on [QMK](https://qmk.fm/). [Setup your environment](https://docs.qmk.fm/#/getting_started_build_tools first) first. More information on the software: [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Clone this repo in the correct qmk_firmware folder

    cd ~/qmk_firmware/keyboards
    git clone git@github.com:Totile/ffcontrol.git

Flashing the default firmware to the controller. Enter controller bootloader when prompted (2 clicks on the reset button)

    qmk flash -kb ffcontrol -km default
