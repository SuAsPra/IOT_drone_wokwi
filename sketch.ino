#include <Servo.h>

// Ultrasonic pins
const int trigPin = 10;
const int echoPin = 11;

// Stepper motor control pins
const int stepPins[] = {2, 4, 6, 8};  // STEP pins for 4 motors
const int dirPins[]  = {3, 5, 7, 9};  // DIR pins for 4 motors

// Servo objects
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Potentiometer analog pins
const int potPins[] = {A0, A1, A2, A3};

// Servo pins
const int servoPins[] = {12, 13, A4, A5};

void setup() {
  // Initialize ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize stepper motor pins
  for (int i = 0; i < 4; i++) {
    pinMode(stepPins[i], OUTPUT);
    pinMode(dirPins[i], OUTPUT);
  }

  // Attach servos to their pins
  servo1.attach(servoPins[0]);
  servo2.attach(servoPins[1]);
  servo3.attach(servoPins[2]);
  servo4.attach(servoPins[3]);

  Serial.begin(9600);
}

void loop() {
  // Measure distance
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  Serial.print("Distance: ");
  Serial.println(distance);

  // Set motor direction based on distance
  bool clockwise = (distance > 30);
  for (int i = 0; i < 4; i++) {
    digitalWrite(dirPins[i], clockwise ? HIGH : LOW);
  }

  // Step all motors together
  for (int step = 0; step < 200; step++) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(stepPins[i], HIGH);
    }
    delayMicroseconds(800);
    for (int i = 0; i < 4; i++) {
      digitalWrite(stepPins[i], LOW);
    }
    delayMicroseconds(800);
  }

  // Read potentiometers and move servos
  int potValues[4];
  int angles[4];
  potValues[0] = analogRead(potPins[0]);
  potValues[1] = analogRead(potPins[1]);
  potValues[2] = analogRead(potPins[2]);
  potValues[3] = analogRead(potPins[3]);

  angles[0] = map(potValues[0], 0, 1023, 0, 180);
  angles[1] = map(potValues[1], 0, 1023, 0, 180);
  angles[2] = map(potValues[2], 0, 1023, 0, 180);
  angles[3] = map(potValues[3], 0, 1023, 0, 180);

  servo1.write(angles[0]);
  servo2.write(angles[1]);
  servo3.write(angles[2]);
  servo4.write(angles[3]);

  delay(10);
} 