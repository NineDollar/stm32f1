#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "stm32f1xx_it.h"
#include "usart.h"
#include "dht11.h"
#include "farm.h"
#include "led.h"
#include "gpio.h"

bool usart1_flag_rx = false;
unsigned char usart1_buff[USART1_STR_MAX];
unsigned char usart1_rx[USART1_STR_MAX];
int i = 0;
/**
 * <p>格式：tmp=25 hum=40</p>
 * USART1中断接收服务函数
 */
void USART1_IRQHandler() {
  uint16_t m;
  if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
    if (uart1_getbyte(&m) == 1) {
      unsigned char t = (unsigned char) m;
      if (m == '\n') {
        usart1_flag_rx = true;
        usart1_buff[i] = '\0';
        strcpy((char *) usart1_rx, (const char *) usart1_buff);
        i = 0;
      } else {
        usart1_buff[i++] = t;
      }
      USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
  }
}

uint8_t tmp = 0;
uint8_t hum = 0;
/**
 * time中断服务函数，1ms 进入一次
 */
void TIM2_IRQHandler(void) {
  static int i = 0;

  if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
    i++;
    if (i >= 1000) {
      led_on();
      dht11_get_data(&tmp, &hum);
      printf("tmp=%d hum=%d\r\n", tmp, hum);
      if (usart1_flag_rx) {
        usart1_flag_rx = false;
        user_tmp = (usart1_rx[4] - '0') * 10;
        user_tmp += usart1_rx[5] - '0';
        user_hum = (usart1_rx[11] - '0') * 10;
        user_hum += usart1_rx[12] - '0';
        show_user_tmp(user_tmp);
        show_user_hum(user_hum);
        printf("user_tmp:%d\r\n", user_tmp);
        printf("user_hum:%d\r\n", user_hum);
      }
      if (tmp >= user_tmp) {
        //  大于用户设置的温度
        printf("温度太高了\r\n");
        tem_led_open();
        show_fun_open();
      } else {
        tem_led_close();
        show_fun_close();
      }
      if (hum >= user_hum) {
        //  大于用户设置的温度
        printf("湿度太大了\r\n");
        hum_led_open();
        show_fun_open();
      } else {
        hum_led_close();
        show_fun_close();
      }
      show_tem_num(tmp);
      show_hum_num(hum);
      i = 0;
      led_off();
    }
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  }
}

/**
 * Cortex-M3 Processor Interruption and Exception Handlers
 */
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void) {
  printf("NMI_Handler\r\n");
  while (1) {
  }
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void) {
  printf("HardFault_Handler\r\n");
  while (1) {
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void) {
  printf("MemManage_Handler\r\n");
  while (1) {
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void) {
  printf("BusFault_Handler\r\n");
  while (1) {
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void) {
  printf("UsageFault_Handler\r\n");
  while (1) {
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void) {
  printf("SVC_Handler\r\n");
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void) {
  printf("DebugMon_Handler\r\n");
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void) {
  printf("PendSV_Handler\r\n");
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void) {
  printf("SysTick_Handler\r\n");
}