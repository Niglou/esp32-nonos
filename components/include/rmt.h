#ifndef H_NONOS_RMT
#define H_NONOS_RMT

#include <registers/struct/rmt_struct.h>

typedef enum { CHANNEL_0, CHANNEL_1, CHANNEL_2, CHANNEL_3, CHANNEL_4, CHANNEL_5, CHANNEL_6, CHANNEL_7 } rmt_ch_t;
typedef enum { TRANSMITTER, RECEIVER } rmt_mode_t;
typedef enum { REF_TICK, APB_CLK } rmt_clk_t;
typedef enum { RMT_DIS, RMT_EN } rmt_bool_t;

class RMTPeriph {
  public:
    RMTPeriph();
    RMTPeriph(rmt_ch_t _ch);
    void attach(rmt_ch_t);
    void mode(rmt_mode_t mode) const;
    void clock(rmt_clk_t clk) const;
    void divider(unsigned int div) const;
    void conti_mode(rmt_bool_t mode) const;
    void carrier(rmt_bool_t state) const;
    void idle_en(rmt_bool_t en) const;
    void idle_lvl(rmt_bool_t high) const;
    void data(unsigned int sel, unsigned int data) const;
    void rst_pos_trans() const;
    void rst_pos_receiv() const;
    void start() const;

    unsigned int* buffer() const;

  private:
    rmt_ch_t ch;

};


inline void RMTPeriph::mode(rmt_mode_t mode) const { RMT.conf_ch[ch].conf1.mem_owner = mode; }
inline void RMTPeriph::clock(rmt_clk_t clk) const { RMT.conf_ch[ch].conf1.ref_always_on = clk; }
inline void RMTPeriph::divider(unsigned int div) const { RMT.conf_ch[ch].conf0.div_cnt = div; }
inline void RMTPeriph::conti_mode(rmt_bool_t mode) const { RMT.conf_ch[ch].conf1.tx_conti_mode = mode; }
inline void RMTPeriph::carrier(rmt_bool_t state) const { RMT.conf_ch[ch].conf0.carrier_en = state; }
inline void RMTPeriph::idle_en(rmt_bool_t en) const { RMT.conf_ch[ch].conf1.idle_out_en = en; }
inline void RMTPeriph::idle_lvl(rmt_bool_t high) const { RMT.conf_ch[ch].conf1.idle_out_lv = high; }
inline void RMTPeriph::data(unsigned int sel, unsigned int data) const { RMTMEM.ch[ch].data[sel].reg = data; }
inline void RMTPeriph::rst_pos_trans() const {
  RMT.conf_ch[ch].conf1.mem_rd_rst = 1;
  RMT.conf_ch[ch].conf1.mem_rd_rst = 0;
}

inline void RMTPeriph::rst_pos_receiv() const {
  RMT.conf_ch[ch].conf1.mem_wr_rst = 1;
  RMT.conf_ch[ch].conf1.mem_wr_rst = 0;
}

inline void RMTPeriph::start() const {
  RMT.conf_ch[ch].conf1.tx_start = 1;
}
inline unsigned int* RMTPeriph::buffer() const {
  return (unsigned int*)(RMTMEM.ch[ch].data);
}

#endif
