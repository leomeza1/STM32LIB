#ifndef GPIOPIN_HPP_
#define GPIOPIN_HPP_


#include "stm32f0xx_hal.h"


class GpioPin
{
public:
    GpioPin(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);   // Constructor

    bool Read();
    void Set();
    void Clear();
    void Toggle();

private:

    GPIO_TypeDef *port;
    uint32_t      pin;
    uint32_t      mode;
    uint32_t      pull;
    uint32_t      speed;
    uint32_t      alternate;

    void moder_configure(void);
    void ahb_peripheral_clock_enable(void);
    void output_type_configure(void);
    void output_speed_configure(void);
    void pull_up_pull_down_configure(void);
};

#endif /* GPIOPIN_HPP_ */
