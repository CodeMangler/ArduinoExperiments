#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

/*
 * Connections:
 *
 * nRF24L01 Pinout:
 * <Antenna this way> ... 8 (IRQ)  | 7 (MISO)
 *                        6 (MOSI) | 5 (SCK)
 *                        4 (CSN)  | 3 (CE)
 *                        2 (Vcc)  | 1 (GND)
 *
 * nRF24L01 | Arduino
 * -------------------
 *   GND    | GND
 *   Vcc    | Vcc (3.3V)
 *   CE     | D9
 *   CSN    | D10
 *   SCK    | D13
 *   MOSI   | D11
 *   MISO   | D12
 *   IRQ    | D2 [Optional - unused in this sketch]
 */

RF24 radio(9, 10); // CE (Chip Enable) and CS (Chip Select) PIN connections to Arduino. The rest of the pins are assumed to be connected via the SPI bus (pins 11, 12 and 13 on UNO)

uint64_t thisRadioAddress = 0xF0F0F0F0F0;
uint64_t otherRadioAddress = 0xF0F0F0F066;

// Uncomment and use these addresses when uploading to the second Arduino + nRF24L01
//uint64_t thisRadioAddress = 0xF0F0F0F066;
//uint64_t otherRadioAddress = 0xF0F0F0F0F0;

int data = 42;
unsigned long LISTEN_TIMEOUT_MICROS = 1000000; // Timeout in microseconds
unsigned long listen_start_time = 0;
bool listen_timeout = false;

int RX_MODE = 0;
int TX_MODE = 1;
int radio_mode = RX_MODE;

int toggle_radio_mode() {
  if (radio_mode == RX_MODE) {
    Serial.println("Switching to TX mode");
    radio_mode = TX_MODE;
  } else {
    Serial.println("Switching to RX mode");    
    radio_mode = RX_MODE;
  }
}

int receive_data() {
  radio.startListening();
  listen_start_time = micros();

  while (!radio.available()) {
    if ((micros() - listen_start_time) > LISTEN_TIMEOUT_MICROS) {
      listen_timeout = true;
      break;
    }
  }

  if(listen_timeout) {
    Serial.println("Timed out waiting for data");
  } else {
    radio.read(&data, sizeof(int));    
    Serial.print("Received: ");
    Serial.println(data);
    Serial.println("Incrementing data for the next transmission");
    data = data + 1;
  }

  listen_timeout = false;
  toggle_radio_mode();
}

int transmit_data() {
  radio.stopListening();
  Serial.print("Transmitting: ");
  Serial.println(data);

  radio.write(&data, sizeof(int));

  Serial.println("Transmission complete");
  toggle_radio_mode();
}

void setup() {
  Serial.begin(9600);
  Serial.println("RF24 RX/TX with nRF24L01");

  radio.begin();
  // Set the PA Level low to prevent power supply (noise) related issues since this is a test sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openReadingPipe(1, thisRadioAddress);
  radio.openWritingPipe(otherRadioAddress);
}

void loop() {
  if (radio_mode == RX_MODE) {
    receive_data();
  } else {
    transmit_data();
  }
}

