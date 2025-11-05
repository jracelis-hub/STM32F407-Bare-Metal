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

	/* Configuration for SysClock */
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

	enum class Prescaler_PLLM : uint32_t 
	{
		PRESCALER_PLLM_DIV2              = (0x2),
		PRESCALER_PLLM_DIV3              = (0x3),
		PRESCALER_PLLM_DIV4              = (0x4),
		PRESCALER_PLLM_DIV5              = (0x5),
		PRESCALER_PLLM_DIV6              = (0x6),
		PRESCALER_PLLM_DIV7              = (0x7),
		PRESCALER_PLLM_DIV8              = (0x8),
		PRESCALER_PLLM_DIV9              = (0x9),
		PRESCALER_PLLM_DIV10             = (0xA),
		PRESCALER_PLLM_DIV11             = (0xB),
		PRESCALER_PLLM_DIV12             = (0xC),
		PRESCALER_PLLM_DIV13             = (0xD),
		PRESCALER_PLLM_DIV14             = (0xE),
		PRESCALER_PLLM_DIV15             = (0xF),
		PRESCALER_PLLM_DIV16             = (0x10),
		PRESCALER_PLLM_DIV17             = (0x11),
		PRESCALER_PLLM_DIV18             = (0x12),
		PRESCALER_PLLM_DIV19             = (0x13),
		PRESCALER_PLLM_DIV20             = (0x14),
		PRESCALER_PLLM_DIV21             = (0x15),
		PRESCALER_PLLM_DIV22             = (0x16),
		PRESCALER_PLLM_DIV23             = (0x17),
		PRESCALER_PLLM_DIV24             = (0x18),
		PRESCALER_PLLM_DIV25             = (0x19),
		PRESCALER_PLLM_DIV26             = (0x1A),
		PRESCALER_PLLM_DIV27             = (0x1B),
		PRESCALER_PLLM_DIV28             = (0x1C),
		PRESCALER_PLLM_DIV29             = (0x1D),
		PRESCALER_PLLM_DIV30             = (0x1E),
		PRESCALER_PLLM_DIV31             = (0x1F),
		PRESCALER_PLLM_DIV32             = (0x20),
		PRESCALER_PLLM_DIV33             = (0x21),
		PRESCALER_PLLM_DIV34             = (0x22),
		PRESCALER_PLLM_DIV35             = (0x23),
		PRESCALER_PLLM_DIV36             = (0x24),
		PRESCALER_PLLM_DIV37             = (0x25),
		PRESCALER_PLLM_DIV38             = (0x26),
		PRESCALER_PLLM_DIV39             = (0x27),
		PRESCALER_PLLM_DIV40             = (0x28),
		PRESCALER_PLLM_DIV41             = (0x29),
		PRESCALER_PLLM_DIV42             = (0x2A),
		PRESCALER_PLLM_DIV43             = (0x2B),
		PRESCALER_PLLM_DIV44             = (0x2C),
		PRESCALER_PLLM_DIV45             = (0x2D),
		PRESCALER_PLLM_DIV46             = (0x2E),
		PRESCALER_PLLM_DIV47             = (0x2F),
		PRESCALER_PLLM_DIV48             = (0x30),
		PRESCALER_PLLM_DIV49             = (0x31),
		PRESCALER_PLLM_DIV50             = (0x32),
		PRESCALER_PLLM_DIV51             = (0x33),
		PRESCALER_PLLM_DIV52             = (0x34),
		PRESCALER_PLLM_DIV53             = (0x35),
		PRESCALER_PLLM_DIV54             = (0x36),
		PRESCALER_PLLM_DIV55             = (0x37),
		PRESCALER_PLLM_DIV56             = (0x38),
		PRESCALER_PLLM_DIV57             = (0x39),
		PRESCALER_PLLM_DIV58             = (0x3A),
		PRESCALER_PLLM_DIV59             = (0x3B),
		PRESCALER_PLLM_DIV60             = (0x3C),
		PRESCALER_PLLM_DIV61             = (0x3D),
		PRESCALER_PLLM_DIV62             = (0x3E),
		PRESCALER_PLLM_DIV63             = (0x3F)
	};

	enum class Prescaler_PLLN : uint32_t
	{
		PRESCALER_PLLN_MUL50             = (0x32),
		PRESCALER_PLLN_MUL51             = (0x33),
		PRESCALER_PLLN_MUL52             = (0x34),
		PRESCALER_PLLN_MUL53             = (0x35),
		PRESCALER_PLLN_MUL54             = (0x36),
		PRESCALER_PLLN_MUL55             = (0x37),
		PRESCALER_PLLN_MUL56             = (0x38),
		PRESCALER_PLLN_MUL57             = (0x39),
		PRESCALER_PLLN_MUL58             = (0x3A),
		PRESCALER_PLLN_MUL59             = (0x3B),
		PRESCALER_PLLN_MUL60             = (0x3C),
		PRESCALER_PLLN_MUL61             = (0x3D),
		PRESCALER_PLLN_MUL62             = (0x3E),
		PRESCALER_PLLN_MUL63             = (0x3F),
		PRESCALER_PLLN_MUL64             = (0x40),
		PRESCALER_PLLN_MUL65             = (0x41),
		PRESCALER_PLLN_MUL66             = (0x42),
		PRESCALER_PLLN_MUL67             = (0x43),
		PRESCALER_PLLN_MUL68             = (0x44),
		PRESCALER_PLLN_MUL69             = (0x45),
		PRESCALER_PLLN_MUL70             = (0x46),
		PRESCALER_PLLN_MUL71             = (0x47),
		PRESCALER_PLLN_MUL72             = (0x48),
		PRESCALER_PLLN_MUL73             = (0x49),
		PRESCALER_PLLN_MUL74             = (0x4A),
		PRESCALER_PLLN_MUL75             = (0x4B),
		PRESCALER_PLLN_MUL76             = (0x4C),
		PRESCALER_PLLN_MUL77             = (0x4D),
		PRESCALER_PLLN_MUL78             = (0x4E),
		PRESCALER_PLLN_MUL79             = (0x4F),
		PRESCALER_PLLN_MUL80             = (0x50),
		PRESCALER_PLLN_MUL81             = (0x51),
		PRESCALER_PLLN_MUL82             = (0x52),
		PRESCALER_PLLN_MUL83             = (0x53),
		PRESCALER_PLLN_MUL84             = (0x54),
		PRESCALER_PLLN_MUL85             = (0x55),
		PRESCALER_PLLN_MUL86             = (0x56),
		PRESCALER_PLLN_MUL87             = (0x57),
		PRESCALER_PLLN_MUL88             = (0x58),
		PRESCALER_PLLN_MUL89             = (0x59),
		PRESCALER_PLLN_MUL90             = (0x5A),
		PRESCALER_PLLN_MUL91             = (0x5B),
		PRESCALER_PLLN_MUL92             = (0x5C),
		PRESCALER_PLLN_MUL93             = (0x5D),
		PRESCALER_PLLN_MUL94             = (0x5E),
		PRESCALER_PLLN_MUL95             = (0x5F),
		PRESCALER_PLLN_MUL96             = (0x60),
		PRESCALER_PLLN_MUL97             = (0x61),
		PRESCALER_PLLN_MUL98             = (0x62),
		PRESCALER_PLLN_MUL99             = (0x63),
		PRESCALER_PLLN_MUL100            = (0x64),
		PRESCALER_PLLN_MUL101            = (0x65),
		PRESCALER_PLLN_MUL102            = (0x66),
		PRESCALER_PLLN_MUL103            = (0x67),
		PRESCALER_PLLN_MUL104            = (0x68),
		PRESCALER_PLLN_MUL105            = (0x69),
		PRESCALER_PLLN_MUL106            = (0x6A),
		PRESCALER_PLLN_MUL107            = (0x6B),
		PRESCALER_PLLN_MUL108            = (0x6C),
		PRESCALER_PLLN_MUL109            = (0x6D),
		PRESCALER_PLLN_MUL110            = (0x6E),
		PRESCALER_PLLN_MUL111            = (0x6F),
		PRESCALER_PLLN_MUL112            = (0x70),
		PRESCALER_PLLN_MUL113            = (0x71),
		PRESCALER_PLLN_MUL114            = (0x72),
		PRESCALER_PLLN_MUL115            = (0x73),
		PRESCALER_PLLN_MUL116            = (0x74),
		PRESCALER_PLLN_MUL117            = (0x75),
		PRESCALER_PLLN_MUL118            = (0x76),
		PRESCALER_PLLN_MUL119            = (0x77),
		PRESCALER_PLLN_MUL120            = (0x78),
		PRESCALER_PLLN_MUL121            = (0x79),
		PRESCALER_PLLN_MUL122            = (0x7A),
		PRESCALER_PLLN_MUL123            = (0x7B),
		PRESCALER_PLLN_MUL124            = (0x7C),
		PRESCALER_PLLN_MUL125            = (0x7D),
		PRESCALER_PLLN_MUL126            = (0x7E),
		PRESCALER_PLLN_MUL127            = (0x7F),
		PRESCALER_PLLN_MUL128            = (0x80),
		PRESCALER_PLLN_MUL129            = (0x81),
		PRESCALER_PLLN_MUL130            = (0x82),
		PRESCALER_PLLN_MUL131            = (0x83),
		PRESCALER_PLLN_MUL132            = (0x84),
		PRESCALER_PLLN_MUL133            = (0x85),
		PRESCALER_PLLN_MUL134            = (0x86),
		PRESCALER_PLLN_MUL135            = (0x87),
		PRESCALER_PLLN_MUL136            = (0x88),
		PRESCALER_PLLN_MUL137            = (0x89),
		PRESCALER_PLLN_MUL138            = (0x8A),
		PRESCALER_PLLN_MUL139            = (0x8B),
		PRESCALER_PLLN_MUL140            = (0x8C),
		PRESCALER_PLLN_MUL141            = (0x8D),
		PRESCALER_PLLN_MUL142            = (0x8E),
		PRESCALER_PLLN_MUL143            = (0x8F),
		PRESCALER_PLLN_MUL144            = (0x90),
		PRESCALER_PLLN_MUL145            = (0x91),
		PRESCALER_PLLN_MUL146            = (0x92),
		PRESCALER_PLLN_MUL147            = (0x93),
		PRESCALER_PLLN_MUL148            = (0x94),
		PRESCALER_PLLN_MUL149            = (0x95),
		PRESCALER_PLLN_MUL150            = (0x96),
		PRESCALER_PLLN_MUL151            = (0x97),
		PRESCALER_PLLN_MUL152            = (0x98),
		PRESCALER_PLLN_MUL153            = (0x99),
		PRESCALER_PLLN_MUL154            = (0x9A),
		PRESCALER_PLLN_MUL155            = (0x9B),
		PRESCALER_PLLN_MUL156            = (0x9C),
		PRESCALER_PLLN_MUL157            = (0x9D),
		PRESCALER_PLLN_MUL158            = (0x9E),
		PRESCALER_PLLN_MUL159            = (0x9F),
		PRESCALER_PLLN_MUL160            = (0xA0),
		PRESCALER_PLLN_MUL161            = (0xA1),
		PRESCALER_PLLN_MUL162            = (0xA2),
		PRESCALER_PLLN_MUL163            = (0xA3),
		PRESCALER_PLLN_MUL164            = (0xA4),
		PRESCALER_PLLN_MUL165            = (0xA5),
		PRESCALER_PLLN_MUL166            = (0xA6),
		PRESCALER_PLLN_MUL167            = (0xA7),
		PRESCALER_PLLN_MUL168            = (0xA8),
		PRESCALER_PLLN_MUL169            = (0xA9),
		PRESCALER_PLLN_MUL170            = (0xAA),
		PRESCALER_PLLN_MUL171            = (0xAB),
		PRESCALER_PLLN_MUL172            = (0xAC),
		PRESCALER_PLLN_MUL173            = (0xAD),
		PRESCALER_PLLN_MUL174            = (0xAE),
		PRESCALER_PLLN_MUL175            = (0xAF),
		PRESCALER_PLLN_MUL176            = (0xB0),
		PRESCALER_PLLN_MUL177            = (0xB1),
		PRESCALER_PLLN_MUL178            = (0xB2),
		PRESCALER_PLLN_MUL179            = (0xB3),
		PRESCALER_PLLN_MUL180            = (0xB4),
		PRESCALER_PLLN_MUL181            = (0xB5),
		PRESCALER_PLLN_MUL182            = (0xB6),
		PRESCALER_PLLN_MUL183            = (0xB7),
		PRESCALER_PLLN_MUL184            = (0xB8),
		PRESCALER_PLLN_MUL185            = (0xB9),
		PRESCALER_PLLN_MUL186            = (0xBA),
		PRESCALER_PLLN_MUL187            = (0xBB),
		PRESCALER_PLLN_MUL188            = (0xBC),
		PRESCALER_PLLN_MUL189            = (0xBD),
		PRESCALER_PLLN_MUL190            = (0xBE),
		PRESCALER_PLLN_MUL191            = (0xBF),
		PRESCALER_PLLN_MUL192            = (0xC0),
		PRESCALER_PLLN_MUL193            = (0xC1),
		PRESCALER_PLLN_MUL194            = (0xC2),
		PRESCALER_PLLN_MUL195            = (0xC3),
		PRESCALER_PLLN_MUL196            = (0xC4),
		PRESCALER_PLLN_MUL197            = (0xC5),
		PRESCALER_PLLN_MUL198            = (0xC6),
		PRESCALER_PLLN_MUL199            = (0xC7),
		PRESCALER_PLLN_MUL200            = (0xC8),
		PRESCALER_PLLN_MUL201            = (0xC9),



		PRESCALER_PLLN_MUL392            = (0x188),
		PRESCALER_PLLN_MUL393            = (0x189),
		PRESCALER_PLLN_MUL394            = (0x18A),
		PRESCALER_PLLN_MUL395            = (0x18B),
		PRESCALER_PLLN_MUL396            = (0x18C),
		PRESCALER_PLLN_MUL397            = (0x18D),
		PRESCALER_PLLN_MUL398            = (0x18E),
		PRESCALER_PLLN_MUL399            = (0x18F),
		PRESCALER_PLLN_MUL400            = (0x190),
		PRESCALER_PLLN_MUL401            = (0x191),
		PRESCALER_PLLN_MUL402            = (0x192),
		PRESCALER_PLLN_MUL403            = (0x193),
		PRESCALER_PLLN_MUL404            = (0x194),
		PRESCALER_PLLN_MUL405            = (0x195),
		PRESCALER_PLLN_MUL406            = (0x196),
		PRESCALER_PLLN_MUL407            = (0x197),
		PRESCALER_PLLN_MUL408            = (0x198),
		PRESCALER_PLLN_MUL409            = (0x199),
		PRESCALER_PLLN_MUL410            = (0x19A),
		PRESCALER_PLLN_MUL411            = (0x19B),
		PRESCALER_PLLN_MUL412            = (0x19C),
		PRESCALER_PLLN_MUL413            = (0x19D),
		PRESCALER_PLLN_MUL414            = (0x19E),
		PRESCALER_PLLN_MUL415            = (0x19F),
		PRESCALER_PLLN_MUL416            = (0x1A0),
		PRESCALER_PLLN_MUL417            = (0x1A1),
		PRESCALER_PLLN_MUL418            = (0x1A2),
		PRESCALER_PLLN_MUL419            = (0x1A3),
		PRESCALER_PLLN_MUL420            = (0x1A4),
		PRESCALER_PLLN_MUL421            = (0x1A5),
		PRESCALER_PLLN_MUL422            = (0x1A6),
		PRESCALER_PLLN_MUL423            = (0x1A7),
		PRESCALER_PLLN_MUL424            = (0x1A8),
		PRESCALER_PLLN_MUL425            = (0x1A9),
		PRESCALER_PLLN_MUL426            = (0x1AA),
		PRESCALER_PLLN_MUL427            = (0x1AB),
		PRESCALER_PLLN_MUL428            = (0x1AC),
		PRESCALER_PLLN_MUL429            = (0x1AD),
		PRESCALER_PLLN_MUL430            = (0x1AE),
		PRESCALER_PLLN_MUL431            = (0x1AF),
		PRESCALER_PLLN_MUL432            = (0x1B0)
	};

	enum class Prescaler_PLLP : uint32_t
	{
		PRESCALER_PLLP_DIV2              = (0x0),
		PRESCALER_PLLP_DIV4              = (0x1),
		PRESCALER_PLLP_DIV6              = (0x2),
		PRESCALER_PLLP_DIV8              = (0x3)
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
			Sys_Clock_PLL(const Sys_Clock& clock_input);

			/* */
			void configure_prescaler_pllm(const Prescaler_PLLM prescaler_pllm);
			void configure_prescaler_plln(const Prescaler_PLLN prescaler_plln);
			void configure_prescaler_pllp(const Prescaler_PLLP prescaler_pllp);

			/* */
			Sys_Clock_PLL& operator /= (const Prescaler_PLLM prescaler_pllp);
			Sys_Clock_PLL& operator /= (const Prescaler_PLLP prescaler_pllp);
			Sys_Clock_PLL& operator *= (const Prescaler_PLLN prescaler_plln);
	};
}

#endif /* SYS_CLOCK_H */
