#pragma once

#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"

//#define CAR_ENGINE_ENABLE

#define CAR_ENGINE_GPIO_PORT_CLOCK RCC_AHB1Periph_GPIOB
#define CAR_ENGINE_GPIO_PORT GPIOB
#define CAR_ENGINE_ENABLE_PIN GPIO_Pin_4
#define CAR_ENGINE_DIRECTION_FORWARD_PIN GPIO_Pin_5
#define CAR_ENGINE_DIRECTION_BACKWARD_PIN GPIO_Pin_6

inline void engine_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(CAR_ENGINE_GPIO_PORT_CLOCK, ENABLE);
    GPIO_InitStructure.GPIO_Pin = CAR_ENGINE_ENABLE_PIN
        | CAR_ENGINE_DIRECTION_FORWARD_PIN
        | CAR_ENGINE_DIRECTION_BACKWARD_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(CAR_ENGINE_GPIO_PORT, &GPIO_InitStructure);
}

inline void engine_stop(void)
{
    GPIO_ResetBits(CAR_ENGINE_GPIO_PORT, 0
            | CAR_ENGINE_DIRECTION_BACKWARD_PIN
            | CAR_ENGINE_ENABLE_PIN
            | CAR_ENGINE_DIRECTION_FORWARD_PIN);
}

#ifdef CAR_ENGINE_ENABLE
inline void engine_forward(void)
{
    engine_stop();
    GPIO_SetBits(CAR_ENGINE_GPIO_PORT, CAR_ENGINE_ENABLE_PIN);
    GPIO_SetBits(CAR_ENGINE_GPIO_PORT, CAR_ENGINE_DIRECTION_FORWARD_PIN);
}

inline void engine_backward(void)
{
    engine_stop();
    GPIO_SetBits(CAR_ENGINE_GPIO_PORT, CAR_ENGINE_ENABLE_PIN);
    GPIO_SetBits(CAR_ENGINE_GPIO_PORT, CAR_ENGINE_DIRECTION_BACKWARD_PIN);
}
#else
#define engine_forward(...);
#define engine_backward(...);
#endif // CAR_ENGINE_ENABLE
