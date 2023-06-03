# SOICT CORE Version 2

## Enviroment

- IDE: Visual Studio Code + Platform IO
- Device: ESP32, ESP32-C3

---

## Features

1. [Enroll WiFi by Adhoc WebServer](#enroll-wifi-by-adhoc-webserver)

---

### Enroll WiFi by Adhoc WebServer

```Arduino
#include <Arduino.h>
#include "WiFiSelfEnroll.h"

WiFiSelfEnroll MyWiFi;

void setup() {
  // Make sure WiFi ssid/password is correct. Otherwise, raise the Adhoc AP Station with ssid = SOICT_CORE_BOARD and password =  12345678
  MyWiFi.setup();
  // TODO something
}

void loop() {
  Serial.printf("%s:  %s / %s \n", MyWiFi.GetDeviceID(), MyWiFi.GetSSID(), MyWiFi.GetPassword());
  delay(1000);
}
```

![Adhoc WebServer to register the WiFi and password](images/c1a5ae8ac5c6c78bd6f7de8950c8cb4d39bf98bd3850aebac52885b3fa16c0cb.png)  

## Workflow inside

```mermaid
  stateDiagram
  [*] --> BOOT_button_pressed?
  BOOT_button_pressed? --> APStation : yes
  BOOT_button_pressed? --> ReadWiFiConfig : no
  ReadWiFiConfig --> TryConnectWiFi
  TryConnectWiFi --> [*]: successful
  TryConnectWiFi --> APStation: alway fail in 15 seconds
  APStation --> reboot: over 300 seconds
  ReadWiFiConfig: Read WiFi ssid/pass from flash memory
  
  state APStation {
      SetAdhocStation --> CreateWebServer
      CreateWebServer  --> ShowCurrentWiFis
      ShowCurrentWiFis --> EnterPassword
      EnterPassword --> SaveWiFiConfig
      SaveWiFiConfig: Write WiFi ssid/pass to flash memory
  }
```