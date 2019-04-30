#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define led 16

RF24 radio(4, 5); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
boolean state = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("master Setup...");

  pinMode(led, OUTPUT);

  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
}

uint16_t count = 0;

void loop() {
  delay(100);
  radio.stopListening();
  char dataBuffer[100];
  count += 1;
  sprintf(dataBuffer, "%d", count);
  radio.write(&dataBuffer, sizeof(dataBuffer));
  Serial.println(dataBuffer);
  digitalWrite(led, !digitalRead(led));

  delay(100);
  digitalWrite(led, !digitalRead(led));
  radio.startListening();
  while (!radio.available());
  radio.read(&state, sizeof(state));
  if (state == HIGH) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
}
