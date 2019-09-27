#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
Adafruit_8x16matrix mouth = Adafruit_8x16matrix();

static const uint8_t PROGMEM
    leftMouth[] =
        {
            B00000000,
            B00000000,
            B00000000,
            B00000000,
            B00001111,
            B00000000,
            B00000000,
            B00000000,
},
    rightMouth[] =
        {
            B00000000,
            B00000000,
            B00000000,
            B00000000,
            B11110000,
            B00000000,
            B00000000,
            B00000000,
};

static const uint8_t PROGMEM
    leftSmile0[] =
        {
            B00000000,
            B00000000,
            B00000000,
            B01000000,
            B00111111,
            B00000000,
            B00000000,
            B00000000,
},
    rightSmile0[] =
        {
            B00000000,
            B00000000,
            B00000000,
            B00000100,
            B11111000,
            B00000000,
            B00000000,
            B00000000,
},
    leftSmile1[] =
        {
            B00000000,
            B00000000,
            B01000000,
            B00100000,
            B00011111,
            B00000000,
            B00000000,
            B00000000,
},
    rightSmile1[] =
        {
            B00000000,
            B00000000,
            B00000010,
            B00000100,
            B11111000,
            B00000000,
            B00000000,
            B00000000,
},
    leftSmile2[] =
        {
            B00000000,
            B00000000,
            B00100000,
            B00010000,
            B00001000,
            B00000111,
            B00000000,
            B00000000,
},
    rightSmile2[] =
        {
            B00000000,
            B00000000,
            B00000100,
            B00001000,
            B00010000,
            B11100000,
            B00000000,
            B00000000,
};

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
        {
            B00111100,
            B01000010,
            B10000001,
            B10011001,
            B10011001,
            B10000001,
            B01000010,
            B00111100,
},
    left_bmp[] =
        {
            B00111100,
            B01000010,
            B10000001,
            B10110001,
            B10110001,
            B10000001,
            B01000010,
            B00111100,
},
    left2_bmp[] =
        {
            B00111100,
            B01000010,
            B10000001,
            B11100001,
            B11100001,
            B10000001,
            B01000010,
            B00111100,
},
    right_bmp[] =
        {
            B00111100,
            B01000010,
            B10000001,
            B10001101,
            B10001101,
            B10000001,
            B01000010,
            B00111100,
},
    right2_bmp[] =
        {
            B00111100,
            B01000010,
            B10000001,
            B10000111,
            B10000111,
            B10000001,
            B01000010,
            B00111100,
},
    blink1_bmp[] =
        {
            B00000000,
            B00000000,
            B00111100,
            B01000010,
            B01000010,
            B00111100,
            B00000000,
            B00000000,
},
    blink2_bmp[] =
        {
            B00000000,
            B00000000,
            B00000000,
            B01111110,
            B01111110,
            B00000000,
            B00000000,
            B00000000,
},
    blink3_bmp[] =
        {
            B00000000,
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

void neutralMouth()
{
    mouth.clear();
    mouth.drawBitmap(0, 0, leftMouth, 8, 16, LED_ON);
    mouth.drawBitmap(7, 0, rightMouth, 8, 16, LED_ON);
    mouth.writeDisplay();
}

void smileUp()
{
    size_t frameTime = 100;
    neutralMouth();
    delay(frameTime);
    mouth.clear();
    mouth.drawBitmap(0, 0, leftSmile0, 8, 16, LED_ON);
    mouth.drawBitmap(8, 0, rightSmile0, 8, 16, LED_ON);
    mouth.writeDisplay();
    delay(frameTime);
    mouth.clear();
    mouth.drawBitmap(0, 0, leftSmile1, 8, 16, LED_ON);
    mouth.drawBitmap(8, 0, rightSmile1, 8, 16, LED_ON);
    mouth.writeDisplay();
    delay(frameTime);
    mouth.clear();
    mouth.drawBitmap(0, 0, leftSmile2, 8, 16, LED_ON);
    mouth.drawBitmap(8, 0, rightSmile2, 8, 16, LED_ON);
    mouth.writeDisplay();
}

void smileDown()
{
    size_t frameTime = 100;
    mouth.clear();
    mouth.drawBitmap(0, 0, leftSmile1, 8, 16, LED_ON);
    mouth.drawBitmap(8, 0, rightSmile1, 8, 16, LED_ON);
    mouth.writeDisplay();
    delay(frameTime);
    mouth.clear();
    mouth.drawBitmap(0, 0, leftSmile0, 8, 16, LED_ON);
    mouth.drawBitmap(8, 0, rightSmile0, 8, 16, LED_ON);
    mouth.writeDisplay();
    delay(frameTime);
    neutralMouth();
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

void setup()
{
    Serial.begin(9600);
    Serial.println("8x8 LED Matrix Test");

    matrix.begin(0x70); // pass in the address
    mouth.begin(0x74);

    matrix.setRotation(3);
    mouth.setRotation(3);

    neutral();
    neutralMouth();
}

void loop()
{
    neutral();
    neutralMouth();
    delay(3000);
    blink();
    delay(100);
    smileUp();
    delay(4000);
    blink();
    delay(200);
    left();
    delay(100);
    neutral();
    delay(3000);
    blink();
    delay(200);
    right();
    delay(100);
    neutral();
    delay(500);
    smileDown();
    delay(500);
    smileUp();
    delay(500);
    smileDown()
    delay(500);
    //blink();

    // smile testing
    /*
    smileUp();
    delay(500);
    smileDown();
    delay(1000);
    */
}
