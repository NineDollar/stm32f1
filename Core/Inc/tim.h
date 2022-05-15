//
// Created by NineDollar on 2022/5/12.
//

#ifndef STM32F1_CORE_SRC_TIM_H_
#define STM32F1_CORE_SRC_TIM_H_
#include "stm32f10x.h"

void tim2_init();

void pwm_tim2_init();
void pwm_gpio_init();
void tim3_init();
bool tim3_delay(uint32_t time);
#endif //STM32F1_CORE_SRC_TIM_H_
