//
// Created by NineDollar on 2022/5/12.
//

#include <stdbool.h>
#include "tim.h"
#include "stm32f10x.h"
#include "stm32f1xx_it.h"

void tim2_init() {
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  //周期
  TIM_TimeBaseStructure.TIM_Period = 1000;
  //分频系数，72M/72=1Mhz
  TIM_TimeBaseStructure.TIM_Prescaler = 72;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_Cmd(TIM2, ENABLE);

  //中断配置 初始化
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  //选择串口中断
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  //抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  //从优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  //使能中断
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
 * time3，1us
 */
void tim3_init() {
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  //周期
  TIM_TimeBaseStructure.TIM_Period = 10000;
  //分频系数，72M/7200=10khz
  TIM_TimeBaseStructure.TIM_Prescaler = 7200;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  TIM_Cmd(TIM3, ENABLE);

  //中断配置 初始化
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
  //选择串口中断
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  //抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  //从优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  //使能中断
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
/**
 *
 * @param time 单位1us
 * @return
 */
bool tim3_delay(uint32_t time) {
  //启动定时器

  while (tim3_times <= time);
  tim3_times = 0;
  //关闭定时器

  return true;
}
