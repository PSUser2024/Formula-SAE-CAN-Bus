#include <FlexCAN_T4.h>
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
CAN_message_t msg;

// CAN-Bus ID

float voltage;
uint8_t bytes[sizeof(float)];
unsigned char data[4];
  
void setup() {
  
  Serial.begin(9600);
  
  can1.begin();
  
  can1.setBaudRate(500000);   // Data rate 500kbps
  
  can1.setMaxMB(16);
}

void loop() {
   
  if (can1.read(msg) ) {
    //canSniff(msg);
      
      data[0] = msg.buf[0];
      data[1] = msg.buf[1];
      data[2] = msg.buf[2];
      data[3] = msg.buf[3];
    //Serial.print(msg.id);
    
    memcpy(&voltage, data, 4);
    
    Serial.print("CAN1 Current Sensor Voltage: "); 
    Serial.print(voltage,2); 

    Serial.print("V   DATA: ");
  for ( uint8_t i = 0; i < msg.len; i++ ) {
    Serial.print(msg.buf[i], HEX); Serial.print(" ");
      
  }
    Serial.print("  TS: "); Serial.println(msg.timestamp);
  }


delay(50);
}
/*void canSniff (const CAN_message_t &msg){ // Global callback to catch any CAN frame coming in
  Serial.println(" ");
  Serial.print("MB: ");
  Serial.print(msg.mb);
  Serial.print("  ID: 0x");
  Serial.print(msg.id, HEX);
  Serial.print("  EXT: ");
  Serial.print(msg.flags.extended);
  Serial.print("  LEN: ");
  Serial.print(msg.len);
  Serial.print(" DATA: ");
  for (uint8_t i = 0; i < 8; i++)
    {
      Serial.print(msg.buf[i], HEX);
      Serial.print(" ");
    }
    
}*/
