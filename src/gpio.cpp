#include "gpio.h"
#include "sys_clock.h"     /* Needed for to enable clock */

namespace bare_metal
{
	Gpio::Gpio(Gpio_Pin pin) : gpio_pin(pin)
	{
		/* Enable Peripheral Clock */
		volatile std::uint32_t *rcc_ahb1enr = reinterpret_cast<volatile std::uint32_t *>(RCC_AHB1ENR);
		*rcc_ahb1enr |= (1U << static_cast<std::uint32_t>(gpio_pin));
	}
}
