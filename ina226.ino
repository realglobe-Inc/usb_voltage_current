#include <Wire.h>

#define CONFIG_DEFAULT     0x4127
#define CONFIG             CONFIG_DEFAULT
#define RESISTER_MILLI_OHM 2
#define CALIB              ( 5120 / RESISTER_MILLI_OHM )

#define REG_CONFIG     0x00
#define REG_CALIB      0x05

static uint8_t suc_addr = 0;

byte ina226_init( uint8_t addr ){
  byte result = 0;

  suc_addr = addr;
  Wire.begin();
  delay(10);

  result = ina226_write( REG_CONFIG, CONFIG );
  if( result ) return result;
  return ina226_write( REG_CALIB, CALIB );
}

byte ina226_write( uint8_t reg, uint16_t data ){
  Wire.beginTransmission( suc_addr );
  Wire.write( reg );
  Wire.write( (uint8_t)( data >> 8 ) );
  Wire.write( (uint8_t)( data & 0xFF ) );
  return Wire.endTransmission();
}
