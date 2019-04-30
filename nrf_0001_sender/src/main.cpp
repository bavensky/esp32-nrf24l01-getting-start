/*** nrf24l01 Master board ***/
// http://maniacbug.github.io/RF24/classRF24.html
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define LED 16 // nano32 board led builtin

RF24 radio(4, 5); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
boolean state = 0;
uint16_t count = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Innitial Transmister...");

  pinMode(LED, OUTPUT);

  radio.begin();
  radio.openWritingPipe(addresses[1]);    //  00002  send data to slave
  radio.openReadingPipe(1, addresses[0]); //  00001  recive data form slave
  radio.setPALevel(RF24_PA_HIGH);         //  RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, and RF24_PA_HIGH=0dBm.
  radio.setDataRate(RF24_250KBPS);        //  RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
}

void loop()
{
  radio.stopListening();
  char dataBuffer[100];
  count += 1;
  sprintf(dataBuffer, "%d", count);
  radio.write(&dataBuffer, sizeof(dataBuffer));
  Serial.println(dataBuffer);
  delay(100);

  // digitalWrite(LED, !digitalRead(led));
}