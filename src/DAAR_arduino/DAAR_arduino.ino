#include <Arduino.h>
#include <Wire.h>
#include <DAAR_sal.h>
#include <LSM9DS0.h>
#include <GA1A1S202WP.h>
#include <LVMAXSONAREZ0.h>
#include <DAAR_interface.h>

LSM9DS0 imu;
GA1A1S202WP light(LIGHT_OUTPUT_PIN);
LVMAXSONAREZ0 distance(DISTANCE_OUTPUT_PIN, DISTANCE_ENABLE_PIN, ANALOG, 3.3f);

void setup() {
  Serial.begin(115200);
  setup_hardware(&imu, &light, &distance);
}

void loop() {
  
}

