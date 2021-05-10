
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x26, 16, 2);
int val11;
int val1;
float val2;

double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();
  
  lcd.setCursor(1, 0);
  lcd.print("Voltage Sensor");
  lcd.setCursor(3, 1);
  lcd.print("Started...");
  
  delay(3000);
  lcd.clear();
}

void loop() {
  float batteryLevel;
  float voltageLevel;
  val11=analogRead(0);  
  
  voltageLevel = mapf(val11, 1618.0, 3118.0, 3.3, 4.2);
  batteryLevel = mapf(val11, 1618.0, 3118.0, 0.0, 100.0);
  
  Serial.print("voltageLevel :");
  lcd.setCursor(3,0);
  lcd.print("Volt.");
  
  Serial.print("\t");
  Serial.print(voltageLevel);
  Serial.print("V.");
  lcd.setCursor(9,0);
  lcd.print(voltageLevel);
  lcd.setCursor(15,0);
  lcd.print("V");
  
  Serial.print("\t");
  Serial.print("batteryLevel :");
  lcd.setCursor(3,1);
  lcd.print("Batt.");
  
  Serial.print("\t");
  Serial.print(batteryLevel);
  Serial.println("%");
  lcd.setCursor(9,1);
  lcd.print(batteryLevel);
  lcd.setCursor(15,1);
  lcd.print("%");
  
  delay(500);
}
