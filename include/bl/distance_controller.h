#pragma once

#include "base_controller.h"
#include <hw_access/ldr.h>
#include <hw_access/led.h>

class DistanceController : public BaseController
{
private:
    static constexpr u16_t CLOSE_DISTANCE_THRESHOLD = 2700;
    static constexpr u16_t VERY_CLOSE_DISTANCE_THRESHOLD = 1700;
    static constexpr u16_t CRITICAL_CLOSE_DISTANCE_THRESHOLD = 1100;

    Ldr *sensor;
    Led *indicator;

public:
    DistanceController(Ldr *sensor, Led *indicator);

    void init() override;
    void run() override;
};
