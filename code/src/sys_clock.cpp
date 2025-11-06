/* Maintainer: Jarron Racelis
 *
 * Source: sys_clock.cpp
 ---------------------------------------------------------------------------------------------
 | Background
 ---------------------------------------------------------------------------------------------
 * Sys_Clock is a driver that assists in configuring the System Clock on
 * STM32F407 Discovery Board. 
 *
 * The system clock can take 2 inputs to drive the system clock:
 * 1. HSI High Speed Internal (RC Oscillator)
 *     - Internally inside the microcontroller
 * 2. HSE High Speed External (Crystal Oscillator)
 *     - External from the microcontroller
 *
 * With a PLL (Phase Lock Loop) engine that supports overclocking or underclocking.
 * PLL takes input from either HSI or HSE and goes through a variation of configurations
 * and output PLLClk as a driver for SYSCLK
 * 
 * The SYSCLK drives HCLK, P1CLK, P2CLK through the manipulation of prescalers
 * Once the SYSCLK is set the following can be configured:
 * HCLK = SYSCLK/AHB Prescaler
 * P1CLK = HCLK/APB1 Prescaler
 * P2CLK = HCLK/APB2 Prescaler
 * FCLK = HCLK
 * SysTick = HCLK || HCLK/8
 ---------------------------------------------------------------------------------------------
 | Specifications
 ---------------------------------------------------------------------------------------------
 * SYSCLK <= 168 MHz
 * APB1 <= 42 MHz
 * APB2 <= 84 MHz
 * if (APBx Prescaler != 1) APBxTIMER * 2
 ---------------------------------------------------------------------------------------------
 | PLL
 ---------------------------------------------------------------------------------------------
 * VCOCLK = PLLinput / (PLLM/PLLM)
 * PLLCLK = SYSCLK = VCOCLK / PLLP
 */

#include "sys_clock.h"

