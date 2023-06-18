# SOICT CORE Version 2

## Enviroment

- IDE: Visual Studio Code + Platform IO
- Device: ESP32, ESP32-C3

---

## Features

1. [Enroll WiFi by Adhoc WebServer](#enroll-wifi-by-adhoc-webserver)
2. [Store data to SIoT center](#store-data-to-siot-center)

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

## Store data to SIoT center

```Arduino
#include <Arduino.h>
#include <siot_core_lib.h>    

// Handler adhoc wifi station
WiFiSelfEnroll MyWiFi;
// SIoT Management Handler, send/receive data to/from SIOT API Center 
SIOTClient siotclient;

void setup() {
  Serial.begin(115200);
  // Make sure WiFi ssid/password is correct. Otherwise, raise the Adhoc AP Station with ssid = SOICT_CORE_BOARD and password =  12345678
  MyWiFi.setup();
  // Declare the virtual device information which you have register at http://siot.soict.ai (free)
  siotclient.Checkin("siot-demo","eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiIwZDI1NWI5Ni05OWMyLTRmNTItOTg1NS0yZWRhNmI3MzYyMzAiLCJpYXQiOjE2ODcwNzQ4OTd9.SHRCTNASXYEPkYR-ZVadu1P19UPRTHQoHcZjzAoUaiM");
  // Send data to the attribute whose id is turnon-siot. Free to declare at siot.soict.ai as you need.
  siotclient.Send("turnon-siot","{\"value\":307}");
  // Anothor attribute
  Serial.print(F("HTTP Response code: "));  
  Serial.println(siotclient.Send("mysensor-fxcjl","{\"value\":15.2025}"));
}

void loop(){

}
```

![Visualize IoT device data ](images/b327a09e82488f609d63c8362a2d1813c67f6e02002bbde42fe7edfa7ac0ba11.png)  

### Step by Step

Purpose: using siot core lib to send data from your IoT to the correctsponding virtual device on SIOT Center

**Register**.

1. Open the SIOT Center <http://siot.soict.ai>
2. Register a new free account, or login with sample account <sinno@soict.hust.edu.vn> and password is 123456
3. On the left navigation menu, click **My devices**
4. Complete the new device with information about name, slug-name, avatar image.
5. Continue register one or more attributes for the new device. Your can add more later.
6. Still at the **My devices**, click on the device button/card.
7. Obtain these parametters to some elsewhere:

- Slug API key
- Bearer token
- HTTP Endpoints

![Slug API key and Bearer token](images/6cd9e3497fdca76cb851d94760fb71cb31bff596a88a899b12e4a7ea2ede714a.png)  
![HTTP Endpoints](images/6cb14b63091573cc067715aa56d9ebbc7f227cd4c9e9f1f53d58ce4542ac6248.png)  

**View Data**.

1. Open the SIOT Center <http://siot.soict.ai>
2. Register a new free account, or login with sample account <sinno@soict.hust.edu.vn> and password is 123456
3. On the left navigation menu, click Arduino Siot Client to see realtime data
   Shortlink: http://siot.soict.ai/devices/siot-demo