#include <Arduino.h>
#include "hw_access/led.h"

Led::Led(u8_t pinValue) : BoardComponent(pinValue) {}

void Led::init()
{
    if (isInitialized)
    {
        return;
    }
    pinMode(pin, OUTPUT);
    deactivate();
    isInitialized = true;
}

LedMode Led::get_mode()
{
    return currentMode;
}

void Led::set_mode(LedMode mode)
{
    if (!allowModeChange)
    {
        return;
    }
    currentMode = mode;
    lastTimeChanged = millis();

    switch (mode)
    {
    case LedMode::Steady:
        activateSteadyMode();
        break;
    case LedMode::BlinkingSlow:
        activateBlinkingSlowMode();
        break;
    case LedMode::BlinkingFast:
        activateBlinkingFastMode();
        break;
    case LedMode::Off:
        deactivate();
    default:
        deactivate();
        break;
    }
}

void Led::set_allowModeChange(bool allowModeChangeValue)
{
    allowModeChange = allowModeChangeValue;
}

void Led::update()
{
    if (currentMode != LedMode::Off && currentMode != LedMode::Steady)
    {
        if (millis() - lastTimeChanged > currentBlinkingPeriod)
        {
            lastTimeChanged = millis();
            state = !state;
            digitalWrite(pin, state ? HIGH : LOW);
        }
    }
}

void Led::activateSteadyMode()
{
    state = 1;
    digitalWrite(pin, HIGH);
}

void Led::activateBlinkingSlowMode()
{
    state = 1;
    currentBlinkingPeriod = BLINKING_SLOW_PERIOD;
    digitalWrite(pin, HIGH);
}

void Led::activateBlinkingFastMode()
{
    state = 1;
    currentBlinkingPeriod = BLINKING_FAST_PERIOD;
    digitalWrite(pin, HIGH);
}

void Led::deactivate()
{
    state = 0;
    digitalWrite(pin, LOW);
}