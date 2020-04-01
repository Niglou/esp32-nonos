#ifndef H_NONOS_I2C
#define H_NONOS_I2C

#include <registers/struct/i2c_struct.h>

typedef enum { I2C_SLAVE, I2C_MASTER } i2c_mode_t;
typedef enum { I2C0_PERIPH, I2C1_PERIPH } i2c_num_t;
typedef enum { I2C_MSB_FIRST, I2C_LSB_FIRST, SAMPLE_SCL_HIGH=0, SAMPLE_SCL_LOW } i2c_data_t;
typedef enum { DIRECT, OPEN_DRAIN } i2c_pin_t;
typedef enum { I2C_START, I2C_WRITE, I2C_READ, I2C_STOP, I2C_END } i2c_cmd_t;

class I2CPeriph {
    public:
        I2CPeriph(i2c_num_t _num);

        void mode(i2c_mode_t mode) const;
        void data_mode(i2c_data_t sample_scl_level, i2c_data_t rx, i2c_data_t tx) const;
        void pin_mode(i2c_pin_t scl, i2c_pin_t sda) const;

        void period(int low_period, int high_period) const;
        void data_timing(int sample_time, int hold_time) const;
        void start_timing(int setup_time, int hold_time) const;
        void stop_timing(int setup_time, int hold_time) const;

        void cmd(int index, i2c_cmd_t cmd, int byte_num, bool check=0, bool ack_value=0) const;
        void data(int data) const;
        int data() const;

        void trans_start() const;
        int  trans_check() const;

    private:
        i2c_dev_t *i2c;
};


inline void I2CPeriph::mode(i2c_mode_t mode) const { (*i2c).ctr.ms_mode = mode; }

inline void I2CPeriph::data_mode(i2c_data_t sample_scl_level, i2c_data_t rx, i2c_data_t tx) const {
    (*i2c).ctr.sample_scl_level = sample_scl_level;
    (*i2c).ctr.rx_lsb_first = rx;
    (*i2c).ctr.tx_lsb_first = tx;
}
inline void I2CPeriph::pin_mode(i2c_pin_t scl, i2c_pin_t sda) const {
    (*i2c).ctr.scl_force_out = scl;
    (*i2c).ctr.sda_force_out = sda;
}
inline void I2CPeriph::period(int low_period, int high_period) const {
    (*i2c).scl_low_period.period = low_period;
    (*i2c).scl_high_period.period = high_period; }

inline void I2CPeriph::data_timing(int sample_time, int hold_time) const {
    (*i2c).sda_sample.time = sample_time;
    (*i2c).sda_hold.time = hold_time;
}
inline void I2CPeriph::start_timing(int setup_time, int hold_time) const {
    (*i2c).scl_rstart_setup.time = setup_time;
    (*i2c).scl_start_hold.time = hold_time;
}
inline void I2CPeriph::stop_timing(int setup_time, int hold_time) const {
    (*i2c).scl_stop_setup.time = setup_time;
    (*i2c).scl_stop_hold.time = hold_time;
}
inline void I2CPeriph::cmd(int index, i2c_cmd_t cmd, int byte_num, bool check, bool ack_value) const {
    (*i2c).command[index].byte_num = byte_num;
    (*i2c).command[index].ack_en = check;
    (*i2c).command[index].ack_exp = 0;
    (*i2c).command[index].ack_val = ack_value;
    (*i2c).command[index].op_code = cmd;
}
inline void I2CPeriph::data(int data) const { (*i2c).fifo_data.data = data; }
inline int  I2CPeriph::data() const { return (*i2c).fifo_data.data; }
inline void I2CPeriph::trans_start() const { (*i2c).ctr.trans_start = 1; }
inline int  I2CPeriph::trans_check() const { return (*i2c).ctr.trans_start; }


#endif
