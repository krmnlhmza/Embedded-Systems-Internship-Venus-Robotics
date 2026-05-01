/*const int ledPins[] = {8, 9, 10}; 
const int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 0) {
    
    int Number = Serial.read() - '0';
    
    if (Number >= 0 && Number < ledCount) {
      
      int targetPin = ledPins[Number]; 
      
      if (digitalRead(targetPin) == HIGH) {
        digitalWrite(targetPin, LOW); 
      } else {
        digitalWrite(targetPin, HIGH);
      }
      
      Serial.println(Number);
    } 
  }
}


const int pinSol    = 3;
const int pinSag    = 5;
const int pinYukari = 6;
const int pinAsagi  = 9;

const int pinX = A0;
const int pinY = A1;

void setup() {
  pinMode(pinSol, OUTPUT);
  pinMode(pinSag, OUTPUT);
  pinMode(pinYukari, OUTPUT);
  pinMode(pinAsagi, OUTPUT);
}

void loop() {
  int xValue = analogRead(pinX); 
  int yValue = analogRead(pinY); 

 
  int parlaklikSol    = 0;
  int parlaklikSag    = 0;
  int parlaklikYukari = 0;
  int parlaklikAsagi  = 0;

 
  if (xValue < 400) {
    parlaklikSol = map(xValue, 400, 0, 0, 255);
  } 
  else if (xValue > 600) {
    parlaklikSag = map(xValue, 600, 1023, 0, 255);
  }

  
  if (yValue < 400) {
    parlaklikYukari = map(yValue, 400, 0, 0, 255);
  } 
  else if (yValue > 600) {
    parlaklikAsagi = map(yValue, 600, 1023, 0, 255);
  }

  
  analogWrite(pinSol, parlaklikSol);
  analogWrite(pinSag, parlaklikSag);
  analogWrite(pinYukari, parlaklikYukari);
  analogWrite(pinAsagi, parlaklikAsagi);

  delay(10);
}




#include <Servo.h>

Servo motor;

const int ledYukari = 5;
const int ledAsagi = 6;
const int pinX = A0;
const int pinY = A1;
const int pinButon = 2;

void setup() {
  motor.attach(9);
  pinMode(ledYukari, OUTPUT);
  pinMode(ledAsagi, OUTPUT);
  pinMode(pinButon, INPUT_PULLUP); // İç direnci aktif et

  motor.write(90);
}

void loop() {
  // 1. BUTON KONTROLÜ (Öncelikli Görev)
  if (digitalRead(pinButon) == LOW) {
    // Servoyu başlangıç konumuna getir
    motor.write(90);
    
    // Işıkları 3 kez yak-sön yap (Blink efekti)
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledYukari, HIGH);
      digitalWrite(ledAsagi, HIGH);
      delay(200);
      digitalWrite(ledYukari, LOW);
      digitalWrite(ledAsagi, LOW);
      delay(200);
    }
    // Buton bırakılana kadar burada bekle (Debounce/Kilit)
    while(digitalRead(pinButon) == LOW); 
  }

  // 2. X EKSENİ -> SERVO
  int xVal = analogRead(pinX);
  int aci = map(xVal, 0, 1023, 0, 180);
  motor.write(aci);

  // 3. Y EKSENİ -> IŞIKLAR (Oransal Parlaklık)
  int yVal = analogRead(pinY);
  
  if (yVal < 450) { // Yukarı itiliyor
    int parlaklik = map(yVal, 450, 0, 0, 255);
    analogWrite(ledYukari, parlaklik);
    analogWrite(ledAsagi, 0);
  } 
  else if (yVal > 580) { // Aşağı itiliyor
    int parlaklik = map(yVal, 580, 1023, 0, 255);
    analogWrite(ledAsagi, parlaklik);
    analogWrite(ledYukari, 0);
  } 
  else { // Orta bölge (Ölü bölge)
    analogWrite(ledYukari, 0);
    analogWrite(ledAsagi, 0);
  }

  delay(15);
}
*/



/*void setup() {
  Serial.begin(9600); 
}
void loop() {
  Serial.print('A'); 

  delay(1000); 

  Serial.print('B'); 

  delay(1000); 
}


char gelenHarf; 

void setup() {
  Serial.begin(9600); 
  
  pinMode(10, OUTPUT); 
  pinMode(9, OUTPUT); 
}

void loop() {
  if (Serial.available() > 0) { 

    gelenHarf = Serial.read(); 

    if (gelenHarf == 'A') {
      digitalWrite(10, HIGH);
      digitalWrite(9, LOW);  
    } 
  
    else if (gelenHarf == 'B') {
      digitalWrite(10, LOW);  
      digitalWrite(9, HIGH); 
    }
  }
}


#include <SoftwareSerial.h>

SoftwareSerial BT(9, 10); 

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  //Komutlar: L = LED aç, K = LED kapat
}

void loop() {

  if (Serial.available()) {
    BT.write(Serial.read());
  }

  if (BT.available()) {
    Serial.write(BT.read());
  }

}
*/
#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11);

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW); // EN LOW = normal mod
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