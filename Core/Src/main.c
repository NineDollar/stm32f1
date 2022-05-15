//
// Created by NineDollar on 2022/5/7.
//
#include "main.h"
#include <stdbool.h>
#include <string.h>
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "tim.h"
#include "adc.h"
#include "dht11.h"
#include "oled.h"
#include "stm32f1xx_it.h"
#include "farm.h"
#include "gpio.h"

#define tmp_default 30
#define hum_default 80

uint8_t user_tmp = tmp_default;
uint8_t user_hum = hum_default;

int main() {
  led_init();
  tim2_init();
  usart1_init();
  dht11_init();
  oled_init();
  tem_hum_led_init();

  printf("usart test\r\n");
  led_off();
  oled_clear();
  tem_led_close();
  hum_led_close();

  show_tem();
  show_tem_num(tmp_default);
  show_hum();
  show_hum_num(hum_default);
  show_fun();
  show_fun_close();

  show_user_tmp(user_tmp);
  show_user_hum(user_hum);

  while (1) {

  }

}