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
#include <siotcorelib/WiFiSelfEnroll.h>

WiFiSelfEnroll MyWiFi = WiFiSelfEnroll();
void setup() {
  // put your setup code here, to run once:
  MyWiFi.setup();
}

void loop() {
  MyWiFi.loop();
  // put your main code here, to run repeatedly:
}
```

![Adhoc WebServer to register the WiFi and password](images/c1a5ae8ac5c6c78bd6f7de8950c8cb4d39bf98bd3850aebac52885b3fa16c0cb.png)  


