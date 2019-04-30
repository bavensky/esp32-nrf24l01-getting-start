/*** nrf24l01 Slave board ***/
// http://maniacbug.github.io/RF24/classRF24.html
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define LED 2 // node32 board led builtin

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
  radio.openWritingPipe(addresses[0]);    // 00001 send data to master
  radio.openReadingPipe(1, addresses[1]); // 00002 recive data form master
  radio.setPALevel(RF24_PA_HIGH);         //  RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, and RF24_PA_HIGH=0dBm.
  radio.setDataRate(RF24_250KBPS);        //  RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
}

void loop()
{
  radio.startListening();
  if (radio.available())
  {
    while (radio.available())
    {
      char dataIncoming[32] = "";
      radio.read(&dataIncoming, sizeof(dataIncoming));
      Serial.println(dataIncoming);
    }
    delay(100);
  }
}