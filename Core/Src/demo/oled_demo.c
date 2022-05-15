//
// Created by NineDollar on 2022/5/14.
//
#include "stm32f10x.h"

/*
int main() {
  u8 t;
  my_delay(8000);
  oled_init();            //初始化OLED
  OLED_Clear();

  t = ' ';
  OLED_ShowCHinese(30, 0, 0);//华
  OLED_ShowCHinese(48, 0, 1);//清
  OLED_ShowCHinese(66, 0, 2);//远
  OLED_ShowCHinese(84, 0, 3);//见
  while (true) {
    oled_clear();
    OLED_ShowCHinese(30, 0, 0);//华
    OLED_ShowCHinese(48, 0, 1);//清
    OLED_ShowCHinese(66, 0, 2);//远
    oled_showchinese(84, 0, 3);//见
    OLED_ShowString(6, 3, (u8 *) "0.96' OLED TEST", 16);
    OLED_ShowString(0, 6, (u8 *) "ASCII:", 16);
    OLED_ShowChar(48, 6, t, 16);//显示ASCII字符
    oled_showstring(63, 6, (u8 *) "CODE:", 16);
    oled_shownum(103, 6, t, 3, 16);//显示ASCII字符的码值
    t++;
    if (t > '~') t = ' ';
    my_delay(2000);
    OLED_DrawBMP(0, 0, 128, 8, BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
    my_delay(2000);
  }
}*/
