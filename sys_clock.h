#ifndef SYS_CLOCK_H
#define SYS_CLOCK_H

#include <cstdint>

/** Max Frequency:
  * SYSClk = 168 MHz
  * AHB (HCLK)
  * SysTick = HCLK or HCLK/8
  * APB1
  * APB2
  *                                                                    Configuration
  * -----------------------------------------------------------------------------------------------------------------------------------------------------
  * |                                                                                                                                                   |
  * |   HSI -------------------------------------------------------                                                                                     |
  * |             |                                               |                                                   -----> /8 ---> Cortex SysTick     | 
  * |             |                                               |                                                   |                                 |
  * |             |                                               ---HSE------> \\     Max 168 MHz                    |----> FCLK Cortex free running   |
  * |   HSE ---------------------------------------------------------HSI------> | | ---> SysCLK ---> /AHB ---> HCLK --|          CLK                    |
  * |    |        |                                                 PLLCLK----> //                                    |                                 |
  * |    |        |                                                      /|\                                          |----> /APB1 ---> PCLK            |
  * |    |        |                            PLL                        |                                           |        |                        |
  * |    |        |                           --------------------------- |                                           |        --*TIM--> TIMER          |
  * |    |        --HSI--> \\                 |                         | |                                           |                                 |
  * |    |                 | | ---> /PLLM --->| --> VCO --------> /PLLP |--                                           -----> /APB2 ---> PCLK            |
  * |    -----------HSE--> //                 | /|\         |           |                                                      |                        |
  * |                                         |  |         \|/          |                                                      --*TIM--> TIMER          |
  * |                                         |  -- *PLLN ---           |                                                                               |
  * |                                         ---------------------------                                                                               |
  * -----------------------------------------------------------------------------------------------------------------------------------------------------
  */

namespace bare_metal
{

	/* Standard frequency for STM32F407 Discovery Board */
	constexpr std::uint32_t FREQUENCY_HSI          = (16000000);       /* 16MHz 16,000,000 Hz */
	constexpr std::uint32_t FREQUENCY_HSE          = (8000000);        /* 8MHz 8,000,000 Hz */

	constexpr std::uint32_t RCC_BASE_ADDRESS       = (0x40023800);                  /* RCC Base Address Register */
	constexpr std::uint32_t RCC_CCR                = (RCC_BASE_ADDRESS + 0x00);     /* (CCR) Clock Control Register */
	constexpr std::uint32_t RCC_PLLCFGR            = (RCC_BASE_ADDRESS + 0x04);     /* (PLLCFGR) PLL Configuration Register */
	constexpr std::uint32_t RCC_CFGR               = (RCC_BASE_ADDRESS + 0x08);     /* (CFGR) Clock Configuration Register */
	constexpr std::uint32_t RCC_CIR                = (RCC_BASE_ADDRESS + 0x0C);     /* (CIR) Clock Interrupt Register */

	enum class Sys_AHB_Prescaler : std::uint32_t
	{
		AHB_PRESCALER_DIV1        = (0x0),
		AHB_PRESCALER_DIV2        = (0x8),
		AHB_PRESCALER_DIV4        = (0x9),
		AHB_PRESCALER_DIV8        = (0xA),
		AHB_PRESCALER_DIV16       = (0xB),
		AHB_PRESCALER_DIV64       = (0xC),
		AHB_PRESCALER_DIV128      = (0xD),
		AHB_PRESCALER_DIV256      = (0xE),
		AHB_PRESCALER_DIV512      = (0xF)
	};

	enum class Sys_APB1_Prescaler : std::uint32_t
	{
		APB1_PRESCALER_DIV1       = (0x0),
		APB1_PRESCALER_DIV2       = (0x4),
		APB1_PRESCALER_DIV4       = (0x5),
		APB1_PRESCALER_DIV8       = (0x6),
		APB1_PRESCALER_DIV16      = (0x7)
	};

	enum class Sys_APB2_Prescaler : std::uint32_t
	{
		APB2_PRESCALER_DIV1       = (0x0),
		APB2_PRESCALER_DIV2       = (0x4),
		APB2_PRESCALER_DIV4       = (0x5),
		APB2_PRESCALER_DIV8       = (0x6),
		APB2_PRESCALER_DIV16      = (0x7)
	};

	enum class Sys_Oscillator_Type : std::uint32_t
	{
		OSC_TYPE_HSI         = (0x1),
		OSC_TYPE_HSE         = (0x2)
	};

	struct Clock_Frequency_Type
	{
		std::uint32_t frequency_sysclk;
		std::uint32_t frequency_ahb;
		std::uint32_t frequency_apb1;
		std::uint32_t frequency_apb2;
	};

	struct PLL_Prescaler_Type
	{
		std::uint32_t prescaler_pllm;
		std::uint32_t prescaler_plln;
		std::uint32_t prescaler_pllp;
	};

	class Sys_Clock
	{
		public:
			Sys_Clock();
			Sys_Clock(Sys_Oscillator_Type osc_type);

			std::uint32_t get_sysclk_frequency() const;
			Clock_Frequency_Type get_frequency() const;

			void configuration_hsi();
			void configuration_hse();

		private:
			void frequency_default_hsi();
			void frequency_default_hse();

		protected:
			Sys_Oscillator_Type oscillator_type;
			Clock_Frequency_Type clock_frequency;
	};

	class Sys_Clock_PLL : public Sys_Clock
	{
		public:
			Sys_Clock_PLL(const Sys_Clock& sys_clock);

		private:
			PLL_Prescaler_Type pll_prescaler;
	};
}

#endif /* SYS_CLOCK_H */
