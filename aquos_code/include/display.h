#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal.h>

#define RSpin 23
#define ENpin 22
#define D4pin 19
#define D5pin 18
#define D6pin 5
#define D7pin 17

#define button 25

LiquidCrystal lcd(RSpin, ENpin, D4pin, D5pin, D6pin, D7pin);
bool page_state = false;
int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState= 0;

void setup_display() { 
    lcd.begin(16,2);
    pinMode(button, INPUT);
}

void serial_display(float& mq4, float& mq135, float& mq136, float& dht){
    Serial.print("CH4\t: "); Serial.println(mq4);
    Serial.print("NH3\t: "); Serial.println(mq135);
    Serial.print("H2S\t: "); Serial.println(mq136);
    Serial.print("dht\t: "); Serial.println(dht);
    Serial.println("");
}

void lcd_display_page1(float& mq4, float& mq135){
    char buf[8];
    // First row: label + value
    lcd.setCursor(0, 0);
    lcd.print("CH4:");
    dtostrf(mq4, 5, 2, buf); // width 5, 2 decimals
    lcd.setCursor(5, 0);
    lcd.print(buf);
    // Clear any leftover chars
    lcd.print("  ");

    // Second row: label + value
    lcd.setCursor(0, 1);
    lcd.print("NH3:");
    dtostrf(mq135, 5, 2, buf);
    lcd.setCursor(5, 1);
    lcd.print(buf);
    lcd.print("  ");
}

void lcd_display_page2(float& mq136, float& dht){
    char buf[8];
    // First row: H2S
    lcd.setCursor(0, 0);
    lcd.print("H2S:");
    dtostrf(mq136, 5, 2, buf);
    lcd.setCursor(5, 0);
    lcd.print(buf);
    lcd.print("  ");

    // Second row: HUM
    lcd.setCursor(0, 1);
    lcd.print("HUM:");
    dtostrf(dht, 5, 2, buf);
    lcd.setCursor(5, 1);
    lcd.print(buf);
    lcd.print("  ");
}

void display_sensor(float& mq4, float& mq135, float& mq136, float& dht){
  buttonState = digitalRead(button);

  // Increment counter on button press (transition from HIGH to LOW)
  if (buttonState == LOW && lastButtonState == HIGH) {
    buttonPushCounter++;
    delay(50);
  }
  
  // Display based on button press count
  if (buttonPushCounter % 2 == 0) {
    lcd_display_page1(mq4, mq135);
  } else {
    lcd_display_page2(mq136, dht);
  }
  
  lastButtonState = buttonState;
}

#endif