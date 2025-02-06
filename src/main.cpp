#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

unsigned long previousMillis = 0;  // Stores the last time the display was updated
const long interval = 1000;        // Interval at which to update the display (in milliseconds)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is the I2C address for many SSD1306 displays
    Serial.println(F("SSD1306 allocation failed"));
    while (true); // Halt if initialization fails
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_INVERSE);

  display.display();
  Serial.println("Hello, ESP32!");
}

void loop() { 
  unsigned long currentMillis = millis(); // Get the current time in milliseconds
  
  if (currentMillis - previousMillis >= interval) {
    // Save the last time the display was updated
    previousMillis = currentMillis;
    
    // Update the display
    display.clearDisplay();  // Clear the display before updating it
    display.setCursor(0, 0); // Set cursor to the top left corner
    display.print("Timer: ");
    display.print(currentMillis / 1000); // Display seconds
    display.display();  // Update the display
  }
}
