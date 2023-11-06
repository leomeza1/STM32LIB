
#include "GpioPin.hpp"

GpioPin::GpioPin(const GPIO_Config_t *gpio_cfg)
    :
    port(gpio_cfg->port),
    pin(gpio_cfg->pin),
	ahb_pclock(gpio_cfg->ahb_pclock),
	mode(gpio_cfg->mode),
	otype(gpio_cfg->otype),
	ospeed(gpio_cfg->ospeed),
	pupd(gpio_cfg->pupd)
{
	ahb_peripheral_clock_enable();

	moder_configure();

	output_type_configure();

	output_speed_configure();

	pull_up_pull_down_configure();
}

bool GpioPin::Read()
{
    return HAL_GPIO_ReadPin(port, pin);
}

void GpioPin::Set()
{
    //HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);

	port->BSRR |= (1U << pin);
}

void GpioPin::Clear()
{
    //HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);

	port->BSRR |= (1U << (pin + GPIOx_BSRR_BR_OFFSET));
}

void GpioPin::Toggle()
{
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
}

void GpioPin::moder_configure(void)
{
	uint32_t register_offset = 0;

	if(pin < 16)
	{
		// Get the register bit offset for the specified pin. This will be
		// used to set the appropriate bits for the specified pin.
		// Reference section 8.4.1 "GPIO port mode register" for details.
		register_offset = pin * 2;

		switch(mode)
		{
		case GPIO_MODER_INPUT:
			// 00: Input mode (reset state)
			port->MODER &= ~(0x3UL << register_offset);
			break;

		case GPIO_MODER_OUTPUT:
			// 01: General purpose output mode
			port->MODER |= (0x1UL << register_offset);
			port->MODER &= ~(0x2UL << register_offset);
			break;

		case GPIO_MODER_ALTERNATE:
			// 10: Alternate function mode
			port->MODER |= (0x2UL << register_offset);
			port->MODER &= ~(0x1UL << register_offset);
			break;

		case GPIO_MODER_ANALOG:
			// 11: Analog mode
			port->MODER |= (0x3UL << register_offset);
			break;

		default:
			// TODO: Add error handling
			break;
		}
	}
	else
	{
		// TODO: Add error handling
	}
}

void GpioPin::ahb_peripheral_clock_enable(void)
{
	switch(ahb_pclock)
	{
	case AHB_PCLOCK_DMA:
		RCC->AHBENR |= RCC_AHBENR_DMAEN;
		break;

	case AHB_PCLOCK_SRAM:
		RCC->AHBENR |= RCC_AHBENR_SRAMEN;
		break;

	case AHB_PCLOCK_FLITF:
		RCC->AHBENR |= RCC_AHBENR_FLITFEN;
		break;

	case AHB_PCLOCK_CRC:
		RCC->AHBENR |= RCC_AHBENR_CRCEN;
		break;

	case AHB_PCLOCK_IOPA:
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
		break;

	case AHB_PCLOCK_IOPB:
		RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
		break;

	case AHB_PCLOCK_IOPC:
		RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
		break;

	case AHB_PCLOCK_IOPD:
		RCC->AHBENR |= RCC_AHBENR_GPIODEN;
		break;

	case AHB_PCLOCK_IOPF:
		RCC->AHBENR |= RCC_AHBENR_GPIOFEN;
		break;

	default:
		// TODO: Add error handling
		break;
	}
}

void GpioPin::output_type_configure(void)
{
	uint32_t register_offset = 0;

	if(pin < 16)
	{
		// Get the register bit offset for the specified pin. This will be
		// used to set the appropriate bits for the specified pin.
		// Reference section 8.4.2 "GPIO port output type register" for details.
		register_offset = pin;

		switch(otype)
		{
		case GPIO_OUTPUT_TYPE_PP:
			// 0: Output push-pull (reset state)
			port->OTYPER &= ~(0x1UL << register_offset);
			break;

		case GPIO_OUTPUT_TYPE_OD:
			// 1: Output open-drain
			port->OTYPER |= (0x1UL << register_offset);
			break;

		default:
			// TODO: Add error handling
			break;
		}
	}
	else
	{
		// TODO: Add error handling
	}
}

void GpioPin::output_speed_configure(void)
{
	uint32_t register_offset = 0;

	if(pin < 16)
	{
		// Get the register bit offset for the specified pin. This will be
		// used to set the appropriate bits for the specified pin.
		// Reference section 8.4.3 "GPIO port output speed register" for details.
		register_offset = pin;

		switch(ospeed)
		{
		case GPIO_OUTPUT_SPEED_LOW:
			// x0: Low speed
			port->OSPEEDR &= ~(0x1UL << register_offset);
			break;

		case GPIO_OUTPUT_SPEED_MEDIUM:
			// 01: Medium speed
			port->OSPEEDR |= (0x1UL << register_offset);
			port->OSPEEDR &= ~(0x2UL << register_offset);
			break;

		case GPIO_OUTPUT_SPEED_HIGH:
			// 11: High speed
			port->OSPEEDR |= (0x3UL << register_offset);
			break;

		default:
			// TODO: Add error handling
			break;
		}
	}
	else
	{
		// TODO: Add error handling
	}
}

void GpioPin::pull_up_pull_down_configure(void)
{
	uint32_t register_offset = 0;

	if(pin < 16)
	{
		// Get the register bit offset for the specified pin. This will be
		// used to set the appropriate bits for the specified pin.
		// Reference section 8.4.4 "GPIO port pull-up/pull-down register" for details.
		register_offset = pin * 2;

		switch(pupd)
		{
		case GPIO_PUPD_NONE:
			// 00: No pull-up, pull-down
			port->PUPDR &= ~(0x3UL << register_offset);
			break;

		case GPIO_PUPD_PULL_UP:
			// 01: Pull-up
			port->PUPDR |= (0x1UL << register_offset);
			port->PUPDR &= ~(0x2UL << register_offset);
			break;

		case GPIO_PUPD_PULL_DOWN:
			// 10: Pull-down
			port->PUPDR &= ~(0x1UL << register_offset);
			port->PUPDR |= (0x2UL << register_offset);
			break;

		case GPIO_PUPD_RESERVED:  // intentional fall-through
		default:
			// TODO: Add error handling
			break;
		}
	}
	else
	{
		// TODO: Add error handling
	}
}
