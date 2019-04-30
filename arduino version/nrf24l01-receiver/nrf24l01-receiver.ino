#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define led 2

RF24 radio(4, 5); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
boolean state = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("slave Setup...");

  pinMode(led, OUTPUT);

  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
}
void loop() {
  //  delay(5);
  //  radio.startListening();
  //  if (radio.available()) {
  //    char text[32] = "";
  //    radio.read(&text, sizeof(text));
  //    Serial.println(text);
  //  }

  digitalWrite(led, !digitalRead(led));
  delay(100);
  digitalWrite(led, !digitalRead(led));
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {
      char text[32] = "";
      radio.read(&text, sizeof(text));
      Serial.println(text);
    }
    delay(100);
    radio.stopListening();
    state = digitalRead(led);
    radio.write(&state, sizeof(state));
  }
}
