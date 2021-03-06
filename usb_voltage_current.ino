#define INA226_ADDR 0x40

#define STATUS_OK 0

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
  Serial.print( "voltage=" );
  if( 0 == result ){
    Serial.print( buff );
  }

  result = ina226_read_ma( &buff );
    Serial.print( ";current=" );
  if( 0 == result ){
    Serial.print( buff );
  }

  result = ina226_read_mw( &buff );
  Serial.print( ";power=" );
  if( 0 == result ){
    Serial.print( buff );
  }
  Serial.print(";status=");
  Serial.print(STATUS_OK);
  Serial.print("\n");

  delay(1000);
}
