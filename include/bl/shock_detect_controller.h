#pragma once

#include "base_controller.h"
#include <hw_access/button.h>
#include <hw_access/led.h>

class ShockDetectController : public BaseController
{
private:
    bool lastSensorState;
    bool shockIndicatorsActivated;

    Button *sensor;
    Led **indicators;
    u8_t indicatorsCount;

public:
    ShockDetectController(Button *sensor, Led *indicators[], u8_t indicatorsCount);

    void init() override;
    void run() override;
};
