#include <Arduino.h>
#include "hw_access/config.h"
#include "hw_access/button.h"

Button::Button(u8_t pinValue) : Component(pinValue) {}

bool Button::get_state()
{
    return state;
}

void Button::init()
{
    if (isInitialized)
    {
        return;
    }
    pinMode(pin, INPUT_PULLDOWN);
    isInitialized = true;
}

void Button::poll()
{
    if (millis() - lastTimeChanged > POLL_PERIOD_MS)
    {
        lastTimeChanged = millis();
        u16_t currentState = digitalRead(pin);
        state = currentState == HIGH;
    }
}