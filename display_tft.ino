int delaySOS;
int delayGPS;

extern int mode;

int lock_touchscreen;

int lock_display0 = 0;
int lock_display1 = 0;
int lock_display11a = 0;
int lock_display11b = 0;
int lock_display1_case0 = 0;
int lock_display1_case1 = 0;
int lock_display1_case3 = 0;

int x_merah, y_merah;
int animasi_titik = 0;
int iterasi;
unsigned long prev_millis_merah;
unsigned long millis_merah2;
int distance_pos[6] = { 0, 2200, 2300, 2450, 2800, 3142 };

void displayInfo() {
  //  Serial.print(F("Location: "));
  if (gps.location.isValid()) {
  } else {
    //    Serial.print(F("INVALID"));
  }
}

void userInterface() {
  switch (menu) {
    case 0:
      menuNavigationDisplay(20, 65);
      break;
    case 1:
      mapSelect(20, 85);
      mode = 1;
      // mapDisplay();
      break;
    case 2:
      mapSelect(20, 85);
      mode = 2;
      break;
    case 3:
      if (lock_display1_case1 == 0) {
        verifSOS(40, 130);
        lock_display1_case1 = 1;
      }
      if (pixel_x >= 40 && pixel_y >= 190 && pixel_x <= 220 && pixel_y <= 210) {
        menu = 4;
        lock_display1_case1 = 0;
      }
      if (pixel_x >= 40 && pixel_y >= 245 && pixel_x <= 220 && pixel_y <= 280) {
        menu = 0;
        lock_display1_case1 = 0;
      }
      break;
    case 4:

      delaySOS++;
      if (delaySOS >= 0 && delaySOS <= 3) {
        if (lock_display1_case3 == 0) {
          sosDisplayRed();
          lock_display1_case3 = 1;
        }

      } else if (delaySOS > 3 && delaySOS <= 6) {
        if (lock_display1_case3 == 1) {
          sosDisplayWhite();
          lock_display1_case3 = 0;
        }
      }

      if (delaySOS > 6) {
        delaySOS = 0;
      }

      if (pixel_x >= 10 && pixel_x <= 40 && pixel_y >= 8 && pixel_y <= 50) {
        menu = 0;
        sosNav = 0;
        // lock_display1_case3 = 0;
      }
      sos = 1;
      break;
  }
}

//==============DISPLAY 0================
void menuNavigationDisplay(uint16_t x0, uint16_t y0) {  //display 0
  if (lock_display0 == 0) {
    tft.fillScreen(TFT_WHITE);
    drawButtonMap(x0, y0);
    drawButtonPosition(x0, y0);
    drawSOSButtonMenu(x0, y0);
    lock_display0 = 1;
  }
  if (pixel_x >= 20 && pixel_x <= 235 && pixel_y >= 59 && pixel_y <= 103) {
    menu = 1;
    lock_display0 = 0;
  } else if (pixel_x >= 20 && pixel_x <= 235 && pixel_y >= 126 && pixel_y <= 165) {
    menu = 2;
    lock_display0 = 0;
  } else if (pixel_x >= 20 && pixel_x <= 235 && pixel_y >= 189 && pixel_y <= 237) {
    menu = 3;
    lock_display0 = 0;
  }
}

