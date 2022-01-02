#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C screen(0x27,16,2);

int relay=2;
int moistureSensor=A0;
int limitVal=40; // humidity value limit at which the system operates
int moisture;
int moisture_map;

void setup() {
  screen.init(); // start to LCD
  screen.backlight(); // include to background light
  pinMode(relay,OUTPUT);
  pinMode(moistureSensor,INPUT);

  digitalWrite(relay,HIGH); // low and high are written in reverse because it reads the value from the relay in reverse

  Serial.begin(9600);

}

void loop() {
  moisture = analogRead(moistureSensor);
  moisture_map = map(moisture, 0, 1023, 100, 0); //to convert the default humidity values into logical numerical data
  Serial.println(moisture);
  Serial.println(moisture_map);
  
  if(moisture_map>=limitVal) // if the measured humidity is higher than the limit value
  {
    digitalWrite(relay,LOW);
    screen.setCursor(13,1);
    screen.print("%"); 
    screen.setCursor(14,1);
    screen.print(moisture_map); // to read to humidity info on LCD
    delay(500);
    screen.setCursor(0,0);
    screen.print("HIGH HUMIDITY   ");
    screen.setCursor(0,1);
    screen.print("SYSTEM OFF    ");


  }
  else // if the measured humidity is lower than the limit value
  {
    digitalWrite(relay,HIGH);
    screen.setCursor(13,1);
    screen.print("%");
    screen.setCursor(14,1);
    screen.print(moisture_map); // to read to humidity info on LCD
    delay(500);
    screen.setCursor(0,0);
    screen.print("LOW HUMIDITY   ");
    screen.setCursor(0,1);
    screen.print("SYSTEM ON    ");
  }
  

}
