#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <DHT22.h>

#define mq4_pin 36
#define mq135_pin 39
#define mq136_pin 34
#define dht22_pin 35

float divider = 5.0f;
DHT22 humsensor(dht22_pin);

// gas status limit
float ch4_safe_limit = 1000.0f;
float ch4_hazard_limit = 1500.0f;
float nh3_safe_limit = 1000.0f;
float nh3_hazard_limit = 1500.0f;
float h2s_safe_limit = 1000.0f;
float h2s_hazard_limit = 1500.0f;

struct Sensor
{
    int buffer = 0;
    float tempval = 0.0f;
    float measured_value = 0.0f;    
    float prev_value = 0.0f;
    String status;
};

float movingAvg(float& storedVal, int& buffer, float value, float& prev_value){
    if (buffer < divider){
        storedVal += value;
        buffer += 1;
        return prev_value;
    } else if (buffer == divider){
        buffer = 0;
        float final_value = storedVal / divider;
        storedVal = 0;
        prev_value = final_value;
        return final_value;
    }
    return prev_value;
}

float readSensor(const int pin, float& storedVal, int& buffer, float& prev_value){
    float value = analogRead(pin);
    float filtered = movingAvg(storedVal, buffer, value, prev_value);
    return filtered;
}

String decide_status(float& sensor_value, float safe_limit, float hazard_limit){
    String status;
    if (sensor_value <= safe_limit) {
        status = "AMAN";
    } else if (sensor_value> safe_limit && sensor_value <= hazard_limit) {
        status = "SEDANG";
    } else {
        status = "BAHAYA";
    }
    return status;
}

float readHumidity(const int pin, float& storedVal, int& buffer, float& prev_value){
    float hum = humsensor.getHumidity();
    return movingAvg(storedVal, buffer, hum, prev_value);
}



#endif
