#include <Wire.h>
#include <Arduino.h>

#define ADC_CHANNEL 0 // Microphone on Analog pin 0
uint16_t minSample = 0xFFFF;
uint16_t maxSample = 0;
uint16_t samples = 0;

ISR(ADC_vect, ISR_BLOCK)
{ // ADC conversion complete

    // Save old sample from 'in' position to xfade buffer:
    //   buffer1[nSamples + xf] = buffer1[in];
    //   buffer2[nSamples + xf] = buffer2[in];
    //   if(++xf >= XFADE) xf = 0;

    // Store new value in sample buffers:
    // int buffer1in = ADCL; // MUST read ADCL first!
    // int buffer2in = ADCH;

    // Serial.println(buffer1in);
    // Serial.println(buffer2in);

    // newSum += abs((((int)buffer2in << 8) | buffer1in) - 512);
    uint16_t sample = ADC;
    samples++;
    if (sample < minSample)
    {
        minSample = sample;
    }
    if (sample > maxSample)
    {
        maxSample = sample;
    }
    //   if(++in >= nSamples) {
    //     in     = 0;
    //     oldsum = (uint8_t)((newsum / nSamples) >> 1); // 0-255
    //     newsum = 0L;
    //   }
    // if (newSum != 511)
    // {
    //     Serial.println("newSum:");
    //     Serial.println(newSum);
    // }

    // newSum = 0;
}

class Microphone
{
public:
    Microphone()
    {
    }
    void startADC()
    {
        // Start up ADC in free-run mode for audio sampling:
        DIDR0 |= _BV(ADC0D);              // Disable digital input buffer on ADC0
        ADMUX = bit(REFS0) | ADC_CHANNEL; // Channel sel, right-adj, AREF to 3.3V regulator
        ADCSRB = 0;                       // Free-run mode
        ADCSRA = _BV(ADEN) |              // Enable ADC
                 _BV(ADSC) |              // Start conversions
                 _BV(ADATE) |             // Auto-trigger enable
                 _BV(ADIE) |              // Interrupt enable
                 _BV(ADPS2) |             // 128:1 prescale...
                 _BV(ADPS1) |             //  ...yields 125 KHz ADC clock...
                 _BV(ADPS0);              //  ...13 cycles/conversion = ~9615 Hz
        sei();
    }
};
