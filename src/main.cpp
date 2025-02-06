#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { // 0x3C is the I2C address for many SSD1306 displays
    Serial.println(F("SSD1306 allocation failed"));
    while (true); // Halt if initialization fails
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_INVERSE);
  display.setCursor(0, 0);
  display.println(F("Hello, world!"));
  display.display();
}

void loop() { 

}
