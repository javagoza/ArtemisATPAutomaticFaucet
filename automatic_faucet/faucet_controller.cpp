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

#include "am_bsp.h"

extern "C"
{
#include "faucet_controller.h"
};

#define FAUCET_LED_LEVEL1 9
#define FAUCET_LED_LEVEL2 10
#define FAUCET_LED_LEVEL3 8
#define FAUCET_LED_LEVEL4 14

#define FAUCET_LEDS 4

#define FAUCET_LEVELS 5

#define FAUCET_RELAYS 3

#define FAUCET_RELAY1 22
#define FAUCET_RELAY2 23
#define FAUCET_RELAY3 27

static int actual_level = 0;

static const int faucet_leds[FAUCET_LEVELS] = {FAUCET_LED_LEVEL1, FAUCET_LED_LEVEL2, FAUCET_LED_LEVEL3, FAUCET_LED_LEVEL4};

static const int faucet_relays[FAUCET_RELAYS] = {FAUCET_RELAY1, FAUCET_RELAY2, FAUCET_RELAY3};

static const int faucet_temperatures[FAUCET_LEVELS][FAUCET_RELAYS] = {
    // cold, cold, hot
    {0, 0, 0},  // level 0 tap is closed
    {1, 0, 0},  // level 1 cold
    {1, 1, 1},  // level 2 warm
    {1, 0, 1},  // level 3 hot
    {0, 0, 1}}; // level 4 very hot

void faucet_begin()
{
    actual_level = 0;
    // Setup LED's as outputs
    // Blue led heart beat
    am_hal_gpio_pinconfig(AM_BSP_GPIO_LED_BLUE, g_AM_HAL_GPIO_OUTPUT_12);
    // Level indicator leds
    for (int i = 0; i < FAUCET_LEDS; i++)
    {
        am_hal_gpio_pinconfig(faucet_leds[i], g_AM_HAL_GPIO_OUTPUT_12);
        // initially off
        //am_hal_gpio_output_clear(leds[i]);
        faucet_set_led_level_low(faucet_leds[i]);
    }

    // setup relays ports as outputs
    for (int i = 0; i < FAUCET_RELAYS; i++)
    {
        am_hal_gpio_pinconfig(faucet_relays[i], g_AM_HAL_GPIO_OUTPUT_12);
        // initially on
        faucet_set_led_level_high(faucet_relays[i]);
    }

    faucet_set_blue_led_low();
};

void faucet_close_faucet(void)
{
    faucet_valves_state_clear();
}

void faucet_open_faucet(void)
{
    faucet_display_level(actual_level);
    faucet_set_valves_level(actual_level);
}

void faucet_display_actual_level(void)
{
    faucet_display_level(actual_level);
}

int faucet_lower_temperature_level(int actuateValves)
{
    if (actual_level > 0)
        actual_level--;

    faucet_display_level(actual_level);

    actuateValves ? faucet_set_valves_level(actual_level)
                  : faucet_valves_state_clear();

    return actual_level;
}

int faucet_raise_temperature_level(int actuateValves)
{
    if (actual_level < 4)
        actual_level++;

    faucet_display_level(actual_level);

    actuateValves ? faucet_set_valves_level(actual_level)
                  : faucet_valves_state_clear();

    return actual_level;
}

void faucet_set_valves_level(const int level)
{
    for (int i = 0; i < FAUCET_RELAYS; i++)
        faucet_temperatures[level][i] ? am_hal_gpio_output_clear(faucet_relays[i])
                                      : am_hal_gpio_output_set(faucet_relays[i]);
}

void faucet_display_level(const int level)
{
    for (int i = 0; i < level; i++)
        am_hal_gpio_output_set(faucet_leds[i]);

    for (int i = level; i < FAUCET_LEDS; i++)
        am_hal_gpio_output_clear(faucet_leds[i]);
}

void faucet_set_blue_led_high(void)
{
    am_hal_gpio_output_set(AM_BSP_GPIO_LED_BLUE);
}

void faucet_level_display_clear(void)
{
    am_hal_gpio_output_clear(FAUCET_LED_LEVEL1);
    am_hal_gpio_output_clear(FAUCET_LED_LEVEL2);
    am_hal_gpio_output_clear(FAUCET_LED_LEVEL3);
    am_hal_gpio_output_clear(FAUCET_LED_LEVEL4);
}

void faucet_valves_state_clear(void)
{
    am_hal_gpio_output_set(FAUCET_RELAY1);
    am_hal_gpio_output_set(FAUCET_RELAY2);
    am_hal_gpio_output_set(FAUCET_RELAY3);
}

void faucet_set_blue_led_low(void)
{
    am_hal_gpio_output_clear(AM_BSP_GPIO_LED_BLUE);
}

void faucet_set_led_level_high(const int ledPort)
{
    am_hal_gpio_output_set(ledPort);
}

void faucet_set_led_level_low(const int ledPort)
{
    am_hal_gpio_output_clear(ledPort);
}
