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

#ifndef FAUCET_CONTROLLER_H_
#define FAUCET_CONTROLLER_H_


#define LED_LEVEL1 9
#define LED_LEVEL2 10
#define LED_LEVEL3 8
#define LED_LEVEL4 14

#define LEDS 4

#define LEVELS 5

#define RELAYS 3
#define RELAY1 22
#define RELAY2 23
#define RELAY3 27

class FaucetController
{
public:
  FaucetController();
  ~FaucetController();

  void set_blue_led_high(void);

  void set_blue_led_low(void);

  void set_led_level_high(const int ledPort);

  void set_led_level_low(const int ledPort);

  void level_display_clear(void);
  void valves_state_clear(void);

  void setUp(void);

  void displayLevel(int level);
  void setValvesState(int level);

private:
  const int leds[LEVELS] = {LED_LEVEL1, LED_LEVEL2, LED_LEVEL3, LED_LEVEL4};

  const int relays[RELAYS] = {RELAY1, RELAY2, RELAY3};

  const int temperatures[LEVELS][RELAYS] = {
      // cold, cold, hot
      {0, 0, 0},
      {1, 0, 0},
      {1, 1, 1},
      {1, 0, 1},
      {0, 0, 1}};
};


#endif // FAUCET_CONTROLLER_H_
