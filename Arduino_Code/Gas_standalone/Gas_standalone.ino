void setup() {
  Serial.begin(9600);

}

void loop() {
  int val;
  val = analogRead(0); //Read Gas value from analog 0    用模拟口A0读取模拟值
  Serial.println(val, DEC); //Print the value to serial port   通过串口打印模拟值
  delay(100);
}
