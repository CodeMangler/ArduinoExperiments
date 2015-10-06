/* Connections:
 *  
 *  HC-05    | Arduino
 *  ------------------
 *    GND    | GND
 *    Vcc    | Vcc (5V)
 *    RX     | D11 (Software TX - see configuration below)
 *    TX     | D10 (Software RX - see configuration below)
 *  EN/KEY   | D9 (Only if EN/KEY are actually connected to PIN 34 on the module. Use a multimeter to confirm)
 *    
 * Boot HC-05 with PIN 34 connected to Vcc (either EN/KEY pins, or just use a jumper wire and touch PIN 34 to Vcc) to boot it in AT mode. LED blinks in two second intervals - 2s ON, 2s OFF.
 * OR, pull PIN 34 to Vcc (again, EN/KEY pins or jumper wire) during operation to switch to AT mode in between. LED continues to blink in the usual pattern - fast blinks.
 */

/*
  These commands are supposed to set baud rates directly, but do not work for the module I have:
    AT+BAUD1-------1200
    AT+BAUD2-------2400
    AT+BAUD3-------4800
    AT+BAUD4-------9600 - Default for HC-05/HC-06
    AT+BAUD5------19200
    AT+BAUD6------38400 - Default for HC-05 when booted in AT mode
    AT+BAUD7------57600 - Default Arduino Firmata speed
    AT+BAUD8-----115200
    AT+BAUD9-----230400
    AT+BAUDA-----460800
    AT+BAUDB-----921600
    AT+BAUDC----1382400

    AT Commands (configure name, firmata baud rate, and set PIN to 0000):
    AT
    > OK
    AT+NAME?
    > <No Response>
    AT+NAME=Psi
    > OK
    AT+VERSION?
    > +VERSION:2.0-20100601
    > OK
    AT+UART?
    > 38400,0,0 // if booted in AT mode. otherwise, 9600,0,0 -> current communication baud rate
    AT+UART=57600,0,0 // configure default baud rate for firmata
    > OK
    AT+ROLE?
    > +ROLE:0 // 0 -> Slave Mode, 1 -> Master Mode. Set to slave mode if not already in Slave mode. Cannot pair with other devices otherwise.
    > OK
    AT+PSWD?
    > +PSWD:1234
    > OK
    AT+PSWD=0000
    > OK
    ------------
    Send AT+ORGL to reset (UART=38400,0,0 ; PIN=1234; Name=HC-05; ROLE=0)
    AT+ROLE=1 // 1 for master mode

    UART quick ref:
    AT+UART=<Baud Rate>,<Stop Bits>,<Parity>
    Baud Rate: 4800 | 9600 | 19200 | 38400 | 57600 | 115200 | 23400 | 460800 | 921600 | 1382400
    Stop Bits: 0 -> 1 bit, 1 -> 2 bits
    Parity: 0 -> None, 1 -> Odd Parity, 2 -> Even Parity
    
    Command list: http://elecfreaks.com/store/download/datasheet/Bluetooth/HC-0305%20serail%20module%20AT%20commamd%20set%20201104%20revised.pdf

    LED Status:
    Constant/Fast Blink: Unpaired (or master mode? or in AT mode - not booted in AT mode)
    On 2s, Off 2s: AT Mode (booted up in AT mode)
    Short blink every 2s: Paired
*/

#include <SoftwareSerial.h>

SoftwareSerial btSerial(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT); // Only if EN/KEY pins on the module are connected
  digitalWrite(9, HIGH);
  Serial.println("Enter AT commands:");
//  btSerial.begin(38400); // HC05 Default AT Mode Baud Rate (when booted with PIN 34 connected to Vcc)
  btSerial.begin(57600); // Baud Rate to use post configuration
}

void loop()
{
  if (btSerial.available()) {
    Serial.write(btSerial.read());
  }
  
  if (Serial.available()){
    btSerial.write(Serial.read());
  }
}

