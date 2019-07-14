#define PIR_pin 12
#define Buzzer_pin 10
#
#define Detected 1
#define Undetected 0

int alarm_time = 0;

void setup() {
  pinMode(PIR_pin, INPUT);
  pinMode(Buzzer_pin, OUTPUT);
  Serial.begin(9600);
  Serial.println("hello");

}

void loop() {
  Serial.println(alarm_time);
  if (digitalRead(PIR_pin) == Undetected)
    alarm_time++;

  else if (digitalRead(PIR_pin) == Detected)
    alarm_time = 0;

  if (alarm_time >= 70) {
    digitalWrite(Buzzer_pin, HIGH);
    delay(500);
    digitalWrite(Buzzer_pin, LOW);
  }
  else
    digitalWrite(Buzzer_pin, LOW);


  delay(50);
}
