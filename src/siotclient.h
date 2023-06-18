#ifndef SIOTClient_h
#define SIOTClient_h
#include <WString.h>


class SIOTClient{
    private:
        /// @brief  secret key generated by SIOT Center of an IoT device, at http://siot.soict.ai
        String ApiKey;
        /// @brief  IoT device's base URL generated by SIOT Center at http://siot.soict.ai
        /// @example http://siot.soict.ai/api/devices/check-newsiot 
        String DeviceBaseURL;
    public:
        void Checkin(String DeviceId, String ApiKey);
        int Send(String AttributeId, String postdata);
};
#endif