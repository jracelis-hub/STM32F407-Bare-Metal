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
	typedef struct 
	{
		volatile std::uint32_t rcc_cr;                 /* 4002 3800 + 0x00 */
		volatile std::uint32_t rcc_pllcfgr;            /* 4002 3800 + 0x04 */
		volatile std::uint32_t rcc_cfgr;               /* 4002 3800 + 0x08 */
		volatile std::uint32_t rcc_cir;                /* 4002 3800 + 0x0C */
		volatile std::uint32_t rcc_ahb1rstr;           /* 4002 3800 + 0x10 */
		volatile std::uint32_t rcc_ahb2rstr;           /* 4002 3800 + 0x14 */
		volatile std::uint32_t rcc_ahb3rstr;           /* 4002 3800 + 0x18 */
		volatile std::uint32_t reserve_1;              /* 4002 3800 + 0x1C */
		volatile std::uint32_t rcc_apb1rstr;           /* 4002 3800 + 0x20 */
		volatile std::uint32_t rcc_apb2rstr;           /* 4002 3800 + 0x24 */
		volatile std::uint32_t rcc_reserve_2[2];       /* 4002 3800 + 0x28 - 0x2C */
		volatile std::uint32_t rcc_ahb1enr;            /* 4002 3800 + 0x30 */
		volatile std::uint32_t rcc_ahb2enr;            /* 4002 3800 + 0x34 */
		volatile std::uint32_t rcc_ahb3enr;            /* 4002 3800 + 0x38 */
		volatile std::uint32_t rcc_reserve_3;          /* 4002 3800 + 0x3C */
		volatile std::uint32_t rcc_apb1enr;            /* 4002 3800 + 0x40 */
		volatile std::uint32_t rcc_apb2enr;            /* 4002 3800 + 0x44 */
		volatile std::uint32_t rcc_reserve_4[2];       /* 4002 3800 + 0x48 - 0x4C */
		volatile std::uint32_t rcc_ahb1lpenr;          /* 4002 3800 + 0x50 */
		volatile std::uint32_t rcc_ahb2lpenr;          /* 4002 3800 + 0x54 */
		volatile std::uint32_t rcc_ahb3lpenr;          /* 4002 3800 + 0x58 */
		volatile std::uint32_t rcc_reserve_5;          /* 4002 3800 + 0x5C */
		volatile std::uint32_t rcc_apb1lpenr;          /* 4002 3800 + 0x60 */
		volatile std::uint32_t rcc_apb2lpenr;          /* 4002 3800 + 0x64 */
		volatile std::uint32_t rcc_reserve_6[2];       /* 4002 3800 + 0x68 - 0x6C */
		volatile std::uint32_t rcc_bdcr;               /* 4002 3800 + 0x70 */
		volatile std::uint32_t rcc_csr;                /* 4002 3800 + 0x74 */
		volatile std::uint32_t rcc_reserve_7[2];       /* 4002 3800 + 0x78 - 0x7C */
		volatile std::uint32_t rcc_sscgr;              /* 4002 3800 + 0x80 */
		volatile std::uint32_t rcc_plli2s;             /* 4002 3800 + 0x84 */
		volatile std::uint32_t rcc_pllsaicfgr;         /* 4002 3800 + 0x88 */
		volatile std::uint32_t rcc_dckcfgr;            /* 4002 3800 + 0x8C */
	} RCC_Register_Handle;

	typedef struct
	{
		volatile std::uint32_t flash_acr;              /* 0x4002 3C00 + 0x00 */
		volatile std::uint32_t flash_keyr;             /* 0x4002 3C00 + 0x04 */
		volatile std::uint32_t flash_optkeyr;          /* 0x4002 3C00 + 0x08 */
		volatile std::uint32_t flash_sr;               /* 0x4002 3C00 + 0x0C */
		volatile std::uint32_t flash_cr;               /* 0x4002 3C00 + 0x10 */
		volatile std::uint32_t flash_optcr;            /* 0x4002 3C00 + 0x14 */
		volatile std::uint32_t flash_reserve[2];       /* 0x4002 3C00 + 0x18 - 0xC */
	} Flash_Register_Handle;

	/* Standard frequency for STM32F407 Discovery Board */
	constexpr std::uint32_t FREQUENCY_HSI          = (16000000);       /* 16MHz 16,000,000 Hz */
	constexpr std::uint32_t FREQUENCY_HSE          = (8000000);        /* 8MHz 8,000,000 Hz */

	/* Configuration for SysClock */
	constexpr std::uint32_t RCC_BASE_ADDRESS       = (0x40023800);                  /* RCC Base Address Register */
	//constexpr std::uint32_t RCC_CR                 = (RCC_BASE_ADDRESS + 0x00);     /* (CR) Clock Control Register */
	//constexpr std::uint32_t RCC_PLLCFGR            = (RCC_BASE_ADDRESS + 0x04);     /* (PLLCFGR) PLL Configuration Register */
	//constexpr std::uint32_t RCC_CFGR               = (RCC_BASE_ADDRESS + 0x08);     /* (CFGR) Clock Configuration Register */
	//constexpr std::uint32_t RCC_CIR                = (RCC_BASE_ADDRESS + 0x0C);     /* (CIR) Clock Interrupt Register */

	/* To Enable Clock For Peripherals on AHB Bus */
	//constexpr std::uint32_t RCC_AHB1ENR            = (RCC_BASE_ADDRESS + 0x30);     /* (RCC_AHB1ENR) Clock Enable AHB1 */
	//constexpr std::uint32_t RCC_AHB2ENR            = (RCC_BASE_ADDRESS + 0x34);     /* (RCC_AHB2ENR) Clock Enable AHB2 */
	//constexpr std::uint32_t RCC_AHB3ENR            = (RCC_BASE_ADDRESS + 0x38);     /* (RCC_AHB3ENR) Clock Enable AHB3 */

	/* To Enable Clock For Peripherals on APB Bus */
	//constexpr std::uint32_t RCC_APB1ENR            = (RCC_BASE_ADDRESS + 0x40);     /* (RCC_APB1ENR) Clock Enable APB1 */
	//constexpr std::uint32_t RCC_APB2ENR            = (RCC_BASE_ADDRESS + 0x44);     /* (RCC_APB2ENR) Clock Enable APB2 */

	/* Configuration for Flash Access Control Register */
	constexpr std::uint32_t FLASH_BASE_ADDRESS     = (0x40023C00);                  /* Flash Access Control Register */

	inline RCC_Register_Handle *RCC = reinterpret_cast<RCC_Register_Handle *>(RCC_BASE_ADDRESS);
	inline Flash_Register_Handle *FLASH = reinterpret_cast<Flash_Register_Handle *>(FLASH_BASE_ADDRESS);

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
		OSC_TYPE_HSI         = (0x0),
		OSC_TYPE_HSE         = (0x1),
		OSC_TYPE_PLL         = (0x2)
	};

	/* Frequency in MHz */
	struct Frequency_Clock_Type
	{
		std::uint32_t frequency_sysclk; /* Refered as SYSCLK */
		std::uint32_t frequency_hclk;    /* Refered as HCLK */
		std::uint32_t frequency_p1clk;   /* Refered as P1CLK */
		std::uint32_t frequency_p2clk;   /* Refered as P2CLK */
	};

	enum class Prescaler_PLLM : std::uint32_t 
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

	enum class Prescaler_PLLN : std::uint32_t
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
		PRESCALER_PLLN_MUL202            = (0xCA),
		PRESCALER_PLLN_MUL203            = (0xCB),
		PRESCALER_PLLN_MUL204            = (0xCC),
		PRESCALER_PLLN_MUL205            = (0xCD),
		PRESCALER_PLLN_MUL206            = (0xCE),
		PRESCALER_PLLN_MUL207            = (0xCF),
		PRESCALER_PLLN_MUL208            = (0xD0),
		PRESCALER_PLLN_MUL209            = (0xD1),
		PRESCALER_PLLN_MUL210            = (0xD2),
		PRESCALER_PLLN_MUL211            = (0xD3),
		PRESCALER_PLLN_MUL212            = (0xD4),
		PRESCALER_PLLN_MUL213            = (0xD5),
		PRESCALER_PLLN_MUL214            = (0xD6),
		PRESCALER_PLLN_MUL215            = (0xD7),
		PRESCALER_PLLN_MUL216            = (0xD8),
		PRESCALER_PLLN_MUL217            = (0xD9),
		PRESCALER_PLLN_MUL218            = (0xDA),
		PRESCALER_PLLN_MUL219            = (0xDB),
		PRESCALER_PLLN_MUL220            = (0xDC),
		PRESCALER_PLLN_MUL221            = (0xDD),
		PRESCALER_PLLN_MUL222            = (0xDE),
		PRESCALER_PLLN_MUL223            = (0xDF),
		PRESCALER_PLLN_MUL224            = (0xE0),
		PRESCALER_PLLN_MUL225            = (0xE1),
		PRESCALER_PLLN_MUL226            = (0xE2),
		PRESCALER_PLLN_MUL227            = (0xE3),
		PRESCALER_PLLN_MUL228            = (0xE4),
		PRESCALER_PLLN_MUL229            = (0xE5),
		PRESCALER_PLLN_MUL230            = (0xE6),
		PRESCALER_PLLN_MUL231            = (0xE7),
		PRESCALER_PLLN_MUL232            = (0xE8),
		PRESCALER_PLLN_MUL233            = (0xE9),
		PRESCALER_PLLN_MUL234            = (0xEA),
		PRESCALER_PLLN_MUL235            = (0xEB),
		PRESCALER_PLLN_MUL236            = (0xEC),
		PRESCALER_PLLN_MUL237            = (0xED),
		PRESCALER_PLLN_MUL238            = (0xEE),
		PRESCALER_PLLN_MUL239            = (0xEF),
		PRESCALER_PLLN_MUL240            = (0xF0),
		PRESCALER_PLLN_MUL241            = (0xF1),
		PRESCALER_PLLN_MUL242            = (0xF2),
		PRESCALER_PLLN_MUL243            = (0xF3),
		PRESCALER_PLLN_MUL244            = (0xF4),
		PRESCALER_PLLN_MUL245            = (0xF5),
		PRESCALER_PLLN_MUL246            = (0xF6),
		PRESCALER_PLLN_MUL247            = (0xF7),
		PRESCALER_PLLN_MUL248            = (0xF8),
		PRESCALER_PLLN_MUL249            = (0xF9),
		PRESCALER_PLLN_MUL250            = (0xFA),
		PRESCALER_PLLN_MUL251            = (0xFB),
		PRESCALER_PLLN_MUL252            = (0xFC),
		PRESCALER_PLLN_MUL253            = (0xFD),
		PRESCALER_PLLN_MUL254            = (0xFE),
		PRESCALER_PLLN_MUL255            = (0xFF),
		PRESCALER_PLLN_MUL256            = (0x100),
		PRESCALER_PLLN_MUL257            = (0x101),
		PRESCALER_PLLN_MUL258            = (0x102),
		PRESCALER_PLLN_MUL259            = (0x103),
		PRESCALER_PLLN_MUL260            = (0x104),
		PRESCALER_PLLN_MUL261            = (0x105),
		PRESCALER_PLLN_MUL262            = (0x106),
		PRESCALER_PLLN_MUL263            = (0x107),
		PRESCALER_PLLN_MUL264            = (0x108),
		PRESCALER_PLLN_MUL265            = (0x109),
		PRESCALER_PLLN_MUL266            = (0x10A),
		PRESCALER_PLLN_MUL267            = (0x10B),
		PRESCALER_PLLN_MUL268            = (0x10C),
		PRESCALER_PLLN_MUL269            = (0x10D),
		PRESCALER_PLLN_MUL270            = (0x10E),
		PRESCALER_PLLN_MUL271            = (0x10F),
		PRESCALER_PLLN_MUL272            = (0x110),
		PRESCALER_PLLN_MUL273            = (0x111),
		PRESCALER_PLLN_MUL274            = (0x112),
		PRESCALER_PLLN_MUL275            = (0x113),
		PRESCALER_PLLN_MUL276            = (0x114),
		PRESCALER_PLLN_MUL277            = (0x115),
		PRESCALER_PLLN_MUL278            = (0x116),
		PRESCALER_PLLN_MUL279            = (0x117),
		PRESCALER_PLLN_MUL280            = (0x118),
		PRESCALER_PLLN_MUL281            = (0x119),
		PRESCALER_PLLN_MUL282            = (0x11A),
		PRESCALER_PLLN_MUL283            = (0x11B),
		PRESCALER_PLLN_MUL284            = (0x11C),
		PRESCALER_PLLN_MUL285            = (0x11D),
		PRESCALER_PLLN_MUL286            = (0x11E),
		PRESCALER_PLLN_MUL287            = (0x11F),
		PRESCALER_PLLN_MUL288            = (0x120),
		PRESCALER_PLLN_MUL289            = (0x121),
		PRESCALER_PLLN_MUL290            = (0x122),
		PRESCALER_PLLN_MUL291            = (0x123),
		PRESCALER_PLLN_MUL292            = (0x124),
		PRESCALER_PLLN_MUL293            = (0x125),
		PRESCALER_PLLN_MUL294            = (0x126),
		PRESCALER_PLLN_MUL295            = (0x127),
		PRESCALER_PLLN_MUL296            = (0x128),
		PRESCALER_PLLN_MUL297            = (0x129),
		PRESCALER_PLLN_MUL298            = (0x12A),
		PRESCALER_PLLN_MUL299            = (0x12B),
		PRESCALER_PLLN_MUL300            = (0x12C),
		PRESCALER_PLLN_MUL301            = (0x12D),
		PRESCALER_PLLN_MUL302            = (0x12E),
		PRESCALER_PLLN_MUL303            = (0x12F),
		PRESCALER_PLLN_MUL304            = (0x130),
		PRESCALER_PLLN_MUL305            = (0x131),
		PRESCALER_PLLN_MUL306            = (0x132),
		PRESCALER_PLLN_MUL307            = (0x133),
		PRESCALER_PLLN_MUL308            = (0x134),
		PRESCALER_PLLN_MUL309            = (0x135),
		PRESCALER_PLLN_MUL310            = (0x136),
		PRESCALER_PLLN_MUL311            = (0x137),
		PRESCALER_PLLN_MUL312            = (0x138),
		PRESCALER_PLLN_MUL313            = (0x139),
		PRESCALER_PLLN_MUL314            = (0x13A),
		PRESCALER_PLLN_MUL315            = (0x13B),
		PRESCALER_PLLN_MUL316            = (0x13C),
		PRESCALER_PLLN_MUL317            = (0x13D),
		PRESCALER_PLLN_MUL318            = (0x13E),
		PRESCALER_PLLN_MUL319            = (0x13F),
		PRESCALER_PLLN_MUL320            = (0x140),
		PRESCALER_PLLN_MUL321            = (0x141),
		PRESCALER_PLLN_MUL322            = (0x142),
		PRESCALER_PLLN_MUL323            = (0x143),
		PRESCALER_PLLN_MUL324            = (0x144),
		PRESCALER_PLLN_MUL325            = (0x145),
		PRESCALER_PLLN_MUL326            = (0x146),
		PRESCALER_PLLN_MUL327            = (0x147),
		PRESCALER_PLLN_MUL328            = (0x148),
		PRESCALER_PLLN_MUL329            = (0x149),
		PRESCALER_PLLN_MUL330            = (0x14A),
		PRESCALER_PLLN_MUL331            = (0x14B),
		PRESCALER_PLLN_MUL332            = (0x14C),
		PRESCALER_PLLN_MUL333            = (0x14D),
		PRESCALER_PLLN_MUL334            = (0x14E),
		PRESCALER_PLLN_MUL335            = (0x14F),
		PRESCALER_PLLN_MUL336            = (0x150),
		PRESCALER_PLLN_MUL337            = (0x151),
		PRESCALER_PLLN_MUL338            = (0x152),
		PRESCALER_PLLN_MUL339            = (0x153),
		PRESCALER_PLLN_MUL340            = (0x154),
		PRESCALER_PLLN_MUL341            = (0x155),
		PRESCALER_PLLN_MUL342            = (0x156),
		PRESCALER_PLLN_MUL343            = (0x157),
		PRESCALER_PLLN_MUL344            = (0x158),
		PRESCALER_PLLN_MUL345            = (0x159),
		PRESCALER_PLLN_MUL346            = (0x15A),
		PRESCALER_PLLN_MUL347            = (0x15B),
		PRESCALER_PLLN_MUL348            = (0x15C),
		PRESCALER_PLLN_MUL349            = (0x15D),
		PRESCALER_PLLN_MUL350            = (0x15E),
		PRESCALER_PLLN_MUL351            = (0x15F),
		PRESCALER_PLLN_MUL352            = (0x160),
		PRESCALER_PLLN_MUL353            = (0x161),
		PRESCALER_PLLN_MUL354            = (0x162),
		PRESCALER_PLLN_MUL355            = (0x163),
		PRESCALER_PLLN_MUL356            = (0x164),
		PRESCALER_PLLN_MUL357            = (0x165),
		PRESCALER_PLLN_MUL358            = (0x166),
		PRESCALER_PLLN_MUL359            = (0x167),
		PRESCALER_PLLN_MUL360            = (0x168),
		PRESCALER_PLLN_MUL361            = (0x169),
		PRESCALER_PLLN_MUL362            = (0x16A),
		PRESCALER_PLLN_MUL363            = (0x16B),
		PRESCALER_PLLN_MUL364            = (0x16C),
		PRESCALER_PLLN_MUL365            = (0x16D),
		PRESCALER_PLLN_MUL366            = (0x16E),
		PRESCALER_PLLN_MUL367            = (0x16F),
		PRESCALER_PLLN_MUL368            = (0x170),
		PRESCALER_PLLN_MUL369            = (0x171),
		PRESCALER_PLLN_MUL370            = (0x172),
		PRESCALER_PLLN_MUL371            = (0x173),
		PRESCALER_PLLN_MUL372            = (0x174),
		PRESCALER_PLLN_MUL373            = (0x175),
		PRESCALER_PLLN_MUL374            = (0x176),
		PRESCALER_PLLN_MUL375            = (0x177),
		PRESCALER_PLLN_MUL376            = (0x178),
		PRESCALER_PLLN_MUL377            = (0x179),
		PRESCALER_PLLN_MUL378            = (0x17A),
		PRESCALER_PLLN_MUL379            = (0x17B),
		PRESCALER_PLLN_MUL380            = (0x17C),
		PRESCALER_PLLN_MUL381            = (0x17D),
		PRESCALER_PLLN_MUL382            = (0x17E),
		PRESCALER_PLLN_MUL383            = (0x17F),
		PRESCALER_PLLN_MUL384            = (0x180),
		PRESCALER_PLLN_MUL385            = (0x181),
		PRESCALER_PLLN_MUL386            = (0x182),
		PRESCALER_PLLN_MUL387            = (0x183),
		PRESCALER_PLLN_MUL388            = (0x184),
		PRESCALER_PLLN_MUL389            = (0x185),
		PRESCALER_PLLN_MUL390            = (0x186),
		PRESCALER_PLLN_MUL391            = (0x187),
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

	enum class Prescaler_PLLP : std::uint32_t
	{
		PRESCALER_PLLP_DIV2              = (0x0),
		PRESCALER_PLLP_DIV4              = (0x1),
		PRESCALER_PLLP_DIV6              = (0x2),
		PRESCALER_PLLP_DIV8              = (0x3)
	};

	enum class Flash_Latency : std::uint32_t
	{
		FLASH_LATENCY_WS0                = (0x0),
		FLASH_LATENCY_WS1                = (0x1),
		FLASH_LATENCY_WS2                = (0x2),
		FLASH_LATENCY_WS3                = (0x3),
		FLASH_LATENCY_WS4                = (0x4),
		FLASH_LATENCY_WS5                = (0x5),
		FLASH_LATENCY_WS6                = (0x6),
		FLASH_LATENCY_WS7                = (0x7)
	};

	enum class Frequency_Sys_Clock_Status : std::uint8_t
	{
		STATUS_SYS_CLOCK_OK              = (0x0),
		STATUS_SYS_CLOCK_NOK             = (0x1)
	};

	class Sys_Clock
	{
		public:
			Sys_Clock();
			Sys_Clock(Sys_Oscillator_Type osc_type);

			/* Gets type of Oscillator Type HSI, HSE, PLL */
			Sys_Oscillator_Type get_oscillator_type() const;

			/* To get the frequency of all or specific clock */
			Frequency_Clock_Type get_frequency() const;
			std::uint32_t get_sysclk_frequency() const;
			std::uint32_t get_hclk_frequency() const;
			std::uint32_t get_p1clk_frequency() const;
			std::uint32_t get_p2clk_frequency() const;

			/* Use to enable pll clock */
			void sysclk_enable_pll();

			/* Use to disable hsi system clk */
			void sysclk_disable_hsi();

			/* Use to select HSE for system clock */
			void sysclk_select_hse();
			void sysclk_select_pll();

			/* Use to choose which source clock input to use */
			void configure_source_pll();

			/* Use to configure the flash latency according to reference manual specifications */
			Frequency_Sys_Clock_Status configure_flash_latency();

			/* Use to configure clock frequency for specific clock peripherals */
			void configure_prescaler_ahb(const Prescaler_AHB prescaler_ahb);
			void configure_prescaler_apb1(const Prescaler_APB1 prescaler_apb1);
			void configure_prescaler_apb2(const Prescaler_APB2 prescaler_apb2);

			/* Use to configure prescalers for PLL Engine for the desired PLLCLK output */
			void configure_prescaler_pllm(const Prescaler_PLLM prescaler_pllm);
			void configure_prescaler_plln(const Prescaler_PLLN prescaler_plln);
			void configure_prescaler_pllp(const Prescaler_PLLP prescaler_pllp);

			/* Alternate way to configure prescalers using operator overload */
			Sys_Clock& operator /=(const Prescaler_AHB prescaler_ahb);
			Sys_Clock& operator /=(const Prescaler_APB1 prescaler_apb1);
			Sys_Clock& operator /=(const Prescaler_APB2 prescaler_apb2);

			/* Alternate way to configure prescaleres usiong opearator overload */
			Sys_Clock& operator /= (const Prescaler_PLLM prescaler_pllp);
			Sys_Clock& operator /= (const Prescaler_PLLP prescaler_pllp);
			Sys_Clock& operator *= (const Prescaler_PLLN prescaler_plln);

		private:
			void frequency_default_hsi();
			void frequency_default_hse();
			void frequency_default_pll();

			void frequency_update_hclk(const Prescaler_AHB prescaler_ahb);
			void frequency_update_p1clk(const Prescaler_APB1 prescaler_apb1);
			void frequency_update_p2clk(const Prescaler_APB2 prescaler_apb2);


			void frequency_update_pllclk(const Prescaler_PLLM prescaler_pllm);
			void frequency_update_pllclk(const Prescaler_PLLP prescaler_pllp);
			void frequency_update_pllclk(const Prescaler_PLLN prescaler_plln);

			Sys_Oscillator_Type oscillator_type;
			Frequency_Clock_Type frequency_clock;
	};
}

#endif /* SYS_CLOCK_H */
