extern int menuMountain;
extern int menuSubMountain;

void mapSelect(uint16_t x0, uint16_t y0) {
  switch (menuMountain) {
    case 0:
      if (lock_display1 == 0) {
        tft.fillScreen(TFT_WHITE);
        drawButtonBack(10, 280);

        writeText(0, 40, TFT_BLACK, 2, "Select Your Mountain");

        tft.fillRoundRect(x0, y0, 200, 50, 5, TFT_BLACK);
        tft.fillRoundRect(x0 + 2, y0 + 2, 200 - 4, 50 - 4, 5, TFT_GREEN);
        writeText(x0 + 34, y0 + 14, TFT_BLACK, 2, "Gn. Merbabu");

        tft.fillRoundRect(x0, y0 + 70, 200, 50, 5, TFT_BLACK);
        tft.fillRoundRect(x0 + 2, y0 + 72, 200 - 4, 50 - 4, 5, TFT_GREEN);
        writeText(x0 + 44, y0 + 84, TFT_BLACK, 2, "Gn. Lawu");
        lock_display1 = 1;
      }
      if (pixel_x >= 30 && pixel_x <= 239 && pixel_y >= 75 && pixel_y <= 116) {
        menuMountain = 1;
        lock_display1 = 0;
      } else if (pixel_x >= 32 && pixel_x <= 235 && pixel_y >= 145 && pixel_y <= 185) {
        menuMountain = 2;
        lock_display1 = 0;
      }

      if (pixel_x >= 14 && pixel_x <= 50 && pixel_y >= 264 && pixel_y <= 300) {
        menu = 0;
        lock_display1 = 0;
      }
      break;
    case 1:
      if (lock_display11a == 0) {
        tft.fillScreen(TFT_WHITE);
        drawButtonBack(10, 280);

        writeText(18, 40, TFT_BLACK, 2, "Select Your Route");

        tft.fillRoundRect(x0, y0, 200, 50, 5, TFT_BLACK);
        tft.fillRoundRect(x0 + 2, y0 + 2, 200 - 4, 50 - 4, 5, TFT_GREEN);
        writeText(x0 + 34, y0 + 14, TFT_BLACK, 2, "   Selo");

        tft.fillRoundRect(x0, y0 + 70, 200, 50, 5, TFT_BLACK);
        tft.fillRoundRect(x0 + 2, y0 + 72, 200 - 4, 50 - 4, 5, TFT_GREEN);
        writeText(x0 + 44, y0 + 84, TFT_BLACK, 2, "Suwanting");

        tft.fillRoundRect(x0, y0 + 140, 200, 50, 5, TFT_BLACK);
        tft.fillRoundRect(x0 + 2, y0 + 142, 200 - 4, 50 - 4, 5, TFT_GREEN);
        writeText(x0 + 34, y0 + 154, TFT_BLACK, 2, "   Wekas");
        lock_display11a = 1;
      }
      if (pixel_x >= 30 && pixel_x <= 239 && pixel_y >= 75 && pixel_y <= 116) {
        menuMountain = 11;
        menuSubMountain = 11;
        lock_display11a = 0;
      } else if (pixel_x >= 32 && pixel_x <= 235 && pixel_y >= 145 && pixel_y <= 185) {
        menuMountain = 11;
        menuSubMountain = 12;
        lock_display11a = 0;
      } else if (pixel_x >= 14 && pixel_x <= 50 && pixel_y >= 264 && pixel_y <= 300) {
        menu = 1;
        menuMountain = 0;
        lock_display1 = 0;
      } else {
        lock_display11a = 1;
      }
      break;
    case 2:
      if (lock_display11b == 0) {
        tft.fillScreen(TFT_WHITE);
        drawButtonBack(10, 280);

        writeText(20, 40, TFT_BLACK, 2, "Select Your Route");

        tft.fillRoundRect(x0, y0, 200, 50, 5, TFT_BLACK);
        tft.fillRoundRect(x0 + 2, y0 + 2, 200 - 4, 50 - 4, 5, TFT_GREEN);
        writeText(x0 + 9, y0 + 14, TFT_BLACK, 2, "Cemoro Kandang");

        tft.fillRoundRect(x0, y0 + 70, 200, 50, 5, TFT_BLACK);
        tft.fillRoundRect(x0 + 2, y0 + 72, 200 - 4, 50 - 4, 5, TFT_GREEN);
        writeText(x0 + 40, y0 + 84, TFT_BLACK, 2, "Candi Cetho");
        lock_display11b = 1;
      }
      if (pixel_x >= 30 && pixel_x <= 239 && pixel_y >= 75 && pixel_y <= 116) {
        menuMountain = 11;
        menuSubMountain = 21;
        lock_display11b = 0;
      } else if (pixel_x >= 32 && pixel_x <= 235 && pixel_y >= 145 && pixel_y <= 185) {
        menuMountain = 11;
        menuSubMountain = 22;
        lock_display11b = 0;
      } else if (pixel_x >= 14 && pixel_x <= 50 && pixel_y >= 264 && pixel_y <= 300) {
        menu = 1;
        menuMountain = 0;
        lock_display1 = 0;
      } else {
        lock_display11b = 1;
      }
      break;
    case 11:
      mapDisplay();
      break;
  }
}