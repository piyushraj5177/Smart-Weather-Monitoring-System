# 🌦️ Smart Weather Monitoring System using ESP32

## 🔍 Objective

Develop a compact weather monitoring solution using ESP32 that can track temperature, humidity, hydrogen gas levels, and rain intensity. Real-time values are shown on an I2C LCD and a buzzer/LED provides safety alerts.

## 🧰 Components

- ESP32 Development Board (with Type-C or Micro USB cable)
- DHT11 Temperature & Humidity Sensor
- MQ-8 Hydrogen Gas Sensor
- Rain Sensor Module
- I2C 16x2 LCD Display
- Buzzer
- LED (with 220Ω resistor)
- Breadboard & Jumper Wires
- Optional: Power Bank for portable use

## 🔌 Circuit Connections

| Component     | Pin         | ESP32 GPIO | Notes                            |
|--------------|-------------|------------|----------------------------------|
| DHT11        | VCC         | 3.3V       | Power                            |
|              | GND         | GND        | Ground                           |
|              | DATA        | GPIO 4     | Data output                      |
| MQ-8 Sensor  | VCC         | 5V         | Requires 5V                      |
|              | GND         | GND        | Ground                           |
|              | AO          | GPIO 35    | Analog gas reading               |
| Rain Sensor  | VCC         | 3.3V/5V    | Power supply                     |
|              | GND         | GND        | Ground                           |
|              | AO          | GPIO 34    | Analog rain detection            |
| Buzzer       | + (VCC)     | GPIO 14    | Buzzer control                   |
|              | - (GND)     | GND        | Ground                           |
| LED          | Anode (+)   | GPIO 26    | Use 220Ω resistor in series      |
|              | Cathode (-) | GND        | Ground                           |
| I2C LCD      | VCC         | 5V         | Power                            |
|              | GND         | GND        | Ground                           |
|              | SDA         | GPIO 21    | I2C data                         |
|              | SCL         | GPIO 22    | I2C clock                        |

## ⚙️ How It Works

- **DHT11** sensor measures temperature & humidity.
- **MQ-8** sensor checks hydrogen gas. If >2000, LED and buzzer alert.
- **Rain Sensor** gives analog moisture value (lower = wetter).
- All data is displayed on a 16x2 I2C LCD.

### LCD Output Format

```
T:<temperature> H:<humidity>
G:<gas_value> R:<rain_value>
```

📌 Example:
```
T:27.0 H:65.0
G:380   R:1023
```

## 💻 Arduino Code Overview

- Initialize all sensors and LCD in `setup()`.
- In `loop()`, continuously read values, display them, and alert if gas is too high.
- Use `analogRead()` for gas and rain sensors, and `dht.readTemperature()/readHumidity()` for DHT11.

> **Thresholds:**  
> - Hydrogen gas (MQ-8): >2000 triggers alert  
> - Rain: Dry ~1023, Wet ~300 (for reference only)

## 📌 Notes

- Connect all grounds together properly.
- Confirm your LCD’s I2C address using an I2C scanner sketch.
- Always use proper resistors (especially for the LED).

## ✅ Result

The system monitors weather parameters in real-time with visual and audio alerts for gas leaks. It's suitable for weather stations, basic IoT monitoring, and safety-critical environments.
