const int sensorPin = A0;     // Digital input pin for the proximity sensor (D0)
const int buzzerPin = A3;     // Digital output pin for the buzzer

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = digitalRead(sensorPin);  // Read the digital value from the proximity sensor (D0)

  if (sensorValue == LOW) {
    digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer when the proximity sensor LED is off
    Serial.println("Object detected!");
  } else {
    digitalWrite(buzzerPin, LOW);   // Turn off the buzzer when the proximity sensor LED is on
  }

  delay(100);  // Adjust the delay value as needed
}
