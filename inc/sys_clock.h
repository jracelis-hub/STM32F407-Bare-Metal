#ifndef SYS_CLOCK_H
#define SYS_CLOCK_H

#include <cstdint>

/** Max Frequency:
  * SYSClk            
  * AHB (HCLK) = SYSCLK / Prescaler
  * SysTick = HCLK or HCLK/8
  * APB1 (P1CLK) = HCLK / Prescaler
  * APB1 * Prescaler = Timer
  * APB2 (P2CLK) = HCLK / Prescaler
  * APB2 * Prescaler = Timer
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
  * 
  * Specifications:
  * Max Values:
  * SYSCLOCK <= 168
  * HCLK <= 168
  * P2CLK <= 84
  * 	if prescaler > 1 TimerCLK * 2
  * P1CLK <= 42
  * 	if prescaler > 1 TimerCLK * 2
  */

namespace bare_metal
{

	/* Standard frequency for STM32F407 Discovery Board */
	constexpr std::uint32_t FREQUENCY_HSI          = (16000000);       /* 16MHz 16,000,000 Hz */
	constexpr std::uint32_t FREQUENCY_HSE          = (8000000);        /* 8MHz 8,000,000 Hz */

	/* Configuration for SysClock Configurations */
	constexpr std::uint32_t RCC_BASE_ADDRESS       = (0x40023800);                  /* RCC Base Address Register */
	constexpr std::uint32_t RCC_CR                 = (RCC_BASE_ADDRESS + 0x00);      /* (CR) Clock Control Register */
	constexpr std::uint32_t RCC_PLLCFGR            = (RCC_BASE_ADDRESS + 0x04);     /* (PLLCFGR) PLL Configuration Register */
	constexpr std::uint32_t RCC_CFGR               = (RCC_BASE_ADDRESS + 0x08);     /* (CFGR) Clock Configuration Register */
	constexpr std::uint32_t RCC_CIR                = (RCC_BASE_ADDRESS + 0x0C);     /* (CIR) Clock Interrupt Register */

	/* To Enable Clock For Peripherals on AHB Bus */
	constexpr std::uint32_t RCC_AHB1ENR            = (RCC_BASE_ADDRESS + 0x30);     /* (RCC_AHB1ENR) Clock Enable AHB1 */
	constexpr std::uint32_t RCC_AHB2ENR            = (RCC_BASE_ADDRESS + 0x34);     /* (RCC_AHB2ENR) Clock Enable AHB2 */
	constexpr std::uint32_t RCC_AHB3ENR            = (RCC_BASE_ADDRESS + 0x38);     /* (RCC_AHB3ENR) Clock Enable AHB3 */

	/* To Enable Clock For Peripherals on APB Bus */
	constexpr std::uint32_t RCC_APB1ENR            = (RCC_BASE_ADDRESS + 0x40);     /* (RCC_APB1ENR) Clock Enable APB1 */
	constexpr std::uint32_t RCC_APB2ENR            = (RCC_BASE_ADDRESS + 0x44);     /* (RCC_APB2ENR) Clock Enable APB2 */

	/* AHB Prescaler SysCLK / Prescaler = HCLK */
	enum class Prescaler_AHB : std::uint32_t
	{
		PRESCALER_AHB_DIV1        = (0x0),
		PRESCALER_AHB_DIV2        = (0x8),
		PRESCALER_AHB_DIV4        = (0x9),
		PRESCALER_AHB_DIV8        = (0xA),
		PRESCALER_AHB_DIV16       = (0xB),
		PRESCALER_AHB_DIV64       = (0xC),
		PRESCALER_AHB_DIV128      = (0xD),
		PRESCALER_AHB_DIV256      = (0xE),
		PRESCALER_AHB_DIV512      = (0xF)
	};

	/* APB1 Prescaler HCLK / Prescaler = P1CLK */
	enum class Prescaler_APB1 : std::uint32_t
	{
		PRESCALER_APB1_DIV1       = (0x0),
		PRESCALER_APB1_DIV2       = (0x4),
		PRESCALER_APB1_DIV4       = (0x5),
		PRESCALER_APB1_DIV8       = (0x6),
		PRESCALER_APB1_DIV16      = (0x7)
	};

