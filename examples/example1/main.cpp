//----------------------------------------------------------------------
// 
//  IDE: Visual Studio Code + PlatformIO extension
//----------------------------------------------------------------------
#include <Arduino.h>
#include "WiFiSelfEnroll.h"

WiFiSelfEnroll MyWiFi;

void setup() {
  // put your setup code here, to run once:
  MyWiFi.setup();
}

void loop() {
  MyWiFi.loop();
  // put your main code here, to run repeatedly:
}