//==========DISPLAY 1===============
void mapDisplay() {  //display 1
  // distancePos0 = gps.distanceBetween(latGPS, lngGPS, latPos0, lngPos0);
  // distancePos1 = gps.distanceBetween(latGPS, lngGPS, latPos1, lngPos1);
  // distancePos2 = gps.distanceBetween(latGPS, lngGPS, latPos2, lngPos2);
  // distanceGoal = gps.distanceBetween(latGPS, lngGPS, latGoal, lngGoal);

  // distancePos0kePos1 = gps.distanceBetween(latPos0, lngPos0, latPos1, lngPos1);
  // distancePos1kePos2 = gps.distanceBetween(latPos1, lngPos1, latPos2, lngPos2);
  // distancePos2keGoal = gps.distanceBetween(latPos2, lngPos2, latGoal, lngGoal);

  switch (sosNav) {
    case 0:
      if (menuSubMountain == 11) {
        if (lock_display1_case0 == 0) {
          tft.fillScreen(TFT_BLACK);
          tft.fillRoundRect(10, 10, 220, 60, 10, TFT_WHITE);
          tft.drawFastHLine(10, 30, 220, TFT_BLACK);
          drawSOSButton(150, 35);
          tft.drawBitmap(20, 90, trees, 200, 213, TFT_TRANSPARENT);
          tft.drawBitmap(20, 100, merbabuSelo, 208, 197, TFT_WHITE);

          drawButtonBack(10, 280);
          tft.fillRoundRect(160, 265, 85, 50, 10, TFT_BLACK);
          lock_display1_case0 = 1;
        }
        delayGPS++;
        // Serial.print(delayGPS++);
        if (delayGPS > 3) {
          tft.fillRoundRect(10, 10, 220, 20, 10, TFT_WHITE);
        }
        if (delayGPS > 4) {
          delayGPS = 0;
        }

        // tft.drawBitmap(110, 290 - jarakMap, point, 16, 16, TFT_RED);
        millis_merah2 = millis();
        if (millis_merah2 - prev_millis_merah > 200) {
          jalanMerah();
          prev_millis_merah = millis();
        }
        updateJarak();
        tft.fillRoundRect(160, 265, 85, 50, 10, TFT_BLACK);
        drawNav(10, 10);
        drawPosition(160, 265);

        tft.setTextColor(TFT_YELLOW);
        tft.setTextSize(1);

        tft.fillRoundRect(128, 78, 50, 20, 2, TFT_BLACK);
        tft.setCursor(130, 80);
        // tft.print(distanceGoal);
        tft.print(distance_pos[5]);
        tft.print("m");
        tft.setCursor(130, 90);
        tft.print("Tujuan");

        // tft.setCursor(10, 75);
        // tft.print(counter);
        // tft.setCursor(10, 85);
        // tft.print("Counter");

        tft.fillRoundRect(58, 128, 30, 20, 2, TFT_BLACK);
        tft.setCursor(60, 130);
        tft.print(distance_pos[4]);
        tft.print("m");
        tft.setCursor(60, 140);
        tft.print("Pos 4");

        tft.fillRoundRect(108, 168, 30, 20, 2, TFT_BLACK);
        tft.setCursor(110, 170);
        tft.print(distance_pos[3]);
        tft.print("m");
        tft.setCursor(110, 180);
        tft.print("Pos 3");

        tft.fillRoundRect(33, 178, 30, 20, 2, TFT_BLACK);
        tft.setCursor(35, 180);
        tft.print(distance_pos[2]);
        tft.print("m");
        tft.setCursor(35, 190);
        tft.print("Pos 2");

        tft.fillRoundRect(18, 198, 30, 20, 2, TFT_BLACK);
        tft.setCursor(20, 200);
        tft.print(distance_pos[1]);
        tft.print("m");
        tft.setCursor(20, 210);
        tft.print("Pos 1");

        tft.fillRoundRect(68, 248, 30, 20, 2, TFT_BLACK);
        tft.setCursor(70, 250);
        tft.print(distance_pos[0]);
        tft.print("m");
        tft.setCursor(70, 260);
        tft.print("Pos 0");
      } else if (menuSubMountain == 12) {
        if (lock_display1_case0 == 0) {
          tft.fillScreen(TFT_BLACK);
          tft.fillRoundRect(10, 10, 220, 60, 10, TFT_WHITE);
          tft.drawFastHLine(10, 30, 220, TFT_BLACK);
          drawSOSButton(150, 35);
          tft.drawBitmap(20, 90, trees, 200, 213, TFT_TRANSPARENT);
          tft.drawBitmap(20, 100, merbabuSuwanting, 208, 197, TFT_WHITE);

          drawButtonBack(10, 280);
          tft.fillRoundRect(160, 265, 85, 50, 10, TFT_BLACK);
          lock_display1_case0 = 1;
        }
        drawNav(10, 10);
        drawPosition(160, 265);

      } else if (menuSubMountain == 21) {
        if (lock_display1_case0 == 0) {
          tft.fillScreen(TFT_BLACK);
          tft.fillRoundRect(10, 10, 220, 60, 10, TFT_WHITE);
          tft.drawFastHLine(10, 30, 220, TFT_BLACK);
          drawSOSButton(150, 35);
          tft.drawBitmap(20, 90, trees, 200, 213, TFT_TRANSPARENT);
          tft.drawBitmap(20, 100, lawuCetho, 176, 199, TFT_WHITE);

          drawButtonBack(10, 280);
          tft.fillRoundRect(160, 265, 85, 50, 10, TFT_BLACK);
          lock_display1_case0 = 1;
        }
        drawNav(10, 10);
        drawPosition(160, 265);
      } else if (menuSubMountain == 22) {
        if (lock_display1_case0 == 0) {
          tft.fillScreen(TFT_BLACK);
          tft.fillRoundRect(10, 10, 220, 60, 10, TFT_WHITE);
          tft.drawFastHLine(10, 30, 220, TFT_BLACK);
          drawSOSButton(150, 35);
          tft.drawBitmap(20, 90, trees, 200, 213, TFT_TRANSPARENT);
          tft.drawBitmap(50, 100, lawuCemoro, 128, 194, TFT_WHITE);

          drawButtonBack(10, 280);
          tft.fillRoundRect(160, 265, 85, 50, 10, TFT_BLACK);
          lock_display1_case0 = 1;
        }
        drawNav(10, 10);
        drawPosition(160, 265);
      }
      break;
    case 1:
      if (lock_display1_case1 == 0) {
        verifSOS(40, 130);
        lock_display1_case1 = 1;
      }
      if (pixel_x >= 40 && pixel_y >= 190 && pixel_x <= 220 && pixel_y <= 210) {
        // menu = 4;
        menuSubMountain = 11;
        sosNav = 3;
        lock_display1_case1 = 0;
      }
      if (pixel_x >= 40 && pixel_y >= 245 && pixel_x <= 220 && pixel_y <= 280) {
        // menu = 1;
        menuSubMountain = 11;
        sosNav = 0;
        lock_display1_case1 = 0;
      }
      if (pixel_x >= 10 && pixel_x <= 40 && pixel_y >= 8 && pixel_y <= 50) {
        menuSubMountain = 0;
        sosNav = 0;
        lock_display1_case1 = 0;
      }
    case 2:
      // demonstrationDisplay(122, 160);
      break;
    case 3:
      delaySOS++;
      // Serial.println(delaySOS);
      if (delaySOS >= 0 && delaySOS <= 3) {
        if (lock_display1_case3 == 0) {
          sosDisplayRed();
          lock_display1_case3 = 1;
        }

      } else if (delaySOS > 3 && delaySOS <= 6) {
        if (lock_display1_case3 == 1) {
          sosDisplayWhite();
          lock_display1_case3 = 0;
        }
      }

      if (delaySOS > 6) {
        delaySOS = 0;
      }

      if (pixel_x >= 10 && pixel_x <= 40 && pixel_y >= 8 && pixel_y <= 50) {
        menu = 0;
        sosNav = 0;
        menuMountain = 0;
        menuSubMountain = 0;
        lock_display1_case3 = 0;
      }
      sos = 1;
      break;
  }

  if (pixel_x >= 160 && pixel_x <= 240 && pixel_y >= 33 && pixel_y <= 53) {
    menuSubMountain = 0;
    sosNav = 1;
    lock_display1_case0 = 0;
  }
  // else if (pixel_x >= 190 && pixel_x <= 247 && pixel_y >= 235 && pixel_y <= 289) {
  //   sosNav = 2;
  // }

  if (pixel_x >= 14 && pixel_x <= 50 && pixel_y >= 264 && pixel_y <= 300) {
    // menu = 0;
    menuSubMountain = 0;
    menu = 1;
    menuMountain = 0;
    lock_display1_case0 = 0;
  }
}

