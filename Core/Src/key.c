//
// Created by NineDollar on 2022/5/9.
//
#include <stdbool.h>
#include "delay.h"
#include "stm32f10x.h"

/**
 * PA5上拉，接地返回true
 */
void key_init() {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

bool key() {
  u8 result = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
  if (!result) {
    delay(100);
    result = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
    while (!result) {
      return true;
    }
  } else {
    return false;
  }
  return false;
}
