#pragma once

#include <Arduino.h>

namespace mtrn3100 {

class UltrasonicSensor {
public:
    // COMPLETE THIS CONSTRUCTOR.
    UltrasonicSensor(uint8_t trigger_pin, uint8_t echo_pin) : trigger_pin(trigger_pin), echo_pin(echo_pin) {
      pinMode(trigger_pin, OUTPUT);
      pinMode(echo_pin, INPUT);
    }

    // COMPLETE THIS FUNCTION.
    float echo() const { 
      // clear trigger_pin
      digitalWrite(trigger_pin, LOW);
      delayMicroseconds(5);
      // send signal
      digitalWrite(trigger_pin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigger_pin, LOW);
      // Determine time of flight and distance
      return 0.1715 * pulseIn(echo_pin, HIGH); 
    }

private:
    const uint8_t trigger_pin;
    const uint8_t echo_pin;
};

}  // namespace mtrn3100