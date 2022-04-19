//在这里VRx(x)连的是模拟端口0，VRy(y)连的是模拟端口1，SW(z)连接到了数字端口7

#include <hcsr04.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 12
#define ECHO_PIN 13
#define Photoelectric_PIN 5
#define Buzzer_PIN 6

#define RocksX_PIN A0
#define RocksY_PIN A1

#define Front_PIN 1
#define Back_PIN 2
#define Left_PIN 3
#define Right_PIN 4

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int value1, value2, speed = 0;
String value3 ;

void setup()
{
  Serial.begin(9600);
  lcd.init(); // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SmartHelperCar");
  lcd.setCursor(2, 1);
  lcd.print("THE Hack 2019!");
}
void loop()
{

  while (!digitalRead(Photoelectric_PIN))
    ;

  digitalWrite(Buzzer_PIN, HIGH);
  delay(50);
  digitalWrite(Buzzer_PIN, LOW);

  lcd.clear();
  lcd.print("Welcome!");
  delay(1000);

  value1 = analogRead(RocksX_PIN);
  Serial.print("X:");
  Serial.print(value1, DEC);

  if (value1 < 127)
  {
    lcd.setCursor(3, 0);
    lcd.print("Turn Left");
    analogWrite(Left_PIN, value1 * 2);
  }
  else
  {
    lcd.setCursor(3, 0);
    lcd.print("Turn Right");
    int value11 = value1 - 127;
    analogWrite(Right_PIN, value11 * 2);
  }

  value2 = analogRead(RocksY_PIN);
  Serial.print("Y:");
  Serial.print(value2, DEC);

  if (value2 < 127)
  {
    lcd.setCursor(3, 0);
    lcd.print("Forward");
    analogWrite(Front_PIN, value2 * 2);
  }
  else
  {
    lcd.setCursor(3, 0);
    lcd.print("Back");
    int value21 = value2 - 127;
    analogWrite(Back_PIN, value21 * 2);
  }
  delay(100);

  value3 = hcsr04.ToString();
  if (value3 < 40)
  {
    for (int i = 0; i < 3; i++)
    {
      digitalWrite(Buzzer_PIN, HIGH);
      delay(50);
      digitalWrite(Buzzer_PIN, LOW);
      delay(50);
    }
    for (int i = 0; i < 4; i++)
    {
      analogWrite(i, 0);
    }
  }
}

void startgo(int s)
{
  if(s>speed)
  {
    for (int i = speed; i < s; i++)
    {
      return i;
    }
  }
  else
  {
    for (int i = speed; i > speed; i--)
    {
      return i;
    }
  }
}
