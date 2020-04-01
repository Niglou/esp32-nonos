#include "i2c.h"

I2CPeriph::I2CPeriph(i2c_num_t _num) {
    if(_num == I2C0_PERIPH) i2c = &I2C0;
    else if(_num == I2C1_PERIPH) i2c = &I2C1;
    else i2c = &I2C0;
    (*i2c).ctr.val = 0;
    (*i2c).ctr.clk_en = 1;
    (*i2c).timeout.tout = 400000; }
