#ifndef WiFiSelfEnroll_h
#define WiFiSelfEnroll_h

class WiFiSelfEnroll{
    private:
    /// @brief true if the Adhoc WiFi is active
    bool    APMode;

    /// @brief send the homepage html to client
    /// @details entrypoint http://192.168.15.1/
    static void _HomePage();

    /// @brief send the scan wifi html to client
    /// @details entrypoint http://192.168.15.1/enroll
    static void _EnrollPage();

    /// @brief send wifi list in csv format to web client
    /// @details entrypoint http://192.168.15.1/cgi/scan
    /// @example 812A,12345678,dce-ktmt,66668888
    static void _APIScan() ;

    /// @brief WebAPI: receive ssid, pass from the HttpGet and save to permanent storage
    /// @details exntrypoint http://192.168.15.1/cgi/save?s=ssid&p=password
    static void _APISave();

    /// @brief WebAPI: reponse the wifi configuration and device id
    /// @details exntrypoint http://192.168.15.1/cgi/save?n=ssid&p=password
    static void _APISettings();
    
    /// @brief Reboot the device
    static void _Reboot();

    public:
    /// @brief Read the ssid / deviceid from flash memory
    /// @return e.g. '812A,12345678'
    void ReadWiFiConfig();

    /// @brief setup the Adhoc wifi
    /// @param ssid     Wifi name. E.g "My WiFi"
    /// @param password  Wifi secret password.
    /// @note should let it at the first part of the global setup() function in Arduino Code.
    /// @example  WiFiSelfEnroll MyWiFi;  MyWiFi.setup("ABC","12345678");
    void SetupStation(const char * ssid, const char * password);    

    /// @brief setup the default Adhoc wifi with ssid = SOICT_CORE_BOARD and password =  12345678
    void setup();
    void setup(const char * ssid, const char * password);
    
    void _loop();
    /// 
    char * GetSSID();

    char * GetPassword();
    char * GetDeviceID();

    bool IsConfigOK();
};
#endif