#include <Wire.h>
#include "eyes.h"
#include "mouth.h"

Mouth mouth;
Eyes eyes;

void setup()
{
    Serial.begin(9600);
    Serial.println("8x8 LED Matrix Test");

    eyes.begin(0x70); // pass in the address
    mouth.begin(0x74);

    eyes.setRotation(3);
    mouth.setRotation(3);

    eyes.neutral();
    mouth.neutral();
}

void loop()
{
    // neutral();
    // neutralMouth();
    // delay(3000);
    // blink();
    // delay(100);
    // smileUp();
    // delay(4000);
    // blink();
    // delay(200);
    // left();
    // delay(100);
    // neutral();
    // delay(3000);
    // blink();
    // delay(200);
    // right();
    // delay(100);
    // neutral();
    // delay(500);
    // smileDown();
    // delay(500);
    // smileUp();
    // delay(500);
    // smileDown();
    // delay(500);
    //blink();

    // smile testing
    /*
    smileUp();
    delay(500);
    smileDown();
    delay(1000);
    */

    if (mouth.isIdle())
    {
        mouth.smile();
    }
    if (eyes.isIdle())
    {
        eyes.blink();
    }
    mouth.tick();
    eyes.tick();
    delay(20);
}