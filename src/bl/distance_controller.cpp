#include <Arduino.h>
#include "bl/distance_controller.h"

DistanceController::DistanceController(Ldr *sensor, Led *indicator)
    : sensor(sensor), indicator(indicator)
{
}

void DistanceController::init()
{
    sensor->init();
    indicator->init();
}

void DistanceController::run()
{
    sensor->poll();

    u16_t sensorValue = sensor->get_value();
    LedMode modeCandidate = indicator->get_mode();

    if (sensorValue > CLOSE_DISTANCE_THRESHOLD)
    {
        modeCandidate = LedMode::Off;
    }
    if (sensorValue <= CLOSE_DISTANCE_THRESHOLD && sensorValue > VERY_CLOSE_DISTANCE_THRESHOLD)
    {
        modeCandidate = LedMode::BlinkingSlow;
    }
    if (sensorValue <= VERY_CLOSE_DISTANCE_THRESHOLD && sensorValue > CRITICAL_CLOSE_DISTANCE_THRESHOLD)
    {
        modeCandidate = LedMode::BlinkingFast;
    }
    if (sensorValue <= CRITICAL_CLOSE_DISTANCE_THRESHOLD)
    {
        modeCandidate = LedMode::Steady;
    }

    if (modeCandidate != indicator->get_mode())
    {
        indicator->set_mode(modeCandidate);
    }
    indicator->update();
}
