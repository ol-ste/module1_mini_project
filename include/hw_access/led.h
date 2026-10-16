#pragma once

#include "board_component.h"
#include "led_mode.h"

class Led : BoardComponent
{
private:
    static constexpr u16_t BLINKING_SLOW_PERIOD_MS = 500;
    static constexpr u16_t BLINKING_FAST_PERIOD_MS = 50;

    LedMode currentMode = LedMode::Off;
    u16_t currentBlinkingPeriod = BLINKING_SLOW_PERIOD_MS;

    bool state;
    bool allowModeChange = true;

    u32_t lastTimeChanged = 0;

    void activateSteadyMode();
    void activateOnceMode();
    void activateBlinkingSlowMode();
    void activateBlinkingFastMode();
    void deactivate();

public:
    Led(u8_t pinValue);

    void init() override;
    LedMode get_mode();
    void set_mode(LedMode mode);
    void set_allowModeChange(bool allowModeChange);
    void update();
};
