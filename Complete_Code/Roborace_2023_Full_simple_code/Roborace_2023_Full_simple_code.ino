

// import library for bluetooth
#include <SoftwareSerial.h>
SoftwareSerial EEBlue(A0, A1);  // RX | TX


// set motor driver pins
// Left motor pins
const byte A_PWM = 6;
const byte A_IN1 = 7;
const byte A_IN2 = 8;

// Right motor pins
const byte B_PWM = 11;
const byte B_IN1 = 10;
const byte B_IN2 = 9;


void setup() {

  // Setup commands for enabling serial monitor and bluetooth module
  Serial.begin(9600);  // Begin communication to Serial monitor
  EEBlue.begin(9600);  // Begin communication to Bluetooth module
  Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!.");

  //Setup motor driver
  // Left motor setup
  pinMode(A_PWM, OUTPUT);
  pinMode(A_IN1, OUTPUT);
  pinMode(A_IN2, OUTPUT);

  // Right motor setup
  pinMode(B_PWM, OUTPUT);
  pinMode(B_IN1, OUTPUT);
  pinMode(B_IN2, OUTPUT);
}

void loop() {

  if (EEBlue.available()) {
    char received_data = EEBlue.read();
    Serial.write(received_data);

    if (received_data == 'F') {
      // Forward
      analogWrite(A_PWM, 100);  // speed
      digitalWrite(A_IN1, HIGH); //dir
      digitalWrite(A_IN2, LOW); //dir

      analogWrite(B_PWM, 100);
      digitalWrite(B_IN1, LOW);
      digitalWrite(B_IN2, HIGH);

    } else if (received_data == 'B') {
      // Backward
      analogWrite(A_PWM, 100);
      digitalWrite(A_IN1, LOW);
      digitalWrite(A_IN2, HIGH);

      analogWrite(B_PWM, 100);
      digitalWrite(B_IN1, HIGH);
      digitalWrite(B_IN2, LOW);

    } else if (received_data == 'L') {
      // Left
      analogWrite(A_PWM, leftSpeed);
      digitalWrite(A_IN1, LOW);
      digitalWrite(A_IN2, HIGH);

      analogWrite(B_PWM, rightSpeed);
      digitalWrite(B_IN1, LOW);
      digitalWrite(B_IN2, HIGH);

    } else if (received_data == 'R') {
      // Right
      analogWrite(A_PWM, leftSpeed);
      digitalWrite(A_IN1, HIGH);
      digitalWrite(A_IN2, LOW);

      analogWrite(B_PWM, 100);
      digitalWrite(B_IN1, HIGH);
      digitalWrite(B_IN2, LOW);

    } else if (received_data == 'S') {
      // Stop
      analogWrite(A_PWM, 0);
      digitalWrite(A_IN1, HIGH);
      digitalWrite(A_IN2, LOW);

      analogWrite(B_PWM, 0);
      digitalWrite(B_IN1, LOW);
      digitalWrite(B_IN2, HIGH);

    } else {
      // do nothing
    }
}

