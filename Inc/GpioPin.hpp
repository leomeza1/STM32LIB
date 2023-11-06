#ifndef GPIOPIN_HPP_
#define GPIOPIN_HPP_

#include "stm32f0xx_hal.h"


// In the GPIOx_BSRR register, the reset bits (BRy) start at bit 16
#define GPIOx_BSRR_BR_OFFSET (16)


typedef enum {
	AHB_PCLOCK_DMA   = 0,
	AHB_PCLOCK_SRAM  = 1,
	AHB_PCLOCK_FLITF = 2,
	AHB_PCLOCK_CRC   = 3,
	AHB_PCLOCK_IOPA  = 4,
	AHB_PCLOCK_IOPB  = 5,
	AHB_PCLOCK_IOPC  = 6,
	AHB_PCLOCK_IOPD  = 7,
	AHB_PCLOCK_IOPF  = 8

} AHB_Peripheral_Clock_t;

typedef enum {
	GPIO_MODER_INPUT     = 0,  // 00: Input mode (reset state)
	GPIO_MODER_OUTPUT    = 1,  // 01: General purpose output mode
	GPIO_MODER_ALTERNATE = 2,  // 10: Alternate function mode
	GPIO_MODER_ANALOG    = 3   // 11: Analog mode

} GPIO_Mode_t;

typedef enum {
	GPIO_OUTPUT_TYPE_PP = 0,  // 0: Output push-pull (reset state)
	GPIO_OUTPUT_TYPE_OD = 1   // 1: Output open-drain

} GPIO_Output_Type_t;

typedef enum {
	GPIO_OUTPUT_SPEED_LOW    = 0,  // x0: Low speed
	GPIO_OUTPUT_SPEED_MEDIUM = 1,  // 01: Medium speed
	GPIO_OUTPUT_SPEED_HIGH   = 2   // 11: High speed

} GPIO_Output_Speed_t;

typedef enum {
	GPIO_PUPD_NONE      = 0,  // 00: No pull-up, pull-down
	GPIO_PUPD_PULL_UP   = 1,  // 01: Pull-up
	GPIO_PUPD_PULL_DOWN = 2,  // 10: Pull-down
	GPIO_PUPD_RESERVED  = 3   // 11: Reserved

} GPIO_Pull_Up_Pull_Down_t;

typedef struct {
	GPIO_TypeDef             *port;
	uint16_t                  pin;
	GPIO_Mode_t               mode;
	AHB_Peripheral_Clock_t    ahb_pclock;
	GPIO_Output_Type_t        otype;
	GPIO_Output_Speed_t       ospeed;
	GPIO_Pull_Up_Pull_Down_t  pupd;

} GPIO_Config_t;


class GpioPin
{
public:
    GpioPin(const GPIO_Config_t *gpio_cfg);   // Constructor

    bool Read();
    void Set();
    void Clear();
    void Toggle();

private:

    GPIO_TypeDef             *port;
    uint16_t                  pin;
    AHB_Peripheral_Clock_t    ahb_pclock;
    GPIO_Mode_t               mode;
    GPIO_Output_Type_t        otype;
    GPIO_Output_Speed_t       ospeed;
    GPIO_Pull_Up_Pull_Down_t  pupd;

    void moder_configure(void);
    void ahb_peripheral_clock_enable(void);
    void output_type_configure(void);
    void output_speed_configure(void);
    void pull_up_pull_down_configure(void);
};

#endif /* GPIOPIN_HPP_ */
