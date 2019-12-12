#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  matrix.begin(0x70);  
}

static const uint8_t PROGMEM
  smiling[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
  frowning[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 };
    
void loop() {
  matrix.clear();
  matrix.drawBitmap(0, 0, smiling, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(700);
  
  matrix.clear();
  matrix.drawBitmap(0, 0, frowning, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(700); 
  matrix.setRotation(0);
}
