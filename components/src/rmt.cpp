#include <registers/dport_reg.h>
#include <registers/rmt_reg.h>

#include "rmt.h"

RMTPeriph::RMTPeriph() {}

RMTPeriph::RMTPeriph(rmt_ch_t _ch) {
  //  Enable RMT clock
  *(volatile uint32_t*)DPORT_PERIP_CLK_EN_REG |= DPORT_RMT_CLK_EN;

  //  Disable RMT reset
  *(volatile uint32_t*)DPORT_PERIP_RST_EN_REG &= ~DPORT_RMT_RST;

  RMT.apb_conf.mem_access_en = 1;
  ch = _ch;
  for(int i = 0; i < 64; i++) RMTMEM.ch[ch].data[i].reg = 0;
}

void RMTPeriph::attach(rmt_ch_t _ch) {
  //  Enable RMT clock
  *(volatile uint32_t*)DPORT_PERIP_CLK_EN_REG |= DPORT_RMT_CLK_EN;

  //  Disable RMT reset
  *(volatile uint32_t*)DPORT_PERIP_RST_EN_REG &= ~DPORT_RMT_RST;

  RMT.apb_conf.mem_access_en = 1;
  ch = _ch;
  for(int i = 0; i < 64; i++) RMTMEM.ch[ch].data[i].reg = 0;

}
