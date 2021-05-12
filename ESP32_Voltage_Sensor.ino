#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x26, 16, 2);
int val11;
int val1;
int val2;

float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0; //30k
float R2 = 7500.0; //7500 ohm resistor

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

  analogReadResolution(10);

  delay(3000);
  lcd.clear();
}

void loop() {  
  float batteryLevel;
  float voltageLevel;
  val11 = analogRead(33);  
  
  // read the value at analog input
  if (val11 >= (val1 - 1) && val11 <= (val1 + 1)) {
    val1 = val11;
  } else if (val11 < (val1 - 50)) {
    val1 = val11;
  } else if (val11 > (val1 + 50)) {
    val1 = val11;
  }

  val2 = val1 / 4;
  
  vout = (val1 * 3.3) / 1023.0;
  vin = vout * (R2/(R1+R2));

  if (val2 > 49) {
    batteryLevel = 100.0;
  } else if (val2 < 20) {
    batteryLevel = 0.0;
  } else {
    batteryLevel = mapf(val2, 0.0, 49.0, 0.0, 99.0);
  }

  Serial.print(val11);
  Serial.print("\t");
  Serial.print(val1);
  Serial.print("\t");
  Serial.print(val2);
  Serial.print("\t");
  Serial.print(vin, 5);
  Serial.print("\t");
  
  lcd.setCursor(0,0);
  lcd.print("       ");  
  lcd.setCursor(0,1);
  lcd.print("       "); 
  lcd.setCursor(0,0);
  lcd.print(val1);  
  lcd.setCursor(0,1);
  lcd.print(val2);  
  
  Serial.print("voltageLevel :");
  Serial.print("\t");
  Serial.print(vout, 3);
  Serial.print("V.");
  
//  lcd.setCursor(4,0);
//  lcd.print("Volt.");  
  lcd.setCursor(9,0);
  lcd.print(vout, 3);
  lcd.setCursor(15,0);
  lcd.print("V");
  
  Serial.print("\t");
  Serial.print("batteryLevel :");
  Serial.print("\t");
  Serial.print(batteryLevel);
  Serial.println("%");
  
//  lcd.setCursor(4,1);
//  lcd.print("Batt.");  
  lcd.setCursor(9,1);
  lcd.print(batteryLevel);
  lcd.setCursor(15,1);
  lcd.print("%");
  
  delay(100);
}
