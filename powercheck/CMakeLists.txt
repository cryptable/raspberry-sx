cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pimoroni_pico_import.cmake)
include(pico_sdk_import.cmake)

project(powermgmnt C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

add_executable(powermgmnt
        powermgmnt.cpp
        powerdisplay.cpp
        )

# Include required libraries
include(common/pimoroni_i2c)
include(common/pimoroni_bus)
include(drivers/st7735/st7735)
include(libraries/bitmap_fonts/bitmap_fonts)
include(libraries/hershey_fonts/hershey_fonts)
include(libraries/pico_graphics/pico_graphics)

# pull in common dependencies
target_link_libraries(powermgmnt pico_stdlib pico_graphics st7735 hardware_spi hardware_i2c)

# STDIO thrugh the USB
pico_enable_stdio_usb(powermgmnt 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(powermgmnt)

