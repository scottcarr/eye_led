#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <stdint.h>

constexpr uint8_t FRAME_SIZE = 8;

class Animation
{
public:
    Animation(const uint8_t **frames,
              uint8_t numFrames,
              uint8_t ticksPerFrame) : mFrames(frames),
                                       mNumFrames(numFrames),
                                       mTicksPerFrame(ticksPerFrame),
                                       mFrameCounter(0),
                                       mIdle(true)
    {
    }

    void begin()
    {
        mTickCounter = 0;
        mFrameCounter = 0;
        mIdle = false;
    }

    void tick()
    {
        mTickCounter++;
        if (mTickCounter > mTicksPerFrame)
        {
            mTickCounter = 0;
            mFrameCounter++;
        }
        if (mFrameCounter == mNumFrames)
        {
            mIdle = true;
            mTickCounter = 0;
            mFrameCounter = 0;
        }
    }

    const uint8_t *getCurrentFrame()
    {
        return mFrames[mFrameCounter];
    }

    bool isIdle()
    {
        return mIdle;
    }

private:
    const uint8_t mTicksPerFrame;
    uint8_t mTickCounter;
    uint8_t mFrameCounter;
    const uint8_t mNumFrames;
    const uint8_t **mFrames;
    bool mIdle;
};

#endif