void drawNav(uint16_t xp, uint16_t yp) {
  tft.setCursor(xp + 10, yp + 5);
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(1);

  if (GPShour < 10) {
    tft.print("0");
    tft.print(GPShour);
  } else {
    tft.print(GPShour);
  }
  tft.print(":");
  if (GPSminute < 10) {
    tft.print("0");
    tft.print(GPSminute);
  } else {
    tft.print(GPSminute);
  }
  tft.print(":");
  tft.print(GPSsecond);

  tft.setCursor(xp + 150, yp + 5);
  tft.print(GPSday);
  tft.print("/");
  tft.print(GPSmonth);
  tft.print("/");
  tft.print(GPSyear);

  tft.fillRoundRect(18, 37, 80, 30, 2, TFT_WHITE);
  tft.setCursor(20, 39);
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(3);
  tft.print(distance_pos[5]);
  tft.print("m");
}

//================DISPLAY 2===============
void demonstrationDisplay(uint16_t x0, uint16_t y0) {  //display 2
  tft.fillScreen(TFT_BLUE);
  tft.fillCircle(x0, y0, 100, TFT_BLACK);
  tft.fillCircle(x0, y0, 95, TFT_WHITE);
  drawButtonBack(10, 10);
  if (pixel_x >= 10 && pixel_x <= 40 && pixel_y >= 8 && pixel_y <= 50) {
    menu = 0;
    sosNav = 0;
  }
}

