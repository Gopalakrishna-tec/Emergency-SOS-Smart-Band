#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <TinyGPS++.h>

/*************** USER CONFIG ****************/
const char ALERT_NUMBER[] = "+918088765085";

/*************** OLED CONFIG ****************/
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/*************** GPS ON UART2 ****************/
TinyGPSPlus gps;
HardwareSerial GPS_Serial(2);

#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
#define GPS_BAUD   115200

String LAT = "--";
String LON = "--";
String IST_TIME = "NO FIX";

/*************** BMP280 ****************/
Adafruit_BMP280 bmp;
float temperature = 0.0, pressure_hPa = 0.0, altitude = 0.0;

/*************** MPU6050 ****************/
Adafruit_MPU6050 mpu;
const float MOTION_THRESHOLD = 23.0;
const int SAMPLE_COUNT = 10;

/*************** SOS BUTTON ****************/
#define SOS_BUTTON 23
bool sosFlag = false;
bool smsSent = false;

/*************** SIM800C ON UART1 ****************/
HardwareSerial sim800(1);

#define SIM800_RX_PIN 25
#define SIM800_TX_PIN 26
#define SIM800_BAUD   9600

/*************** SIGNAL STRENGTH ****************/
int lastRssi = 99;

/*************** READ GSM RESPONSE ****************/
String readResponse(unsigned long timeoutMs) {
  unsigned long start = millis();
  String resp = "";
  while (millis() - start < timeoutMs) {
    while (sim800.available()) {
      resp += char(sim800.read());
    }
  }
  return resp;
}

/*************** UPDATE CSQ ****************/
void updateSignalStrength() {
  sim800.println("AT+CSQ");
  delay(200);
  String r = readResponse(400);

  int idx = r.indexOf("+CSQ:");
  if (idx >= 0) {
    int comma = r.indexOf(",", idx);
    if (comma > idx) {
      String v = r.substring(idx + 5, comma);
      v.trim();
      lastRssi = v.toInt();
    }
  }
}

/*************** SEND SMS ****************/
void sendSMS(const String &lat, const String &lon, const String &timeStr,
             float alt, float pres, float tempC) {

  sim800.println("AT");
  delay(300);

  sim800.println("AT+CMGF=1");
  delay(300);

  sim800.print("AT+CMGS=\"");
  sim800.print(ALERT_NUMBER);
  sim800.println("\"");
  delay(400);

  sim800.println("SOS ALERT!");
  sim800.println("Women Safety Device V1.0");
  sim800.print("Time: "); sim800.println(timeStr);
  sim800.print("Lat: "); sim800.println(lat);
  sim800.print("Lon: "); sim800.println(lon);
  sim800.print("Alt: "); sim800.print(alt); sim800.println(" m");
  sim800.print("P: "); sim800.print(pres); sim800.println(" hPa");
  sim800.print("T: "); sim800.print(tempC); sim800.println(" C");

  sim800.print("Map: https://maps.google.com/?q=");
  sim800.print(lat); sim800.print(","); sim800.println(lon);

  delay(300);
  sim800.write(26); // CTRL+Z
}

/*************** MAKE A CALL ****************/
void callNumber() {
  sim800.println("AT");
  delay(300);
  sim800.print("ATD");
  sim800.print(ALERT_NUMBER);
  sim800.println(";");
}

/*************** WAIT FOR CALL RESPONSE ****************/
bool callAnswered() {
  unsigned long start = millis();
  while (millis() - start < 15000) { // wait max 15 sec
    if (sim800.available()) {
      String r = sim800.readString();
      r.toUpperCase();

      if (r.indexOf("NO CARRIER") >= 0) return false;
      if (r.indexOf("BUSY") >= 0)       return false;
      if (r.indexOf("NO ANSWER") >= 0)  return false;
      if (r.indexOf("ERROR") >= 0)      return false;
      if (r.indexOf("CONNECT") >= 0)    return true;
      if (r.indexOf("OK") >= 0)         return true;
    }
  }
  return false;
}

