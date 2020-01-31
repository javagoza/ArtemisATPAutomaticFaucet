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

#include "faucet_controller.h"
#include "Arduino.h"
#include "am_bsp.h" // NOLINT

FaucetController::FaucetController()
{
    // Setup LED's as outputs
    // Blue led heart beat
    am_hal_gpio_pinconfig(AM_BSP_GPIO_LED_BLUE, g_AM_HAL_GPIO_OUTPUT_12);
    // Level indicator leds
    for (int i = 0; i < LEVELS; i++)
    {
        am_hal_gpio_pinconfig(leds[i], g_AM_HAL_GPIO_OUTPUT_12);
        // initially off
        //am_hal_gpio_output_clear(leds[i]);
        set_led_level_low(leds[i]);
    }

        // setup relays ports as outputs
    for (int i = 0; i < RELAYS; i++)
    {
      am_hal_gpio_pinconfig(relays[i], g_AM_HAL_GPIO_OUTPUT_12);
      // initially on
      set_led_level_high(relays[i]);
    }


    // pinMode(LED_BUILTIN, OUTPUT);
    set_blue_led_low();
};
FaucetController::~FaucetController(){};

void FaucetController::setUp(void){
      // Setup LED's as outputs

    // Level indicator leds
    for (int i = 0; i < LEDS; i++)
    {
      am_hal_gpio_pinconfig(leds[i], g_AM_HAL_GPIO_OUTPUT_12);
      // initially off
      am_hal_gpio_output_clear(leds[i]);
    }
    // setup relays ports as outputs
    for (int i = 0; i < RELAYS; i++)
    {
      am_hal_gpio_pinconfig(relays[i], g_AM_HAL_GPIO_OUTPUT_12);
      // initially on
      am_hal_gpio_output_clear(relays[i]);
    }

}

void FaucetController::setValvesState(int level) {
    for (int i = 0; i < RELAYS; i++)
    {
      if (temperatures[level][i])
      {
        am_hal_gpio_output_clear(relays[i]);
      }
      else
      {
        am_hal_gpio_output_set(relays[i]);
      }
    }
}

void FaucetController::displayLevel(int level){
        for (int i = 0; i < level; i++)
    {
      am_hal_gpio_output_set(leds[i]);
    }
    for (int i = level; i < LEDS; i++)
    {
      am_hal_gpio_output_clear(leds[i]);
    }
}

void FaucetController::set_blue_led_high(void)
{
    am_hal_gpio_output_set(LED_BUILTIN);
}

void FaucetController::level_display_clear(void)
{

      am_hal_gpio_output_clear(LED_LEVEL1);
      am_hal_gpio_output_clear(LED_LEVEL2);
      am_hal_gpio_output_clear(LED_LEVEL3);
      am_hal_gpio_output_clear(LED_LEVEL4);
   
}

void FaucetController::valves_state_clear(void)
{

      am_hal_gpio_output_set(RELAY1);
      am_hal_gpio_output_set(RELAY2);
      am_hal_gpio_output_set(RELAY3);

   
}

void FaucetController::set_blue_led_low(void)
{
    am_hal_gpio_output_clear(LED_BUILTIN);
}

void FaucetController::set_led_level_high(const int ledPort)
{
    am_hal_gpio_output_set(ledPort);
}

void FaucetController::set_led_level_low(const int ledPort)
{
    am_hal_gpio_output_clear(ledPort);
}