namespace bare_metal
{

/* Beginning Sys_Clock Source Code
 */

void Sys_Clock::frequency_default_hse()
{
	this->frequency_clock.frequency_sysclk = FREQUENCY_HSE;
	this->frequency_clock.frequency_hclk = FREQUENCY_HSE;
	this->frequency_clock.frequency_p1clk = FREQUENCY_HSE;
	this->frequency_clock.frequency_p2clk = FREQUENCY_HSE;
}

void Sys_Clock::frequency_default_hsi()
{
	this->frequency_clock.frequency_sysclk = FREQUENCY_HSI;
	this->frequency_clock.frequency_hclk = FREQUENCY_HSI;
	this->frequency_clock.frequency_p1clk = FREQUENCY_HSI;
	this->frequency_clock.frequency_p2clk = FREQUENCY_HSI;
}

void Sys_Clock::frequency_update_hclk(Prescaler_AHB prescaler_ahb)
{
	switch(prescaler_ahb)
	{
		case Prescaler_AHB::PRESCALER_AHB_DIV1:
			this->frequency_clock.frequency_hclk = (this->frequency_clock.frequency_sysclk) / 1U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV2:
			this->frequency_clock.frequency_hclk = (this->frequency_clock.frequency_sysclk) / 2U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV4:
			this->frequency_clock.frequency_hclk = (this->frequency_clock.frequency_sysclk) / 4U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV8:
			this->frequency_clock.frequency_hclk = (this->frequency_clock.frequency_sysclk) / 8U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV16:
			this->frequency_clock.frequency_hclk = (this->frequency_clock.frequency_sysclk) / 16U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV64:
			this->frequency_clock.frequency_hclk = (this->frequency_clock.frequency_sysclk) / 64U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV128:
			this->frequency_clock.frequency_hclk = (this->frequency_clock.frequency_sysclk) / 128U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV256:
			this->frequency_clock.frequency_hclk = (this->frequency_clock.frequency_sysclk) / 256U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV512:
			this->frequency_clock.frequency_hclk = (this->frequency_clock.frequency_sysclk) / 512U;
			break;
	}
	this->frequency_clock.frequency_p1clk = this->frequency_clock.frequency_hclk;
	this->frequency_clock.frequency_p2clk = this->frequency_clock.frequency_hclk;
}

void Sys_Clock::frequency_update_p1clk(Prescaler_APB1 prescaler_apb1)
{
	switch(prescaler_apb1)
	{
		case Prescaler_APB1::PRESCALER_APB1_DIV1:
			this->frequency_clock.frequency_p1clk = (this->frequency_clock.frequency_hclk) / 1U;
			break;
		case Prescaler_APB1::PRESCALER_APB1_DIV2:
			this->frequency_clock.frequency_p1clk = (this->frequency_clock.frequency_hclk) / 2U;
			break;
		case Prescaler_APB1::PRESCALER_APB1_DIV4:
			this->frequency_clock.frequency_p1clk = (this->frequency_clock.frequency_hclk) / 4U;
			break;
		case Prescaler_APB1::PRESCALER_APB1_DIV8:
			this->frequency_clock.frequency_p1clk = (this->frequency_clock.frequency_hclk) / 8U;
			break;
		case Prescaler_APB1::PRESCALER_APB1_DIV16:
			this->frequency_clock.frequency_p1clk = (this->frequency_clock.frequency_hclk) / 16U;
			break;
	}
}

void Sys_Clock::frequency_update_p2clk(Prescaler_APB2 prescaler_apb2)
{
	switch(prescaler_apb2)
	{
		case Prescaler_APB2::PRESCALER_APB2_DIV1:
			this->frequency_clock.frequency_p2clk = (this->frequency_clock.frequency_hclk) / 1U;
			break;
		case Prescaler_APB2::PRESCALER_APB2_DIV2:
			this->frequency_clock.frequency_p2clk = (this->frequency_clock.frequency_hclk) / 2U;
			break;
		case Prescaler_APB2::PRESCALER_APB2_DIV4:
			this->frequency_clock.frequency_p2clk = (this->frequency_clock.frequency_hclk) / 4U;
			break;
		case Prescaler_APB2::PRESCALER_APB2_DIV8:
			this->frequency_clock.frequency_p2clk = (this->frequency_clock.frequency_hclk) / 8U;
			break;
		case Prescaler_APB2::PRESCALER_APB2_DIV16:
			this->frequency_clock.frequency_p2clk = (this->frequency_clock.frequency_hclk) / 16U;
			break;
	}
}

void Sys_Clock::frequency_default_pll()
{
	this->frequency_clock.frequency_sysclk = this->frequency_clock.frequency_hclk;
	this->frequency_clock.frequency_sysclk = this->frequency_clock.frequency_p1clk;
	this->frequency_clock.frequency_sysclk = this->frequency_clock.frequency_p2clk;
}

Sys_Clock::Sys_Clock() : oscillator_type(Sys_Oscillator_Type::OSC_TYPE_HSI)
{
	frequency_default_hsi();
}

Sys_Clock::Sys_Clock(Sys_Oscillator_Type osc_type) : oscillator_type(osc_type)
{
	if (this->oscillator_type == Sys_Oscillator_Type::OSC_TYPE_HSI)
	{
		frequency_default_hsi();
	}
	else if (this->oscillator_type == Sys_Oscillator_Type::OSC_TYPE_HSE)
	{
		/* Enable HSE */
		volatile std::uint32_t *rcc_cr = reinterpret_cast<volatile std::uint32_t *>(RCC_CR);
		*rcc_cr |= (1U << 16U);
		/* Keeps looping if 0 if not HSERDY is in ready state */
		while(!(*rcc_cr & (1U << 17U)));
		frequency_default_hse();
	}
}

void Sys_Clock::sysclk_disable_hsi()
{
	volatile std::uint32_t *rcc_cr = reinterpret_cast<volatile std::uint32_t *>(RCC_CR);
	/* Clear HSION field */
	*rcc_cr &= ~(1U << 0);
}

void Sys_Clock::sysclk_select_hse()
{
	/* Select HSE as System Clock Source */
	volatile std::uint32_t *rcc_cfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_CFGR);
	*rcc_cfgr |= (1U << 0U);
	/* Reads SW bit until it shows the System Clock Status is enabled 01 HSE */
	while((*rcc_cfgr & (3U << 2U)) != (1U << 2U));
	/* Disable HSI now since HSE is enabled */
	sysclk_disable_hsi();
}

void Sys_Clock::sysclk_select_pll()
{
	volatile std::uint32_t *rcc_cfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_CFGR);
	/* Clear the Selected Clock */
	*rcc_cfgr &= ~(3U << 0U);
	/* Set the Clock to PLL as System Clock */
	*rcc_cfgr |= (2U << 0U);
	/* Loops until System Clock Status is enabled PLL 10 */
	while((*rcc_cfgr & (3U << 2U)) != (2U << 2U));
	frequency_default_pll();
}

void Sys_Clock::configure_prescaler_ahb(const Prescaler_AHB prescaler_ahb)
{
	volatile uint32_t *rcc_cfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_CFGR);
	/* Clear and Configure HCLK = SYS_CLK/PRESCALER_AHB */
	*rcc_cfgr &= ~(15U << 4U);
	*rcc_cfgr |= (static_cast<std::uint32_t>(prescaler_ahb) << 4U);
	frequency_update_hclk(prescaler_ahb);
}

