//
// Created by NineDollar on 2022/5/15.
//

#include "gpio.h"
#include "stm32f10x.h"

void tem_hum_led_init() {
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void tem_led_open() {
  GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
}

void tem_led_close() {
  GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
}

void hum_led_open() {
  GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
}

void hum_led_close() {
  GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
}