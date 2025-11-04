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
	this->frequency_clock.frequency_ahb = FREQUENCY_HSE;
	this->frequency_clock.frequency_apb1 = FREQUENCY_HSE;
	this->frequency_clock.frequency_apb2 = FREQUENCY_HSE;
}

void Sys_Clock::frequency_default_hsi()
{
	this->frequency_clock.frequency_sysclk = FREQUENCY_HSI;
	this->frequency_clock.frequency_ahb = FREQUENCY_HSI;
	this->frequency_clock.frequency_apb1 = FREQUENCY_HSI;
	this->frequency_clock.frequency_apb2 = FREQUENCY_HSI;
}

Sys_Clock::Sys_Clock() : oscillator_type(Sys_Oscillator_Type::OSC_TYPE_HSI)
{
	volatile std::uint32_t *rcc_cr = reinterpret_cast<volatile std::uint32_t *>(RCC_CR);
	*rcc_cr |= (1U << 0);
    /* Waits until the RDY Flag is set to enable */
	while(!(*rcc_cr & (1U << 1))); 
	frequency_default_hsi();
}


Sys_Clock::Sys_Clock(Sys_Oscillator_Type osc_type) : oscillator_type(osc_type)
{
	volatile std::uint32_t *rcc_cr = reinterpret_cast<volatile std::uint32_t *>(RCC_CR);

	if (this->oscillator_type == Sys_Oscillator_Type::OSC_TYPE_HSI)
	{
		*rcc_cr |= (1U << 0);
        /* Waits until the RDY Flag is set to enable */
		while(!(*rcc_cr & (1U << 1))); 
		frequency_default_hsi();
	}
	else if (this->oscillator_type == Sys_Oscillator_Type::OSC_TYPE_HSE)
	{
		*rcc_cr |= (1U << 16);
		while(!(*rcc_cr & (1U << 17)));
		frequency_default_hse();
	}
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

void Sys_Clock::configuration_hsi()
{
	if (this->oscillator_type != Sys_Oscillator_Type::OSC_TYPE_HSI)
	{
		return;
	}
}

void Sys_Clock::configuration_hse()
{
	if (this->oscillator_type != Sys_Oscillator_Type::OSC_TYPE_HSE)
	{
		return;
	}
}

void Sys_Clock_PLL::prescaler_default_pll()
{
	/* Based on default reset values */
	this->prescaler_pll.prescaler_pllm = 16;
	this->prescaler_pll.prescaler_plln = 192;
	this->prescaler_pll.prescaler_pllp = 4;
}

Sys_Clock_PLL::Sys_Clock_PLL()
{
	prescaler_default_pll();
}

}
