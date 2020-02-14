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

#include "command_responder.h"

#include "am_bsp.h" // NOLINT

extern "C"
{
#include "faucet_controller.h"
};

static int faucetLevel = 0;

// Change temperature level and actuate valves if necesessary respondig to commands
void RespondToCommand(tflite::ErrorReporter *error_reporter,
                      int32_t current_time, const char *found_command,
                      uint8_t score, bool is_new_command, bool activate_valves)
{
  static bool is_initialized = false;
  if (!is_initialized)
  {

    // Blue led heart beat
    am_hal_gpio_pinconfig(AM_BSP_GPIO_LED_BLUE, g_AM_HAL_GPIO_OUTPUT_12);

    faucet_begin();

    is_initialized = true;
  }
  static int count = 0;

  // Toggle the blue LED every time an inference is performed.
  ++count;
  count & 1 ? am_hal_gpio_output_set(AM_BSP_GPIO_LED_BLUE) : am_hal_gpio_output_clear(AM_BSP_GPIO_LED_BLUE);

  if (is_new_command)
  {
    error_reporter->Report("Heard %s (%d) @%dms", found_command, score,
                           current_time);
    // Level up if 'up' was heard.
    if (found_command[0] == 'u' && found_command[1] == 'p')
    {
      faucetLevel = faucet_raise_temperature_level(activate_valves);
      error_reporter->Report("UP level(%d)\n", faucetLevel);
    }
    // Level down if 'down' was heard.
    if (found_command[0] == 'd' && found_command[1] == 'o')
    {
      faucetLevel = faucet_lower_temperature_level(activate_valves);
      error_reporter->Report("DOWN level(%d)\n", faucetLevel);
    }
    if (found_command[0] == 'u' && found_command[1] == 'n')
    {
      error_reporter->Report("\nUNKNOWN");
    }
  }
}
