#include <Encoder.h>

/*
 * Connections:
 * 
 * RotaryEncoder pins aren't really numbered like the other components.
 * The 3 pin side notifies the rotary motion, and the two pin side acts as a regular push button.
 * Two pin switch is connected like a regular switch. i.e. one pin to GND (or Vcc) and the other to a signal pin.
 * Of the 3 pins, middle one is the ground, and the other two pins encode the transition direction in gray code.
 * Connect middle to GND, and the other two to two signal pins and monitor transitions.
 * 
 * RotaryEncoder | Arduino
 * ------------------
 *    A (1)      | D2
 * GND (2/Middle)| GND
 *    B (3)      | D3
 *    SW         | D4
 *  GND (SW)     | GND
 *  
 */

int rotaryPinA = 2;
int rotaryPinB = 3;
int rotaryPushPin = 4;

Encoder rotary(rotaryPinA, rotaryPinB);

long rotaryPosition = 0;
int pushButtonState;
int lastPushButtonState = LOW;
long debounceDelay = 50; // milliseconds
long lastDebounceTime = 0;

void setup() {
  pinMode(rotaryPushPin, INPUT);
  digitalWrite(rotaryPushPin, HIGH); // Enable pull up resistors
 
  Serial.begin(9600);
  Serial.println("Rotary Encoder with push button test");
}

void loop() {
  long currentPosition = rotary.read();
  if(currentPosition != rotaryPosition){
    rotaryPosition = currentPosition;
    Serial.print("Position: ");
    Serial.print(rotaryPosition);
    Serial.println(); 
  }

  // Read and debounce the push button state
  int currentPushButtonState = digitalRead(rotaryPushPin);
  if(currentPushButtonState != lastPushButtonState){
    lastDebounceTime = millis();
  }
  
  if((millis() - lastDebounceTime) > debounceDelay) {
    if(currentPushButtonState != pushButtonState){
      pushButtonState = currentPushButtonState;
      Serial.println(pushButtonState ? "Released" : "Pushed");
    }
  }

  lastPushButtonState = currentPushButtonState;
}

