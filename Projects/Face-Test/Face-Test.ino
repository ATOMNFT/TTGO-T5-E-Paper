#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#define EPD_MOSI 23
#define EPD_SCLK 18
#define EPD_BUSY 4
#define EPD_RSET 16
#define EPD_DC 17
#define EPD_CS 5

GxEPD2_BW<GxEPD2_290_GDEY029T94, GxEPD2_290_GDEY029T94::HEIGHT>
display(GxEPD2_290_GDEY029T94(EPD_CS, EPD_DC, EPD_RSET, EPD_BUSY));

void showFace(const char* face) {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(10, 40);
    display.setTextSize(3);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(&FreeMonoBold9pt7b);
    display.println(face);
    display.display(true);
}

void setup() {
    display.init();
    display.setRotation(1);
}

void loop() {
    showFace("O_O");
    delay(1000);
    showFace("-_-");
    delay(1000);
    showFace("O_O");
    delay(1000);
}
