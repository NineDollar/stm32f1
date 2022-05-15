#ifndef __STM32F1xx_IT_H
#define __STM32F1xx_IT_H

#ifdef __cplusplus
extern "C" {
#endif

#define USART1_STR_MAX 100
extern bool usart1_flag_rx;
extern unsigned char usart1_buff[USART1_STR_MAX];

extern uint32_t tim3_times;

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_IT_H */
