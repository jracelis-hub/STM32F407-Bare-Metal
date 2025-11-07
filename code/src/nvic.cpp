#include "nvic.h"

namespace bare_metal
{
	/* 1000 Hz = .001 ms in delay 
	 * based on your requirements pass in the delay you want in Hertz */
	Nvic::Nvic(const Sys_Clock& sys_clock, const std::uint32_t hz_clk_delay)
	{
		/* SYST_RVR to configure the count down value */
		volatile std::uint32_t *syst_rvr = reinterpret_cast<volatile std::uint32_t *>(SYST_RVR);
		/* SYST_CSR to enable settings for the SYSTick */
		volatile std::uint32_t *syst_csr = reinterpret_cast<volatile std::uint32_t *>(SYST_CSR);

		/* The reload_value is to determine when to call SysTick exception 
		 * Note: When counting down the - 1 is taken account for when it reloads
		 * CSR */
		std::uint32_t reload_value = (sys_clock.get_sysclk_frequency()/hz_clk_delay) - 1;

		/* Clear the value of SVR before setting */
		*syst_rvr &= ~(0x00FFFFFF);
		/* Set the counter value */
		*syst_rvr |= reload_value;

		/* Enable Systick Settings */
		*syst_csr |= (1U << 1U); /* Enables SysTick exception(interrupt) */
		*syst_csr |= (1U << 2U); /* Indicates the clock source, sysclk */

		/* Enables the configured counter */
		*syst_csr |= (1 << 0U);
	}
}
