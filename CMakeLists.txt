cmake_minimum_required(VERSION 3.8)
project(orthoboxes)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Config/AppConfig.h
        Config/LUFAConfig.h
        adc.c
        adc.h
        box.c
        box.h
        Descriptors.c
        Descriptors.h
        GenericHID.c
        GenericHID.h
        led.c
        led.h
        ModuleSystem.h
        peggy.c
        peggy.h
        pokey.c
        pokey.h
        Timer.c
        Timer.h
        WireConversions.c
        WireConversions.h webusb.h)

include_directories(lufa /usr/local/CrossPack-AVR/avr/include)

add_executable(orthoboxes ${SOURCE_FILES})