//----------------------------------------------------------------------
//  IDE: Visual Studio Code + PlatformIO extension
//  Author: Nguyen Duc Tien, tien.nguyenduc@hust.edu.vn
//  Website: https://soict.hust.edu.vn/ths-nguyen-duc-tien.html
//----------------------------------------------------------------------
#include <Arduino.h>
#include <WiFiSelfEnroll.h>  // SIOT Core Lib - seft setup wifi network

// Handler adhoc wifi station
WiFiSelfEnroll MyWiFi;

void setup() {
  //just for debug
  Serial.begin(115200);
  // Make sure WiFi ssid/password is correct. Otherwise, raise the Adhoc AP Station with ssid = SOICT_CORE_BOARD and password =  12345678
  MyWiFi.setup();
  // TODO something
}

void loop() {
  Serial.println(MyWiFi.GetDeviceID());
  Serial.printf("  %s / %s \n", MyWiFi.GetSSID(), MyWiFi.GetPassword());
  delay(1000);
}