#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>

/*
 * Connections:
 * 
 * TinyRTC | Arduino
 * ------------------
 *    Vcc  | Vcc (5V)
 *    GND  | GND
 *    SDA  | A4 (Analog 4)
 *    SCL  | A5 (Analog 5)
 *    
 *    LCD  | Arduino
 * ------------------
 *   VSS   | GND
 *   VDD   | Vcc (5V)
 *   V0    | D9 (PWM)
 *   RS    | D12
 *   RW    | GND
 *   E     | D11
 *   D0    | Unconnected
 *   D1    | Unconnected
 *   D2    | Unconnected
 *   D3    | Unconnected
 *   D4    | D5
 *   D5    | D4
 *   D6    | D3
 *   D7    | D2
 *   A     | Vcc (5V)
 *   K     | GND
 */

RTC_DS1307 rtc;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String hour, minute, second, date, month, year;
String timeString, dateString;

int D9 = 9;

void setup() {
  timeString = String();
  dateString = String();
  Serial.begin(9600); // Set baud rate for Serial Monitor to be able to listen to this
  Serial.println("Testing TinyRTC (based on DS1307) and a 16x2 LCD");
  Wire.begin();

  rtc.begin(); // Invoke the RTC library
//  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set RTC date and time to the date and time this sketch was compiled. Required only for the first time.
  //[Note: Without setting an initial date and time, the RTC counter does not increment/work at all]

  lcd.begin(16, 2);
  pinMode(A3, OUTPUT);
  pinMode(D9, OUTPUT); // Set D9 to output for PWM
  analogWrite(D9, 80); // Contrast level (0-255 - PWM)
}

void loop() {
  DateTime now = rtc.now(); // Read from the RTC chip

  hour = String(now.hour());
  minute = String(now.minute());
  second = String(now.second());
  date = String(now.day());
  month = String(now.month());
  year = String(now.year());

  timeString = String(hour + ":" + minute + ":" + second);
  dateString = String(year + "/" + month + "/" + date);

  Serial.println(timeString + ' ' + dateString);

  lcd.home();
  lcd.print(timeString);
  lcd.setCursor(0, 1);
  lcd.print(dateString);

  delay(1000);
  lcd.clear();
}

