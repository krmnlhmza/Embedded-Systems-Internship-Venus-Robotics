#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11);

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("Master hazır!");
  Serial.println("L = LED aç, K = LED kapat");
}

void loop() {
  if (Serial.available()) {
    char gonderilen = Serial.read();
    BT.write(gonderilen);
    Serial.print("Gönderildi: ");
    Serial.println(gonderilen);
  }
  if (BT.available()) {
    Serial.write(BT.read());
  }
}