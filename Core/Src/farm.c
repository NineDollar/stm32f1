//
// Created by NineDollar on 2022/5/14.
//

#include "farm.h"
#include "oled.h"

/**
 * 温(0) 度(1) 湿(2) 度(3) 风(4) 扇(5) 打(6) 开(7) 关(8) 闭(9)
 */

uint8_t tem_x = 0;
uint8_t tem_y = 1;
uint8_t hum_x = 0;
uint8_t hum_y = 4;

/**
 * <p>oled显示</p>
 * 温度:
 */
void show_tem() {
  oled_showchinese(0, 1, 0);
  oled_showchinese(18, 1, 1);
  oled_showstring(36, 2, (uint8_t *) ":", 1);
}

/**
 * 在温度文字后显示温度数字
 * @param num 数字
 */
void show_tem_num(uint32_t num) {
  oled_shownum(46, 1, num, 2, 16);
  oled_showchinese(66, 1, 10);
}

/**
 * <p>oled显示</p>
 * 湿度:
 */
void show_hum() {
  oled_showchinese(0, 4, 2);
  oled_showchinese(18, 4, 3);
  oled_showstring(36, 5, (uint8_t *) ":", 1);
}

/**
 * 在湿度文字后显示湿度数字
 * @param num 数字
 */
void show_hum_num(uint32_t num) {
  oled_shownum(46, 4, num, 2, 16);
  oled_showstring(65, 4, (uint8_t *) "hp", 16);
}

/**
 * <p>oled显示</p>
 * 风扇:
 */
void show_fun() {
  oled_showchinese(86, 1, 4);
  oled_showchinese(104, 1, 5);
}

/**
 * oled显示“打开”
 */
void show_fun_open() {
  oled_showchinese(86, 4, 6);
  oled_showchinese(104, 4, 7);
}

void show_fun_close() {
  oled_showchinese(86, 4, 8);
  oled_showchinese(104, 4, 9);
}

void show_user_tmp(uint32_t user_tmp) {
  oled_showstring(0, 0, (unsigned char *) "tmp", 12);
  OLED_ShowChar(24, 0, ':', 12);
  oled_shownum(31, 0, user_tmp, 2, 12);
}

void show_user_hum(uint32_t user_hum) {
  oled_showstring(75, 0, (unsigned char *) "hmp", 12);
  OLED_ShowChar(100, 0, ':', 12);
  oled_shownum(107, 0, user_hum, 2, 12);
}