//=================DISPLAY 3===============

void sosDisplayRed() {  //display 3
  tft.fillScreen(TFT_RED);
  drawButtonBack(10, 10);
  writeText(30, 84, TFT_BLACK, 3, "Sending");
  writeText(10, 112, TFT_BLACK, 3, "An Emergency");
  writeText(30, 140, TFT_BLACK, 3, "Message");
}

void sosDisplayWhite() {  //display 3
  tft.fillScreen(TFT_WHITE);
  drawButtonBack(10, 10);
  writeText(30, 84, TFT_RED, 3, "Sending");
  writeText(10, 112, TFT_RED, 3, "An Emergency");
  writeText(30, 140, TFT_RED, 3, "Message");
}

void verifSOS(int x, int y) {
  tft.fillScreen(TFT_YELLOW);
  drawButtonBack(10, 10);
  tft.fillRoundRect(x - 20, y - 80, 200, 100, 5, TFT_BLACK);
  tft.fillRoundRect(x - 18, y - 78, 200 - 4, 100 - 4, 5, TFT_WHITE);
  tft.fillRoundRect(x, y + 60, 160, 50, 5, TFT_BLACK);
  tft.fillRoundRect(x + 2, y + 62, 160 - 4, 50 - 4, 5, TFT_GREEN);
  tft.fillRoundRect(x, y + 120, 160, 50, 5, TFT_BLACK);
  tft.fillRoundRect(x + 2, y + 122, 160 - 4, 50 - 4, 5, TFT_RED);
  // tft.fillRoundRect(x, y+120, 160, 50, 5, TFT_BLACK);
  // tft.fillRoundRect(x+2, y+122, 160-4, 50-4, 5, TFT_BLUE);
  writeText(x + 55, y + 74, TFT_BLACK, 3, "YES");
  writeText(x + 65, y + 134, TFT_BLACK, 3, "NO");
  // writeText(x+4, y+127 , TFT_BLACK, 2, " Lihat titik\n      Pendaki");
  writeText(x - 16, y - 75, TFT_BLACK, 2, "   Kirim sinyal\n      darurat?");
  writeText(x - 20, y - 40, TFT_BLACK, 2, "   False alarm\n        akan\n  dikenakan sanksi");
}

