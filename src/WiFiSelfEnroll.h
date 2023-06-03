#ifndef WiFiSelfEnroll_h
#define WiFiSelfEnroll_h

class WiFiSelfEnroll{
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