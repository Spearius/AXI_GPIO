# AXI GPIO - Zybo Z7-10

## Overview
This project demonstrates the use of AXI GPIO peripherals on the Zybo Z7-10 development board using Vivado to build the hardware side and Vitis to build the software side.
The hardware design was created in Vivado using the Zynq-7000 Processing System and multiple AXI GPIO peripherals. The hardware platform was exported to Vitis, where C programming was developed to control the onboard LEDs and RGB LED using the four onboard switches.

## Hardware
ZYNQ - Zybo-Z7 (7010 Development Board)

## Software
Vivado 2023.1
Vitis 2023.1
C Programming Language

## AXI GPIO Configuration
Three AXI GPIO peripherals are used:

AXI GPIO 0 (output)
&#x20;  - Controls LED0 through LED3.
&#x20;  - Configured as an output.

AXI GPIO 1 (output)
&#x20;  - Controls the onboard RGB LED.
&#x20;  - Configured as an output.

AXI GPIO 2 (input)
&#x20;  - Reads SW0 through SW3.
&#x20;  - Configured as an input.

## Functionality
The switches control the LEDs and RGB LED as follows:

AXI GPIO 2 Switch Input Function:

SW0 - LED0 ON and RGB LED Red
SW1 - LED1 ON and RGB LED Green
SW2 - LED2 ON and RGB LED Blue
SW3 - LED3 ON and RGB LED White
SW0 + SW1 - 4-bit Binary Counter enabled
SW2 + SW3 - 4-bit Ring counter enabled
Other Switch Combinations - LEDs OFF & RGB LED OFF

The Binary Counter repeatedly counts from `0000` through `1111`.
The Ring Counter repeatedly cycles through `0001 -> 0010 -> 0100 -> 1000 -> 0001`.
