#include "MeOrion.h"
#include <SoftwareSerial.h>
#include <Wire.h>



MePIRMotionSensor myPIR(PORT_8);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Val:");
  Serial.println(myPIR.isPeopleDetected());
  
  delay(100);
}
