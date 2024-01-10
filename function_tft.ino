extern float lat, lng;
extern int alt;

//=================FUNCTION FOR USER INTERFACE==================

void drawButtonMap(uint16_t x0, uint16_t y0) {
  tft.fillRoundRect(x0, y0, 200, 50, 5, TFT_BLACK);
  tft.fillRoundRect(x0 + 2, y0 + 2, 200 - 4, 50 - 4, 5, TFT_GREEN);
  writeText(x0 + 24, y0 + 14, TFT_BLACK, 2, "Hiking Route");
}

void drawButtonPosition(uint16_t x0, uint16_t y0) {
  tft.fillRoundRect(x0, y0 + 70, 200, 50, 5, TFT_BLACK);
  tft.fillRoundRect(x0 + 2, y0 + 72, 200 - 4, 50 - 4, 5, TFT_BLUE);
  writeText(x0 + 20, y0 + 84, TFT_BLACK, 2, "Demonstration");
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

void drawPosition(uint16_t xp, uint16_t yp) {
  tft.setCursor(xp + 5, yp + 5);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  tft.print(lat, 7);
  tft.setCursor(xp + 5, yp + 20);
  tft.print(lng, 7);
  tft.setCursor(xp + 10, yp + 35);
  tft.print(alt, 7);
  tft.print(" MDPL");
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

//=================FUNCTION FOR SELECT MOUNTAIN==================
void drawMenuMountain(uint16_t x0, uint16_t y0, char *text) {
  tft.fillRoundRect(x0, y0 + 140, 200, 50, 5, TFT_BLACK);
  tft.fillRoundRect(x0 + 2, y0 + 142, 200 - 4, 50 - 4, 5, TFT_GREEN);
  writeText(x0 + 5, y0 + 155, TFT_BLACK, 2, text);
}

void drawMenuSubMountain(uint16_t x0, uint16_t y0, char *text) {
  tft.fillRoundRect(x0, y0 + 140, 200, 50, 5, TFT_BLACK);
  tft.fillRoundRect(x0 + 2, y0 + 142, 200 - 4, 50 - 4, 5, TFT_YELLOW);
  writeText(x0 + 5, y0 + 155, TFT_BLACK, 2, text);
}