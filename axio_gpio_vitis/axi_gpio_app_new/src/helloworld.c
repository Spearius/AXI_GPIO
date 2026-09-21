/*
 * ECE 524L - AXI GPIO Lab
 *
 * This program uses three AXI GPIO peripherals on the Zybo Z7:
 *
 * 1. Four onboard LEDs (LD0 - LD3) configured as outputs.
 * 2. One RGB LED configured as an output.
 * 3. Four onboard switches (SW0 - SW3) configured as inputs.
 *
 * Switch Functions:
 * SW0       -> LD0 ON, RGB Red
 * SW1       -> LD1 ON, RGB Green
 * SW2       -> LD2 ON, RGB Blue
 * SW3       -> LD3 ON, RGB White
 * SW0 + SW1 -> 4-bit binary counter on LD0 - LD3
 * SW2 + SW3 -> 4-bit ring counter on LD0 - LD3
 *
 * All other switch combinations turn the LEDs and RGB LED OFF.
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpio.h"

#define LED_DELAY (100000000)

int main()
{
	// INSTANTIATIONS:
    XGpio Gpio_LED;
    XGpio Gpio_RGB;
    XGpio Gpio_SW;

	// LOCAL VARIABLES:
    int Status;
    volatile int delay;
    u32 switchValue;
    int binaryCount;
    int ringCount;

    // INITIALIZATIONS:
    init_platform();

    // LED GPIO Initialization (output)
    Status = XGpio_Initialize(&Gpio_LED, XPAR_AXI_GPIO_0_DEVICE_ID);
    if (Status != XST_SUCCESS)
    {
        xil_printf("LED GPIO Initialization Failed.\r\n");
        return XST_FAILURE;
    }

    // RGB GPIO Initialization (output)
    Status = XGpio_Initialize(&Gpio_RGB, XPAR_AXI_GPIO_1_DEVICE_ID);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RGB GPIO Initialization Failed.\r\n");
        return XST_FAILURE;
    }

    // Switch GPIO Initialization (input)
    Status = XGpio_Initialize(&Gpio_SW, XPAR_AXI_GPIO_2_DEVICE_ID);

    // Check if the initialization was successful
    if (Status != XST_SUCCESS)
    {
        xil_printf("Switch GPIO Initialization Failed.\r\n");
        return XST_FAILURE;
    }

    xil_printf("GPIOs successfully initialized.\r\n");

    // Found in xgpio.c file for function implementation
    XGpio_SetDataDirection(&Gpio_LED, 1, 0x0);
    XGpio_SetDataDirection(&Gpio_RGB, 1, 0x0);
    XGpio_SetDataDirection(&Gpio_SW, 1, 0xF);

    while(1)
    {
    	switchValue = XGpio_DiscreteRead(&Gpio_SW,1);

    	if (switchValue == 0x1)			// Switch0
    	{
    		XGpio_DiscreteWrite(&Gpio_LED, 1, 0x1);
    		XGpio_DiscreteWrite(&Gpio_RGB, 1, 0x4);
    	}

    	else if (switchValue == 0x2)	// Switch1
    	{
    	    XGpio_DiscreteWrite(&Gpio_LED, 1, 0x2);
    	    XGpio_DiscreteWrite(&Gpio_RGB, 1, 0x2);
    	}

    	else if (switchValue == 0x4)	// Switch2
    	{
    	    XGpio_DiscreteWrite(&Gpio_LED, 1, 0x4);
    	    XGpio_DiscreteWrite(&Gpio_RGB, 1, 0x1);
    	}

    	else if (switchValue == 0x8)	// Switch3
    	{
    	    XGpio_DiscreteWrite(&Gpio_LED, 1, 0x8);
    	    XGpio_DiscreteWrite(&Gpio_RGB, 1, 0x7);
    	}

    	// Binary Counter Section
    	else if (switchValue == 0x3)	// Switch0and1
    	{
    	    // Turn RGB LED OFF
    	    XGpio_DiscreteWrite(&Gpio_RGB, 1, 0x0);

    	    binaryCount = 0;

    	    while (XGpio_DiscreteRead(&Gpio_SW, 1) == 0x3)
    	    {
    	        XGpio_DiscreteWrite(&Gpio_LED, 1, binaryCount);

    	        for (delay = 0; delay < LED_DELAY; delay++);

    	        binaryCount++;

    	        if (binaryCount > 0xF)
    	        {
    	            binaryCount = 0;
    	        }
    	    }
    	}

    	// Ring Counter Section
    	else if (switchValue == 0xC)	// Switch2and3
    	{
    	    // Turn RGB LED OFF
    	    XGpio_DiscreteWrite(&Gpio_RGB, 1, 0x0);

    	    // RING COUNTER
    	    ringCount = 0x1;

    	    while (XGpio_DiscreteRead(&Gpio_SW, 1) == 0xC)
    	    {
    	        XGpio_DiscreteWrite(&Gpio_LED, 1, ringCount);

    	        for (delay = 0; delay < LED_DELAY; delay++);

    	        ringCount = ringCount << 1;

    	        if (ringCount > 0x8)
    	        {
    	            ringCount = 0x1;
    	        }
    	    }
    	}

    	// OFF Condition
    	else
    	{
    	    XGpio_DiscreteWrite(&Gpio_LED, 1, 0x0);
    	    XGpio_DiscreteWrite(&Gpio_RGB, 1, 0x0);
    	}
    }

}
