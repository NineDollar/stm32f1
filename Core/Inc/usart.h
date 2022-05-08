#ifndef __USART_H
#define __USART_H

#include "stdio.h"
#include "stm32f10x.h"

void USART1_Config(void);
void UART1Test(void);
void UART1SendByte(unsigned char SendData);

#endif //__USART_H

