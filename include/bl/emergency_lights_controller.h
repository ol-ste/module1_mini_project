#pragma once

#include "base_controller.h"
#include <hw_access/button.h>
#include <hw_access/led.h>

class EmergencyLightsController : public BaseController
{
private:
    bool lastButtonState;

    Button *button;
    Led *frontEmgLight;
    Led *backEmgLight;

public:
    EmergencyLightsController(Button *button, Led *frontEmgLight, Led *backEmgLight);

    void init() override;
    void run() override;
};
