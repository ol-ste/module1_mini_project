#pragma once

#include "component.h"

class Ldr : public Component
{
private:
    static constexpr u8_t WINDOW_SIZE = 4;

    u16_t readings[WINDOW_SIZE];
    u8_t idx = 0;
    u32_t sum = 0;

    u16_t normalizedValue = 0;
    u32_t lastTimeChanged = 0;

    u16_t calculateMovingAvg(u16_t rawData);
    void filterInit(u16_t initData);

public:
    Ldr(u8_t pinValue);

    u16_t get_value();
    void init() override;
    void poll();
};