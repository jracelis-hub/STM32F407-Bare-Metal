/*
 * sys_clock.cpp
 *
 *  Created on: Oct 31, 2025
 *      Author: jarron_racelis
 */

#include "sys_clock.h"

namespace bare_metal
{

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
			this->frequency_clock.frequency_hclk /= 1U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV2:
			this->frequency_clock.frequency_hclk /= 2U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV4:
			this->frequency_clock.frequency_hclk /= 4U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV8:
			this->frequency_clock.frequency_hclk /= 8U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV16:
			this->frequency_clock.frequency_hclk /= 16U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV64:
			this->frequency_clock.frequency_hclk /= 64U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV128:
			this->frequency_clock.frequency_hclk /= 128U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV256:
			this->frequency_clock.frequency_hclk /= 256U;
			break;
		case Prescaler_AHB::PRESCALER_AHB_DIV512:
			this->frequency_clock.frequency_hclk /= 512U;
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

void Sys_Clock::sysclk_select_hse()
{
	/* Select HSE as System Clock Source */
	volatile std::uint32_t *rcc_cfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_CFGR);
	*rcc_cfgr |= (1U << 0U);
	/* Reads SW bit until it shows the System Clock Status is enabled 01 HSE */
	while((*rcc_cfgr & (3U << 2U)) != (1U << 2U));
}

void Sys_Clock::configure_prescaler_ahb(const Prescaler_AHB prescaler_ahb)
{
	volatile uint32_t *rcc_cfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_CFGR);
	/* Configure HCLK = SYS_CLK/PRESCALER_AHB */
	*rcc_cfgr |= (static_cast<std::uint32_t>(prescaler_ahb) << 4U);
	frequency_update_hclk(prescaler_ahb);
}

void Sys_Clock::configure_prescaler_apb1(const Prescaler_APB1 prescaler_apb1)
{
	volatile uint32_t *rcc_cfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_CFGR);
	/* Configure P1CLK = HCLK/PRESCALER_APB */
	*rcc_cfgr |= (static_cast<std::uint32_t>(prescaler_apb1) << 10U);
	frequency_update_p1clk(prescaler_apb1);
}

void Sys_Clock::configure_prescaler_apb2(const Prescaler_APB2 prescaler_apb2)
{
	volatile uint32_t *rcc_cfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_CFGR);
	/* Configure P1CLK = HCLK/PRESCALER_APB */
	*rcc_cfgr |= (static_cast<std::uint32_t>(prescaler_apb2) << 13U);
	frequency_update_p2clk(prescaler_apb2);
}

Sys_Clock& Sys_Clock::operator /=(const Prescaler_AHB prescaler_ahb)
{
	volatile uint32_t *rcc_cfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_CFGR);
	/* Configure HCLK = SYS_CLK/PRESCALER_AHB */
	*rcc_cfgr |= (static_cast<std::uint32_t>(prescaler_ahb) << 4U);
	frequency_update_hclk(prescaler_ahb);
	return *this;
}

Sys_Clock& Sys_Clock::operator /=(const Prescaler_APB1 prescaler_apb1)
{
	volatile uint32_t *rcc_cfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_CFGR);
	/* Configure P1CLK = HCLK/PRESCALER_APB1 */
	*rcc_cfgr |= (static_cast<std::uint32_t>(prescaler_apb1) << 10U);
	frequency_update_p1clk(prescaler_apb1);
	return *this;
}

Sys_Clock& Sys_Clock::operator /=(const Prescaler_APB2 prescaler_apb2)
{
	volatile uint32_t *rcc_cfgr = reinterpret_cast<volatile std::uint32_t *>(RCC_CFGR);
	/* Configure P2CLK = HCLK/PRESCALER_APB2 */
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

void Sys_Clock_PLL::prescaler_default_pll()
{
	/* Based on default reset values */
	this->prescaler_pll.prescaler_pllm = 16U;
	this->prescaler_pll.prescaler_plln = 192U;
	this->prescaler_pll.prescaler_pllp = 4U;
}

Sys_Clock_PLL::Sys_Clock_PLL()
{
	prescaler_default_pll();
}

}
