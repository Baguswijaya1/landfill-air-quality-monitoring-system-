#ifndef WEB_SERVER_DASHBOARD_H
#define WEB_SERVER_DASHBOARD_H

#include <Arduino.h>
#include <WebServer.h>

WebServer server(80);

// Sensor values and statuses are updated from main.cpp
float sensor_mq4 = 0;
float sensor_mq135 = 0;
float sensor_mq136 = 0;
float sensor_humidity = 0;
String sensor_mq4_status = "AMAN";
String sensor_mq135_status = "AMAN";
String sensor_mq136_status = "AMAN";

String status_class(const String& status) {
    if (status == "AMAN") {
        return "safe";
    }
    if (status == "SEDANG") {
        return "warning";
    }
    return "danger";
}

void handle_root() {
    String mq4_class = status_class(sensor_mq4_status);
    String mq135_class = status_class(sensor_mq135_status);
    String mq136_class = status_class(sensor_mq136_status);

    String html = "<!DOCTYPE html><html><head><title>Aquos Sensor Dashboard</title>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<style>";
    html += "body { font-family: Arial, sans-serif; text-align: center; padding: 20px; }";
    html += ".sensor { display: inline-block; margin: 10px; padding: 15px; border: 1px solid #ccc; border-radius: 8px; min-width: 220px; }";
    html += ".value { font-size: 24px; font-weight: bold; color: #0066cc; }";
    html += ".safe { color: #1b8f3a; font-weight: bold; }";
    html += ".warning { color: #d4a400; font-weight: bold; }";
    html += ".danger { color: #d11f1f; font-weight: bold; }";
    html += ".status-label { margin-top: 8px; font-size: 18px; }";
    html += "</style></head><body>";
    html += "<h1>Sensor Dashboard</h1>";

    html += "<div class='sensor'><p>Metana (CH4): <span class='value'>";
    html += String(sensor_mq4, 2);
    html += "</span></p><p class='status-label'>Status: <span class='";
    html += mq4_class;
    html += "'>";
    html += sensor_mq4_status;
    html += "</span></p></div>";

    html += "<div class='sensor'><p>Ammonia (NH3): <span class='value'>";
    html += String(sensor_mq135, 2);
    html += "</span></p><p class='status-label'>Status: <span class='";
    html += mq135_class;
    html += "'>";
    html += sensor_mq135_status;
    html += "</span></p></div>";

    html += "<div class='sensor'><p>Hidrogen Sulfida (H2S): <span class='value'>";
    html += String(sensor_mq136, 2);
    html += "</span></p><p class='status-label'>Status: <span class='";
    html += mq136_class;
    html += "'>";
    html += sensor_mq136_status;
    html += "</span></p></div>";

    html += "<div class='sensor'><p>Kelembapan: <span class='value'>";
    html += String(sensor_humidity, 2);
    html += "%</span></p></div>";

    html += "</body></html>";
    server.send(200, "text/html", html);
}

void setup_webserver() {
    server.on("/", handle_root);
    server.begin();
    Serial.println("Web Server started");
}

void handle_webserver() {
    server.handleClient();
}

#endif