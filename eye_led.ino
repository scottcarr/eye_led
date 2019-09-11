#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

static const uint8_t PROGMEM
//  neutral_bmp[] =
//  { B00000000,
//    B00011000,
//    B00100100,
//    B01000010,
//    B01000010,
//    B00100100,
//    B00011000,
//    B00000000,
//  },
  neutral_bmp[] =
  { B00111100,
    B01000010,
    B10000001,
    B10011001,
    B10011001,
    B10000001,
    B01000010,
    B00111100,
  },
  left_bmp[] =
  { B00111100,
    B01000010,
    B10000001,
    B10110001,
    B10110001,
    B10000001,
    B01000010,
    B00111100,
  },
  left2_bmp[] =
  { B00111100,
    B01000010,
    B10000001,
    B11100001,
    B11100001,
    B10000001,
    B01000010,
    B00111100,
  },
  right_bmp[] =
  { B00111100,
    B01000010,
    B10000001,
    B10001101,
    B10001101,
    B10000001,
    B01000010,
    B00111100,
  },
  right2_bmp[] =
  { B00111100,
    B01000010,
    B10000001,
    B10000111,
    B10000111,
    B10000001,
    B01000010,
    B00111100,
  },
  blink1_bmp[] =
  { B00000000,
    B00000000,
    B00111100,
    B01000010,
    B01000010,
    B00111100,
    B00000000,
    B00000000,
  },  
  blink2_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B01111110,
    B01111110,
    B00000000,
    B00000000,
    B00000000,
  },
  blink3_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B01111110,
    B00000000,
    B00000000,
    B00000000,
  };

void blink()
{
  size_t delayTime = 40;
  matrix.clear();
  matrix.drawBitmap(0, 0, blink1_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(delayTime);
  
  matrix.clear();
  matrix.drawBitmap(0, 0, blink2_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(delayTime);
  
  matrix.clear();
  matrix.drawBitmap(0, 0, blink3_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(delayTime);

  matrix.clear();
  matrix.drawBitmap(0, 0, blink2_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(delayTime);

  matrix.clear();
  matrix.drawBitmap(0, 0, blink1_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(delayTime);

  matrix.clear();
  matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(delayTime);
}

void neutral()
{
  matrix.clear();
  matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
}

void left()
{
  matrix.clear();
  matrix.drawBitmap(0, 0, left_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(100);
  matrix.clear();
  matrix.drawBitmap(0, 0, left2_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(100);
  matrix.clear();
  matrix.drawBitmap(0, 0, left_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
}

void right()
{
  matrix.clear();
  matrix.drawBitmap(0, 0, right_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(100);
  matrix.clear();
  matrix.drawBitmap(0, 0, right2_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(100);
  matrix.clear();
  matrix.drawBitmap(0, 0, right_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
}

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  
  matrix.begin(0x70);  // pass in the address

  matrix.setRotation(3);
  neutral();
}

void loop() {
  neutral();
  delay(3000);
  blink();
  delay(4000);
  blink();
  delay(2000);
  left();
  delay(100);
  neutral();
  delay(1000);
  blink();
  delay(3000);
  right();
  delay(100);
  //blink();
}
