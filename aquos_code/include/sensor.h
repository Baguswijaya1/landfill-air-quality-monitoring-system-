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

struct Sensor
{
    int buffer = 0;
    float tempval = 0.0f;
    float measured_value = 0.0f;    
    float prev_value = 0.0f;
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
    return movingAvg(storedVal, buffer, value, prev_value);
}

float readHumidity(const int pin, float& storedVal, int& buffer, float& prev_value){
    float hum = humsensor.getHumidity();
    return movingAvg(storedVal, buffer, hum, prev_value);
}



#endif
