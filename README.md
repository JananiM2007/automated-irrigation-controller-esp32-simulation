#  Automated Irrigation Controller using ESP32

An ESP32-based **Automated Irrigation Controller** that monitors soil moisture (simulated using a potentiometer), processes analog sensor data using **oversampling** and an **Exponential Moving Average (EMA) filter**, and automatically controls a water pump through a relay using **hysteresis-based decision logic**.

This project demonstrates key embedded systems concepts such as ADC processing, signal filtering, sensor calibration, relay interfacing, and closed-loop automation.

---

##  Features

- Analog sensor data acquisition using ESP32 ADC
- Oversampling for improved measurement accuracy
-  Exponential Moving Average (EMA) filtering
-  Moisture percentage calculation using `map()` and `constrain()`
-  Dual-threshold hysteresis logic
-  Automatic relay-controlled pump operation
-  Real-time LCD display
-  LED indicators for soil moisture status
-  Serial Monitor output for debugging

---

##  Components Used

| Component | Quantity |
|-----------|----------|
| ESP32 DevKit V1 | 1 |
| Potentiometer (Soil Moisture Sensor Simulation) | 1 |
| 16×2 I2C LCD | 1 |
| 1-Channel Relay Module | 1 |
| Red LED | 1 |
| Yellow LED | 1 |
| Green LED | 1 |
| 220Ω Resistors | 3 |
| Jumper Wires | As Required |

---

##  Circuit Connections

### Potentiometer

| Potentiometer | ESP32 |
|---------------|-------|
| VCC | 3.3V |
| GND | GND |
| Wiper | GPIO34 |

### Relay Module

| Relay | ESP32 |
|--------|-------|
| VCC | 5V |
| GND | GND |
| IN | GPIO26 |

### LEDs

| LED | ESP32 GPIO |
|-----|------------|
| Green | GPIO18 |
| Yellow | GPIO19 |
| Red | GPIO23 |

### I2C LCD

| LCD | ESP32 |
|-----|-------|
| SDA | GPIO21 |
| SCL | GPIO22 |
| VCC | 5V |
| GND | GND |

---

##  Working Principle

1. The potentiometer simulates varying soil moisture levels.
2. The ESP32 reads the analog voltage through its ADC.
3. Multiple ADC samples are averaged using oversampling.
4. An Exponential Moving Average (EMA) filter smooths the sensor readings.
5. ADC values are converted into moisture percentage using calibration.
6. Hysteresis logic controls the relay:
   - Pump ON when moisture < **30%**
   - Pump OFF when moisture > **45%**
7. LCD displays moisture percentage and pump status.
8. LEDs indicate soil condition:
   - 🟢 Green → Wet
   - 🟡 Yellow → Moderate
   - 🔴 Red → Dry

---

##  Hysteresis Logic

| Moisture Level | Pump Status |
|----------------|-------------|
| < 30% | ON |
| 30% – 45% | Previous State (Deadband) |
| > 45% | OFF |

This deadband prevents rapid relay switching and improves system reliability.

---

##  Project Preview

> Add screenshots of:

- Circuit Diagram
- Wokwi Simulation
- LCD Output
- Serial Monitor
- Relay Status
- Complete Project Setup

---

##  Future Improvements

- Replace the potentiometer with a real soil moisture sensor
- IoT cloud monitoring using MQTT or ThingSpeak
- Mobile application for remote monitoring
- Weather forecast integration
- Automatic irrigation scheduling
- Solar-powered operation
- Data logging and analytics

---

##  Technologies Used

- Embedded C++
- Arduino IDE
- ESP32
- Wokwi Simulator
- I2C Communication
- ADC Processing

---

##  Learning Outcomes

Through this project, the following embedded systems concepts were implemented:

- Analog-to-Digital Conversion (ADC)
- Sensor Calibration
- Oversampling
- Exponential Moving Average (EMA) Filtering
- Digital Signal Processing
- Hysteresis Control
- Relay Interfacing
- GPIO Programming
- Closed-Loop Feedback Control

---

##  License

This project is intended for educational and learning purposes.

---

##  Author

**Janani M**

Electronics and Communication Engineering

