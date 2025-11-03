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
-----------------------------------------------------------------------------------------------------------------------------------------------------
```
