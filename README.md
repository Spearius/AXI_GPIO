\# AXI GPIO - Zybo Z7-10



\## Overview



This project demonstrates the use of AXI GPIO peripherals on the Zybo Z7-10 development board using Vivado and Vitis.



The hardware design was created in Vivado using the Zynq-7000 Processing System and multiple AXI GPIO peripherals. The hardware platform was exported to Vitis, where a C application was developed to control the onboard LEDs and RGB LED using the four onboard switches.



\## Hardware



\- Digilent Zybo Z7-10

\- Zynq-7000 SoC

\- 4 onboard switches

\- 4 onboard LEDs

\- Onboard RGB LED



\## Software



\- Vivado 2023.1

\- Vitis 2023.1

\- C



\## AXI GPIO Configuration



Three AXI GPIO peripherals are used:



1\. AXI GPIO 0

&#x20;  - Controls LED0 through LED3.

&#x20;  - Configured as an output.



2\. AXI GPIO 1

&#x20;  - Controls the onboard RGB LED.

&#x20;  - Configured as an output.



3\. AXI GPIO 2

&#x20;  - Reads SW0 through SW3.

&#x20;  - Configured as an input.



\## Functionality



The switches control the LEDs and RGB LED as follows:



| Switch Input | Function |

| --- | --- |

| SW0 | LED0 ON and RGB LED Red |

| SW1 | LED1 ON and RGB LED Green |

| SW2 | LED2 ON and RGB LED Blue |

| SW3 | LED3 ON and RGB LED White |

| SW0 + SW1 | 4-bit binary counter on LED0-LED3 |

| SW2 + SW3 | 4-bit ring counter on LED0-LED3 |

| Other combinations | LEDs OFF |



The binary counter repeatedly counts from `0000` through `1111`.



The ring counter repeatedly cycles through:



`0001 -> 0010 -> 0100 -> 1000 -> 0001`



\## Project Files



\- `axi\_gpio\_rc.xpr` - Vivado project file.

\- `axi\_gpio\_rc.srcs/` - Vivado block design and IP configuration files.

\- `axi\_gpio\_rc\_wrapper.xsa` - Original exported hardware platform.

\- `axi\_gpio\_rc\_wrapper\_new.xsa` - Updated exported hardware platform.

\- `axio\_gpio\_vitis/axi\_gpio\_app/src/helloworld.c` - Original Vitis C application.

\- `axio\_gpio\_vitis/axi\_gpio\_app\_new/src/helloworld.c` - Updated Vitis C application.



\## Notes



Generated Vivado and Vitis build files are excluded from the repository using `.gitignore`.

