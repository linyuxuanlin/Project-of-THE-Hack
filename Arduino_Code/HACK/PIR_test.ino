#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT11;

#define PIR_pin 12
#define Buzzer_pin 10
#define Detected 1
#define Undetected 0
#define LED_pin 13
#define Gas_pin 0
#define DHT11_pin 9
#define Fall_pin 8


int Alarm_time = 0;
int Serial_state = 0; // 模式状态：1-PIR,2-Gas
int Mode_state = 0;
int Gas_val; // CO 气体传感变量
float Humidity; // 湿度
float Temperature; // 温度
boolean Fall_state; // 摔倒检测变量

void setup() {
  pinMode(PIR_pin, INPUT);
  pinMode(Buzzer_pin, OUTPUT);
  pinMode(LED_pin, OUTPUT);
  pinMode(Gas_pin, INPUT);
  pinMode(Fall_pin, INPUT);
  Serial.begin(9600);
  Serial.println("hello");

}

void loop() {
  if (Serial.available() > 0) {
    Serial_state = Serial.read() - 48; // 转码
    //Serial.println(Serial_state);
    if (Serial_state == 1)
      Mode_state = 1;
    else if (Serial_state == 2)
      Mode_state = 2;
    else if (Serial_state == 3)
      Mode_state = 3;
    else if (Serial_state == 4)
      Mode_state = 4;
  }
  switch (Mode_state) {
    case 1: //字符1，以下类推
      PIR_func();
      //Serial.println("PIR");
      break;
    case 2:
      Gas_func();
      //Serial.println("Gas");
      break;
    case 3:
      DHT11_func();
      break;
    case 4:
      //Serial.println("fall");
      Fall_func();
      break;
      //default:
      //  break;
  }
  delay(100);
}

// 人体红外检测
void PIR_func() {
  Serial.println(Alarm_time);
  if (digitalRead(PIR_pin) == Undetected)
    Alarm_time++;

  else if (digitalRead(PIR_pin) == Detected)
    Alarm_time = 0;

  if (Alarm_time >= 70) {
    digitalWrite(Buzzer_pin, HIGH);
    delay(500);
    digitalWrite(Buzzer_pin, LOW);
  }
  else
    digitalWrite(Buzzer_pin, LOW);
}

// 一氧化碳检测
void Gas_func() {
  Gas_val = analogRead(Gas_pin);
  Serial.println(Gas_val, DEC);
  if (Gas_val > 890) {
    digitalWrite(Buzzer_pin, HIGH);
    delay(500);
    digitalWrite(Buzzer_pin, LOW);
    delay(500);
  }
  else
    digitalWrite(Buzzer_pin, LOW);
}

// 温湿度检测
void DHT11_func() {
  DHT11.read(DHT11_pin);
  Humidity = DHT11.humidity;
  Temperature = DHT11.temperature;
  Serial.print("Humidity: ");
  Serial.println(Humidity);
  Serial.print("Temperature: ");
  Serial.println(Temperature);
  delay(500);
}

// 摔倒检测
void Fall_func() {
  Fall_state = digitalRead(Fall_pin);
  Serial.println(Fall_state);
  if (Fall_state == 0) {
    Serial.println("Fall !!");
    digitalWrite(Buzzer_pin, HIGH);
    delay(500);
    digitalWrite(Buzzer_pin, LOW);
    delay(500);
    digitalWrite(Buzzer_pin, HIGH);
    delay(500);
    digitalWrite(Buzzer_pin, LOW);
    delay(500);
  } else
    digitalWrite(Buzzer_pin, LOW);
}
