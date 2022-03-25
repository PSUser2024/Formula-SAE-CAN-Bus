
#include <FlexCAN_T4.h>

FlexCAN_T4<CAN0, RX_SIZE_256, TX_SIZE_16> can0;
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
CAN_message_t msg;

#ifndef __MK66FX1M0__
  #error "Teensy 3.6 with dual CAN bus is required to run this example"
#endif

uint16_t  CAN_ID =  0x700;    // CAN-Bus ID

float voltage;
uint8_t bytes[sizeof(float)];
unsigned char data[4];
  
void setup() {
  
  Serial.begin(38400);
  
  /*can1.begin();
  
  can1.setBaudRate(500000);   // Data rate 500kbps
  
  can1.setMaxMB(16);
 */ 
 
  
 
  
  can0.begin();
  
  can0.setBaudRate(500000);   // Data rate 500kbps
  
  can0.setMaxMB(16);
  
  
}

void loop() {
  
  
  int x = analogRead(14);
  float voltage = x * (3.3/1023);

  memcpy(bytes, &voltage, sizeof (voltage));
  msg.len = 8;
  msg.id = CAN_ID;

  msg.buf[0] = bytes[0];
  msg.buf[1] = bytes[1];
  msg.buf[2] = bytes[2];
  msg.buf[3] = bytes[3];
  msg.buf[4] = 0;
  msg.buf[5] = 0;
  msg.buf[6] = 0;
  msg.buf[7] = 0;


  can0.write(msg);                      //Transmit the CAN data out

  
  

  
  /*if ( can0.read(msg) ) {
    
    Serial.print("CAN0 Voltage:");
    Serial.print(voltage); 

    Serial.print(" DATA: ");
    
      Serial.print(msg.buf[7]); Serial.print(" ");
    
    Serial.print("  TS: "); Serial.println(msg.timestamp);
  }*/
  
  /*if ( can1.read(msg) ) {
      data[0] = msg.buf[0];
      data[1] = msg.buf[1];
      data[2] = msg.buf[2];
      data[3] = msg.buf[3];

    //memcpy(&voltage, data, 4);
    
    Serial.print("CAN1 "); 
    //Serial.print(voltage,2); 

    Serial.print("   DATA: ");
  for ( uint8_t i = 0; i < msg.len; i++ ) {
    Serial.print(msg.buf[i], HEX); Serial.print(" ");
      
  }
    Serial.print("  TS: "); Serial.println(msg.timestamp);
  }*/
}
