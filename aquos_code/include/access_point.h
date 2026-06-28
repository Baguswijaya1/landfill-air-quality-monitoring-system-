#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include <Arduino.h>
#include <WiFi.h>

#define AP_SSID "AQUOS-Batur"
#define AP_PASSWORD "Batur123"

void setup_access_point() {
    WiFi.mode(WIFI_AP);
    bool ap_ready = WiFi.softAP(AP_SSID, AP_PASSWORD);
    if (!ap_ready){
        Serial.println("failed to start access point");
        return;
    }

    // set custom IP configuration
    IPAddress apIP(192, 168, 4, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAPConfig(apIP, apIP, subnet);
    
    // result
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP Started. IP: "); Serial.println(IP);
}

#endif