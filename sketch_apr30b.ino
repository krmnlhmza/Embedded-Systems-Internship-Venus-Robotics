#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BT(10, 11);
Servo servo;

// ---- STRUCT ----
struct CommandData {
  char action;
  int value;
  bool valid;
};

// ---- LED PINLER ----
const int LED1 = 3;
const int LED2 = 4;
const int LED3 = 5;

bool led1State = false;
bool led2State = false;
bool led3State = false;

// ---- PARSE FUNCTION (SENİN KODUN) ----
CommandData parse_data_transfer_func(Stream &serial) {
  CommandData command;

  while(serial.available() > 0) {

    if (serial.peek() == '<') {

      if (serial.available() >= (int)sizeof(CommandData) + 2) {

        serial.read(); // '<'

        serial.readBytes((char*)&command, sizeof(CommandData));

        if (serial.read() == '>') {
          return command;
        }
      } else {
        break;
      }

    } else {
      serial.read(); // çöpleri temizle
    }
  }

  command.valid = false;
  return command;
}

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  servo.attach(6);
  servo.write(90);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  Serial.println("SLAVE READY");
}

void loop() {

  CommandData cmd = parse_data_transfer_func(BT);

  if (cmd.valid) {

    Serial.print("Gelen: ");
    Serial.print(cmd.action);
    Serial.print(" - ");
    Serial.println(cmd.value);

    // ---- SERVO ----
    if (cmd.action == 'S') {
      if (cmd.value >= 0 && cmd.value <= 180) {
        servo.write(cmd.value);
      }
    }

    // ---- LED ----
    else if (cmd.action == 'a') {
      led1State = !led1State;
      digitalWrite(LED1, led1State);
    }
    else if (cmd.action == 'b') {
      led2State = !led2State;
      digitalWrite(LED2, led2State);
    }
    else if (cmd.action == 'c') {
      led3State = !led3State;
      digitalWrite(LED3, led3State);
    }
  }
}