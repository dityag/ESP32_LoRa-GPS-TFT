#include "SPI.h"
#include "TFT_eSPI.h"
#include <TouchScreen.h>
#include "EBYTE.h"

#define PIN_RX 16  // Serial2 RX (connect this to the EBYTE Tx pin)
#define PIN_TX 17  // Serial2 TX pin (connect this to the EBYTE Rx pin)

#define PIN_M0 19  // D4 on the board (possibly pin 24)
#define PIN_M1 22  // D2 on the board (possibly called pin 22)
#define PIN_AX 21  // D15 on the board (possibly called pin 21)

EBYTE Transceiver(&Serial, PIN_M0, PIN_M1, PIN_AX);

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
int sos, sosMenu = 0;
int lora_success;

unsigned long previousMillis = 0;   // will store last time LED was updated
unsigned long previousMillis2 = 0;  // will store last time LED was updated
unsigned long previousMillis3 = 0;  // will store last time LED was updated
unsigned long previousMillis4 = 0;  // will store last time LED was updated
unsigned long previousMillis5 = 0;  // will store last time LED was updated
unsigned long Last;

// constants won't change:
const long interval = 4000;    // interval at which to blink (milliseconds)
const long interval2 = 2000;   // interval at which to blink (milliseconds)
const long interval3 = 10;     // interval at which to blink (milliseconds)
const long interval4 = 1000;   // interval at which to blink (milliseconds)
const long interval5 = 10000;  // interval at which to blink (milliseconds)

#define MINPRESSURE 10
#define MAXPRESSURE 40000
TFT_eSPI tft = TFT_eSPI();                    // Invoke custom library
const int XP = 27, XM = 15, YP = 4, YM = 14;  //ID=0x9341
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
int pixel_x, pixel_y, point_z;  //Touch_getXY() updates global vars
uint8_t buffer = -1;
uint8_t counter;
#define PRIMARY 0xa512

//GSM Object & Variable----------------------------
#define SIM_TX 16
#define SIM_RX 17
#define SIM_BAUDRATE 9600

int _timeout;
String _buffer;
String number = "+6285781041578";

HardwareSerial SIM(2);

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

  tft.init();
  tft.setRotation(2);

  GSM_init();
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    dataTransmit[0] = 's';
    dataTransmit[1] = 'v';
    dataTransmit[2] = '0';

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
    if (Serial.available()) {
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

        lora_success = 11;

        latTransmit = latReceive;
        lngTransmit = lngReceive;
        distancePos0Transmit = distancePos0Receive;
        GPShourTransmit = GPShourReceive;
        GPSminuteTransmit = GPSminuteReceive;
        GPSsecondTransmit = GPSsecondReceive;
        GPSdayTransmit = GPSdayReceive;
        GPSmonthTransmit = GPSmonthReceive;
        GPSyearTransmit = GPSyearReceive;

        Last = millis();
      }
      else if (dataReceive[0] == 's' && dataReceive[1] == 'v' && dataReceive[2] == '2') {
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

        lora_success = 2;

        latTransmit = latReceive;
        lngTransmit = lngReceive;
        distancePos0Transmit = distancePos0Receive;
        GPShourTransmit = GPShourReceive;
        GPSminuteTransmit = GPSminuteReceive;
        GPSsecondTransmit = GPSsecondReceive;
        GPSdayTransmit = GPSdayReceive;
        GPSmonthTransmit = GPSmonthReceive;
        GPSyearTransmit = GPSyearReceive;

        Last = millis();
      }
      else if (dataReceive[0] == 's' && dataReceive[1] == 'v' && dataReceive[2] == '1') {
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

        lora_success = 1;

        latTransmit = latReceive;
        lngTransmit = lngReceive;
        distancePos0Transmit = distancePos0Receive;
        GPShourTransmit = GPShourReceive;
        GPSminuteTransmit = GPSminuteReceive;
        GPSsecondTransmit = GPSsecondReceive;
        GPSdayTransmit = GPSdayReceive;
        GPSmonthTransmit = GPSmonthReceive;
        GPSyearTransmit = GPSyearReceive;

        Last = millis();
      }
    } else {
      // if the time checker is over some prescribed amount
      // let the user know there is no incoming data
      if ((millis() - Last) > 2000) {
        // Serial.println("Searching: ");
        lora_success = 0;
        Last = millis();
      }
    }
  }
  unsigned long currentMillis3 = millis();

  if (currentMillis3 - previousMillis3 >= interval3) {
    // save the last time you blinked the LED
    previousMillis3 = currentMillis3;
    GetTSPoint();
  }

  unsigned long currentMillis4 = millis();

  if (currentMillis4 - previousMillis4 >= interval4) {
    // save the last time you blinked the LED
    previousMillis4 = currentMillis4;
    if (sos == 0) {
      dataDisplay(20, 65);
      update_data(20, 65);
      sosMenu = 0;
    } else if (sos == 1) {
      requestSOS();

      sosMenu++;
      if (sosMenu > 5) {
        sosMenu = 5;
      }
    }
  }
  unsigned long currentMillis5 = millis();

  if (currentMillis5 - previousMillis5 >= interval5) {
    // save the last time you blinked the LED
    previousMillis5 = currentMillis5;
    // SendMessage();
  }
}
