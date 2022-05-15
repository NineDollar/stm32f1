#include "usart.h"
#include "led.h"
#include "delay.h"

/**
 * printf重定义
 */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)

/**
 * 1.开电源
 * 初始化
 * 串口使能
 * 发送数据
 * TX:PA9
 * RX:PA10
 */
void usart1_init() {
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  setvbuf(stdout, NULL, _IONBF, 0);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  //复用推挽输出
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  //浮空输入
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);
  USART_Cmd(USART1, ENABLE);
  printf("\r\n");

  //中断接收
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  //抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  //重优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  //使能中断
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
 * 发送
 * @param SendData
 */
void uart1_sendbyte(uint16_t SendData) {
  USART_SendData(USART1, SendData);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/**
 * 接收
 * @param GetData
 * @return
 */
unsigned char uart1_getbyte(uint16_t *GetData) {
  // USART_FLAG_RXNE接收标志位
  if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET) {
    return 0;
  }
  *GetData = USART_ReceiveData(USART1);
  return 1;
}

/**
 * 测试
 */
/*void UART1Test(void) {
  unsigned char i = 0;
  while (1) {
    while (uart1_getbyte(&i)) {
      USART_SendData(USART1, i);
    }
  }
}*/

/**
 * 重定义
 * @param ch
 * @return
 */
PUTCHAR_PROTOTYPE {
  USART_SendData(USART1, (uint8_t) ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
  return ch;
};

GETCHAR_PROTOTYPE {
  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
  return (int) USART_ReceiveData(USART1);
};


