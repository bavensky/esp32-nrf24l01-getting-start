#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define led 16

RF24 radio(4, 5); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
boolean state = 0;

uint32_t pevToggle = 0;
void ledToggle(int timeToggle) {
  uint32_t curToggle = millis();
  if (curToggle - pevToggle >= timeToggle) {
    pevToggle = curToggle;
    digitalWrite(led, !digitalRead(led));
  }

  if (curToggle - pevToggle >= timeToggle * 2) {
    pevToggle = curToggle;
    digitalWrite(led, !digitalRead(led));
  }
}

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
int rc = 0;

uint32_t pevTime = 0;

void loop() {
  uint32_t curTime = millis();
  if (curTime - pevTime >= 200) {
    pevTime = curTime;

    radio.stopListening();
    char dataBuffer[100];
    count += 1;
    sprintf(dataBuffer, "%d", count);

    rc = radio.write(&dataBuffer, sizeof(dataBuffer));
    if (rc) {
      ledToggle(200);
      Serial.println("Successfully");
    } else {
      digitalWrite(led, HIGH);
    }
  }


  //  digitalWrite(led, !digitalRead(led));
  //  radio.startListening();
  //  while (!radio.available());
  //  radio.read(&state, sizeof(state));
  //  if (state == HIGH) {
  //    digitalWrite(led, HIGH);
  //  }
  //  else {
  //    digitalWrite(led, LOW);
  //  }
}
