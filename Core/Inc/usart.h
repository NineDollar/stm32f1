#ifndef __USART_H
#define __USART_H

#include "stdio.h"
#include "stm32f10x.h"

void usart1_init(void);
void uart1test(void);
void uart1_sendbyte(uint16_t SendData);
unsigned char uart1_getbyte(uint16_t *GetData);
#endif //__USART_H

