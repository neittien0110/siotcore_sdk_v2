#include "WiFiSelfEnroll.h"         /// raw html of pages
#include <WiFi.h>
#include <WebServer.h>              /// create webserver
#include "WiFISelfPages.h"          /// raw html of pages
#include "Preferences.h"            /// use permanent flash storage  https://randomnerdtutorials.com/esp32-save-data-permanently-preferences/

/// @brief print more debug information to serial
#define _DEBUG_

/// @brief the namespace id to store inside the flash, by Preferences lib. Must no longer than 15 characters.
#define FLASH_NAMESPACE "WiFiSelfEnroll"
#define FLASH_NAMESPACE_KEY_SSID "ssid"
#define FLASH_NAMESPACE_KEY_PASSWORD "pass"
#define FLASH_NAMESPACE_KEY_DEVICEID "id"

/// @brief the default wifi SSID
#define SOICT_WIFI_SSID "SOICT_CORE_BOARD"
/// @brief the default wifi password
 #define SOICT_WIFI_PASSWORD "12345678"

/// @brief  the current ssid. A pointer to parambuf
String ssid;
/// @brief  the current password. A pointer to parambuf
String password;
/// @brief  the current deviceid. A pointer to parambuf
String deviceid;
/// @brief  adhoc webserver to configure the new wifi network
WebServer server(80);
/// @brief flash mem handler 
Preferences preferences;

/*-------------------------------------------------------------------------*/
/// @brief send the homepage html to client
/// @details entrypoint http://192.168.15.1/
void WiFiSelfEnroll::_HomePage()
{
#ifdef _DEBUG_        
    Serial.println("WiFiSelf: /");
#endif
    server.send(200,"text/html", HOME_HTML);
}

/*-------------------------------------------------------------------------*/
/// @brief send the scan wifi html to client
/// @details entrypoint http://192.168.15.1/enroll
void WiFiSelfEnroll::_EnrollPage()  {
#ifdef _DEBUG_        
    Serial.println("WiFiSelf: /enroll");
#endif
    server.send(200,"text/html", ENROLL_HTML);
}
/*-------------------------------------------------------------------------*/
/// @brief send wifi list in csv format to web client
/// @details entrypoint http://192.168.15.1/cgi/scan
/// @example 812A,12345678,dce-ktmt,66668888
void WiFiSelfEnroll::_APIScan()  {
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    String res = String(200);
    res = "";
    if (n != 0) {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            res = res + WiFi.SSID(i) + ',' + WiFi.RSSI(i);
            if (i != n-1) {res = res +',';}
            Serial.println(res);
        delay(10);
        }
    }
#ifdef _DEBUG_        
    Serial.println(res);
#endif
    server.send(200,"text/plain", res);
}
/*-------------------------------------------------------------------------*/
/// @brief WebAPI: receive ssid, pass from the HttpGet and save to permanent storage
/// @details exntrypoint http://192.168.15.1/cgi/save?s=ssid&p=password
void WiFiSelfEnroll::_APISave()  {
#ifdef _DEBUG_       
    Serial.println("WiFiSelf: /cgi/save");
    Serial.println(server.uri());
#endif        
    /// Control the flash memory with its idendification namespace, and write mode
    preferences.begin(FLASH_NAMESPACE, false);         

    String myArg="s";
    /// Save SSID
    if (server.hasArg(myArg)) {
        preferences.putString(FLASH_NAMESPACE_KEY_SSID, server.arg(myArg));
        #ifdef _DEBUG_             
        Serial.println(server.arg(myArg));
        #endif        
    }   

    /// Save Password
    myArg="p";
    if (server.hasArg(myArg)) {
        preferences.putString(FLASH_NAMESPACE_KEY_PASSWORD, server.arg(myArg));
        #ifdef _DEBUG_             
        Serial.println(server.arg(myArg));
        #endif        
    }    

    /// Save DeviceID
    myArg="d";
    if (server.hasArg(myArg)) {
        preferences.putString(FLASH_NAMESPACE_KEY_DEVICEID, server.arg(myArg));
        #ifdef _DEBUG_             
        Serial.println(server.arg(myArg));
        #endif        
    }    

    /// Save DeviceID
    if (server.hasArg("clear")) {
        preferences.clear();
        #ifdef _DEBUG_             
        Serial.println("clear namespace");
        #endif        
    }   

    /// Close the preferences to end the flash handler
    preferences.end();
    /// Response to the web client
    server.send(200,"text/plain", "done deal");
}

