#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
#define DHTPIN 4
#define DHTTYPE DHT11
#define MQ8PIN 35
#define RAINPIN 34
#define BUZZER 14
#define LED 26

// Sensor & display objects
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Use 0x3F if 0x27 doesn't work

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);         // SDA = GPIO 21, SCL = GPIO 22 for ESP32
  dht.begin();
  lcd.begin(16, 2);
  lcd.backlight();            // Turn on LCD backlight

  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Weather Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Validate sensor data
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.setCursor(0, 0);
    lcd.print("DHT Read Error ");
    delay(2000);
    return;
  }

  int gasValue = analogRead(MQ8PIN);
  int rainValue = analogRead(RAINPIN);

  // Print to Serial Monitor
  Serial.print("Temp: "); Serial.print(temp); Serial.print("°C, ");
  Serial.print("Humidity: "); Serial.print(hum); Serial.print("%, ");
  Serial.print("H2 Gas: "); Serial.print(gasValue); Serial.print(", ");
  Serial.print("Rain: "); Serial.println(rainValue);

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("T:"); lcd.print(temp, 1);
  lcd.print(" H:"); lcd.print(hum, 1);

  lcd.setCursor(0, 1);
  lcd.print("G:"); lcd.print(gasValue);
  lcd.print(" R:"); lcd.print(rainValue);

  // Alert if gas value too high
  if (gasValue > 2000) {  // Adjust threshold if needed
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED, LOW);
  }

  delay(2000); // Update every 2 seconds
}