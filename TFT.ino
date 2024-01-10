
void GetTSPoint() {
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);  //restore shared pins
  pinMode(XM, OUTPUT);

  pixel_x = map(p.x, 3600, 700, 0, 240);
  pixel_y = map(p.y, 800, -2700, 0, 320);
  point_z = p.z;
}

void dataDisplay(uint16_t x0, uint16_t y0) {  //display 0
  tft.fillScreen(TFT_WHITE);
  drawButtonMap(x0, y0);
}

//=================FUNCTION FOR USER INTERFACE==================

void update_data(uint16_t x0, uint16_t y0) {
  char buf[50];
  sprintf(buf, "Lat: %f", latReceive);
  writeText(x0 + 10, y0 + 10, TFT_BLACK, 1, buf);

  char buf2[50];
  sprintf(buf2, "Long: %f", lngReceive);
  writeText(x0 + 10, y0 + 20, TFT_BLACK, 1, buf2);

  char buf3[50];
  sprintf(buf3, "Distance: %d m", distancePos0Receive);  //
  writeText(x0 + 10, y0 + 60, TFT_BLACK, 1, buf3);

  char buf4[50];
  sprintf(buf4, "Hour: %d", GPShourReceive);
  writeText(x0 + 10, y0 + 70, TFT_BLACK, 1, buf4);

  char buf5[50];
  sprintf(buf5, "Minute: %d", GPSminuteReceive);
  writeText(x0 + 10, y0 + 110, TFT_BLACK, 1, buf5);

  char buf6[50];
  sprintf(buf6, "Second: %d", GPSsecondReceive);
  writeText(x0 + 10, y0 + 125, TFT_BLACK, 1, buf6);

  char buf7[50];
  sprintf(buf7, "day: %d", GPSdayReceive);
  writeText(x0 + 10, y0 + 160, TFT_BLACK, 1, buf7);

  char buf8[50];
  sprintf(buf8, "Month: %d", GPSmonthReceive);
  writeText(x0 + 10, y0 + 185, TFT_BLACK, 1, buf8);

  char buf9[50];
  sprintf(buf9, "Year: %d", GPSyearReceive);
  writeText(x0 + 10, y0 + 210, TFT_BLACK, 1, buf9);

  char buf10[50];
  sprintf(buf10, "Count: %d", counter);
  writeText(x0 + 10, y0 + 235, TFT_BLACK, 1, buf10);
}

void drawButtonMap(uint16_t x0, uint16_t y0) {
  if (lora_success == 11) {
    tft.fillRoundRect(x0, y0 - 50, 200, 40, 5, TFT_BLACK);
    tft.fillRoundRect(x0 + 2, y0 - 52, 200 - 4, 40 - 4, 5, TFT_GREEN);
    char buf[50];
    sprintf(buf, "Receive SUCCESS C1");
    writeText(x0 + 10, y0 - 40, TFT_BLACK, 2, buf);
  } else if (lora_success == 2) {
    tft.fillRoundRect(x0, y0 - 50, 200, 40, 5, TFT_BLACK);
    tft.fillRoundRect(x0 + 2, y0 - 52, 200 - 4, 40 - 4, 5, TFT_GREEN);
    char buf[50];
    sprintf(buf, "Receive SUCCESS S2");
    writeText(x0 + 10, y0 - 40, TFT_BLACK, 2, buf);
  } else if (lora_success == 1) {
    tft.fillRoundRect(x0, y0 - 50, 200, 40, 5, TFT_BLACK);
    tft.fillRoundRect(x0 + 2, y0 - 52, 200 - 4, 40 - 4, 5, TFT_GREEN);
    char buf[50];
    sprintf(buf, "Receive SUCCESS S1");
    writeText(x0 + 10, y0 - 40, TFT_BLACK, 2, buf);

  } else if (lora_success == 0) {
    tft.fillRoundRect(x0, y0 - 50, 200, 40, 5, TFT_BLACK);
    tft.fillRoundRect(x0 + 2, y0 - 52, 200 - 4, 40 - 4, 5, TFT_RED);
    char buf[50];
    sprintf(buf, "Receive FAIL");
    writeText(x0 + 30, y0 - 40, TFT_BLACK, 2, buf);
  }
  tft.fillRoundRect(x0, y0, 200, 40, 5, TFT_BLACK);
  tft.fillRoundRect(x0 + 2, y0 + 2, 200 - 4, 40 - 4, 5, TFT_ORANGE);

  tft.fillRoundRect(x0, y0 + 50, 200, 40, 5, TFT_BLACK);
  tft.fillRoundRect(x0 + 2, y0 + 52, 200 - 4, 40 - 4, 5, TFT_ORANGE);

  tft.fillRoundRect(x0, y0 + 100, 200, 40, 5, TFT_BLACK);
  tft.fillRoundRect(x0 + 2, y0 + 102, 200 - 4, 40 - 4, 5, TFT_ORANGE);

  tft.fillRoundRect(x0, y0 + 150, 200, 80, 5, TFT_BLACK);
  tft.fillRoundRect(x0 + 2, y0 + 152, 200 - 4, 80 - 4, 5, TFT_ORANGE);
}

