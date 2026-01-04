---

# 🚨 Emergency SOS Smart Band (ESP32)

An **ESP32-based Emergency SOS Smart Band** developed for **women’s safety and personal emergency response**.
The device instantly sends an SOS SMS containing **live GPS location data** and **automatically places emergency calls** with an **auto-redial mechanism** until the call is answered.

> **Designed for rapid response when every second matters.**

---

## ✨ Key Features

* One-button **SOS emergency trigger**
* **Automatic SOS activation** on abnormal motion or fall detection
* **Live GPS location tracking**
* SOS **SMS alert with Google Maps location link**
* **Automatic voice calling** with auto-redial every **30 seconds**
* Real-time system and sensor data on **OLED display**
* Environmental monitoring:

  * Temperature
  * Pressure
  * Altitude
* GSM signal strength monitoring
* **Local time display (UTC-based conversion)**

---

## 🧠 Working Principle

When an SOS event is triggered (manually or automatically):

1. An **SOS SMS alert** is sent to the emergency contact
2. **Live GPS coordinates** are included via a Google Maps link
3. An **emergency call** is initiated
4. If unanswered, the system **retries every 30 seconds**
5. The cycle continues until the call is successfully answered

---

## 🛠 Hardware Components

* ESP32 Development Board
* SIM800C GSM Module
* GPS Module (Neo-6M or equivalent)
* SSD1306 OLED Display (128 × 64)
* BMP280 Sensor (Temperature, Pressure, Altitude)
* MPU6050 Sensor (Motion & Fall Detection)
* SOS Push Button
* GSM & GPS Antennas
* Rechargeable Battery / Power Supply

---

## 🔌 Pin Configuration

### 📍 GPS Module (UART2)

| ESP32 Pin | GPS Pin |
| --------- | ------- |
| GPIO 16   | RX      |
| GPIO 17   | TX      |

### 📞 SIM800C GSM Module (UART1)

| ESP32 Pin | SIM800C Pin |
| --------- | ----------- |
| GPIO 25   | RX          |
| GPIO 26   | TX          |

### 🆘 SOS Push Button

| ESP32 Pin | Function                  |
| --------- | ------------------------- |
| GPIO 23   | SOS Button (INPUT_PULLUP) |

---

## 📚 Required Libraries

Install the following libraries via **Arduino Library Manager**:

* Adafruit SSD1306
* Adafruit GFX Library
* Adafruit BMP280 Library
* Adafruit MPU6050 Library
* Adafruit Unified Sensor
* TinyGPS++

---

## ⚙️ Configuration

Edit the emergency contact number in the source code:

```cpp
const char ALERT_NUMBER[] = "+XXXXXXXXXXXX";
```

> 🔧 Replace `XXXXXXXXXX` with the **mobile number** and `+XX` with the **country code**
> *(Example: `+91XXXXXXXXXX` for India)*

---

## 🌍 Time Zone Configuration (UTC → Local Time)

The firmware converts **UTC time received from GPS** to **local time** using a fixed offset.

By default, the code is set for **India (IST – UTC +5:30)**.
If you are using this project in **any other country**, you must change the UTC offset values to match your region.

### 🇮🇳 Example: India (IST – UTC +5:30)

```cpp
int utcOffsetHours = 5;
int utcOffsetMinutes = 30;
```

### 🇺🇸 Example: United States (Eastern Standard Time – UTC −5:00)

```cpp
int utcOffsetHours = -5;
int utcOffsetMinutes = 0;
```

### 🇬🇧 Example: United Kingdom (GMT – UTC +0:00)

```cpp
int utcOffsetHours = 0;
int utcOffsetMinutes = 0;
```

> ⚠️ **Important:**
>
> * Set the UTC offset according to your **local region**
> * Incorrect values will result in **wrong time shown on OLED and SMS alerts**
> * Daylight Saving Time (DST), if applicable, must be handled manually

---

## 📩 SMS Alert Contents

Each SOS SMS includes:

* Emergency alert message
* Device identifier
* Current local time
* Latitude & Longitude
* Altitude (meters)
* Atmospheric pressure (hPa)
* Temperature (°C)
* Google Maps live location link

---

## 🖥 OLED Display Information

The OLED screen displays:

* Device name
* Current local time
* Latitude & Longitude
* Temperature
* Altitude
* Pressure
* SOS system status

---

## 🔁 Auto-Redial Logic

* Automatically places a call to the emergency contact
* Retries every **30 seconds** if unanswered
* Stops **only after the call is successfully answered**

---

## 🚀 Upload & Deployment Instructions

1. Open **Arduino IDE**
2. Select **Board → ESP32 Dev Module**
3. Choose the correct **COM port**
4. Install all required libraries
5. Upload the code
6. Power the device and verify GSM/GPS connectivity

---

## ⚠️ Important Notes

* SIM card must support **SMS and voice calling**
* Ensure adequate **GSM network coverage**
* GPS requires **clear sky visibility** for faster fix
* Intended strictly for **educational, research, and safety applications**

---

## 🔮 Future Enhancements

* Support for **multiple emergency contacts**
* Companion **mobile application**
* Battery level monitoring & alerts
* Cloud-based data logging
* Haptic feedback (vibration motor / buzzer)

---

## ❤️ Safety First

**Emergency SOS Smart Band — Because help should never be far away.**

---

## 🏁 Project Credits & Acknowledgements

This project was **conceptualized, planned, researched, and developed** under the **TARRL (Tulunadu Amateur Radio Relay League)** initiative, with a focus on **safety & assurity-oriented embedded systems**.

🔗 **Official Website:** [https://www.tarrltulunadu.in](https://www.tarrltulunadu.in)

---

### 👤 Core Contributors (TARRL)

* **Mr. S. Renu Kshirsagar (VU3CQM)**
  *Trustee & E&TW Head – TARRL*
  **Software Development & System Planning**

* **Vaibhav V. K. Naik (VU3ZNL)**
  *President & Honorable Trustee – TARRL*
  Department of Electronics
  St. Philomena Pre-University College, Puttur
  **Software & Hardware Development, Research, and Overall Project Planning**

---

### 🏢 Institutional Support & Funding

* **Tulunadu Amateur Radio Relay League (TARRL)**
  Provided organizational support and a research-driven environment for project planning and development.

* **IDT Labs**
  Department of Electronics and Communication Engineering
  KVG College of Engineering (KVGCE), Sullia

  The authors sincerely acknowledge **IDT Labs** for **financial support (funding)**, **planning assistance**, and **presentation guidance**. Special thanks are extended to the **11 team members** who supported the project through collaboration and teamwork.

---

### 📜 Declaration

This project is intended solely for **educational, research, and safety-focused use**.
All contributors have been duly acknowledged, and no conflict of interest is declared.

---