void jalanMerah() {
  if (animasi_titik == 0) {
    iterasi++;
    x_merah++;
    y_merah++;
    float x_merahf = float(x_merah);
    float y_merahf = float(y_merah) * 1.4;
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_RED);
    delay(300);
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_BLACK);
    tft.drawBitmap(20, 90, trees, 200, 213, TFT_TRANSPARENT);
    tft.drawBitmap(20, 100, merbabuSelo, 208, 197, TFT_WHITE);
    if (x_merah == 25) {
      animasi_titik = 1;
      iterasi = 0;
    }
    if (distance_pos[1] > 0) {
      distance_pos[1] -= 70;
    }
    distance_pos[2] -= 60;
    distance_pos[3] -= 40;
    distance_pos[4] -= 50;
    distance_pos[5] -= 20;
  } else if (animasi_titik == 1) {
    iterasi++;
    x_merah--;
    float x_merahf = float(x_merah);
    float y_merahf = float(y_merah) + iterasi * 1.8;
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_RED);
    delay(300);
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_BLACK);
    tft.drawBitmap(20, 90, trees, 200, 213, TFT_TRANSPARENT);
    tft.drawBitmap(20, 100, merbabuSelo, 208, 197, TFT_WHITE);
    if (x_merah == 16) {
      animasi_titik = 2;
      y_merah = y_merahf;
      iterasi = 0;
    }
    if (distance_pos[1] > 0) {
      distance_pos[1] -= 40;
    }
    distance_pos[2] -= 40;
    distance_pos[3] -= 30;
    distance_pos[4] -= 20;
    distance_pos[5] -= 20;
  } else if (animasi_titik == 2) {
    iterasi++;
    x_merah++;
    float x_merahf = float(x_merah);
    float y_merahf = float(y_merah) + iterasi * 1.28;
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_RED);
    delay(300);
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_BLACK);
    tft.drawBitmap(20, 90, trees, 200, 213, TFT_TRANSPARENT);
    tft.drawBitmap(20, 100, merbabuSelo, 208, 197, TFT_WHITE);
    if (x_merah == 30) {
      animasi_titik = 3;
      y_merah = y_merahf;
      iterasi = 0;
    }
    if (distance_pos[1] > 0) {
      distance_pos[1] -= 50;
    }
    distance_pos[2] -= 20;
    distance_pos[3] -= 30;
    distance_pos[4] -= 20;
    distance_pos[5] -= 20;
  } else if (animasi_titik == 3) {
    iterasi++;
    x_merah++;
    float x_merahf = float(x_merah);
    float y_merahf = float(y_merah) + iterasi * 0.7;
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_RED);
    delay(300);
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_BLACK);
    tft.drawBitmap(20, 90, trees, 200, 213, TFT_TRANSPARENT);
    tft.drawBitmap(20, 100, merbabuSelo, 208, 197, TFT_WHITE);
    if (x_merah == 60) {
      animasi_titik = 4;
      y_merah = y_merahf;
      iterasi = 0;
    }
    if (distance_pos[2] > 0) {
      distance_pos[2] -= 20;
    }
    distance_pos[3] -= 20;
    distance_pos[4] -= 10;
    distance_pos[5] -= 10;
  } else if (animasi_titik == 4) {
    iterasi++;
    x_merah--;
    float x_merahf = float(x_merah);
    float y_merahf = float(y_merah) + iterasi * 0.4;
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_RED);
    delay(300);
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_BLACK);
    tft.drawBitmap(20, 90, trees, 200, 213, TFT_TRANSPARENT);
    tft.drawBitmap(20, 100, merbabuSelo, 208, 197, TFT_WHITE);
    if (x_merah == 55) {
      animasi_titik = 5;
      y_merah = y_merahf;
      iterasi = 0;
    }
    if (distance_pos[3] > 0) {
      distance_pos[3] -= 40;
    }
    distance_pos[4] -= 10;
    distance_pos[5] -= 10;
  } else if (animasi_titik == 5) {
    iterasi++;
    x_merah++;
    float x_merahf = float(x_merah);
    float y_merahf = float(y_merah) + iterasi;
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_RED);
    delay(300);
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_BLACK);
    tft.drawBitmap(20, 90, trees, 200, 213, TFT_TRANSPARENT);
    tft.drawBitmap(20, 100, merbabuSelo, 208, 197, TFT_WHITE);
    if (x_merah == 65) {
      animasi_titik = 6;
      y_merah = y_merahf;
      iterasi = 0;
    }
    if (distance_pos[4] > 0) {
      distance_pos[4] -= 40;
    }
    distance_pos[5] -= 20;
  } else if (animasi_titik == 6) {
    iterasi++;
    x_merah--;
    float x_merahf = float(x_merah);
    float y_merahf = float(y_merah) + iterasi * 2.6;
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_RED);
    delay(300);
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_BLACK);
    tft.drawBitmap(20, 90, trees, 200, 213, TFT_TRANSPARENT);
    tft.drawBitmap(20, 100, merbabuSelo, 208, 197, TFT_WHITE);
    if (x_merah == 60) {
      animasi_titik = 7;
      y_merah = y_merahf;
      iterasi = 0;
    }
    if (distance_pos[4] > 0) {
      distance_pos[4] -= 50;
    }
    distance_pos[5] -= 50;
  } else if (animasi_titik == 7) {
    iterasi++;
    x_merah++;
    float x_merahf = float(x_merah);
    float y_merahf = float(y_merah) + iterasi * 1.08;
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_RED);
    delay(300);
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_BLACK);
    tft.drawBitmap(20, 90, trees, 200, 213, TFT_TRANSPARENT);
    tft.drawBitmap(20, 100, merbabuSelo, 208, 197, TFT_WHITE);
    if (x_merah == 78) {
      animasi_titik = 8;
      y_merah = y_merahf;
      iterasi = 0;
    }
    if (distance_pos[5] > 0) {
      distance_pos[5] -= 50;
    }
  } else if (animasi_titik == 8) {
    iterasi++;
    x_merah--;
    float x_merahf = float(x_merah);
    float y_merahf = float(y_merah) + iterasi * 3;
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_RED);
    delay(300);
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_BLACK);
    tft.drawBitmap(20, 90, trees, 200, 213, TFT_TRANSPARENT);
    tft.drawBitmap(20, 100, merbabuSelo, 208, 197, TFT_WHITE);
    if (x_merah == 74) {
      animasi_titik = 9;
      y_merah = y_merahf;
      iterasi = 0;
    }
    if (distance_pos[5] > 0) {
      distance_pos[5] -= 30;
    }
  } else if (animasi_titik == 9) {
    iterasi++;
    x_merah++;
    float x_merahf = float(x_merah);
    float y_merahf = float(y_merah) + iterasi * 0.625;
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_RED);
    delay(300);
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_BLACK);
    tft.drawBitmap(20, 90, trees, 200, 213, TFT_TRANSPARENT);
    tft.drawBitmap(20, 100, merbabuSelo, 208, 197, TFT_WHITE);
    if (x_merah == 90) {
      animasi_titik = 10;
      y_merah = y_merahf;
      iterasi = 0;
    }
    if (distance_pos[5] > 0) {
      distance_pos[5] -= 20;
    }
  } else if (animasi_titik == 10) {
    iterasi++;
    x_merah++;
    float x_merahf = float(x_merah);
    float y_merahf = float(y_merah) + iterasi * 0.066;
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_RED);
    delay(300);
    tft.drawBitmap(35 + int(x_merahf), 260 - int(y_merahf), point, 16, 16, TFT_BLACK);
    tft.drawBitmap(20, 90, trees, 200, 213, TFT_TRANSPARENT);
    tft.drawBitmap(20, 100, merbabuSelo, 208, 197, TFT_WHITE);
    if (x_merah == 120) {
      animasi_titik = 11;
      y_merah = y_merahf;
      iterasi = 0;
    }
    if (distance_pos[5] > 0) {
      distance_pos[5] -= 30;
    }
  }
}

void updateJarak() {

  if (distance_pos[1] < 0) distance_pos[1] = 0;
  if (distance_pos[2] < 0) distance_pos[2] = 0;
  if (distance_pos[3] < 0) distance_pos[3] = 0;
  if (distance_pos[4] < 0) distance_pos[4] = 0;
  if (distance_pos[5] < 0) distance_pos[5] = 0;
}