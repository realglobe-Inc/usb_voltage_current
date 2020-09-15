#define INA226_ADDR 0x40

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);

  if( ina226_init( INA226_ADDR ) ){
    while( 1 ) delay(10);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int16_t buff = 0;
  byte result = 0;

  result = ina226_read_mv( &buff );
  Serial.print( "mv=" );
  if( 0 == result ){
    Serial.print( buff );
  }

  result = ina226_read_ma( &buff );
    Serial.print( ";ma=" );
  if( 0 == result ){
    Serial.print( buff );
  }

  result = ina226_read_mw( &buff );
  Serial.print( ";mw=" );
  if( 0 == result ){
    Serial.print( buff );
  }
  Serial.println( "" );

  delay(1000);
}