void Sys_Clock::configure_prescaler_apb1(const Prescaler_APB1 prescaler_apb1)
{
	volatile uint32_t *rcc_cfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_CFGR);
	/* Configure P1CLK = HCLK/PRESCALER_APB */
	*rcc_cfgr &= ~(7 << 10U);
	*rcc_cfgr |= (static_cast<std::uint32_t>(prescaler_apb1) << 10U);
	frequency_update_p1clk(prescaler_apb1);
}

void Sys_Clock::configure_prescaler_apb2(const Prescaler_APB2 prescaler_apb2)
{
	volatile uint32_t *rcc_cfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_CFGR);
	/* Configure P1CLK = HCLK/PRESCALER_APB */
	*rcc_cfgr &= ~(7 << 13U);
	*rcc_cfgr |= (static_cast<std::uint32_t>(prescaler_apb2) << 13U);
	frequency_update_p2clk(prescaler_apb2);
}

Sys_Clock& Sys_Clock::operator /=(const Prescaler_AHB prescaler_ahb)
{
	volatile uint32_t *rcc_cfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_CFGR);
	/* Configure HCLK = SYS_CLK/PRESCALER_AHB */
	*rcc_cfgr &= ~(15U << 4U);
	*rcc_cfgr |= (static_cast<std::uint32_t>(prescaler_ahb) << 4U);
	frequency_update_hclk(prescaler_ahb);
	return *this;
}

Sys_Clock& Sys_Clock::operator /=(const Prescaler_APB1 prescaler_apb1)
{
	volatile uint32_t *rcc_cfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_CFGR);
	/* Configure P1CLK = HCLK/PRESCALER_APB1 */
	*rcc_cfgr &= ~(7 << 10U);
	*rcc_cfgr |= (static_cast<std::uint32_t>(prescaler_apb1) << 10U);
	frequency_update_p1clk(prescaler_apb1);
	return *this;
}

Sys_Clock& Sys_Clock::operator /=(const Prescaler_APB2 prescaler_apb2)
{
	volatile uint32_t *rcc_cfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_CFGR);
	/* Configure P2CLK = HCLK/PRESCALER_APB2 */
	*rcc_cfgr &= ~(7 << 13U);
	*rcc_cfgr |= (static_cast<std::uint32_t>(prescaler_apb2) << 13U);
	frequency_update_p2clk(prescaler_apb2);
	return *this;
}

std::uint32_t Sys_Clock::get_sysclk_frequency() const
{
	return this->frequency_clock.frequency_sysclk;
}

Frequency_Clock_Type Sys_Clock::get_frequency() const 
{
	return this->frequency_clock;
}

Sys_Oscillator_Type Sys_Clock::get_oscillator_type() const
{
	return this->oscillator_type;
}

void Sys_Clock::frequency_update_pllclk(const Prescaler_PLLM prescaler_pllm)
{
	this->frequency_clock.frequency_sysclk /= static_cast<uint32_t>(prescaler_pllm);
}

void Sys_Clock::frequency_update_pllclk(const Prescaler_PLLP prescaler_pllp)
{
	switch(prescaler_pllp)
	{
		case Prescaler_PLLP::PRESCALER_PLLP_DIV2:
			this->frequency_clock.frequency_sysclk /= 2U;
			break;
		case Prescaler_PLLP::PRESCALER_PLLP_DIV4:
			this->frequency_clock.frequency_sysclk /= 4U;
			break;
		case Prescaler_PLLP::PRESCALER_PLLP_DIV6:
			this->frequency_clock.frequency_sysclk /= 6U;
			break;
		case Prescaler_PLLP::PRESCALER_PLLP_DIV8:
			this->frequency_clock.frequency_sysclk /= 8U;
			break;
	}
}

void Sys_Clock::frequency_update_pllclk(const Prescaler_PLLN prescaler_plln)
{
	this->frequency_clock.frequency_sysclk *= static_cast<uint32_t>(prescaler_plln);
}

void Sys_Clock::configure_prescaler_pllm(const Prescaler_PLLM prescaler_pllm)
{
	volatile uint32_t *rcc_pllcfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_PLLCFGR);	
	*rcc_pllcfgr &= ~(18U << 0U);
	*rcc_pllcfgr |= (static_cast<uint32_t>(prescaler_pllm) << 0U);
	frequency_update_pllclk(prescaler_pllm);
}

