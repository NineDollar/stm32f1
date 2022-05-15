//
// Created by NineDollar on 2022/5/13.
//

#ifndef STM32F1_CORE_SRC_DHT11_H_
#define STM32F1_CORE_SRC_DHT11_H_
#include "stm32f10x.h"

void dht11_init(void);

int dht11_get_data(u8 *temp, u8 *humi);

#endif //STM32F1_CORE_SRC_DHT11_H_
