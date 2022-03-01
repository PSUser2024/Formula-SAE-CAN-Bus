//TODO:::
//Packing function "pack" will be multiple of 10 Note:Used to pack 1 or more sensors data into global variable sensorBuf







//SENSORS:::: strain guages, steering angle, coolant temp, accl pos, brake pos, coolant flow
enum{
    strainAll = 0x1;
    steeringAng = 0x2;
    coolantTemp = 0x3;
    acclPos = 0x4;
    brakePos = 0x5;
    coolantFlow = 0x6;
}ID_vals;

//PINS::::::
struct sensorPins{
    int strainFL = 14;
    int strainFR = 15;
    int strainBL = 16;
    int strainBR = 17;
    int steeringAng = 18;
    int coolantTemp = 19;
    int acclPos = 20;
    int brakePos = 21;
    int coolantFlow = 22;
  };

 struct sensorPins Pins; //Use Pins. to access the individual values EX: Pins.strainFL will give you straingFL integer value

int sensorBuf[6];

//FUNCTION: packFunc
//Used
int packFunc(int pack({
  
}

void setup() {
  pinMode(Pins.strainFL, INPUT);
  pinMode(Pins.strainFR, INPUT);
  pinMode(Pins.strainBL, INPUT);
  pinMode(Pins.strainBR, INPUT);
  pinMode(Pins.steeringAng, INPUT);
  pinMode(Pins.coolantTemp, INPUT);
  pinMode(Pins.acclPos, INPUT);
  pinMode(Pins.brakePos, INPUT);
  pinMode(Pins.coolantFlow, INPUT); 
  
}

void loop() {
  
  //Initialize buffer to 0 for debugging ease
  for(int i=0; i<=(sizeof(sensorBuf)/sizeof(sensorBuf[0])); i++){
    sensorBuf[i] = 0;
  } 
  for(int i =0; i < sensorLen; i++){
    int analogVal = analogRead(Pins[i].pinNum);
  }
}
