#ifndef WiFiSelfEnroll_h
#define WiFiSelfEnroll_h
#include <Preferences.h>            /// use permanent flash storage  https://randomnerdtutorials.com/esp32-save-data-permanently-preferences/
#include <WiFi.h>
#include <WebServer.h>              /// create webserver

class WiFiSelfEnroll{
    private:
        static String ssid;
        static char myssid[32];
        static String password;
        static char mypassword[20];
        static String deviceid;
        static char mydeviceid[30];
        static Preferences preferences;
        static WiFiClient wificlient;
        static WebServer server;
    private:
        /// @brief true if the Adhoc WiFi is active
        bool    APMode;
        static void _HomePage();
        static void _EnrollPage();
        static void _APIScan() ;
        static void _APISave();
        static void _APISettings();
        static void _Reboot();  
        void _loop();
    public:
        void ReadWiFiConfig();
        void SetupStation(const char * ssid, const char * password);    
        void setup();  
        void setup(const char * adhoc_ssid, const char * adhoc_password);    
        char * GetSSID();
        char * GetPassword();
        char * GetDeviceID();
        bool IsConfigOK();
};
#endif