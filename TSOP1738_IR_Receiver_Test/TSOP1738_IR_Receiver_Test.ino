/* Connections:
 *  
 *  TSOP1738   | Arduino
 *  ---------------------
 *      GND    | GND
 *      Vs     | Vcc (5V)
 *      OUT    | D12
 * 
 * On TSOP1738, GND and Vs are the two pins that are close together. Among the two, GND is the one near the edge.
 */

// IR Remote Library from: https://github.com/z3t0/Arduino-IRremote/releases/download/2.0.1/IRremote.zip
#include <IRremote.h>

int TSOP1738_PIN = 12;
IRrecv ir_receiver(TSOP1738_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  Serial.println("TSOP1738 IR Receiver Test");
  ir_receiver.enableIRIn(); // Start the receiver
}

void loop() {
  if (ir_receiver.decode(&results)) {
    Serial.println(results.value, HEX);
    ir_receiver.resume(); // Receive the next value
  }
}

