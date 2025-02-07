#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define BUZZER 5
#define LED_1 15

// global variables
int seconds = 00;
int minutes = 0;
int hours = 0;
int days = 0;

int C_4 = 262;
int D_4 = 294;
int E_4 = 330;
int F_4 = 349;
int G_4 = 392;
int A_4 = 440;
int B_4 = 494;
int C_5 = 523;

int notes[] = {
    C_4, D_4, E_4, G_4, F_4, E_4, C_4, A_4, C_5, G_4
};

int durations[] = {
    500, 500, 750, 500, 750, 750, 1000, 750, 1000, 1500
};

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void print_line(String message, int column = 0, int row = 0, int size = 1, int color = SSD1306_WHITE);
void print_time_now();
void ring_alarm();

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

  pinMode(BUZZER, OUTPUT);
  pinMode(LED_1, OUTPUT);
digitalWrite(LED_1, HIGH);
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  { 
    Serial.println(F("SSD1306 allocation failed"));
    while (true)
      ; 
  }
  print_line("Welcome to the medibox");
  display.clearDisplay();
ring_alarm();
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

void ring_alarm()
{
  for (int i = 0; i < sizeof(notes) / sizeof(notes[0]); i++)
  {
    tone(BUZZER, notes[i], durations[i]);
  }
}
