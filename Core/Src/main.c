//
// Created by NineDollar on 2022/5/7.
//
#include <stdbool.h>
#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
#include <stdarg.h>

int main() {
  SystemInit();
  USART1_Config();
  printf("abcd\n");
  printf("printfÊä³ö\n");

  while (true) {
    UART1Test();
    delay(300);
  }
}