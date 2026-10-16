#include <Arduino.h>
#include "hw/board_config.h"
#include "hw_access/led.h"
#include "hw_access/ldr.h"
#include "hw_access/button.h"
#include "bl/distance_controller.h"
#include "bl/headlight_controller.h"
#include "bl/emergency_lights_controller.h"
#include "bl/shock_detect_controller.h"

#define CONTROLLERS_COUNT 4

Led distanceIndicator(LED_BLUE_PIN);
Ldr distanceSensor(LDR_LEFT_PIN);

Ldr lightsSensor(LDR_RIGHT_PIN);
Led headlight(LED_WHITE_PIN);

Button emergencyButton(BTN_RIGHT_PIN);
Led frontEmergencyLight(LED_YELLOW_RIGHT_PIN);
Led backEmergencyLight(LED_YELLOW_LEFT_PIN);

Button shockSensor(BTN_LEFT_PIN);
Led *allIndicators[] = {&distanceIndicator, &headlight, &frontEmergencyLight, &backEmergencyLight};

DistanceController distanceController(&distanceSensor, &distanceIndicator);
HeadlightController headlightController(&lightsSensor, &headlight);
EmergencyLightsController emergencyLightsController(&emergencyButton, &frontEmergencyLight, &backEmergencyLight);
ShockDetectController shockDetectorControllr(&shockSensor, allIndicators, 4);

BaseController *controllers[CONTROLLERS_COUNT] = {&distanceController, &headlightController, &emergencyLightsController, &shockDetectorControllr};

void setup()
{
  Serial.begin(115200);

  for (u8_t i = 0; i < CONTROLLERS_COUNT; i++)
  {
    controllers[i]->init();
  }
  Serial.println("Started...");
}

void loop()
{
  for (u8_t i = 0; i < CONTROLLERS_COUNT; i++)
  {
    controllers[i]->run();
  }
}