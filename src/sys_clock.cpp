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
	this->clock_frequency.frequency_sysclk = FREQUENCY_HSE;
	this->clock_frequency.frequency_ahb = FREQUENCY_HSE;
	this->clock_frequency.frequency_apb1 = FREQUENCY_HSE;
	this->clock_frequency.frequency_apb2 = FREQUENCY_HSE;
}

void Sys_Clock::frequency_default_hsi()
{
	this->clock_frequency.frequency_sysclk = FREQUENCY_HSI;
	this->clock_frequency.frequency_ahb = FREQUENCY_HSI;
	this->clock_frequency.frequency_apb1 = FREQUENCY_HSI;
	this->clock_frequency.frequency_apb2 = FREQUENCY_HSI;
}

Sys_Clock::Sys_Clock() : oscillator_type(bare_metal::Sys_Oscillator_Type::OSC_TYPE_HSI)
{
	std::uint32_t *rcc_cr = (uint32_t *)(RCC_CCR);
	*rcc_cr |= (1U << 0);
	while(!(*rcc_cr & (1U << 1))); /* Waits until the RDY Flag is set to enable */
	frequency_default_hsi();
}


Sys_Clock::Sys_Clock(Sys_Oscillator_Type osc_type) : oscillator_type(osc_type)
{
	std::uint32_t *rcc_cr = (uint32_t *)(RCC_CCR);

	if (this->oscillator_type == Sys_Oscillator_Type::OSC_TYPE_HSI)
	{
		*rcc_cr |= (1U << 0);
		while(!(*rcc_cr & (1U << 1))); /* Waits until the RDY Flag is set to enable */
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
	return this->clock_frequency.frequency_sysclk;
}

Clock_Frequency_Type Sys_Clock::get_frequency() const 
{
	return this->clock_frequency;
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

Sys_Clock_PLL::Sys_Clock_PLL(const Sys_Clock& sys_clock)
{
	if (this->oscillator_type == Sys_Oscillator_Type::OSC_TYPE_HSI)
	{

	}
	else if (this->oscillator_type == Sys_Oscillator_Type::OSC_TYPE_HSE)
	{

	}
}

}
