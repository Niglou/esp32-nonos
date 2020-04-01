#include "timer.h"

TIMPeriph::TIMPeriph() {}

TIMPeriph::TIMPeriph(timer_group_t group, timer_num_t timer) {
  if(group == GROUP0) timg = &TIMERG0;
  else if(group == GROUP1) timg = &TIMERG1;
  t_num = timer;
}

void TIMPeriph::attach(timer_group_t group, timer_num_t timer) {
  if(group == GROUP0) timg = &TIMERG0;
  else if(group == GROUP1) timg = &TIMERG1;
  t_num = timer;
}
