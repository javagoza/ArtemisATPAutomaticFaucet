
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

#ifndef FAUCET_PROXIMITY_SENSOR_H_
#define FAUCET_PROXIMITY_SENSOR_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"


class FaucetProximitySensor {
    public:
        FaucetProximitySensor();
        ~FaucetProximitySensor();
        boolean begin(tflite::ErrorReporter *error_reporter);
        uint16_t getProximity();
        
};
#endif // FAUCET_PROXIMITY_SENSOR_H_