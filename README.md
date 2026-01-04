# 🚨 Emergency SOS Smart Band (ESP32)

An **ESP32-based Emergency SOS Smart Band** designed for **women’s safety**.
The device sends an SOS SMS with live GPS location and automatically places calls to an emergency contact until the call is answered.

---

## 📌 Features

* One-button SOS emergency trigger
* Automatic SOS on abnormal motion / fall detection
* Live GPS tracking
* SMS alert with Google Maps location link
* Automatic calling with **auto-redial every 30 seconds**
* Real-time sensor data on OLED display
* Temperature, pressure, altitude monitoring
* GSM signal strength monitoring
* IST time conversion

---

## 🧠 Working Principle

When SOS is triggered:

1. SMS alert is sent to the emergency number
2. GPS location is shared via Google Maps link
3. Phone call is initiated
4. If unanswered, device retries every 30 seconds
5. Process continues until the call is answered

---

## 🛠 Hardware Components

* ESP32 Development Board
* SIM800C GSM Module
* GPS Module (Neo-6M or equivalent)
* SSD1306 OLED Display (128×64)
* BMP280 Sensor (Temperature, Pressure, Altitude)
* MPU6050 Sensor (Motion / Fall Detection)
* SOS Push Button
* GSM & GPS Antennas
* Battery / Power Supply

---

## 🔌 Pin Connections

### GPS (UART2)

| ESP32 Pin | GPS |
| --------- | --- |
| GPIO 16   | RX  |
| GPIO 17   | TX  |

### SIM800C (UART1)

| ESP32 Pin | SIM800 |
| --------- | ------ |
| GPIO 25   | RX     |
| GPIO 26   | TX     |

### SOS Button

| ESP32 Pin | Function                  |
| --------- | ------------------------- |
| GPIO 23   | SOS Button (INPUT_PULLUP) |

---

## 📚 Required Libraries

Install the following libraries from Arduino Library Manager:

* Adafruit SSD1306
* Adafruit GFX Library
* Adafruit BMP280 Library
* Adafruit MPU6050 Library
* Adafruit Unified Sensor
* TinyGPS++

---

## ⚙️ Configuration

Edit the emergency contact number in the code:

```cpp
const char ALERT_NUMBER[] = "+91XXXXXXXXXX";
```

---

## 📩 SMS Alert Includes

* SOS Alert Message
* Device name
* Time (IST)
* Latitude & Longitude
* Altitude (m)
* Pressure (hPa)
* Temperature (°C)
* Google Maps live location link

---

## 🖥 OLED Display Information

* Device name
* Current time (IST)
* Latitude & Longitude
* Temperature
* Altitude
* Pressure
* SOS status

---

## 🔁 Auto-Redial Feature

* Automatically calls emergency contact
* Retries every **30 seconds**
* Stops only when call is answered

---

## 🚀 Upload Instructions

1. Open Arduino IDE
2. Select **Board → ESP32 Dev Module**
3. Select correct COM port
4. Install required libraries
5. Upload the code
6. Power the device

---

## ⚠️ Important Notes

* SIM card must support **SMS and calling**
* Ensure sufficient network signal
* Intended for **educational and safety use only**

---

## 📈 Future Improvements

* Multiple emergency contacts
* Mobile app integration
* Battery level monitoring
* Cloud data logging
* Vibration / buzzer feedback

---

## ❤️ Safety First

**Emergency SOS Smart Band – Every second matters.**
**Credits**
1.Vaibhav V K Naik ( VU3ZNL) - President & Honable Trustee - TARRL , Dept of Electronics - ST Philomena Pre University College, Puttur.
2.IDT Labs - Department of Electronics and Commnucation - KVG College of Engineering (KVGCE) Sullia.
