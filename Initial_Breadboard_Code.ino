#include <Servo.h>

const int analogInPin = A0;

Servo myservo;
int sensorValue = 0;
int outputValue = 0;
int pos = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
}

void loop() {
  sensorValue = analogRead(analogInPin);

  Serial.print("sensor = ");
  Serial.println(sensorValue);

  delay(2);

  if (sensorValue > 100) {
    for (pos = 0; pos <= 180; pos += 1) {
      myservo.write(pos);
      delay(20);
    }
    for (pos = 180; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(20);
    }
  }
}
