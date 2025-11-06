#ifndef NVIC_H
#define NVIC_H

#include <cstdint>

/* 16000000 Hz = 6.25 x 10^-8 s
 * 1000 Hz = 1 x 10^-3 s delay 
 */

namespace bare_metal
{
	constexpr std::uint32_t SYST_CSR =                 (0xE000E010);
	constexpr std::uint32_t SYST_RVR =                 (0xE000E014);
	constexpr std::uint32_t SYST_CVR =                 (0xE000E018);
	constexpr std::uint32_t SYST_CLALIB =              (0xE000E01C);
	
	/* SysTick Timer SVR is copied into CVR 
	 * When the SysTick is enabled it will start counting down
	 * Once CVR reaches zero the SVR will get reloaded into a fresh register 
	 * CVR Does the counting 
	 * SVR(4) -> CVR -> Count down 4 3 2 1 0 reload(4) --> System Exception Triggers 
	 * Note: That the clock cycle took 5 seconds if you want it to be at the value specified subtract the reload value by 1 */
	class Nvic
	{
		Nvic(const Sys_Clock& sys_clock, const std::uint32_t counter);	



	};
}

#endif /* NVIC_H */
