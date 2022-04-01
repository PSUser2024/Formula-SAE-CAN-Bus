#include <FlexCAN_T4.h>
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
CAN_message_t msg;

// CAN-Bus ID

uint16_t ch1temp;
uint8_t bytes[sizeof(float)];
unsigned char data[4];
  
void setup() {
  
  Serial.begin(115200);
  
  can1.begin();
  
  can1.setBaudRate(1000000);   // Data rate 500kbps
  
  //can1.onReceive(canSniff);
  
}

void loop() {
  //canSniff(msg);
  if (can1.read(msg)) {
    if(msg.id == 0x4B4){

    
      Serial.print(msg.id);
      Serial.print("   ");
      data[1] = msg.buf[0];
      data[0] = msg.buf[1];
      data[2] = msg.buf[2];
      data[3] = msg.buf[3];
      data[4] = msg.buf[4];
      data[5] = msg.buf[5];
      data[6] = msg.buf[6];
      data[7] = msg.buf[7];
    //Serial.print(msg.id);

      memcpy(&ch1temp, data, 2);
Serial.println(ch1temp, HEX);
Serial.println("Hi");
   //ch1temp = data[0] << 8;
   //ch1temp = ch1temp || data[1]; 
   int temp = ((ch1temp / 10) - 100);
   Serial.println("hello");
   Serial.println(temp);
   Serial.println("Hey");
 
    
    //memcpy(&temp, data, 8);
    //Serial.println(temp);
    
  /*  Serial.print("  CAN1 Current Sensor Voltage: "); 
    Serial.print(voltage,2); 

    Serial.print("V   DATA: ");
  for ( uint8_t i = 0; i < msg.len; i++ ) {
    Serial.print(msg.buf[i], HEX); Serial.print(" ");
      
  }
    Serial.print("  TS: "); Serial.println(msg.timestamp);
    */
  }
  }
delay(50);
}
void canSniff (const CAN_message_t &msg){ // Global callback to catch any CAN frame coming in
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
    
}
