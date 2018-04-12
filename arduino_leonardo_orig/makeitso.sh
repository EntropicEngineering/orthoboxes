#!/bin/sh
#turns a connected leonardo back into a leonardo
avrdude -p atmega32u4 -P usb -c avrispmkii -U flash:w:ard_leo_orig.bin -U lfuse:w:ard_leo_orig_low.bin -U hfuse:w:ard_leo_orig_high.bin -U efuse:w:ard_leo_orig_ext.bin
