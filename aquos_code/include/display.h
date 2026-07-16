#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <sensor.h>

#define RSpin 4
#define ENpin 5
#define D4pin 19
#define D5pin 21
#define D6pin 22
#define D7pin 23

#define button 25

LiquidCrystal lcd(RSpin, ENpin, D4pin, D5pin, D6pin, D7pin);
// bool page_state = false;
// int buttonPushCounter = 0;
// int buttonState = 0;
// int lastButtonState= 0;

void setup_display() { 
    lcd.begin(16,2);
    lcd.setCursor(2,0);
    lcd.print("AQUOS-BATUR");
    lcd.setCursor(2,1);
    lcd.print("KKN-UGM 2026");
    delay(2000);
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(500);
}

void serial_display(float& mq4, float& mq135, float& mq136, float& dht, float& temp){
    Serial.print("CH4\t: "); Serial.print(mq4);
    Serial.print("\tNH3\t: "); Serial.print(mq135);
    Serial.print("\tH2S\t: "); Serial.print(mq136);
    Serial.print("\tdht\t: "); Serial.print(dht);
    Serial.print("\ttemp\t: "); Serial.print(temp);
    Serial.println("");
}

void lcd_display_page1(float& mq4, float& mq136){
    char buf[16];

    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("CH4:");
    dtostrf(mq4, 5, 2, buf);
    lcd.setCursor(5, 0);
    lcd.print(buf);
    if (mq4 > ch4_threshold){
        lcd.setCursor(14, 0);
        lcd.print("!!");
    }


    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("H2S:");
    dtostrf(mq136, 5, 2, buf);
    lcd.setCursor(5, 1);
    lcd.print(buf);
    if (mq136 > h2s_threshold){
        lcd.setCursor(14, 1);
        lcd.print("!!");
    }
}

void lcd_display_page2(float& temp, float& hum){
    char buf[16];

    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    dtostrf(temp, 5, 2, buf);
    lcd.setCursor(5, 0);
    lcd.print(buf);

    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Hum:");
    dtostrf(hum, 5, 2, buf);
    lcd.setCursor(5, 1);
    lcd.print(buf);
}

#endif
