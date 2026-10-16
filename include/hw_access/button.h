#pragma once

#include "board_component.h"

class Button : public BoardComponent
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
