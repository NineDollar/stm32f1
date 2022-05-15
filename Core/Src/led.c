//
// Created by NineDollar on 2022/5/8.
//
#include <stdbool.h>
#include "led.h"
#include "stm32f10x.h"

void led_init() {
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void led_on() {
  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
}

void led_off() {
  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
}