	/* APB2 Prescaler HCLK / Prescaler = P2CLK */
	enum class Prescaler_APB2 : std::uint32_t
	{
		PRESCALER_APB2_DIV1       = (0x0),
		PRESCALER_APB2_DIV2       = (0x4),
		PRESCALER_APB2_DIV4       = (0x5),
		PRESCALER_APB2_DIV8       = (0x6),
		PRESCALER_APB2_DIV16      = (0x7)
	};

	/* Oscillator Type: 
	 * HSI = Internal MCU RC Oscillator 
	 * HSE = External MCU Crystall Oscillator   */
	enum class Sys_Oscillator_Type : std::uint8_t
	{
		OSC_TYPE_HSI         = (0x1),
		OSC_TYPE_HSE         = (0x2)
	};

	/* Frequency in MHz */
	struct Frequency_Clock_Type
	{
		std::uint32_t frequency_sysclk; /* Refered as SYSCLK */
		std::uint32_t frequency_hclk;    /* Refered as HCLK */
		std::uint32_t frequency_p1clk;   /* Refered as P1CLK */
		std::uint32_t frequency_p2clk;   /* Refered as P2CLK */
	};

	/* PLL Prescalers 
	 * Input = HSI or HSE
	 * Vco = Input / PLLM 
	 * Vcof = Vco * PLLN 
	 * PLLCLK = Vcof / PLLP */
	struct Prescaler_PLL_Type
	{
		std::uint32_t prescaler_pllm;
		std::uint32_t prescaler_plln;
		std::uint32_t prescaler_pllp;
	};

	/* Sys_Clock SYSCLK 
	 * Input = HSI or HSE */
	class Sys_Clock
	{
		public:
			Sys_Clock();
			Sys_Clock(Sys_Oscillator_Type osc_type);

			/* Gets type of Oscillator Type HSI, HSE */
			Sys_Oscillator_Type get_oscillator_type() const;

			/* To get the frequency of all or specific clock */
			Frequency_Clock_Type get_frequency() const;
			std::uint32_t get_sysclk_frequency() const;
			std::uint32_t get_hclk_frequency() const;
			std::uint32_t get_p1clk_frequency() const;
			std::uint32_t get_p2clk_frequency() const;

			/* Use to select HSE for system clock */
			void sysclk_select_hse();

			/* Use to configure clock frequency for specific clock peripherals */
			void configure_prescaler_ahb(const Prescaler_AHB prescaler_ahb);
			void configure_prescaler_apb1(const Prescaler_APB1 prescaler_apb1);
			void configure_prescaler_apb2(const Prescaler_APB2 prescaler_apb2);

			/* Alternate way to configure prescalers using operator overload */
			Sys_Clock& operator /=(const Prescaler_AHB prescaler_ahb);
			Sys_Clock& operator /=(const Prescaler_APB1 prescaler_apb1);
			Sys_Clock& operator /=(const Prescaler_APB2 prescaler_apb2);

		private:
			void frequency_default_hsi();
			void frequency_default_hse();
			void frequency_update_hclk(const Prescaler_AHB prescaler_ahb);
			void frequency_update_p1clk(const Prescaler_APB1 prescaler_apb1);
			void frequency_update_p2clk(const Prescaler_APB2 prescaler_apb2);

		protected:
			Sys_Oscillator_Type oscillator_type;
			Frequency_Clock_Type frequency_clock;
	};

	/* PLL Engine that inherits input from Sys_Clock 
	 * PLL Engine can underclock or overclock SYSCLK with PLL scaler manipulation */
	class Sys_Clock_PLL : public Sys_Clock
	{
		public:
		/* f(VCO clock) = f(PLL clock input) × (PLLN / PLLM)
         * f(PLL general clock output) = f(VCO clock) / PLLP */
			Sys_Clock_PLL();

		private:
			void prescaler_default_pll();

		private:
			Prescaler_PLL_Type prescaler_pll;
	};
}

#endif /* SYS_CLOCK_H */
