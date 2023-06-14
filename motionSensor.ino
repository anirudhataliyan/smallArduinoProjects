// The time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;

// The time when the sensor outputs a low impulse
unsigned long lowIn;

// The amount of milliseconds the sensor has to be low
// before we assume all motion has stopped
unsigned long pause = 5000;

boolean lockLow = true;
boolean takeLowTime;

int pirPin = 3;    // The digital pin connected to the PIR sensor's output
int ledPin = 13;

/////////////////////////////
// SETUP
void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  // Give the sensor some time to calibrate
  Serial.print("Calibrating sensor...");
  for (int i = 0; i < calibrationTime; i++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
}

////////////////////////////
// LOOP
void loop() {
  if (digitalRead(pirPin) == HIGH) {
    if (lockLow) {
      // Makes sure we wait for a transition to LOW before any further output is made
      lockLow = false;
      Serial.println("---");
      Serial.print("Motion detected at ");
      Serial.print(millis() / 1000);
      Serial.println(" sec");
    }
    digitalWrite(ledPin, HIGH);  // Turn on the LED
    takeLowTime = true;
  }

  if (digitalRead(pirPin) == LOW) {
    if (takeLowTime) {
      lowIn = millis();  // Save the time of the transition from HIGH to LOW
      takeLowTime = false;  // Make sure this is only done at the start of a LOW phase
    }
    // If the sensor is low for more than the given pause,
    // we assume that no more motion is going to happen
    if (!lockLow && millis() - lowIn > pause) {
      // Makes sure this block of code is only executed again after
      // a new motion sequence has been detected
      lockLow = true;
      Serial.print("Motion ended at ");  // Output
      Serial.print((millis() - pause) / 1000);
      Serial.println(" sec");
      digitalWrite(ledPin, LOW);  // Turn off the LED
    }
  }
}
