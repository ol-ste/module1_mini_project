#pragma once

class BoardComponent
{
protected:
    u8_t pin;
    bool isInitialized;

public:
    BoardComponent(u8_t pinValue);

    virtual void init() = 0;
};
