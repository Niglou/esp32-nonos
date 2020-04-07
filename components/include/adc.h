#ifndef H_NONOS_ADC
#define H_NONOS_ADC

#include <registers/struct/sens_struct.h>
#include <registers/struct/syscon_struct.h>

typedef enum {
    RTC_ADC_1   = 0,
    RTC_ADC_2
} adc_unit_t;

typedef enum {
    ADC_ATTEN_DB_0   = 0,  // The input voltage of ADC will be reduced to about 1/1
    ADC_ATTEN_DB_2_5 = 1,  // The input voltage of ADC will be reduced to about 1/1.34
    ADC_ATTEN_DB_6   = 2,  // The input voltage of ADC will be reduced to about 1/2
    ADC_ATTEN_DB_11  = 3,  // The input voltage of ADC will be reduced to about 1/3.
    ADC_ATTEN_MAX,
} adc_atten_t;

typedef enum {
    ADC_WIDTH_BIT_9  = 0, // ADC capture width is 9Bit
    ADC_WIDTH_BIT_10 = 1, // ADC capture width is 10Bit
    ADC_WIDTH_BIT_11 = 2, // ADC capture width is 11Bit
    ADC_WIDTH_BIT_12 = 3, // ADC capture width is 12Bit
    ADC_WIDTH_MAX,
} adc_bits_width_t;

typedef enum {
    ADC_CHANNEL_0 = 0, /*!< ADC channel */
    ADC_CHANNEL_1,     /*!< ADC channel */
    ADC_CHANNEL_2,     /*!< ADC channel */
    ADC_CHANNEL_3,     /*!< ADC channel */
    ADC_CHANNEL_4,     /*!< ADC channel */
    ADC_CHANNEL_5,     /*!< ADC channel */
    ADC_CHANNEL_6,     /*!< ADC channel */
    ADC_CHANNEL_7,     /*!< ADC channel */
    ADC_CHANNEL_8,     /*!< ADC channel */
    ADC_CHANNEL_9,     /*!< ADC channel */
    ADC_CHANNEL_MAX,
} adc_channel_t;


class ADCPeriph
{
  public:

    ADCPeriph();
    ADCPeriph(adc_unit_t unit);
    void attach(adc_unit_t unit);
    void set_width(adc_bits_width_t bits) const;
    void set_channel_atten(adc_channel_t channel, adc_atten_t atten) const;
    void hall_enable(bool enable) const;
    void start_async(adc_channel_t channel) const;

    unsigned short get_raw(adc_channel_t channel) const;
    unsigned short get_raw_async() const;


  private:

    adc_unit_t _unit;
    void adc1_fsm_disable() const;


};

#endif
