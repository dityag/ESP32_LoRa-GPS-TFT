#include "EBYTE.h"

#define PIN_RX 16  // Serial2 RX (connect this to the EBYTE Tx pin)
#define PIN_TX 17  // Serial2 TX pin (connect this to the EBYTE Rx pin)

#define PIN_M0 18  // D4 on the board (possibly pin 24)
#define PIN_M1 19  // D2 on the board (possibly called pin 22)
#define PIN_AX 5   // D15 on the board (possibly called pin 21)

EBYTE Transceiver(&Serial2, PIN_M0, PIN_M1, PIN_AX);

char dataTransmit[25];
char dataReceive[25];
float latTransmit, lngTransmit;
float latReceive, lngReceive;
int distancePos0Receive, distancePos0Transmit;
int distancePos1Receive, distancePos1Transmit;
int distancePos2Receive, distancePos2Transmit;
int distancePos3Receive, distancePos3Transmit;
int GPShourReceive, GPShourTransmit;
int GPSminuteReceive, GPSminuteTransmit;
int GPSsecondReceive, GPSsecondTransmit;
int GPSdayReceive, GPSdayTransmit;
int GPSmonthReceive, GPSmonthTransmit;
int GPSyearReceive, GPSyearTransmit;
int sos;
int ok;
uint8_t buffer = -1;
uint8_t counter;

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

unsigned long previousMillis = 0;   // will store last time LED was updated
unsigned long previousMillis2 = 0;  // will store last time LED was updated
unsigned long previousMillis3 = 0;  // will store last time LED was updated
unsigned long Last;

// constants won't change:
const long interval = 4000;   // interval at which to blink (milliseconds)
const long interval2 = 2000;  // interval at which to blink (milliseconds)
const long interval3 = 10;    // interval at which to blink (milliseconds)


void setup() {


  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  Serial2.begin(9600);

  Serial.println("Starting Reader");

  // this init will set the pinModes for you
  Serial.println(Transceiver.init());

  Transceiver.SetAddressH(0b11111111);
  Transceiver.SetAddressL(0b11111111);
  Transceiver.SetSpeed(0b00011000);
  Transceiver.SetChannel(0b00000110);
  Transceiver.SetOptions(0b01000100);
  Transceiver.SaveParameters(PERMANENT);
  Transceiver.PrintParameters();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.setTextSize(2);
  display.println("   ECHO");
  display.setTextSize(1);
  display.println("Electronic Companion");
  display.println("Hiking & Orientation");
  display.setTextSize(2);
  display.println("  WELCOME");
  display.println(" SERVER 2");
  display.display();
  delay(2000);
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    dataTransmit[0] = 's';
    dataTransmit[1] = 'v';
    dataTransmit[2] = '2';

    memcpy(dataTransmit + 3, &latTransmit, 4);
    memcpy(dataTransmit + 7, &lngTransmit, 4);
    memcpy(dataTransmit + 11, &distancePos0Transmit, 2);
    memcpy(dataTransmit + 13, &GPShourTransmit, 1);
    memcpy(dataTransmit + 14, &GPSminuteTransmit, 1);
    memcpy(dataTransmit + 15, &GPSsecondTransmit, 1);
    memcpy(dataTransmit + 16, &GPSdayTransmit, 1);
    memcpy(dataTransmit + 17, &GPSmonthTransmit, 1);
    memcpy(dataTransmit + 18, &GPSyearTransmit, 1);
    if (sos == 1) {
      dataTransmit[19] = 's';
      dataTransmit[20] = 'o';
      dataTransmit[21] = 's';
    } else {
      dataTransmit[19] = '0';
      dataTransmit[20] = '0';
      dataTransmit[21] = '0';
    }
    Transceiver.SendStruct(&dataTransmit, sizeof(dataTransmit));
  }

  unsigned long currentMillis2 = millis();

  if (currentMillis2 - previousMillis2 >= interval2) {
    // save the last time you blinked the LED
    previousMillis2 = currentMillis2;
    if (Serial2.available()) {
      Transceiver.GetStruct(&dataReceive, sizeof(dataReceive));
      if (dataReceive[0] == 'c' && dataReceive[1] == 'l' && dataReceive[2] == '1') {
        memcpy(&latReceive, dataReceive + 3, 4);
        memcpy(&lngReceive, dataReceive + 7, 4);
        memcpy(&distancePos0Receive, dataReceive + 11, 2);
        memcpy(&GPShourReceive, dataReceive + 13, 1);
        memcpy(&GPSminuteReceive, dataReceive + 14, 1);
        memcpy(&GPSsecondReceive, dataReceive + 15, 1);
        memcpy(&GPSdayReceive, dataReceive + 16, 1);
        memcpy(&GPSmonthReceive, dataReceive + 17, 1);
        memcpy(&GPSyearReceive, dataReceive + 18, 1);

        if (dataReceive[19] == 's' && dataReceive[20] == 'o' && dataReceive[21] == 's') {
          sos = 1;
        } else {
          sos = 0;
        }

         if (dataReceive[22] != buffer){
          counter++;
        }
        buffer = dataReceive[22];

        latTransmit = latReceive;
        lngTransmit = lngReceive;
        distancePos0Transmit = distancePos0Receive;
        GPShourTransmit = GPShourReceive;
        GPSminuteTransmit = GPSminuteReceive;
        GPSsecondTransmit = GPSsecondReceive;
        GPSdayTransmit = GPSdayReceive;
        GPSmonthTransmit = GPSmonthReceive;
        GPSyearTransmit = GPSyearReceive;
        // memcpy(&ok, dataReceive + 11, 1);
        // ok = 1;
        Serial.print(latReceive, 10);
        Serial.print(" ");
        Serial.print(lngReceive, 10);
        Serial.print(" ");
        Serial.println(ok);
        Last = millis();
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        // Display static text
        display.println("SUCCESS C1");
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 15);
        // Display static text
        display.print("LAT : ");
        display.println(latReceive, 10);
        display.print("LONG : ");
        display.println(lngReceive, 10);
        display.print("Distance : ");
        display.print(distancePos0Receive);
        display.println(" m");
        display.print("Time : ");
        display.print(GPShourReceive);
        display.print(":");
        display.print(GPSminuteReceive);
        display.print(":");
        display.println(GPSsecondReceive);
        // display.print("Date : ");
        // display.print(GPSdayReceive);
        // display.print("/");
        // display.print(GPSmonthReceive);
        // display.print("/");
        // display.println(GPSyearReceive);
        if(sos == 1){
          display.println("     SOS WOYY");
        }
        else if(sos == 0){
          display.println("");
        }
        display.print("Counter : ");
        display.println(counter);
        display.display();
      }
    } else {
      // if the time checker is over some prescribed amount
      // let the user know there is no incoming data
      if ((millis() - Last) > 2000) {
        Serial.println("Searching: ");
        display.clearDisplay();

        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(40, 0);
        // Display static text
        display.println("FAIL");
        display.display();
        Last = millis();
      }
    }
  }
  unsigned long currentMillis3 = millis();

  if (currentMillis3 - previousMillis3 >= interval3) {
    // save the last time you blinked the LED
    previousMillis3 = currentMillis3;
  }
}