void drawButtonCompass(uint16_t x0, uint16_t y0) {
  tft.fillRoundRect(x0, y0 + 70, 200, 50, 5, TFT_BLACK);
  tft.fillRoundRect(x0 + 2, y0 + 72, 200 - 4, 50 - 4, 5, TFT_BLUE);
  writeText(x0 + 39, y0 + 84, TFT_BLACK, 3, "COMPASS");
}

void drawSOSButtonMenu(uint16_t x0, uint16_t y0) {
  tft.fillRoundRect(x0, y0 + 140, 200, 50, 5, TFT_BLACK);
  tft.fillRoundRect(x0 + 2, y0 + 142, 200 - 4, 50 - 4, 5, TFT_RED);
  writeText(x0 + 5, y0 + 155, TFT_BLACK, 2, "Send SOS Message");
}

void drawSOSButton(uint16_t xp, uint16_t yp) {
  tft.fillRoundRect(xp, yp, 70, 30, 15, TFT_BLACK);
  tft.fillRoundRect(xp + 2, yp + 2, 66, 26, 15, TFT_RED);
  writeText(xp + 10, yp + 4, TFT_BLACK, 3, "SOS");
}

void drawCompass(uint16_t xp, uint16_t yp) {
  tft.fillCircle(xp, yp, 30, TFT_WHITE);
}

void drawButtonBack(uint16_t xp, uint16_t yp) {
  tft.fillRoundRect(xp, yp, 30, 30, 5, TFT_BLACK);
  tft.fillRoundRect(xp + 2, yp + 2, 26, 26, 5, TFT_YELLOW);
  writeText(xp + 7, yp + 7, TFT_BLACK, 2, "<");
}

void writeText(uint16_t xp, uint16_t yp, uint16_t color, uint8_t size, char *text) {
  tft.setCursor(xp, yp);
  tft.setTextColor(color);
  tft.setTextSize(size);
  tft.print(text);
}

void requestSOS() {
  if (sosMenu == 1) {
    tft.fillScreen(TFT_YELLOW);
    drawButtonBack(10, 10);
    writeText(50, 84, TFT_BLACK, 3, "Client");
    writeText(25, 124, TFT_BLACK, 3, "Requesting");
    writeText(10, 157, TFT_BLACK, 3, "An Emergency");
    writeText(30, 200, TFT_BLACK, 3, "Message");
  }
  switch (sosMenu) {
    case 2:
      writeText(30, 200, TFT_BLACK, 3, "Message.");
      break;
    case 3:
      writeText(30, 200, TFT_BLACK, 3, "Message..");
      break;
    case 4:
      writeText(30, 200, TFT_BLACK, 3, "Message...");
      break;
    case 5:
      tft.fillScreen(TFT_RED);
      int x0 = 10, y0 = 80;
      tft.fillRoundRect(x0, y0 - 30, 220, 200, 5, TFT_BLACK);
      tft.fillRoundRect(x0 + 2, y0 - 30 + 2, 220 - 4, 200 - 4, 5, TFT_WHITE);
      drawButtonBack(10, 10);
      writeText(62, 94, TFT_BLACK, 3, "Sending");
      writeText(40, 127, TFT_BLACK, 3, "Emergency");
      writeText(55, 160, TFT_BLACK, 3, "Message");
      writeText(20, 198, TFT_BLACK, 3, "to BASARNAS");
      break;
  }
  // if (pixel_x >= 10 && pixel_x <= 40 && pixel_y >= 8 && pixel_y <= 50) {
  //   menu = 0;
  //   sosNav = 0;
  // }
}