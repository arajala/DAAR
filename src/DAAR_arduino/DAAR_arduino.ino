#include <LSM9DS0.h>
#include <GA1A1S202WP.h>
#include <LVMAXSONAREZ0.h>
#include <DAAR_interface.h>

LSM9DS0 imu;
GA1A1S202WP light(LIGHT_PIN);
LVMAXSONAREZ0 distance(ULTRASONIC_PIN, ANALOG);

void setup() {
  Serial.begin(115200);
  setup_hardware(&imu, &light, &distance);
}

void loop() {
  
}
