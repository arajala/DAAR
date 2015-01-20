#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <DAAR_sal.h>
#include <LiquidCrystal.h>
#include <LSM9DS0.h>
#include <GA1A1S202WP.h>
#include <LVMAXSONAREZ0.h>
#include <FGPMMOPA6H.h>
#include <DAAR_interface.h>

SoftwareSerial debug(9, 10);

LSM9DS0 imu;
GA1A1S202WP light(LIGHT_OUTPUT_PIN);
LVMAXSONAREZ0 distance(DISTANCE_OUTPUT_PIN,
    DISTANCE_ENABLE_PIN, ANALOG, 3.3f);
FGPMMOPA6H gps;
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, 
    LCD_D0_PIN, LCD_D1_PIN, LCD_D2_PIN, LCD_D3_PIN);

vtg_t gps_vtg_packet;
DisplayInfo_t display_info;

void setup() {
  debug.begin(9600);
  Serial.begin(9600);
  setup_hardware(&imu, &light, &distance, &gps, &lcd);
}

void loop() {
  float light_intensity = light.read_light_analog();
  if (light_intensity < LIGHT_INDICATOR_THRESH) {
    display_info.light_on = 1;
  } else {
    display_info.light_on = 0;
  }
  display_info.current_speed = gps.read_speed_mph();
  display(display_info);
  debug.print("Speed = ");
  debug.print(display_info.current_speed);
  debug.print("  Light = ");
  debug.println(display_info.light_on);
}

void serialEvent() {
  gps.serial_event();
}
