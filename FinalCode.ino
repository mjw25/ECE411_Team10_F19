/**********************************************************************
   File Name:     "FinalCode.ino"
   Project:       Hide & Seek Box
   Engineers:     Se Min Park, Zoe DeFreitas, Matt Wilson
   Revision:      3.0
   Date Revised:  12/10/2019
   Date Created:  12/09/2019

   Description:   This code enables an Atmega328P-PU processor loaded
                  with Arduino Uno bootloader to take a binary sensor
                  volume input and outputs a smile or frown to an
                  8x8 LED Dot Matrix I2C Driver using I2C communication
                  protocol through the Adafruit_LEDBackpack library.
 **********************************************************************/

// Includes all necesary libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// Defines Sound Sensor Input Pin
#define soundSensor 10

// Instantiates the LED Dot Matrix Object
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

// Setup Function
void setup() {
  // Sets up controller to send serial data for debugging
  Serial.begin(9600);

  // Sets up the LED Dot Matrix
  matrix.begin(0x70);

  // Sets up the Sound Sensor input pin
  pinMode(soundSensor, INPUT);
}

// Initializes global boolean for storing Sound Sensor polling results
bool soundInput = false;

// Sets up the following definitions to be stored in Flash
static const uint8_t PROGMEM
//Define Smiling Face
smiling[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
},
//Define Frowning Face
frowning[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01000010,
  B00111100
};

//Function to initiate frowning
void Frown() {
  // Writes Frown to LED Matrix
  matrix.clear(); // Clear LED
  matrix.drawBitmap(0, 0, frowning, 8, 8, LED_ON); // Send Frown to module
  matrix.writeDisplay(); // Display Frown
  matrix.setRotation(0); // Dot Matrix Rotation

  // Delays from changing from frown to smile by 5 seconds
  // + resets time if Volume Sensor is triggered again
  for (int t = 0; t < 50; t++) {
    // Polling Rate = 10 polls/s
    delay(100);
    // Reads Sound Sensor input
    soundInput = digitalRead(soundSensor);
    // Resets timer if sensor is triggered
    if (soundInput == true)
      Frown();
  }
  return;
}

//Function to initiate smiling
void Smile() {
  // Writes smile to LED
  matrix.clear(); // Clear LED
  matrix.drawBitmap(0, 0, smiling, 8, 8, LED_ON); // Send Smile to module
  matrix.writeDisplay(); // Display Smile
  return;
}

// Main Loop Function
void loop() {
  // Poll Volume Sensor for Volume Threshold Trigger
  soundInput = digitalRead(soundSensor);

  // If Volume Sensor is triggered, display Frown, else display Smile
  if (soundInput == true)
    Frown();
  else
    Smile();
}
