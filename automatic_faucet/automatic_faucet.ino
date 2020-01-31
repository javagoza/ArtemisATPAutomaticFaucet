/* Author: Enrique Albertos

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include <Wire.h>
#include "BLE_level_controller.h"
#include "faucet_controller.h"
#include "faucet_microspeech.h"
#include "faucet_proximity_sensor.h"
#include "Arduino.h"
#include "main_functions.h"

#define DEBOUNCE_COUNT 10

enum State
{
  IDLE = 0,
  ONLY_LEVEL = 1,
  OPEN = 2,
  BLUETOOTH = 3
};
enum State actualState = IDLE;

// Globals, used for compatibility with Arduino-style sketches.
namespace
{
FaucetMicrospeech *faucetMicrospeech = nullptr;
FaucetController *faucetController = nullptr;
FaucetProximitySensor *faucetProximitySensor = nullptr;
tflite::ErrorReporter *error_reporter = nullptr;

} // namespace

void setup_logging()
{
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;
}

// The name of this function is important for Arduino compatibility.
void setup()
{

  setup_logging();
  error_reporter->Report("Logging setup");
  Wire.begin();

  faucetProximitySensor->begin(error_reporter);
  error_reporter->Report("Proximity sensor setup");

  faucetMicrospeech->begin(error_reporter);
  error_reporter->Report("Microspeech setup");
}

State getNewState(uint16_t proxValue)
{
  if (proxValue > 5 && proxValue < 20)
    return ONLY_LEVEL;
  if (proxValue > 20 && proxValue < 400)
    return OPEN;
  if (proxValue > 400)
    return BLUETOOTH;
  return IDLE;
}

// The name of this function is important for Arduino compatibility.
void loop()
{

  static bool is_ble_ready = false;
  static bool is_ble_initialized = false;

  static int counter = 0;

  //Get proximity value. The value ranges from 0 to 65535
  uint16_t proxValue = faucetProximitySensor->getProximity();
  State newState = getNewState(proxValue);

  if (newState == actualState && counter > 0)
  {
    counter--;
  }

  if (newState != actualState)
  {
    counter++;
  }

  if (counter >= DEBOUNCE_COUNT)
  {
    counter = 0;
    actualState = newState;
    error_reporter->Report("Proximity Value: %d Actual state: %d", proxValue, actualState);
  }

  if (actualState == ONLY_LEVEL)
  {
    // TODO adjust actual level
    // Do not activate valves only change temp level
    faucetController->valves_state_clear();
    faucetMicrospeech->process(error_reporter, false);
  }
  else if (actualState == OPEN)
  {
    // TODO adjust actual level
    // Activate valves and change temp level
    faucetMicrospeech->process(error_reporter, true);
  }
  else if (actualState == BLUETOOTH)
  {
    faucetController->set_blue_led_high();
    if (!is_ble_initialized)
    {
      is_ble_initialized = true;

      error_reporter->Report("Ble setup");
      setup_ble();
      is_ble_ready = true;
    }
    if (is_ble_ready)
    {
      loop_ble();
    }
  }
  else
  {
    faucetController->set_blue_led_low();

    //faucetController->level_display_clear();
    faucetController->valves_state_clear();
  }
}