/*-------------------------------------------------------------------------*/
/// @brief WebAPI: reponse the wifi configuration and device id
/// @details exntrypoint http://192.168.15.1/cgi/save?n=ssid&p=password
void WiFiSelfEnroll::_APISettings()  {
#ifdef _DEBUG_       
    Serial.println("WiFiSelf: /cgi/settings");
#endif
    char buf[50];
    (ssid + "," + password + ',' + deviceid).toCharArray(buf,50);
    /// Response to the web client
    server.send(200,"text/plain", buf);
}
/*-------------------------------------------------------------------------*/
/// @brief Read the ssid / deviceid into flash memory
/// @return e.g. '812A,12345678'
void WiFiSelfEnroll::_ReadWiFiConfig()  {
    byte len;
#ifdef _DEBUG_       
    Serial.printf("_ReadWiFiConfig");
#endif    
    /// Control the flash memory with its idendification namespace, and read mode
    preferences.begin(FLASH_NAMESPACE, true); 
    ssid = preferences.getString(FLASH_NAMESPACE_KEY_SSID);
    password = preferences.getString(FLASH_NAMESPACE_KEY_PASSWORD);
    deviceid = preferences.getString(FLASH_NAMESPACE_KEY_DEVICEID);
    preferences.end();
#ifdef _DEBUG_       
    Serial.printf("In Flash: %s / %s , %s\n", ssid, password, deviceid);
#endif
    return;
}        
    
///--------------------------------------------------------------------
/// @brief Restart the device
void WiFiSelfEnroll::_Restart()  {
    #ifdef _DEBUG_             
    Serial.println("restart...");
    #endif              
    ESP.restart();
}

void WiFiSelfEnroll::setup(const char * adhoc_ssid, const char * adhoc_password) {
    
    // Read the current wifi config
    _ReadWiFiConfig();

    IPAddress local_ip(192,168,9,1);
    IPAddress gateway(192,168,9,1);
    IPAddress subnet(255,255,255,0);

    //if (ssid == NULL) {
    //    ssid = (char * ) SOICT_WIFI_SSID;
    //};
    //if (password == NULL) {
    //    password = (char * ) SOICT_WIFI_PASSWORD;
    //};

    ///LED_BUILTIN is used for wifi indicator 
    pinMode(LED_BUILTIN, OUTPUT);

    /// Indicator: start the wifi
    digitalWrite(LED_BUILTIN, HIGH);       

#ifdef _DEBUG_
    Serial.begin(115200);
    Serial.print("Adhoc WiFi: ");
    Serial.print(adhoc_ssid);
    Serial.print(" / ");
    Serial.println(adhoc_password);
#endif    
    
    /// set as a Wi-Fi station and access point simultaneously
    WiFi.mode(WIFI_AP_STA);

    /// Broadcast the Adhoc WiFi
    if (WiFi.softAPConfig(local_ip,gateway,subnet)) {
#ifdef _DEBUG_
        Serial.println("WiFi configuration is okay");
#endif                
    }
    if (WiFi.softAP(adhoc_ssid, adhoc_password,7,false)) {
#ifdef _DEBUG_
        Serial.println("WiFi is ready!");
#endif                
    }

#ifdef _DEBUG_        
    /// WiFi is ready
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
#endif    

    /// Route the website
    server.on("/", _HomePage);
    server.on("/enroll", _EnrollPage);
    server.on("/cgi/scan", _APIScan);
    server.on("/cgi/save", _APISave);
    server.on("/cgi/settings", _APISettings);
    server.on("/restart", _Restart);
    /// Show the own website
    server.begin();
}

void WiFiSelfEnroll::setup(){
    WiFiSelfEnroll::setup(SOICT_WIFI_SSID, SOICT_WIFI_PASSWORD);
}

void WiFiSelfEnroll::loop()  {          
#ifdef _DEBUG_        
    Serial.printf("Stations connected to soft-AP = %d \n", WiFi.softAPgetStationNum());
#endif        
    //polling and call event functions
    server.handleClient();
    //Indicator
    digitalWrite(LED_BUILTIN, HIGH);       
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);        
    delay(1000);

}

