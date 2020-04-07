
#include "adc.h"

ADCPeriph::ADCPeriph() {}

ADCPeriph::ADCPeriph(adc_unit_t unit)
{
  if(unit == RTC_ADC_1) {
    SENS.sar_read_ctrl.sar1_dig_force = false;      //RTC controller controls the ADC, not digital controller
    SENS.sar_meas_start1.meas1_start_force = true;  //RTC controller controls the ADC,not ulp coprocessor
    SENS.sar_meas_start1.sar1_en_pad_force = true;  //RTC controller controls the data port, not ulp coprocessor
    SENS.sar_touch_ctrl1.xpd_hall_force = true;     // RTC controller controls the hall sensor power,not ulp coprocessor
    SENS.sar_touch_ctrl1.hall_phase_force = true;   // RTC controller controls the hall sensor phase,not ulp coprocessor
    adc1_fsm_disable();
  }
  else if(unit == RTC_ADC_2) {
    SENS.sar_read_ctrl.sar1_dig_force = false;      //RTC controller controls the ADC, not digital controller
    SENS.sar_meas_start2.meas2_start_force = true;  //RTC controller controls the ADC,not ulp coprocessor
    SENS.sar_meas_start2.sar2_en_pad_force = true;  //RTC controller controls the data port, not ulp coprocessor

  }
  _unit = unit;
}

void ADCPeriph::attach(adc_unit_t unit)
{
  if(unit == RTC_ADC_1) {
    SENS.sar_read_ctrl.sar1_dig_force = false;      //RTC controller controls the ADC, not digital controller
    SENS.sar_meas_start1.meas1_start_force = true;  //RTC controller controls the ADC,not ulp coprocessor
    SENS.sar_meas_start1.sar1_en_pad_force = true;  //RTC controller controls the data port, not ulp coprocessor
    SENS.sar_touch_ctrl1.xpd_hall_force = true;     // RTC controller controls the hall sensor power,not ulp coprocessor
    SENS.sar_touch_ctrl1.hall_phase_force = true;   // RTC controller controls the hall sensor phase,not ulp coprocessor
    adc1_fsm_disable();
  }
  else if(unit == RTC_ADC_2) {
    SENS.sar_read_ctrl2.sar2_dig_force = false;      //RTC controller controls the ADC, not digital controller
    SENS.sar_meas_start2.meas2_start_force = true;  //RTC controller controls the ADC,not ulp coprocessor
    SENS.sar_meas_start2.sar2_en_pad_force = true;  //RTC controller controls the data port, not ulp coprocessor
    SENS.sar_read_ctrl2.sar2_pwdet_force = false;   //RTC controller controls the ADC, not PWDET
    SYSCON.saradc_ctrl.sar2_mux = true;             //RTC controller controls the ADC, not PWDET
  }
  _unit = unit;
}

void ADCPeriph::set_width(adc_bits_width_t bits) const
{
  if(_unit == RTC_ADC_1) {
    SENS.sar_start_force.sar1_bit_width = bits;
    SENS.sar_read_ctrl.sar1_sample_bit = bits;
    SENS.sar_read_ctrl.sar1_data_inv = 1;
  }
  else if(_unit == RTC_ADC_2) {
    SENS.sar_start_force.sar2_bit_width = bits;
    SENS.sar_read_ctrl2.sar2_sample_bit = bits;
    SENS.sar_read_ctrl2.sar2_data_inv = 1;
  }
}

void ADCPeriph::set_channel_atten(adc_channel_t channel, adc_atten_t atten) const
{
  if(_unit == RTC_ADC_1) {
    SENS.sar_atten1 = ( atten << (channel*2));
  }
  else if(_unit == RTC_ADC_2) {
    SENS.sar_atten2 = ( atten << (channel*2));
  }
}

unsigned short ADCPeriph::get_raw(adc_channel_t channel) const
{
  if(_unit == RTC_ADC_1) {
    SENS.sar_meas_start1.sar1_en_pad = (1 << channel); // select channel
    SENS.sar_meas_start1.meas1_start_sar = 0;
    SENS.sar_meas_start1.meas1_start_sar = 1;
    while (SENS.sar_meas_start1.meas1_done_sar == 0);
    return SENS.sar_meas_start1.meas1_data_sar;
  }
  else if(_unit == RTC_ADC_2) {
    SENS.sar_meas_start2.sar2_en_pad = (1 << channel); // select channel
    SENS.sar_meas_start2.meas2_start_sar = 0;
    SENS.sar_meas_start2.meas2_start_sar = 1;
    while (SENS.sar_meas_start2.meas2_done_sar == 0);
    return SENS.sar_meas_start2.meas2_data_sar;
  }
  return 0;
}

void ADCPeriph::start_async(adc_channel_t channel) const
{
  if(_unit == RTC_ADC_1) {
    while (SENS.sar_meas_start1.meas1_done_sar == 0);
    SENS.sar_meas_start1.sar1_en_pad = (1 << channel); // select channel
    SENS.sar_meas_start1.meas1_start_sar = 0;
    SENS.sar_meas_start1.meas1_start_sar = 1;
  }
  else if (_unit == RTC_ADC_2) {
    while (SENS.sar_meas_start2.meas2_done_sar == 0);
    SENS.sar_meas_start2.sar2_en_pad = (1 << channel); // select channel
    SENS.sar_meas_start2.meas2_start_sar = 0;
    SENS.sar_meas_start2.meas2_start_sar = 1;
  }
}

unsigned short ADCPeriph::get_raw_async() const
{
  if(_unit == RTC_ADC_1) {
    while (SENS.sar_meas_start1.meas1_done_sar == 0);
    return SENS.sar_meas_start1.meas1_data_sar;
  }
  else if (_unit == RTC_ADC_2) {
    while (SENS.sar_meas_start2.meas2_done_sar == 0);
    return SENS.sar_meas_start2.meas2_data_sar;
  }
  return 0;
}

void ADCPeriph::adc1_fsm_disable() const
{
  //channel is set in the  convert function
  SENS.sar_meas_wait2.force_xpd_amp = 2;
  //disable FSM, it's only used by the LNA.
  SENS.sar_meas_ctrl.amp_rst_fb_fsm = 0;
  SENS.sar_meas_ctrl.amp_short_ref_fsm = 0;
  SENS.sar_meas_ctrl.amp_short_ref_gnd_fsm = 0;
  SENS.sar_meas_wait1.sar_amp_wait1 = 1;
  SENS.sar_meas_wait1.sar_amp_wait2 = 1;
  SENS.sar_meas_wait2.sar_amp_wait3 = 1;
}
