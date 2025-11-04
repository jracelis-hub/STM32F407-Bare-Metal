# STM32F407 Discovery Baremetal

A baremetal project written in C++ for STM32F407 Discovery board, tackling system clock manipulation.

## Tools

Requirements:
- `stm32cubeIDE` - to test on stm32f407 discovery
- `arm-none-eabi-g++` - to compile source files
- `make` - automate build process

Hardware:
- STM32F407 Discovery Board
- Micro-USB-B Cable

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
|    |        |                                                      /|\                                          |----> /APB1 ---> PCLK            |
|    |        |                            PLL                        |                                           |        |                        |
|    |        |                           --------------------------- |                                           |        --*TIM--> TIMER          |
|    |        --HSI--> \\                 |                         | |                                           |                                 |
|    |                 | | ---> /PLLM --->| --> VCO --------> /PLLP |--                                           -----> /APB2 ---> PCLK            |
|    -----------HSE--> //                 | /|\         |           |                                                      |                        |
|                                         |  |         \|/          |                                                      --*TIM--> TIMER          |
|                                         |  -- *PLLN ---           |                                                                               |
|                                         ---------------------------                                                                               |
|                                                                                                                                                   |
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
|                                                                                                                                                   |
-----------------------------------------------------------------------------------------------------------------------------------------------------
```

**Steps To Configure Clock:**

1. Enable Sys Clock
2. Configure Sys Clock
	- a. Turn of other clock if used
3. Enable Peripheral Clock
	- AHB
	- APB
4. Configure Perihperal Clock

To Output Clock using the Microcontroller Clock Output(MCO):
1. Source Driving into MCO
	- RCC Clock Configuration Register
2. Configure specific pin for Micontroller Clock Ouput
	- Refer GPIOs for Alternative Functions (STM32F Datasheet)
	- a. Enable Clock For GPIOs

Logical Analyzer

- Connect MCO GPIO configured pin <--> Logical Analyzer Ch0
- Connect GND Logial Analyzer <--> GND Board
