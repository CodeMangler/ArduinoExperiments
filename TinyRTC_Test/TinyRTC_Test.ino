#include <Wire.h>
#include <RTClib.h>

/*
 * Connections:
 * 
 * TinyRTC | Arduino
 * ------------------
 *    Vcc  | Vcc (5V)
 *    GND  | GND
 *    SDA  | A4 (Analog 3)
 *    SCL  | A5 (Analog 5)
 */

RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600); // Set baud rate for Serial Monitor to be able to listen to this
  Serial.println("Testing TinyRTC based on DS1307");
  Wire.begin();

  rtc.begin(); // Invoke the RTC library
//  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set RTC date and time to the date and time this sketch was compiled. Required only for the first time.
  //[Note: Without setting an initial date and time, the RTC counter does not increment/work at all]
}

void loop() {
  DateTime now = rtc.now(); // Read from the RTC chip

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  delay(3000);
}

