#include <Arduino.h>
#include <vector>
#include <sensor.h>
#include <display.h>

Sensor MQ4;
Sensor MQ135;
Sensor MQ136;
Sensor humidity;

void setup() {
  Serial.begin(9600);
  Serial.println("starting sensor");
  setup_display();
}

void loop() {
  MQ4.measured_value = readSensor(mq4_pin, MQ4.tempval, MQ4.buffer, MQ4.prev_value);
  MQ135.measured_value = readSensor(mq135_pin, MQ135.tempval, MQ135.buffer, MQ135.prev_value);
  MQ136.measured_value = readSensor(mq136_pin, MQ136.tempval, MQ136.buffer, MQ136.prev_value);
  humidity.measured_value = readHumidity(dht22_pin, humidity.tempval, humidity.buffer, humidity.prev_value);
  serial_display(MQ4.measured_value, MQ135.measured_value, MQ136.measured_value, humidity.measured_value);

  display_sensor(MQ4.measured_value, MQ135.measured_value, MQ136.measured_value, humidity.measured_value);
}

