//
// Created by NineDollar on 2022/5/13.
//

#include <stdio.h>
#include "dht11.h"
#include "stm32f10x.h"
#include "delay.h"

/**
 * ��ʼ��DHT11��IO��
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
//DHT11����
void dht11_io_in() {
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
//DHT11���
void dht11_io_out() {
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//�ȴ�DHT11�Ļ�Ӧ
int dht11_check() {
  again:
  dht11_io_out(); //PB0�ܽ�����Ϊ����ܽ�
  GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);
  delay10ms();
  GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);

  //��������18ms
  delay10ms();
  delay10ms();
  delay10ms();

  //DQ=1
  GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);

  dht11_io_in(); //PB0�ܽ�����Ϊ����ܽ�
  //��������20~40us
  delay10us();
  delay10us();
  delay10us();

  if (RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))//DHT11������80us
  {
    while (!(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)));  //�ȴ���Ӧ�źŽ���

    while ((GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)));  //DHT11������Ӧ�źź��ٰ���������80us

    return 0;
  } else
    goto again;
}

/**
 * <p>��DHT11��ȡһ������</p>
 * <p>temp:�¶�ֵ(��Χ:0~50��)</p>
 * <p>humi:ʪ��ֵ(��Χ:20%~90%)</p>
 * <p>����ֵ��0,����;-1,��ȡʧ��</p>
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
      while (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0));//�ȴ��͵�ƽ���� 50us
      count = 0;
      while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))//�ȴ��ߵ�ƽ������count����,ͨ�������жϵ�ǰֵΪ0����1
      {
        delay10us();
        count++;
      }

      if (count > 5)//�ߵ�ƽ
      {
        data[i / 8] |= 1 << (7 - i % 8); //����Ӧλ��1 ע�⣺���ݴ���ʱ�Ӹߵ��ʹ���
      }
    }
    delay10ms();

    //���ݽ������֮��PB0�ܽ�ģʽ����Ϊ����������ݸߵ�ƽ
    dht11_io_out();//PB0�ܽ�Ϊ����ܽ�
    GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);//����ߵ�ƽ
    //�жϽ��������Ƿ���ȷ
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