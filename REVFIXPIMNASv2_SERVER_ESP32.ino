#include "SPI.h"
#include "TFT_eSPI.h"
#include <TouchScreen.h>
#include <TinyGPSPlus.h>
#include "EBYTE.h"
#include "userInterface.h"
#include "mapMerbabu.h"
#include "mapLawu.h"

unsigned long previousMillis = 0;          // will store last time LED was updated
unsigned long previousMillis2 = 0;         // will store last time LED was updated
unsigned long previousMillis3 = 0;         // will store last time LED was updated
unsigned long previousMillisTransmit = 0;  // will store last time LED was updated
unsigned long previousMillisReceive = 0;   // will store last time LED was updated
unsigned long Last;
unsigned long previousMillisSimulation = 0;  // will store last time LED was updated

// constants won't change:
const long interval = 1000;          // interval at which to blink (milliseconds)
const long interval2 = 200;          // interval at which to blink (milliseconds)
const long interval3 = 100;          // interval at which to blink (milliseconds)
const long intervalTransmit = 4000;  // interval at which to blink (milliseconds)
const long intervalReceive = 1000;   // interval at which to blink (milliseconds)
const long intervalSimulation = 1000;

#define PIN_RX 3  // Serial2 RX (connect this to the EBYTE Tx pin)
#define PIN_TX 1  // Serial2 TX pin (connect this to the EBYTE Rx pin)

#define PIN_M0 19  // D4 on the board (possibly pin 24)
#define PIN_M1 22  // D2 on the board (possibly called pin 22)
#define PIN_AX 21  // D15 on the board (possibly called pin 21)

// LORA
EBYTE Transceiver(&Serial, PIN_M0, PIN_M1, PIN_AX);
char dataTransmit[25];
char dataReceive[25];
float latReceive, lngReceive;
int ok;

// TFT
#define MINPRESSURE 10
#define MAXPRESSURE 40000
TFT_eSPI tft = TFT_eSPI();                    // Invoke custom library
const int XP = 27, XM = 15, YP = 4, YM = 14;  //ID=0x9341
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 1000);
int pixel_x, pixel_y, point_z;  //Touch_getXY() updates global vars
#define PRIMARY 0xa512
int count_touch;
int lock_touch;

int menuMountain;
int menuSubMountain;

int mode;

// GPS
#define RXD2 16
#define TXD2 17
static const uint32_t GPSBaud = 115200;
TinyGPSPlus gps;
float latGPS, lngGPS;
int altGPS;
int GPSday, GPSmonth, GPSyear, GPShour, GPSminute, GPSsecond;
float lat, lng;
int alt;

//Dummy GPS
float latDummyGPS = -6.9239243, lngDummyGPS = 107.7745552;
int altDummyGPS = 364;

// UserInterface
int menu;
int sos;
int sosNav;
int jarakMap = 1;

const int potPin = 36;

// Potentiometer value
int potValue = 0;
int battery;

void GetTSPoint() {
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);  //restore shared pins
  pinMode(XM, OUTPUT);

  // if (lock_touch == 0) {
  pixel_x = map(p.x, 3600, 700, 0, 240);
  pixel_y = map(p.y, 800, -2700, 0, 320);
  point_z = p.z;
  //   lock_touch = 1;
  // }

  // if (p.z < -10) {
  //   count_touch++;
  // }

  // if (count_touch > 5) {
  //   lock_touch = 0;
  //   count_touch = 0;
  // }
  // Serial.print("x: ");
  // Serial.print(pixel_x);
  // Serial.print("y: ");
  // Serial.print(pixel_y);
  // Serial.print("z: ");
  // Serial.println(point_z);

  // Serial.print("l: ");
  // Serial.println(lock_touch);
  // Serial.print("c: ");
}

void setup() {
  Serial.begin(9600);
  Transceiver.init();
  Transceiver.SetAddressH(0b11111111);
  Transceiver.SetAddressL(0b11111111);
  Transceiver.SetSpeed(0b00011000);
  Transceiver.SetChannel(0b00000110);
  Transceiver.SetOptions(0b01000100);
  Transceiver.SaveParameters(PERMANENT);
  Transceiver.PrintParameters();

  Serial2.begin(GPSBaud, SERIAL_8N1, RXD2, TXD2);
  tft.init();
  tft.setRotation(0);
  pinMode(potPin, INPUT_PULLUP);
  // verifSOS(40, 130);
  menu = 0;
}

