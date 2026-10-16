#include <Arduino.h>
#include "bl/emergency_lights_controller.h"

EmergencyLightsController::EmergencyLightsController(Button *button, Led *frontEmgLight, Led *backEmgLight)
    : button(button), frontEmgLight(frontEmgLight), backEmgLight(backEmgLight)
{
}

void EmergencyLightsController::init()
{
    button->init();
    frontEmgLight->init();
    backEmgLight->init();
}

void EmergencyLightsController::run()
{
    button->poll();

    bool buttonState = button->get_state();
    if (buttonState != lastButtonState)
    {
        lastButtonState = buttonState;
        LedMode modeCandiate = frontEmgLight->get_mode();
        if (lastButtonState)
        {
            if (modeCandiate == LedMode::Off)
            {
                modeCandiate = LedMode::BlinkingSlow;
            }
            else
            {
                modeCandiate = LedMode::Off;
            }
        }

        if (modeCandiate != frontEmgLight->get_mode())
        {
            frontEmgLight->set_mode(modeCandiate);
            backEmgLight->set_mode(modeCandiate);
        }
    }

    frontEmgLight->update();
    backEmgLight->update();
}
