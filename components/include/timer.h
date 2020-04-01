#ifndef H_NONOS_TIMER
#define H_NONOS_TIMER

#include <registers/struct/timer_struct.h>

typedef enum { GROUP0, GROUP1 } timer_group_t;
typedef enum { TIMER0, TIMER1 } timer_num_t;
typedef enum { DECREASE, INCREASE } timer_dir_t;

class TIMPeriph {
  public:
    TIMPeriph();
    TIMPeriph(timer_group_t group, timer_num_t timer);
    void attach(timer_group_t group, timer_num_t timer);
    void enable() const;
    void disable() const;
    void alarm_en(bool value) const;
    void divider(unsigned int div) const;
    void dir(timer_dir_t dir) const;
    void alarm(unsigned long long value) const;
    void alarm_l(unsigned int value) const;
    void alarm_h(unsigned int value) const;
    void counter(unsigned long long value) const;
    void counter_l(unsigned int value) const;
    void counter_h(unsigned int value) const;

    unsigned long long alarm() const;
    unsigned int alarm_l() const;
    unsigned int alarm_h() const;
    unsigned long long counter() const;
    unsigned int counter_l() const;
    unsigned int counter_h() const;


  private:
    timg_dev_t *timg;
    timer_num_t t_num;

};


inline void TIMPeriph::enable() const { timg->hw_timer[t_num].config.enable = 1; }
inline void TIMPeriph::disable() const { timg->hw_timer[t_num].config.enable = 0; }
inline void TIMPeriph::alarm_en(bool value) const { timg->hw_timer[t_num].config.alarm_en = value; }
inline void TIMPeriph::divider(unsigned int div) const { timg->hw_timer[t_num].config.divider = div; }
inline void TIMPeriph::dir(timer_dir_t dir) const { timg->hw_timer[t_num].config.increase = dir; }

inline void TIMPeriph::alarm(unsigned long long value) const {
  timg->hw_timer[t_num].alarm_low = value;
  timg->hw_timer[t_num].alarm_high = (value >> 32);
}

inline void TIMPeriph::alarm_l(unsigned int value) const { timg->hw_timer[t_num].alarm_low = value; }
inline void TIMPeriph::alarm_h(unsigned int value) const { timg->hw_timer[t_num].alarm_high = value; }

inline void TIMPeriph::counter(unsigned long long value) const {
    timg->hw_timer[t_num].load_low = value;
    timg->hw_timer[t_num].load_high = (value >> 32);
    timg->hw_timer[t_num].reload = 1;
}

inline void TIMPeriph::counter_l(unsigned int value) const {
    timg->hw_timer[t_num].load_low = value;
    timg->hw_timer[t_num].reload = 1;
}

inline void TIMPeriph::counter_h(unsigned int value) const {
    timg->hw_timer[t_num].load_high = value;
    timg->hw_timer[t_num].reload = 1;
}

inline unsigned long long TIMPeriph::alarm() const {
  unsigned long long low_reg = timg->hw_timer[t_num].alarm_low;
  unsigned long long high_reg = timg->hw_timer[t_num].alarm_low;
  return ( (high_reg << 32) | low_reg );
}

inline unsigned int TIMPeriph::alarm_l() const { return timg->hw_timer[t_num].alarm_low; }
inline unsigned int TIMPeriph::alarm_h() const { return timg->hw_timer[t_num].alarm_high; }

inline unsigned long long TIMPeriph::counter() const {
  timg->hw_timer[t_num].update = 1;
  unsigned long long low_reg = timg->hw_timer[t_num].cnt_low;
  unsigned long long high_reg = timg->hw_timer[t_num].cnt_high;
  return ( (high_reg << 32) | low_reg );
}

inline unsigned int TIMPeriph::counter_l() const {
  timg->hw_timer[t_num].update = 1;
  return timg->hw_timer[t_num].cnt_low;
}

inline unsigned int TIMPeriph::counter_h() const {
  timg->hw_timer[t_num].update = 1;
  return timg->hw_timer[t_num].cnt_high;
}


#endif /* H_NONOS_TIMER */
