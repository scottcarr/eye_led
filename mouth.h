#include "Adafruit_LEDBackpack.h"
#include "Animation.h"
//Adafruit_8x16matrix mouth = Adafruit_8x16matrix();

namespace
{

static const uint8_t ticksPerFrame = 5;

static const uint8_t PROGMEM leftSmile[][8] =
    {
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
        {
            B00000000,
            B00000000,
            B00100000,
            B00010000,
            B00001000,
            B00000111,
            B00000000,
            B00000000,
        }};

static const uint8_t PROGMEM rightSmile[][8] =
    {
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
        {
            B00000000,
            B00000000,
            B00000100,
            B00001000,
            B00010000,
            B11100000,
            B00000000,
            B00000000,
        }};

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

static const uint8_t *smileFramesLeft[] =
    {
        leftMouth,
        leftSmile[0],
        leftSmile[1],
        leftSmile[2],
        leftSmile[1],
        leftSmile[0],
        leftMouth};

static const uint8_t *smileFramesRight[] =
    {
        rightMouth,
        rightSmile[0],
        rightSmile[1],
        rightSmile[2],
        rightSmile[1],
        rightSmile[0],
        rightMouth};
} // end anonymous namespace

class Mouth
{
public:
    Mouth() : mSmileAnimationLeft(smileFramesLeft,
                                  sizeof(smileFramesLeft) / 2,
                                  ticksPerFrame),
              mSmileAnimationRight(smileFramesRight,
                                   sizeof(smileFramesRight) / 2,
                                   ticksPerFrame)
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
        matrix.drawBitmap(0, 0, leftMouth, 8, 16, LED_ON);
        matrix.drawBitmap(7, 0, rightMouth, 8, 16, LED_ON);
        matrix.writeDisplay();
    }
    void smile()
    {
        matrix.clear();
        mSmileAnimationLeft.begin();
        mSmileAnimationRight.begin();
    }

    void drawFrame()
    {
        matrix.clear();
        matrix.drawBitmap(0, 0, mSmileAnimationLeft.getCurrentFrame(), 8, 16, LED_ON);
        matrix.drawBitmap(7, 0, mSmileAnimationRight.getCurrentFrame(), 8, 16, LED_ON);
        matrix.writeDisplay();
    }

    bool isIdle()
    {
        return mSmileAnimationLeft.isIdle() && mSmileAnimationRight.isIdle();
    }

    void tick()
    {
        if (!isIdle())
        {
            drawFrame();
            mSmileAnimationLeft.tick();
            mSmileAnimationRight.tick();
        }
    }

private:
    Animation mSmileAnimationLeft;
    Animation mSmileAnimationRight;
    Adafruit_8x16matrix matrix;
};
