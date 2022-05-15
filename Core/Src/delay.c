#include "stm32f10x.h"
void delay(u32 time) {
  int i = 0;
  for (i = 0; i < 8050 * time; i++) {
  }
}

void my_delay(int n) {
  int i = 0;
  while (n--)
    for (i = 0; i < 8050; i++);
}

void delay10us() {
  int i = 100;
  while (i--);
}

void delay10ms() {
  int n = 10, i;
  while (n--)
    for (i = 0; i < 8050; i++);
}


