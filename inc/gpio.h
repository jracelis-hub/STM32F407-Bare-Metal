#ifndef GPIO_H
#define GPIO_H

#include <cstdint>

namespace bare_metal
{
	/* Base address of each GPIO */
	constexpr std::uint32_t GPIOA                      = (0x40020000);
	constexpr std::uint32_t GPIOB                      = (0x40020400);
	constexpr std::uint32_t GPIOC                      = (0x40020800);
	constexpr std::uint32_t GPIOD                      = (0x40020C00);
	constexpr std::uint32_t GPIOE                      = (0x40021000);
	constexpr std::uint32_t GPIOF                      = (0x40021400);
	constexpr std::uint32_t GPIOG                      = (0x40021800);
	constexpr std::uint32_t GPIOH                      = (0x40021C00);
	constexpr std::uint32_t GPIOI                      = (0x40022000);

	/* Pin Location for each GPIO on AHB */
	enum class Gpio_Pin : std::uint32_t
	{
		GPIO_PIN_A        = (0),
		GPIO_PIN_B        = (1),
		GPIO_PIN_C        = (2),
		GPIO_PIN_D        = (3),
		GPIO_PIN_E        = (4),
		GPIO_PIN_F        = (5),
		GPIO_PIN_G        = (6),
		GPIO_PIN_H        = (7),
		GPIO_PIN_I        = (8)
	};

	struct Gpio_Configuration_Type
	{
		

	};
	
	class Gpio
	{
		public:
			Gpio(Gpio_Pin pin);

		private:
			Gpio_Pin gpio_pin;
			Gpio_Configuration_Type gpio_configuration;
	};
}

#endif /* GPIO_H */
