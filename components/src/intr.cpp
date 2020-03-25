#include "intr.h"

extern "C" {

  void ISR_LVL2() __attribute__((weak));
  void ISR_LVL3() __attribute__((weak));
  void ISR_LVL4() __attribute__((weak));
  void ISR_LVL5() __attribute__((weak));

}

void ISR_LVL2() {}
void ISR_LVL3() {}
void ISR_LVL4() {}
void ISR_LVL5() {}

void intr_enable(unsigned int interrupt) {
    asm volatile (
		"wsr %0, intenable;"
		"rsync"
		::"r"(interrupt));
}
