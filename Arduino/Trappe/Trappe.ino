#include <Servo.h>

int positionServo = 0;
Servo servo;

void ouvrirTrappe(){
  servo.write(180);
  positionServo = 180;
}

void fermerTrappe(){
  servo.write(0);
  positionServo = 0;
}

void setup(){
  Serial.begin(9600);
  servo.attach(11);
}

void loop(){

}
