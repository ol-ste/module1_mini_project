#pragma once

class Component
{
protected:
    u8_t pin;
    bool isInitialized;

public:
    Component(u8_t pinValue);

    virtual void init() = 0;
};
