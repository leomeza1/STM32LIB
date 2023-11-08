
#include "GpioPin.hpp"


GpioPin::GpioPin(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init)
    :
    port(GPIOx),
    pin(GPIO_Init->Pin),
	mode(GPIO_Init->Mode),
	pull(GPIO_Init->Pull),
	speed(GPIO_Init->Speed),
	alternate(GPIO_Init->Alternate)
{
    // Enable the GPIO port clock
    if(GPIOx == GPIOA)
    {
        RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    }
    else if(GPIOx == GPIOB)
    {
        RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    }
    else if(GPIOx == GPIOC)
    {
        RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    }
    else if(GPIOx == GPIOD)
    {
        RCC->AHBENR |= RCC_AHBENR_GPIODEN;
    }
    else if(GPIOx == GPIOF)
    {
        RCC->AHBENR |= RCC_AHBENR_GPIOFEN;
    }

    // If this pin is configured for output, reset the output level
    if(GPIO_Init->Mode & MODE_OUTPUT)
    {
        HAL_GPIO_WritePin(GPIOx, GPIO_Init->Pin, GPIO_PIN_RESET);
    }

    // Just use HAL to initialize the GPIO pin
    HAL_GPIO_Init(GPIOx, GPIO_Init);
}

bool GpioPin::Read()
{
    return HAL_GPIO_ReadPin(port, pin);
}

void GpioPin::Set()
{
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);

	//port->BSRR |= (1U << pin);
}

void GpioPin::Clear()
{
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);

	//port->BSRR |= (1U << (pin + GPIOx_BSRR_BR_OFFSET));
}

void GpioPin::Toggle()
{
    HAL_GPIO_TogglePin(port, pin);
}