void Sys_Clock::configure_prescaler_plln(const Prescaler_PLLN prescaler_plln)
{
	volatile uint32_t *rcc_pllcfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_PLLCFGR);
	*rcc_pllcfgr &= ~(511U << 6U);
	*rcc_pllcfgr |= (static_cast<uint32_t>(prescaler_plln) << 6U);
	frequency_update_pllclk(prescaler_plln);
}

void Sys_Clock::configure_prescaler_pllp(const Prescaler_PLLP prescaler_pllp)
{
	volatile uint32_t *rcc_pllcfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_PLLCFGR);
	*rcc_pllcfgr &= ~(15U << 16U);
	*rcc_pllcfgr |= (static_cast<uint32_t>(prescaler_pllp) << 16U);
	frequency_update_pllclk(prescaler_pllp);
}

Sys_Clock& Sys_Clock::operator *=(const Prescaler_PLLN prescaler_plln)
{
	volatile uint32_t *rcc_pllcfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_PLLCFGR);
	*rcc_pllcfgr &= ~(511U << 6U);
	*rcc_pllcfgr |= (static_cast<uint32_t>(prescaler_plln) << 6U);
	return *this;
}

Sys_Clock& Sys_Clock::operator /=(const Prescaler_PLLM prescaler_pllm)
{
	volatile uint32_t *rcc_pllcfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_PLLCFGR);	
	*rcc_pllcfgr &= ~(18U << 0U);
	*rcc_pllcfgr |= (static_cast<uint32_t>(prescaler_pllm) << 0U);
	return *this;
}

Sys_Clock& Sys_Clock::operator /=(const Prescaler_PLLP prescaler_pllp)
{
	volatile uint32_t *rcc_pllcfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_PLLCFGR);
	*rcc_pllcfgr &= ~(15U << 16U);
	*rcc_pllcfgr |= (static_cast<uint32_t>(prescaler_pllp) << 16U);
	return *this;
}

void Sys_Clock::sysclk_enable_pll()
{
	volatile uint32_t *rcc_cr = reinterpret_cast<volatile std::uint32_t *>(RCC_CR);
	*rcc_cr |= (1U << 24U);
	/* Waits until it is at a PLLRDY state */
	while(!(*rcc_cr & (1U << 25U)));
}

void Sys_Clock::configure_source_pll()
{
	if (this->oscillator_type == Sys_Oscillator_Type::OSC_TYPE_HSE)
	{
		volatile std::uint32_t *rcc_pllcfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_PLLCFGR);
		*rcc_pllcfgr |= (1U << 22U);
	}
}

Frequency_Sys_Clock_Status Sys_Clock::configure_flash_latency()
{
	if (this->frequency_clock.frequency_sysclk < 0U || this->frequency_clock.frequency_sysclk > 168000000U)
	{
		return Frequency_Sys_Clock_Status::STATUS_SYS_CLOCK_NOK;
	}

	volatile std::uint32_t *flash_acr = reinterpret_cast<volatile std::uint32_t *>(FLASH_ACR);

	if (this->frequency_clock.frequency_sysclk >= 0U && this->frequency_clock.frequency_sysclk <= 30000000U)
	{
		*flash_acr |= (static_cast<std::uint32_t>(Flash_Latency::FLASH_LATENCY_WS0) << 0U);
	}
	else if (this->frequency_clock.frequency_sysclk > 30000000U && this->frequency_clock.frequency_sysclk <= 60000000U)
	{
		*flash_acr |= (static_cast<std::uint32_t>(Flash_Latency::FLASH_LATENCY_WS1) << 0U);
	}
	else if (this->frequency_clock.frequency_sysclk > 60000000U && this->frequency_clock.frequency_sysclk <= 90000000U)
	{
		*flash_acr |= (static_cast<std::uint32_t>(Flash_Latency::FLASH_LATENCY_WS2) << 0U);
	}
	else if (this->frequency_clock.frequency_sysclk > 90000000U && this->frequency_clock.frequency_sysclk <= 120000000U)
	{
		*flash_acr |= (static_cast<std::uint32_t>(Flash_Latency::FLASH_LATENCY_WS3) << 0U);
	}
	else if (this->frequency_clock.frequency_sysclk > 120000000U && this->frequency_clock.frequency_sysclk <= 150000000U)
	{
		*flash_acr |= (static_cast<std::uint32_t>(Flash_Latency::FLASH_LATENCY_WS4) << 0U);
	}
	else if (this->frequency_clock.frequency_sysclk > 150000000U && this->frequency_clock.frequency_sysclk <= 168000000U)
	{
		*flash_acr |= (static_cast<std::uint32_t>(Flash_Latency::FLASH_LATENCY_WS5) << 0U);
	}
	return Frequency_Sys_Clock_Status::STATUS_SYS_CLOCK_OK;
}

}
