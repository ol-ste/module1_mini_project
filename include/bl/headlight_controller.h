#pragma once

#include "base_controller.h"
#include <hw_access/ldr.h>
#include <hw_access/led.h>

class HeadlightController : public BaseController
{
private:
    static constexpr u16_t TURNON_LIGHT_THRESHOLD = 2700;

    Ldr *sensor;
    Led *headlight;

public:
    HeadlightController(Ldr *lightsSensor, Led *headlight);

    void init() override;
    void run() override;
};
