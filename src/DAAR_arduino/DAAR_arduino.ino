#include <Arduino.h>
#include <Wire.h>
#include <DAAR_sal.h>
#include <LiquidCrystal.h>
#include <LSM9DS0.h>
#include <GA1A1S202WP.h>
#include <LVMAXSONAREZ0.h>
#include <FGPMMOPA6H.h>
#include <DAAR_interface.h>

//LSM9DS0 imu;
GA1A1S202WP light(LIGHT_OUTPUT_PIN);
LVMAXSONAREZ0 distance(DISTANCE_OUTPUT_PIN,
    DISTANCE_ENABLE_PIN, ANALOG, 3.3f);
FGPMMOPA6H gps;
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, 
    LCD_D0_PIN, LCD_D1_PIN, LCD_D2_PIN, LCD_D3_PIN);

vtg_t gps_vtg_packet;
DisplayInfo_t display_info;

void setup() {
  Serial.begin(9600);
  uint8_t map_light_indicator[8] = {2, 20, 8, 15, 8, 20, 2, 0};
  lcd.createChar(LIGHT_INDICATOR_CODE, map_light_indicator);
  lcd.begin(16, 2);
//  setup_hardware(&imu, &light, &distance, &gps, &lcd);
}

void loop() {
  float light_intensity = light.read_light_analog();
  if (light_intensity < LIGHT_INDICATOR_THRESH) {
    display_info.light_on = 1;
  } else {
    display_info.light_on = 0;
  }
  float target_distance = distance.read_distance_analog();
  display_info.target_distance = target_distance;
//  display_info.current_speed = gps.read_speed_mph();
  gps_vtg_packet = gps.read_vtg();
  display_info.current_speed = gps_vtg_packet.speed_1 * 1.15077945f;
  display(display_info, &lcd);
  Serial.print("Speed = ");
  Serial.print(display_info.current_speed);
  Serial.print(" Distance = ");
  Serial.print(display_info.target_distance);
  Serial.print("  Light = ");
  Serial.println(display_info.light_on);
}

void serialEvent() {
  gps.serial_event();
}
