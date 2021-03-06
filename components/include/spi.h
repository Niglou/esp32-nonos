#ifndef H_NONOS_SPI
#define H_NONOS_SPI

#include <registers/struct/spi_struct.h>

// Phase
#define SPI_CMD   0x10
#define SPI_ADDR  0x8
#define SPI_DUMMY 0x4
#define SPI_MISO  0x2
#define SPI_MOSI  0x1

typedef enum { SPI0_PERIPH, SPI1_PERIPH, SPI2_PERIPH, SPI3_PERIPH } spi_periph_t;
typedef enum { MASTER, SLAVE } spi_mode_t;
typedef enum { MSB_FIRST, LSB_FIRST } spi_bit_order_t;
typedef enum { SPI_LITTE_ENDIAN, SPI_BIG_ENDIAN } spi_byte_order_t;
typedef enum { SPI_DIS, SPI_EN } spi_bool_t;
typedef enum { NORMAL, FULLDUPLEX } spi_com_t;
typedef enum { LOW, HIGH } spi_edge_t;
typedef enum { NONE, MOSI, MISO } spi_buf_t;
typedef enum { SPI_READ_QIO, SPI_READ_DIO, SPI_READ_QUAD, SPI_READ_DUAL, SPI_READ_FAST, SPI_READ_SLOW } spi_read_t;

class SPIPeriph {
  public:
    SPIPeriph();
    SPIPeriph(spi_periph_t _spi);
    void attach(spi_periph_t _spi);
    void mode(spi_mode_t mode) const;
    void bit_order(spi_bit_order_t write, spi_bit_order_t read) const;
    void byte_order(spi_byte_order_t write, spi_byte_order_t read) const;
    void phase(unsigned int phase) const;
    void keep_cs(bool value) const;
    void cmd(unsigned int cmd) const;
    void addr_h(unsigned int addr) const;
    void addr_l(unsigned int addr) const;
    void cmd_len(unsigned int len) const;
    void dummy_len(unsigned int len) const;
    void addr_len(unsigned int len) const;
    void mosi_len(unsigned int len) const;
    void miso_len(unsigned int len) const;
    void full_duplex(spi_com_t full_duplex) const;
    void read_mode(spi_read_t mode) const;
    void clk_sys(bool sys) const;
    void pre_div(unsigned int div) const;
    void clkcnt(unsigned int cnt) const;
    void clkcnt(unsigned int cnt, unsigned int cnt_l, unsigned int cnt_h) const;
    void clk_edge_idle(spi_edge_t edge) const;
    void clk_miso_delay(unsigned int mode, unsigned int num) const;
    void clk_mosi_delay(unsigned int mode, unsigned int num) const;
    void cs_setup(bool en, unsigned int value = 1) const;
    void cs_hold(bool en, unsigned int value = 1) const;
    void buf_highpart(spi_buf_t highpart) const;
    void buffer(unsigned int index, unsigned int data) const;
    void clear_all_buffer() const;
    void transfer() const;

    unsigned int mode() const;
    unsigned int cmd() const;
    unsigned int addr() const;
    unsigned int* buffer() const;
    unsigned int buffer(unsigned int read) const;
    unsigned int transfer_status() const;

  private:
    spi_dev_t *spi;
};

inline unsigned int SPIPeriph::mode() const { return (*spi).slave.slave_mode; }
inline unsigned int SPIPeriph::addr() const { return (*spi).addr; }
inline unsigned int* SPIPeriph::buffer() const { return (unsigned int*)&((*spi).data_buf); }
inline unsigned int SPIPeriph::buffer(unsigned int read) const { return (*spi).data_buf[(read & 0xF)]; }
inline unsigned int SPIPeriph::transfer_status() const { return (*spi).cmd.usr; }


#endif
