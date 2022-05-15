//
// Created by NineDollar on 2022/5/13.
//

#include <stdio.h>
#include "dht11.h"
#include "stm32f10x.h"
#include "delay.h"

/**
 * 初始化DHT11的IO口
 * B0
 */
void dht11_init() {
  int i = 100;
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);

  while (i--)
    delay10ms();
}
//DHT11输入
void dht11_io_in() {
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
//DHT11输出
void dht11_io_out() {
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//等待DHT11的回应
int dht11_check() {
  again:
  dht11_io_out(); //PB0管脚设置为输出管脚
  GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);
  delay10ms();
  GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);

  //拉低至少18ms
  delay10ms();
  delay10ms();
  delay10ms();

  //DQ=1
  GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);

  dht11_io_in(); //PB0管脚设置为输入管脚
  //主机拉高20~40us
  delay10us();
  delay10us();
  delay10us();

  if (RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))//DHT11会拉低80us
  {
    while (!(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)));  //等待响应信号结束

    while ((GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)));  //DHT11发送响应信号后，再把总线拉高80us

    return 0;
  } else
    goto again;
}

/**
 * <p>从DHT11读取一次数据</p>
 * <p>temp:温度值(范围:0~50°)</p>
 * <p>humi:湿度值(范围:20%~90%)</p>
 * <p>返回值：0,正常;-1,读取失败</p>
 * @param tem
 * @param hum
 * @return
 */
int dht11_get_data(u8 *tem, u8 *hum) {
  int count = 0;
  u8 data[5] = {0};

  u8 i;
  if (0 == dht11_check()) {
    for (i = 0; i < 40; i++) {
      while (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0));//等待低电平结束 50us
      count = 0;
      while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))//等待高电平结束并count计数,通过计数判断当前值为0还是1
      {
        delay10us();
        count++;
      }

      if (count > 5)//高电平
      {
        data[i / 8] |= 1 << (7 - i % 8); //将对应位置1 注意：数据传输时从高到低传输
      }
    }
    delay10ms();

    //数据接收完成之后将PB0管脚模式设置为输出，并数据高电平
    dht11_io_out();//PB0管脚为输出管脚
    GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);//输出高电平
    //判断接收数据是否正确
    if (data[4] != (data[0] + data[1] + data[2] + data[3])) {
      return -1;
    } else {
      *tem = data[2];
      *hum = data[0];
      return 0;
    }
  }
  return -1;
}