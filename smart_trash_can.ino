/*
 * Smart Trash Can with IR Sensor
 * Opens lid when hand is detected, closes after delay
 * 
 * Hardware: Arduino UNO, IR Obstacle Sensor, SG90 Servo
 * Author: theetee (based on @aprende.domotica concept)
 */

#include <Servo.h>

Servo lidServo;

const int IR_SENSOR_PIN = 7;
const int SERVO_PIN = 9;

const int LID_CLOSED = 0;
const int LID_OPEN = 90;
const int DELAY_BEFORE_CLOSE = 3000;

bool isOpen = false;

void setup() {
  Serial.begin(9600);
  lidServo.attach(SERVO_PIN);
  lidServo.write(LID_CLOSED);
  pinMode(IR_SENSOR_PIN, INPUT);
  
  Serial.println("Smart Trash Can Ready!");
  Serial.println("Wave your hand over the sensor...");
  
  delay(2000);
}

void loop() {
  int sensorValue = digitalRead(IR_SENSOR_PIN);
  
  if (sensorValue == LOW && !isOpen) {
    Serial.println("Hand detected! Opening lid...");
    openLid();
    isOpen = true;
  }
  
  if (sensorValue == HIGH && isOpen) {
    delay(DELAY_BEFORE_CLOSE);
    Serial.println("Closing lid...");
    closeLid();
    isOpen = false;
  }
  
  delay(50);
}

void openLid() {
  for (int pos = LID_CLOSED; pos <= LID_OPEN; pos++) {
    lidServo.write(pos);
    delay(15);
  }
}

void closeLid() {
  for (int pos = LID_OPEN; pos >= LID_CLOSED; pos--) {
    lidServo.write(pos);
    delay(15);
  }
}
