#include <Arduino.h>
#include "bl/shock_detect_controller.h"

ShockDetectController::ShockDetectController(Button *sensor, Led *indicators[], u8_t indicatorsCount)
    : sensor(sensor),
      indicators(indicators),
      indicatorsCount(indicatorsCount)
{
}

void ShockDetectController::init()
{
    sensor->init();
    for (u8_t i = 0; i < indicatorsCount; i++)
    {
        indicators[i]->init();
    }
}

void ShockDetectController::run()
{
    sensor->poll();

    bool sensorState = sensor->get_state();
    if (sensorState != lastSensorState)
    {
        lastSensorState = sensorState;
        if (lastSensorState)
        {
            if (!shockIndicatorsActivated)
            {
                for (u8_t i = 0; i < indicatorsCount; i++)
                {
                    indicators[i]->set_mode(LedMode::BlinkingFast);
                    indicators[i]->set_allowModeChange(false);
                }
                shockIndicatorsActivated = true;
            }
            else
            {
                for (u8_t i = 0; i < indicatorsCount; i++)
                {
                    indicators[i]->set_allowModeChange(true);
                    indicators[i]->set_mode(LedMode::Off);
                }
                shockIndicatorsActivated = false;
            }
        }
    }

    for (u8_t i = 0; i < indicatorsCount; i++)
    {
        indicators[i]->update();
    }
}
