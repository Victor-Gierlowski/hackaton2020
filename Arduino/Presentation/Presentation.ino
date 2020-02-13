#include<SoftwareSerial.h>
#include<Servo.h>
#define Tx 10
#define Rx 11

Servo servo;

SoftwareSerial bt(Tx,Rx);
char c;

void ouvrirTrappe(){
  servo.write(180);
}

void fermerTrappe(){
  servo.write(0);
}

void setup(){
  bt.begin(9600);
  Serial.begin(9600);
  servo.attach(9);
}

void loop(){
  while(bt.available()){
    c = bt.read();
    if(c == 'F')
      fermerTrappe();
    else if(c =='O')
      ouvrirTrappe();
  }
}
