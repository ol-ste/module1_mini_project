#include <Arduino.h>
#include "bl/headlight_controller.h"

HeadlightController::HeadlightController(Ldr *sensor, Led *headlight)
    : sensor(sensor), headlight(headlight)
{
}

void HeadlightController::init()
{
    sensor->init();
    headlight->init();
}

void HeadlightController::run()
{
    sensor->poll();

    u16_t sensorValue = sensor->get_value();
    LedMode modeCandidate = headlight->get_mode();

    if (sensorValue > TURNON_LIGHT_THRESHOLD)
    {
        modeCandidate = LedMode::Off;
    }
    else
    {
        modeCandidate = LedMode::Steady;
    }

    if (modeCandidate != headlight->get_mode())
    {
        headlight->set_mode(modeCandidate);
    }
    headlight->update();
}
