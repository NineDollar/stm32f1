//
// Created by NineDollar on 2022/5/13.
//

#include "pwm.h"
#include "stm32f10x.h"

/**
 * PA1
 */
void pwm_gpio_init() {
  GPIO_InitTypeDef GPIO_InitStructure;

  //开启gpio口电源
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  //PA1初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  //速度10Mhz
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  //复用推挽输出
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  //初始化
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * tim2 ch2
 */
void pwm_tim2_init(void) {
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  //配置周期，对于蜂鸣器就是频率
  //1ms
  TIM_TimeBaseStructure.TIM_Period = 1000;
  //72M / 72 = 1Mhz
  TIM_TimeBaseStructure.TIM_Prescaler = 72;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  //配置占空比
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  //500us高电平   500us低电平
  TIM_OCInitStructure.TIM_Pulse = 100;
  //pwm2本来低电平，输出极性低就是高电平开始了
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OutputState = ENABLE;
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);

  TIM_Cmd(TIM2, ENABLE);
}