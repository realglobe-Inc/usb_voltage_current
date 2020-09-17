#include <Wire.h>

#define CONFIG_DEFAULT     0x4127
#define CONFIG             CONFIG_DEFAULT
#define RESISTER_MILLI_OHM 2
#define CALIB              ( 5120 / RESISTER_MILLI_OHM )
#define LSB_BUS            1.25
#define LSB_POWER          25

#define REG_CONFIG         0x00
#define REG_BUSV           0x02
#define REG_POWER          0x03
#define REG_CURRENT        0x04
#define REG_CALIB          0x05

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

byte ina226_read_mv( int16_t *data ){
  uint16_t buff = 0;
  byte result = 0;

  result = ina226_read( REG_BUSV, (uint16_t*) &buff );
  if( result ) return result;

  *data = buff * LSB_BUS;

  return 0;
}

byte ina226_read_mw( int16_t *data ){
  int16_t buff = 0;
  byte result = 0;

  result = ina226_read( REG_POWER, (uint16_t*) &buff );
  if( result ) return result;

  *data = buff * LSB_POWER;
  return 0;
}

byte ina226_read_ma( int16_t *data ){
  uint16_t buff = 0;
  byte result = 0;

  return ina226_read( REG_CURRENT, (uint16_t*)data );
}

byte ina226_write( uint8_t reg, uint16_t data ){
  Wire.beginTransmission( suc_addr );
  Wire.write( reg );
  Wire.write( (uint8_t)( data >> 8 ) );
  Wire.write( (uint8_t)( data & 0xFF ) );
  return Wire.endTransmission();
}

byte ina226_read( uint8_t reg, uint16_t *data ){
  byte result = 0;

  Wire.beginTransmission( suc_addr );
  Wire.write( reg );
  result = Wire.endTransmission();
  if( result ) return result;
//  delay(5);

  Wire.requestFrom( suc_addr, sizeof(*data) );
  result = Wire.available();
  if( result != sizeof(*data) ){
    return result;
  }

  *data = 0;
  for( uint8_t i = 0; i < sizeof(*data); i++ ){
    *data <<= 8;
    *data |= Wire.read();
  }

  return 0;
}
