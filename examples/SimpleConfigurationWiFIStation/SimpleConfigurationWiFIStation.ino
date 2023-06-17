//----------------------------------------------------------------------
//  IDE: Visual Studio Code + PlatformIO extension
//  Organization: School of Information and Communication Technogloy,
//                Ha Noi Univerversity of Science and Technology
//  Website: https://soict.hust.edu.vn
//  Example 1: Connect WiFi network
//  Purpose: using siot core lib to configure WiFi network for your IoT 
//           device by smartphone. No need re programming.
//----------------------------------------------------------------------
#include <Arduino.h>
#if true
  #include <siot_core_lib.h>   // SIOT Core Lib - all packages or you could select each package manually.
#else
  #include <WiFiSelfEnroll.h>  // SIOT Core Lib - seft setup wifi network
#endif

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