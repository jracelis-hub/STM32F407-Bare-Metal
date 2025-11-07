# STM32F407 Discovery Baremetal

A baremetal project written in C++ for STM32F407 Discovery board, tackling system clock configurations. The design intent is to learn the basics of registers and bit manipulation, while removing the abstraction found in many C/C++ microcontroller libraries. The bare metal clock driver 

## STM32F407 Discovery Clock Flow

```
                                                                 Configuration
-----------------------------------------------------------------------------------------------------------------------------------------------------
|                                                                                                                                                   |
|   HSI -------------------------------------------------------                                                                                     |
|             |                                               |                                                   -----> /8 ---> Cortex SysTick     | 
|             |                                               |                                                   |                                 |
|             |                                               ---HSE------> \\     Max 168 MHz                    |----> FCLK Cortex free running   |
|   HSE ---------------------------------------------------------HSI------> | | ---> SysCLK ---> /AHB ---> HCLK --|          CLK                    |
|    |        |                                                 PLLCLK----> //                                    |                                 |
|    |        |                                                      /|\                                          |----> /APB1 ---> P2CLK           |
|    |        |                            PLL                        |                                           |        |                        |
|    |        |                           --------------------------- |                                           |        --*TIM--> TIMER          |
|    |        --HSI--> \\                 |                         | |                                           |                                 |
|    |                 | | ---> /PLLM --->| --> VCO --------> /PLLP |--                                           -----> /APB2 ---> P1CLK           |
|    -----------HSE--> //                 | /|\         |           |                                                      |                        |
|                                         |  |         \|/          |                                                      --*TIM--> TIMER          |
|                                         |  -- *PLLN ---           |                                                                               |
|                                         ---------------------------                                                                               |
|                                                                                                                                                   |
|                          /\                                                                                                                       |
|                         / | <--- LSI                                                                                                              | 
|                        /  | <--- LSE                                                                                                              |
|   MCO1 <-- /Prescaler |   |                                                                                                                       |
|                        \  | <--- HSI                                                                                                              |
|                         \ | <--- HSE                                                                                                              |
|                          \/                                                                                                                       |
|                                                                                                                                                   |
|                          /\                                                                                                                       |
|                         / | <--- LSI                                                                                                              |
|                        /  | <--- LSE                                                                                                              |
|   MCO2 <-- /Prescaler |   |                                                                                                                       |
|                        \  | <--- HSI                                                                                                              |
|                         \ | <--- HSE                                                                                                              |
|                          \/                                                                                                                       |
-----------------------------------------------------------------------------------------------------------------------------------------------------
```

## Quick Start

**Steps To Configure Clock:**

1. Determine system clock frequency requirements for project intent
2. Choose system clock type:
	- HSE (external)
	- HSI (internal microcontroller)
	- PLL (over/under clocking)
		- Needs clock input (HSI or HSE)
3. Configure System clock 
	- Select HSI
	- Select HSE
	- Select PLL
4. Configure Peripheral Clock
	- AHB - High speed bus
	- APB1 - High speed peripheral bus
	- APB2 - Low speed peripheral bus
5. Enable Peripheral Clock

**Driver Usage**

The driver is broken into a class `Sys_Clock`, sys_clock is the input to all hardware on the peripheral.

It drives the peripheral buses and the system as a whole.

`Sys_Clock` can be created two ways:
```
Sys_Clock hsi = Sys_Clock();

/* Or */

Sys_Clock hse = Sys_Clock(Sys_Oscillator_Type osc_type);
```

`Sys_Oscillator_Type` is nothing but a enum class that specifies the type of input source clock being used:
- HSI 
- HSE
- PLL

> By default upon microcontroller power on reset, HSI is already the default clock.

If HSE is needed for precise accuracy do the following:
```
Sys_Clock hse = Sys_Clock(Sys_Oscillator_Type::OSC_TYPE_HSE);
hse.sysclk_select_hse();
```
- `Sys_Clock(Sys_Oscillator_Type::OSC_TYPE_HSE` - enables HSE but does not use it as the system clock
- `.sysclk_select_hse()` - selects HSE as clock source and from here HSI can be disabled (done within `sysclk_select_hse()`)

To use PLL for overclocking or underclocking it needs an input clock soure, either HSI or HSE. 

After the initial object is created HSI or HSE use:
```
hse.configure_source_pll();
hsi.configure_source_pll();
/* Prescaleres to configure PLLCLK to desired clock frequency */
hsi.configure_prescaler_pllm(Prescaler_PLLM pllm);
hsi.configure_prescaler_plln(Prescaler_PLLN plln);
hsi.configure_prescaler_pllp(Prescaler_PLLM pllp);

if (hsi.configure_flash_latency() != Frequency_Sys_Clock_Status::STATUS_SYS_CLOCK_OK)
{ error_handler(); }
hsi.sysclk_select_pll();
```
- `Prescaler_PLLx` - a enum class that provides a strongly type parameter that provides guards of what type of prescalers can be passed into PLL.
- `.configure_source_pll()` - chooses which clock input is driving the pll (HSI or HSE)
- `.configure_prescaler_pllx` - the prescalers is there to manipulate the input clock to produce the output PLLCLK
- `.configure_flash_latency()` - depending on the frequency of the clock there has to be wait states in order to use a specific latency, it returns a `NOK` or `OK` as the microcontroller will crash if not done
- `.configure_select_pll()` - selects PLL as system clock

> [!CAUTION]
> There are requirements and specification that need to be met. The bare metal driver is there a bare skeleton but does not check if you are within the requirements of the microcontroller. Please refer to the datasheet to clock requirements.

## Tools

Requirements:
- `stm32cubeIDE` - to test on stm32f407 discovery
- `arm-none-eabi-g++` - to compile source files
- `make` - automate build process

Hardware:
- STM32F407 Discovery Board
- Micro-USB-B Cable
