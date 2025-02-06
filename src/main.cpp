#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// global variables
int seconds = 0;
int minutes = 0;
int hours = 0;
int days = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void print_line(String message, int column = 0, int row = 0, int size = 1, int color = SSD1306_WHITE);
void print_time_now();

const uint8_t crossIcon[] PROGMEM = {
    0b00111100, // ..@..@..
    0b00111100, // ..@..@..
    0b11111111, // @@@@@@@@
    0b11111111, // ..@..@..
    0b11111111, // ..@..@..
    0b11111111, // @@@@@@@@
    0b00111100, // ..@..@..
    0b00111100  // ..@..@..
};

void setup()
{
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  { // 0x3C is the I2C address for many SSD1306 displays
    Serial.println(F("SSD1306 allocation failed"));
    while (true)
      ; // Halt if initialization fails
  }
  print_line("Welcome to the medibox");
  display.clearDisplay();
}

void loop()
{
  seconds++;
  if (seconds == 60)
  {
    seconds = 0;
    minutes++;
  }
  if (minutes == 60)
  {
    minutes = 0;
    hours++;
  }
  if (hours == 24)
  {
    hours = 0;
    days++;
  }
  display.drawBitmap(0, 0, crossIcon, 8, 8, SSD1306_WHITE);
  print_time_now();
  display.clearDisplay();
  delay(1000);
}

void print_line(String message, int column, int row, int size, int color)
{
  display.setTextSize(size);
  display.setTextColor(color);
  display.setCursor(column, row);
  display.println(message);
  display.display();
  // delay(2000);
}

void print_time_now()
{
  print_line("Time: " + String(hours) + ":" + String(minutes) + ":" + String(seconds), 20, 32,1.75);
}