void loop() {

  unsigned long currentMillis = millis();

  while (Serial2.available() > 0)
    if (gps.encode(Serial2.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10) {
    while (true)
      ;
  }
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    GPSsecond = gps.time.second();
    GPSminute = gps.time.minute();
    GPShour = gps.time.hour();
    GPShour = GPShour + 7;
    if (GPShour > 23) {
      GPShour = GPShour - 24;
    } else {
      if (GPShour < 0) {
        GPShour = GPShour + 24;
      }
    }
    GPSday = gps.date.day();
    GPSmonth = gps.date.month();
    GPSyear = gps.date.year();
    if (mode == 1) {
      if (gps.location.isValid()) {
        lat = latGPS;
        lng = lngGPS;
        alt = altGPS;
      }
    } else if (mode == 2) {
      lat = latDummyGPS;
      lng = lngDummyGPS;
      alt = altDummyGPS;
    }
  }

  unsigned long currentMillis2 = millis();

  if (currentMillis2 - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis2;
    sos = 0;
    userInterface();
    if (ok == 1) {
      writeText(75, 17, TFT_TRANSPARENT, 1, "Connected S0");
    } else if (ok == 2) {
      writeText(75, 17, TFT_TRANSPARENT, 1, "Connected S1");
    } else if (ok == 3) {
      writeText(75, 17, TFT_TRANSPARENT, 1, "Connected S2");
    } else {
      writeText(75, 17, TFT_RED, 1, "Not Connected");
    }
    tft.fillRoundRect(205, 0, 30, 15, 2, TFT_BLACK);
    tft.setCursor(210, 5);
    tft.setTextColor(TFT_YELLOW);
    tft.setTextSize(1);
    tft.print(battery);
    tft.print("%");
  }

  unsigned long currentMillis3 = millis();

  if (currentMillis3 - previousMillis3 >= interval3) {
    previousMillis3 = currentMillis3;
    GetTSPoint();
    // Serial.println(menuSubMountain);
    // Serial.print(pixel_x);
    // Serial.print(" ");
    // Serial.println(pixel_y);
  }

  unsigned long currentMillisSimulation = millis();

  if (currentMillisSimulation - previousMillisSimulation >= intervalSimulation) {
    // save the last time you blinked the LED
    previousMillisSimulation = currentMillisSimulation;
    potValue = analogRead(potPin);
    battery = map(potValue, 2613, 3429, 0, 100);
  }

  unsigned long currentMillisTransmit = millis();

  if (currentMillisTransmit - previousMillisTransmit >= intervalTransmit) {
    previousMillisTransmit = currentMillisTransmit;
    dataTransmit[0] = 'c';
    dataTransmit[1] = 'l';
    dataTransmit[2] = '1';
    memcpy(dataTransmit + 3, &lat, 4);
    memcpy(dataTransmit + 7, &lng, 4);
    memcpy(dataTransmit + 11, &jarakMap, 2);
    memcpy(dataTransmit + 13, &GPShour, 1);
    memcpy(dataTransmit + 14, &GPSminute, 1);
    memcpy(dataTransmit + 15, &GPSsecond, 1);
    memcpy(dataTransmit + 16, &GPSday, 1);
    memcpy(dataTransmit + 17, &GPSmonth, 1);
    memcpy(dataTransmit + 18, &GPSyear, 1);
    if (sos == 1) {
      dataTransmit[19] = 's';
      dataTransmit[20] = 'o';
      dataTransmit[21] = 's';
    } else {
      dataTransmit[19] = '0';
      dataTransmit[20] = '0';
      dataTransmit[21] = '0';
    }
    // memcpy(dataTransmit + 22, &counter, 1);
    Transceiver.SendStruct(&dataTransmit, sizeof(dataTransmit));
  }

  unsigned long currentMillisReceive = millis();

  if (currentMillisReceive - previousMillisReceive >= intervalReceive) {
    previousMillisReceive = currentMillisReceive;
    if (Serial.available()) {
      Transceiver.GetStruct(&dataReceive, sizeof(dataReceive));
      if (dataReceive[0] == 's' && dataReceive[1] == 'v' && dataReceive[2] == '0') {
        memcpy(&latReceive, dataReceive + 3, 4);
        memcpy(&lngReceive, dataReceive + 7, 4);
        // memcpy(&ok, dataReceive + 11, 1);
        ok = 1;
        Last = millis();
      } else if (dataReceive[0] == 's' && dataReceive[1] == 'v' && dataReceive[2] == '1') {
        memcpy(&latReceive, dataReceive + 3, 4);
        memcpy(&lngReceive, dataReceive + 7, 4);
        // memcpy(&ok, dataReceive + 11, 1);
        ok = 2;
        Last = millis();
      } else if (dataReceive[0] == 's' && dataReceive[1] == 'v' && dataReceive[2] == '2') {
        memcpy(&latReceive, dataReceive + 3, 4);
        memcpy(&lngReceive, dataReceive + 7, 4);
        // memcpy(&ok, dataReceive + 11, 1);
        ok = 3;
        Last = millis();
      }
    } else {
      // if the time checker is over some prescribed amount
      // let the user know there is no incoming data
      if ((millis() - Last) > 4000) {
        ok = 0;
        Last = millis();
      }
    }
  }
}
