// Servo Header File
#include <Servo.h>

// Sensor Pin
const int analogInPin = A0;

// Initialize Servo Object
Servo myservo;

// Initialize Sensor Input/Servo Position Output Int Variables
int sensorValue = 0;
int pos = 0;

// Sets up debugging Serial and Servo Controller Pin
void setup() {
  Serial.begin(9600);
  myservo.attach(9);
}

void loop() {
  // Read Sensor Input
  sensorValue = analogRead(analogInPin);

  // Displays sensor value in Serial Monitor
  Serial.print("sensor = ");
  Serial.println(sensorValue);

  // Sample Rate = 2ms
  delay(2);

  // Sensor Threshold to Actuate Servo
  if (sensorValue > 100) {
    // Servo Actuation Rotates Servo back and forth once
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
