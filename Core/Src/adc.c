//
// Created by NineDollar on 2022/5/13.
//

#include "adc.h"
#include "stm32f10x.h"

void adc1_init(void) {
  //ADC结构体变量
  ADC_InitTypeDef ADC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  //1. 上电 使ADC能够工作
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);

  //2.GPIO 配置	PA1 ADC12_IN1
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  //模拟输入
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  ADC_DeInit(ADC1);

  //ADC1 和 ADC2 工作在独立模式
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  //模数转换工作在扫描模式（多通道）还是单次（单通道）模式
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  //模数转换工作在连续模式
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  //转换由软件控制而不是外部触发启动
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  //ADC数据向右边对齐
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  //转换通道为1
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  //初始化ADC
  ADC_Init(ADC1, &ADC_InitStructure);

  //ADC1选择信道1,音序等级1,采样时间55.5个周期
  //设置指定ADC的规则组通道，设置它们的转化顺序和采样时间
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);

  //使能ADC
  ADC_Cmd(ADC1, ENABLE);

  //使能ADCx软件启动注入组转换功能
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

uint32_t adc_check(void) {
  uint16_t ResultVolt = 0;
  uint8_t i;

  for (i = 0; i < 8; i++) {
    //等待转换完成
    while (RESET == ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    //返回最近一次ADC 规则组的转换结果
    ResultVolt += ADC_GetConversionValue(ADC1);
  }
  //求平均值
  ResultVolt = ResultVolt / 8;
  //计算对应的电压 基准电压为3.3V，12位AD对应的最大数字量为4096(2^12)。所以 adc x/ResultVolt = 3.3/4096得到 adc x
  ResultVolt = (ResultVolt * 3300) / 4096;
  return ResultVolt;
}