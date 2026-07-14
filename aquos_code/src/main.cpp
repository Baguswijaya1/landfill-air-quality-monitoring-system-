#include <Arduino.h>
#include <vector>
#include <sensor.h>
#include <display.h>
#include <access_point.h>
#include <web_server_dashboard.h>

Sensor MQ4;
Sensor MQ135;
Sensor MQ136;
Sensor humidity;
Sensor temperature;


const int display_delay = 2000;
unsigned long prevTime = 0;
int counter = 0;

void setup() {
  // Serial.begin(9600);
  Serial.println("starting sensor");
  setup_display();
  setup_sensors();

  setup_access_point();
  setup_webserver();
}

void loop() {
  unsigned long currentTime = millis();
  MQ4.measured_value = readSensor(mq4_pin, MQ4.tempval, MQ4.buffer, MQ4.prev_value);
  MQ135.measured_value = readSensor(mq135_pin, MQ135.tempval, MQ135.buffer, MQ135.prev_value);
  MQ136.measured_value = readSensor(mq136_pin, MQ136.tempval, MQ136.buffer, MQ136.prev_value);
  // humidity.measured_value = readHumidity(dht22_pin, humidity.tempval, humidity.buffer, humidity.prev_value);
  // temperature.measured_value  = readTemperature(dht22_pin, temperature.tempval, temperature.buffer, temperature.prev_value);
  sensors_event_t event;

  MQ4.status = decide_status(MQ4.measured_value, ch4_threshold);
  MQ135.status = decide_status(MQ135.measured_value, nh3_threshold);
  MQ136.status = decide_status(MQ136.measured_value, h2s_threshold);

  if (currentTime - prevTime >= display_delay){
    prevTime = currentTime;
    // humidity.measured_value = readHumidity(dht22_pin, humidity.tempval, humidity.buffer, humidity.prev_value);
    // temperature.measured_value  = readTemperature(dht22_pin, temperature.tempval, temperature.buffer, temperature.prev_value);
    // humidity.measured_value = readHumidity();
    // temperature.measured_value = readTemperature();
    // counter += 1;
    lcd_display_page1(MQ4.measured_value, MQ136.measured_value);
    // if (counter % 2 == 0){
    //   lcd_display_page1(MQ4.measured_value, MQ136.measured_value);
    // }  else {
    //   lcd_display_page2(MQ135.measured_value, humidity.measured_value);
    // }
  }

  sensor_mq4 = MQ4.measured_value;
  sensor_mq135 = MQ135.measured_value;
  sensor_mq136 = MQ136.measured_value;
  // sensor_humidity = humidity.measured_value;
  sensor_humidity = 0;
  sensor_temperature = temperature.measured_value;
  sensor_mq4_status = MQ4.status;
  sensor_mq135_status = MQ135.status;
  sensor_mq136_status = MQ136.status;

  
    
  
  // serial_display(MQ4.measured_value, MQ135.measured_value, MQ136.measured_value, humidity.measured_value, temperature.measured_value);
  // display_sensor(MQ4.measured_value, MQ135.measured_value, MQ136.measured_value, humidity.measured_value);


  handle_webserver();
}

