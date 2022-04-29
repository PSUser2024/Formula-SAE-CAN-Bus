#include <FlexCAN_T4.h>
#include "SPI.h"
#include "ILI9341_t3.h"
#include <ILI9341_T4.h>
#include "font_Arial.h"

#define TFT_DC  9
#define TFT_CS 10

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
CAN_message_t msg;
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

uint16_t ch1temp;
uint8_t bytes[sizeof(float)];
unsigned char data[4];
uint16_t id_hex;
float temp = 0;
float previoustemp = 0; 
char tempChar[10];
char motor_speedChar[10];
char sensorValueChar[10];
float motor_speed = 0;
float previous_motor_speed = 0;

float sensorPin = A0;
float sensorValue = 0;
float previous_sensorValue=0;

void setup() {
  pinMode(sensorPin, INPUT);
  tft.begin();
  can1.begin();
  can1.setBaudRate(1000000); // data rate of temp sensor & set for motor controller
  
// Note: you can now set the SPI speed to any value
// the default value is 30Mhz, but most ILI9341 displays
// can handle at least 60Mhz and as much as 100Mhz
  tft.setClock(30000000);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.setRotation(1);
  tft.println("This Showcases Multiple   functions of the VCU.");
  
  
  Serial.begin(250000);
  

/*if (msg.id == 1204){
      tft.print(msg.id, HEX);
      tft.print("   ");
      */
} 



void loop() {
  float safe = analogRead(sensorPin);
  safe = safe*3.3/1023;
  Serial.println(safe);
  if (safe > 2){
  tft.fillRect(50,60,80,30,ILI9341_RED);
  }
  else{
  tft.fillRect(50,60,80,30,ILI9341_GREEN);
  }
 
  
  if(sensorValue != previous_sensorValue)
  { 
    previous_sensorValue = sensorValue;
    String sensorValueString = String(sensorValue,2);
    sensorValueString.toCharArray(sensorValueChar,10);
    
    tft.fillRect(50,190,100,30,ILI9341_BLACK);
    printText(sensorValueChar, ILI9341_WHITE,50,190,4);
    
    
    }
  
  
  
  
  printText("rpm", ILI9341_WHITE,180,100,4);
  printText("Saftey Circuit", ILI9341_WHITE,140,60,2);
  printText("Volts", ILI9341_WHITE,180,190,4);
  
  if (can1.read(msg)) {
    /*if (msg.id==0xA0){Serial.println(msg.id,HEX);}
    if (msg.id==0xA1){Serial.println(msg.id,HEX);}
    if (msg.id==0xA2){Serial.println(msg.id,HEX);}
    if (msg.id==0xA3){Serial.println(msg.id,HEX);}
    if (msg.id==0xA4){Serial.println(msg.id,HEX);}
    if (msg.id==0xA5){Serial.println(msg.id,HEX);}
    if (msg.id==0xA6){Serial.println(msg.id,HEX);}
    if (msg.id==0xA7){Serial.println(msg.id,HEX);}
    if (msg.id==0xA8){Serial.println(msg.id,HEX);}
    if (msg.id==0xA9){Serial.println(msg.id,HEX);}
    */
    //Motor controller can stuff
    
    if(msg.id == 0x0A5){
      motor_speed = (msg.buf[3] *256) + msg.buf[2];
      if(motor_speed != previous_motor_speed && motor_speed <2001)
  {
    
    previous_motor_speed = motor_speed;
    String motor_speedString = String(motor_speed,1);
    motor_speedString.toCharArray(motor_speedChar,10);
    
    tft.fillRect(50,100,110,30,ILI9341_BLACK);
    printText(motor_speedChar, ILI9341_WHITE,50,100,4);
    
    
    }
   }
    
    if(msg.id == 0x4B4){
      data[0] = msg.buf[0];
      data[1] = msg.buf[1];
      data[2] = msg.buf[2];
      data[3] = msg.buf[3];
      data[4] = msg.buf[4];
      data[5] = msg.buf[5];
      data[6] = msg.buf[6];
      data[7] = msg.buf[7];

   ch1temp = (data[2]*256)+ data[3]; 
   temp = ((ch1temp / 10) - 100);
   if(temp != previoustemp)
  {
    
    previoustemp = temp;
    String tempString = String(temp,1);
    tempString.toCharArray(tempChar,10);
    tft.fillRect(10,150,200,30,ILI9341_BLACK);
    printText(tempChar, ILI9341_WHITE,50,150,4);
    printText("o", ILI9341_WHITE,230,145,3);
    printText("C", ILI9341_WHITE,250,150,4);
      }
    }
  }
}

void printText(char *text, uint16_t color, int x, int y,int textSize)
{
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.setTextWrap(true);
  tft.print(text);
}
