#include <Servo.h>

/*
 * Connections:
 * 
 * Servo [Tower Pro SG90] | Arduino
 * ---------------------------------
 *   Vcc [Red - Middle]   | Vcc (5V)
 *   GND [Black/Brown]    | GND
 *   Control [Yellow]     | D2 (Digital PIN 2)
 */

Servo testServo;
int angle = 0;
int D2 = 2; // Digital PIN 2

void setup() {
  testServo.attach(D2);
}

void loop() {
  for (angle = 0; angle <= 180; angle += 1) { // Rotate the shaft from 0 to 180 degrees in steps of 1 degree
    testServo.write(angle);
    delay(15); // Wait for the servo to reach the position
  }

  for (angle = 180; angle >= 0; angle -= 1) { // Rotate the shaft from 180 to 0 degrees in steps of 1 degree
    testServo.write(angle);
    delay(15); // Wait for the servo to reach the position
  }
}

