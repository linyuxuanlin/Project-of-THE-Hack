#include "MeOrion.h"

Me7SegmentDisplay disp(PORT_4);
MePotentiometer myPotentiometer(PORT_6);
MeUltrasonicSensor ultraSensor(PORT_3);
MeJoystick joystick(PORT_8);
MeLightSensor lightSensor(PORT_7);

int16_t x = 0;    /* a variable for the Joystick's x value */
int16_t y = 0;    /* a variable for the Joystick's y value */
float angle = 0;       /* The relative angle of XY */
float OffCenter = 0;    /* offset with the center */

int sp[3];

int i = 0;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  /* read the both joystick axis values: */
  x = joystick.readX();
  y = joystick.readY();

  /* print the results to the serial monitor: */
  //    Serial.print("Joystick X = ");
  //    Serial.print(x);
  //    Serial.print("  Joystick Y = ");
  //    Serial.print(y);

  while (lightSensor.read() > 50) {
    Serial.println("请先坐下");
    disp.display(0);
    delay(1000);
  }

  disp.display(ultraSensor.distanceCm());
  while (ultraSensor.distanceCm() < 30) {
    Serial.println("啊啊啊啊太近啦！停下！");
    disp.display(ultraSensor.distanceCm());
    for (int i = 0; i < 4; i++) {
      sp[i] = 0;
    }
    delay(100);
  }

  if (y > 0) {
    sp[0] = y * 0.5;
    sp[1] = 0;
  }
  else {
    y = abs(y);
    sp[1] = y * 0.5;
    sp[0] = 0;
  }

  if (x > 0) {
    sp[3] = x * 0.5;
    sp[2] = 0;
  }
  else {
    x = abs(x);
    sp[2] = x * 0.5;
    sp[3] = 0;
  }

  for (i = 0; i < 4; i++) {
    Serial.print(sp[i]);
    Serial.print(",");
  }
  Serial.println("");

  delay(100);
}
