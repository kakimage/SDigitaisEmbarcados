
#ifndef __I2C__
#define __I2C__
#include <stdint.h>

 void i2c_init(uint8_t scl, uint8_t sda);
  void i2c_start(void );
   void i2c_stop(void );
   uint8_t i2c_le_byte (void);
    uint8_t i2c_escreve_byte (uint8_t dado);

#endif