/*************** AUTO REDIAL EVERY 30 SEC ****************/
void autoRedialUntilAnswered() {

  while (true) {
    display.clearDisplay();
    display.setCursor(5, 20);
    display.print("Calling...");
    display.display();

    callNumber();

    bool ok = callAnswered();
    if (ok) {
      display.clearDisplay();
      display.setCursor(5, 20);
      display.print("CALL ANSWERED");
      display.display();
      return;  // STOP
    }

    // Call failed → retry after 30 sec
    display.clearDisplay();
    display.setCursor(5, 20);
    display.print("No Answer");
    display.setCursor(5, 35);
    display.print("Retrying in 30s");
    display.display();

    for (int i = 0; i < 30; i++) delay(1000);
  }
}

/*************** SETUP ****************/
void setup() {
  Serial.begin(115200);
  Wire.begin();

  pinMode(SOS_BUTTON, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) while (1);
  display.clearDisplay();

  if (!bmp.begin(0x76)) while (1);

  if (!mpu.begin()) while (1);
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  GPS_Serial.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  sim800.begin(SIM800_BAUD, SERIAL_8N1, SIM800_RX_PIN, SIM800_TX_PIN);
  delay(2000);
}

/*************** MAIN LOOP ****************/
void loop() {

  while (GPS_Serial.available() > 0) {
    gps.encode(GPS_Serial.read());
  }

  if (gps.location.isValid()) {
    LAT = String(gps.location.lat(), 6);
    LON = String(gps.location.lng(), 6);
  }

  if (gps.time.isValid()) {
    int h = gps.time.hour();
    int m = gps.time.minute();
    int s = gps.time.second();

    m += 30;
    if (m >= 60) { m -= 60; h++; }
    h += 5;
    if (h >= 24) h -= 24;

    char buf[16];
    sprintf(buf, "%02d:%02d:%02d", h, m, s);
    IST_TIME = buf;
  }

  temperature = bmp.readTemperature();
  pressure_hPa = bmp.readPressure() / 100.0;
  altitude = bmp.readAltitude(1013.25);

  sensors_event_t a, g, t;
  float sum = 0;
  for (int i = 0; i < SAMPLE_COUNT; i++) {
    mpu.getEvent(&a, &g, &t);
    sum += fabs(a.acceleration.x) +
           fabs(a.acceleration.y) +
           fabs(a.acceleration.z);
  }
  float avgAccel = sum / SAMPLE_COUNT;

  if (avgAccel > MOTION_THRESHOLD) sosFlag = true;
  if (digitalRead(SOS_BUTTON) == LOW) sosFlag = true;

  static unsigned long lastCSQ = 0;
  if (millis() - lastCSQ > 1000) {
    updateSignalStrength();
    lastCSQ = millis();
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Women Safety Device");
  display.setCursor(0, 12);
  display.print("Time: "); display.print(IST_TIME);
  display.setCursor(0, 22);
  display.print("Lat: "); display.print(LAT);
  display.setCursor(0, 32);
  display.print("Lon: "); display.print(LON);
  display.setCursor(0, 42);
  display.print("T:"); display.print(temperature, 1); display.print("C");
  display.setCursor(64, 42);
  display.print("Alt:"); display.print((int)altitude); display.print("m");
  display.setCursor(0, 52);
  display.print("P:"); display.print((int)pressure_hPa); display.print("hPa");
  display.setCursor(64, 52);
  display.print("SOS:"); display.print(sosFlag ? "YES" : "NO");
  display.display();

  /*************** SOS ACTION (SMS + CALL + AUTO-REDIAL) ***************/
  if (sosFlag && !smsSent) {

    display.clearDisplay();
    display.setCursor(10, 24);
    display.print("Sending SMS...");
    display.display();

    sendSMS(LAT, LON, IST_TIME, altitude, pressure_hPa, temperature);

    smsSent = true;
    sosFlag = false;

    delay(1500);

    display.clearDisplay();
    display.setCursor(10, 24);
    display.print("Calling...");
    display.display();

    delay(1000);

    autoRedialUntilAnswered();  // <---- MAIN LOGIC ADDED
  }

  delay(50);
}
