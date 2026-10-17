#pragma once

#include "component.h"

class Button : public Component
{
private:
    u32_t lastTimeChanged = 0;
    bool state = false;

public:
    Button(u8_t pinValue);

    bool get_state();
    void init() override;
    void poll();
};
