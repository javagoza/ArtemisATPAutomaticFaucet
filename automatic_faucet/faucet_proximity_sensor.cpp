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

#include "faucet_proximity_sensor.h"
#include <Wire.h>
#include "SparkFun_VCNL4040_Arduino_Library.h"

namespace
{
VCNL4040 proximitySensor;
}

FaucetProximitySensor::FaucetProximitySensor() {}

FaucetProximitySensor::~FaucetProximitySensor() {}

boolean FaucetProximitySensor::begin(tflite::ErrorReporter *error_reporter)
{
  error_reporter->Report("VCNL4040 setup");

  if (proximitySensor.begin() == false)
  {
    error_reporter->Report("Device not found. Please check wiring.");
    while (1)
      ; //Freeze!
  }
  return true;
}

uint16_t FaucetProximitySensor::getProximity(void)
{
  return proximitySensor.getProximity();
}
