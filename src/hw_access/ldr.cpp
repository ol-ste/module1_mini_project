#include <Arduino.h>
#include "hw_access/config.h"
#include "hw_access/ldr.h"

Ldr::Ldr(u8_t pinValue) : BoardComponent(pinValue) {}

u16_t Ldr::get_value()
{
    return normalizedValue;
}

void Ldr::init()
{
    if (isInitialized)
    {
        return;
    }
    pinMode(pin, INPUT);
    u16_t initAdcValue = analogRead(pin);
    filterInit(initAdcValue);
    normalizedValue = initAdcValue;
    isInitialized = true;
}

void Ldr::poll()
{
    if (millis() - lastTimeChanged > POLL_PERIOD_MS)
    {
        lastTimeChanged = millis();
        u16_t adc_value = analogRead(pin);
        normalizedValue = calculateMovingAvg(adc_value);
    }
}

void Ldr::filterInit(u16_t initData)
{
    for (u8_t i = 0; i < WINDOW_SIZE; i++)
    {
        readings[i] = initData;
        sum += readings[i];
    }
}

u16_t Ldr::calculateMovingAvg(u16_t rawData)
{
    sum -= readings[idx];
    sum += rawData;
    readings[idx] = rawData;
    idx++;

    if (idx >= WINDOW_SIZE)
    {
        idx = 0;
    }

    return sum / WINDOW_SIZE;
}
