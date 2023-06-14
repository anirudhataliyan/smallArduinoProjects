#include <Arduino.h>
#include <TM1637Display.h>

// Define the pin connections
#define CLK_PIN 4
#define DIO_PIN 5

TM1637Display display(CLK_PIN, DIO_PIN);

// Define segment patterns for digits 0-9 and blank
const uint8_t segments[] = {
  0b00111111,  // 0
  0b00000110,  // 1
  0b01011011,  // 2
  0b01001111,  // 3
  0b01100110,  // 4
  0b01101101,  // 5
  0b01111101,  // 6
  0b00000111,  // 7
  0b01111111,  // 8
  0b01100111,  // 9
  0b00000000   // Blank
};

unsigned long previousMillis = 0;
unsigned long interval = 60000; // 1 minute interval

byte hours = 7;
byte minutes = 29;

void setup() {
  // Initialize the display
  display.setBrightness(7); // Adjust the brightness (0-7)
}

void loop() {
  unsigned long currentMillis = millis();

  // Check if the interval has elapsed
  if (currentMillis - previousMillis >= interval) {
    // Increment the time
    minutes++;
    if (minutes >= 60) {
      minutes = 0;
      hours++;
      if (hours >= 24) {
        hours = 0;
      }
    }

    previousMillis = currentMillis;
  }

  byte hour_1 = hours / 10;
  byte hour_2 = hours % 10;
  byte minute_1 = minutes / 10;
  byte minute_2 = minutes % 10;

  display.setSegments(&segments[hour_1], 1, 0);
  display.setSegments(&segments[hour_2], 1, 1);
  display.setSegments(&segments[minute_1], 1, 2);
  display.setSegments(&segments[minute_2], 1, 3);

  delay(100); // Small delay to avoid flickering
}
