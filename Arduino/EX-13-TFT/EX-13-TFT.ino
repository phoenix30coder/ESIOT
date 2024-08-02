#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

/*Pin details */
#define TFT_CS        10
#define TFT_RST        9 
#define TFT_DC         8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


void tftPrintTest() {
  tft.fillRoundRect(0, 0, 160, 100, 8, ST77XX_WHITE);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.println("thingZkit");
}


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.print(F("thingZkit_IoT_TFT Test"));
// Use this initializer if using a 1.8" TFT screen:
tft.initR(INITR_BLACKTAB);    
Serial.println(F("Initialized"));
tft.fillScreen(ST77XX_BLACK);

tftPrintTest();
}

void loop() {
  // put your main code here, to run repeatedly:

}
