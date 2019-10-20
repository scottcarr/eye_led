#include "Adafruit_LEDBackpack.h"
#include "animation.h"

//Adafruit_8x8matrix eyes = Adafruit_8x8matrix();

static const uint8_t PROGMEM
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

static const uint8_t *blinkFrames[] =
    {
        blink1_bmp,
        blink2_bmp,
        blink3_bmp,
        blink2_bmp,
        blink1_bmp,
        neutral_bmp};

class Eyes
{
public:
    Eyes() : mBlinkAnimation(blinkFrames, sizeof(blinkFrames) / 2, 2 /*ticksPerFrame*/)
    {
    }

    void begin(uint8_t address)
    {
        matrix.begin(address);
    }

    void setRotation(uint8_t rotation)
    {
        matrix.setRotation(rotation);
    }

    void neutral()
    {
        matrix.clear();
        matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
        matrix.writeDisplay();
    }

    void blink()
    {
        mBlinkAnimation.begin();
    }

    void tick()
    {
        const uint8_t *frame = nullptr;
        if (mBlinkAnimation.isIdle())
        {
            cooldown_timer--;
        }
        else
        {

            frame = mBlinkAnimation.getCurrentFrame();
            mBlinkAnimation.tick();
        }

        if (frame != nullptr)
        {
            matrix.clear();
            matrix.drawBitmap(0, 0, frame, 8, 8, LED_ON);
            matrix.writeDisplay();
            cooldown_timer = 100;
        }
    }

    bool isIdle()
    {
        return cooldown_timer == 0 && mBlinkAnimation.isIdle();
    }

private:
    Adafruit_8x8matrix matrix;
    Animation mBlinkAnimation;
    unsigned int cooldown_timer = 0;
};

// void left()
// {
//     eyes.clear();
//     eyes.drawBitmap(0, 0, left_bmp, 8, 8, LED_ON);
//     eyes.writeDisplay();
//     delay(100);
//     eyes.clear();
//     eyes.drawBitmap(0, 0, left2_bmp, 8, 8, LED_ON);
//     eyes.writeDisplay();
//     delay(100);
//     eyes.clear();
//     eyes.drawBitmap(0, 0, left_bmp, 8, 8, LED_ON);
//     eyes.writeDisplay();
// }

// void right()
// {
//     eyes.clear();
//     eyes.drawBitmap(0, 0, right_bmp, 8, 8, LED_ON);
//     eyes.writeDisplay();
//     delay(100);
//     eyes.clear();
//     eyes.drawBitmap(0, 0, right2_bmp, 8, 8, LED_ON);
//     eyes.writeDisplay();
//     delay(100);
//     eyes.clear();
//     eyes.drawBitmap(0, 0, right_bmp, 8, 8, LED_ON);
//     eyes.writeDisplay();
// }