#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

#define mq4_pin 36
#define mq135_pin 39
#define mq136_pin 34
#define dht22_pin 35

#define DHTTYPE DHT22

float divider = 5.0f;
DHT_Unified dht(dht22_pin, DHTTYPE);
// // in analog read
// gas status limit
// float ch4_threshold = 513.0f;
// float nh3_threshold = 1;
// float h2s_threshold = 581.0f;

// scaled to /15
float ch4_threshold = 34.20;
float nh3_threshold = 1;
float h2s_threshold = 38.733f;

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

String decide_status(float sensor_value, float hazard_threshold){
    String status;  
    if (sensor_value < hazard_threshold){
        status = "AMAN";
    } else {
        status = "BURUK";
    }
    return status;
}

void setup_sensors(){
    // analogSetPinAttenuation(mq4_pin, ADC_11db);
    analogSetPinAttenuation(mq135_pin, ADC_11db);
    // analogSetPinAttenuation(mq136_pin, ADC_11db);
    dht.begin();
}

float readHumidity(){
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)){
        Serial.println("error reading temperature");
        return 0.1;
    } else {
        return event.temperature;
    }
}

float readTemperature(){
    sensors_event_t event;
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)){
        Serial.println("error reading humidity");
        return 0.1;
    } else{
        return event.relative_humidity;
    }
}

float change_to_scale(float value){
    return value/15;
}



#endif
