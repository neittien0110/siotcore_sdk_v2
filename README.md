# SOICT CORE Version 2

## Enviroment

- IDE: Visual Studio Code + Platform IO
- Architecture: esp32,esp8266
  - Tested: [esp32doit-devkit-v1](https://docs.platformio.org/en/latest/boards/espressif32/esp32doit-devkit-v1.html), [esp32-c3-devkitm-1](https://docs.espressif.com/projects/esp-idf/en/v5.0/esp32c3/hw-reference/esp32c3/user-guide-devkitm-1.html)
  - Tested: [Wemos D1 Mini V3.0.0](https://grobotronics.com/wemos-d1-mini-esp8266-v2.0.html?sl=en)

---

## Features

1. [Enroll WiFi by Adhoc WebServer](#enroll-wifi-by-adhoc-webserver)
---

## Enroll WiFi by Adhoc WebServer

```Arduino
#include <Arduino.h>
#include <siot_core_lib.h>   // SIOT Core Lib - all packages or you could select each package manually.

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
```

![Adhoc WebServer to register the WiFi and password](images/c1a5ae8ac5c6c78bd6f7de8950c8cb4d39bf98bd3850aebac52885b3fa16c0cb.png)  

### Workflow inside

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
