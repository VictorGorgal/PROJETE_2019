#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
 
MAX30105 particleSensor;

const int MPU_ADDR = 0x68;
int16_t accelerometer_x, accelerometer_y, accelerometer_z;
char tmp_str[7];
char* convert_int16_to_str(int16_t i) {
sprintf(tmp_str, "%6d", i);
 return tmp_str; 
}
 
const byte RATE_SIZE = 10; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
long tempo;
 
float beatsPerMinute;
int beatAvg;
int med;

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);
 
void setup(){
Serial.begin(9600);
mySerial.begin(9600);
pinMode(12, OUTPUT);

Wire.begin();
Wire.beginTransmission(MPU_ADDR);
Wire.write(0x6B);
Wire.write(0); 
Wire.endTransmission(true);

particleSensor.begin(Wire, I2C_SPEED_FAST); //Use default I2C port, 400kHz speed
particleSensor.setup(); //Configure sensor with default settings
particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
tempo=millis();
}

 
void loop(){

Wire.beginTransmission(MPU_ADDR);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU_ADDR, 7*2, true);

accelerometer_x = Wire.read()<<8 | Wire.read();
accelerometer_y = Wire.read()<<8 | Wire.read();
accelerometer_z = Wire.read()<<8 | Wire.read();

med = (accelerometer_x + accelerometer_y + accelerometer_z) / 3;

long irValue = particleSensor.getIR();
 
if (checkForBeat(irValue) == true){
  digitalWrite(12, HIGH);
  delay(15);
  digitalWrite(12, LOW);

long delta = millis() - lastBeat;
lastBeat = millis();
 
beatsPerMinute = 60 / (delta / 1000.0);
 
if (beatsPerMinute < 255 && beatsPerMinute > 20){
  rates[rateSpot++] = (byte)beatsPerMinute;
  rateSpot %= RATE_SIZE;
 

beatAvg = 0;
for (byte x = 0 ; x < RATE_SIZE ; x++)
  beatAvg += rates[x];
  beatAvg /= RATE_SIZE;
    }
  }

 if((millis()-tempo)>1000)
 {
Serial.print(beatAvg);
mySerial.print(beatAvg);
Serial.print(",");
mySerial.print(",");
Serial.println(med);
mySerial.print(med);
mySerial.print(".");
tempo=millis();
 }
}
