#ifndef WEB_SERVER_DASHBOARD_H
#define WEB_SERVER_DASHBOARD_H

#include <Arduino.h>
#include <WebServer.h>

WebServer server(80);

// // Global variables for sensor values (you'll pass these from main)
float sensor_mq4 = 0;
float sensor_mq135 = 0;
float sensor_mq136 = 0;
float sensor_humidity = 0;

void handle_root() {
    String html = R"(
    <!DOCTYPE html>
    <html>
    <head>
        <title>Aquos Sensor Dashboard</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
            body { font-family: Arial; text-align: center; padding: 20px; }
            .sensor { display: inline-block; margin: 10px; padding: 15px; border: 1px solid #ccc; border-radius: 5px; }
            .value { font-size: 24px; font-weight: bold; color: #0066cc; }
        </style>
    </head>
    <body>
        <h1>Aquos Sensor Dashboard</h1>
        <div class="sensor">
            <p>CH4 (MQ4): <span class="value">)";
    html += String(sensor_mq4, 2);
    html += R"(</span></p>
        </div>
        <div class="sensor">
            <p>NH3 (MQ135): <span class="value">)";
    html += String(sensor_mq135, 2);
    html += R"(</span></p>
        </div>
        <div class="sensor">
            <p>H2S (MQ136): <span class="value">)";
    html += String(sensor_mq136, 2);
    html += R"(</span></p>
        </div>
        <div class="sensor">
            <p>Humidity: <span class="value">)";
    html += String(sensor_humidity, 2);
    html += R"(%</span></p>
        </div>
    </body>
    </html>
    )";
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