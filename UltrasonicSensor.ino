

#define TRIG_PIN   3  // The Arduino Nano pin connected to TRIG pin of ultrasonic sensor
#define ECHO_PIN   2  // The Arduino Nano pin connected to ECHO pin of ultrasonic sensor
#define BUZZER_PIN 9  // The Arduino Nano pin connected to Piezo Buzzer

#define DISTANCE_THRESHOLD  30 // in centimeters

float duration_us, distance_cm;

void setup() {
  Serial.begin (9600);         // Initialize the Serial to communicate with the Serial Monitor.
  pinMode(TRIG_PIN, OUTPUT);   // set arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);    // set arduino pin to input mode
  pinMode(BUZZER_PIN, OUTPUT); // set arduino pin to output mode
}

void loop() {
  // Produce a 10-microsecond pulse to the TRIG pin.
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the pulse duration from the ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.035 * duration_us;

  if (distance_cm < DISTANCE_THRESHOLD)
    digitalWrite(BUZZER_PIN, HIGH); // turn on Piezo Buzzer
  else
    digitalWrite(BUZZER_PIN, LOW);  // turn off Piezo Buzzer

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
}
