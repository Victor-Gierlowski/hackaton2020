//libraries
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Wire.h>
#include <Servo.h>
#include <Ultrasonic.h>
#include <SoftwareSerial.h>

//all variables
uint8_t gyro=0; uint8_t accel=0;uint8_t mag=0; uint8_t syst=0;
int flightMode;
int masterEngineSpeed = constrain(masterEngineSpeed,45,145);
int engineSpeed1 = constrain(engineSpeed1,45,145);
int engineSpeed2 = constrain(engineSpeed2,45,145);
int engineSpeed3 = constrain(engineSpeed3,45,145);
int engineSpeed4 = constrain(engineSpeed4,45,145);
int altEngPwr1Mem;
int altEngPwr2Mem;
int altEngPwr3Mem;
int altEngPwr4Mem;
int sustentationTime=25;
float roll, pitch, heading;
float targetRoll, targetPitch, targetHeading;
float altitude;
float masterAltitude;
float targetAltitude;
long gndProximity;
long masterGndProximity;
boolean averageGndProximity=false;
boolean start = false; 
boolean calib = false;
boolean emergency = false;
boolean altitudeChange = false;
void stabilisation();
void atitudeConformation();
void ultrasonicTakeoff();
void sustentation();
int stab=0;
Servo enginePower1;
Servo enginePower2;
Servo enginePower3;
Servo enginePower4;
Ultrasonic ultrasonic(2);

//Servo trappe + Bluetooth
#define Tx 10
#define Rx 11
#define servoTrappe 8
SoftwareSerial bluetoothSerial(Tx,Rx);
Servo servoT;
boolean trappeOuverte = false;
/*macro*/

#define engineConforming enginePower1.write(engineSpeed1);enginePower2.write(engineSpeed2);enginePower3.write(engineSpeed3);enginePower4.write(engineSpeed4);
#define masterEngineConforming enginePower1.write(masterEngineSpeed);enginePower2.write(masterEngineSpeed);enginePower3.write(masterEngineSpeed);enginePower4.write(masterEngineSpeed);


//defining values for I²C sensors
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(); 


void setup(){  
  Serial.begin(9600);
  //Trappe setup
  bluetoothSerial.begin(9600); // Setup le module bluetooth
  servoT.attach(servoTrappe);
  goupiller();
  //pins 4 EVERYTHING
  enginePower1.attach(4);
  enginePower2.attach(5);
  enginePower3.attach(6);
  enginePower4.attach(7);
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  Serial.println("test"); 

  //orientation sensor setup
  Serial.println("Orientation Sensor Test"); Serial.println("");
//  sensor initialisation
  if(!bno.begin())
  {                                                                  //BNO055
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }                               
  delay(1000);
  bno.setExtCrystalUse(true);
  delay(500);
  flightMode=0;
  masterEngineSpeed=45;
  masterEngineConforming;
}
void loop(){
//  calib=true;
//  while (calib==false)
//    {
//      
//      digitalWrite(24, HIGH);
//      digitalWrite(25, HIGH);
//      Serial.println("La calibration doit être effectuée");
//      delay(200);
//      digitalWrite(25, LOW);
//      bno.getCalibration(&syst, &gyro, &accel, &mag);
//      Serial.print("Sys:");
//      Serial.print(syst, DEC);
//      Serial.print(" G:");
//      Serial.print(gyro, DEC);
//      Serial.print(" A:");
//      Serial.print(accel, DEC);
//      Serial.print(" M:");
//      Serial.println(mag, DEC);
//      delay(500);
//      while (gyro != 3)
//        {
//          bno.getCalibration(&syst, &gyro, &accel, &mag);
//          Serial.print("Calibration du gyroscope:  ");
//          Serial.println(gyro, DEC);
//          delay(400);
//        }
//      Serial.println("la calibration du gyroscope est OKAY");
//      digitalWrite(25, HIGH);
//      delay(500);
//      digitalWrite(25, LOW);
//      while (accel != 3)
//        { 
//          bno.getCalibration(&syst, &gyro, &accel, &mag);
//          Serial.print("Calibration de l'accéléromètre:  ");
//          Serial.println(accel, DEC);
//          delay(400);
//        }
//      Serial.println("La calibration de l'accéléromètre est OKAY");
//      digitalWrite(25, HIGH);
//      delay(200);
//      digitalWrite(25, LOW);
//      delay(200);
//      digitalWrite(25, HIGH);
//      delay(200);
//      digitalWrite(25, LOW);
//      while (mag != 3)
//        { 
//          bno.getCalibration(&syst, &gyro, &accel, &mag);
//          Serial.print("Calibration du magnétomètre:  ");
//          Serial.println(mag, DEC);
//          delay(400);
//        }
//      Serial.println("la calibration du magnétomètre est OKAY");
//      digitalWrite(25, HIGH);
//      delay(200);
//      digitalWrite(25, LOW);
//      delay(200);
//      digitalWrite(25, HIGH);
//      delay(200);
//      digitalWrite(25, LOW);
//      delay(200);
//      digitalWrite(25, LOW);
//      calib=true;
//      Serial.println("");
//      Serial.println("CALIBRATION OKAY");
//      Serial.println("");
//      Serial.println("===================================================");    
//    }
      
/* ============== Allumer les leds RGB à la fin de la calibration  ======================== */

      digitalWrite(22, HIGH);
      digitalWrite(24, HIGH);
      // Tant qu'on a pas de réponse du module bluetooth on attend
    while(!false){
      Serial.println("Attente bluetooth");
      if(bluetoothSerial.available()) // Si le module lis quelque chose on casse la boucle
        break;
    }
    Serial.println("go");
    delay(15000);
//    while(masterEngineSpeed<60)
//    {
//      Serial.println("masterEngine++");
//      masterEngineSpeed++;
//      masterEngineConforming;
//      engineSpeed1++;
//      engineSpeed2++;
//      engineSpeed3++;
//      engineSpeed4++;
//      delay(50);
//    }
    if (flightMode==0){                                                 //definition of the variable engine speed
    Serial.println("Flight Mode 0");
    masterEngineSpeed = 45 ;
    if (averageGndProximity==false)
    {
      Serial.println("Phase de decollage");
      ultrasonicTakeoff();
      Serial.println("Fin de décollage");
      Serial.println(gndProximity);
      averageGndProximity=true;
    }
    
    masterGndProximity=gndProximity;
    Serial.println(masterGndProximity);
//    while (abs(gndProximity-masterGndProximity)<3) {
//      delay(50);    
//      Serial.print("gndproximity - masterproximity");  
//      Serial.println(abs(gndProximity-masterGndProximity));
//      ultrasonicTakeoff();
//      Serial.print("actuel - base:  ");
//      Serial.println(abs(gndProximity-masterGndProximity));
//      masterEngineSpeed++;
//      Serial.println (masterEngineSpeed);
//      masterEngineConforming;  
//    }
   Serial.println("Deccollé");
   masterEngineSpeed=masterEngineSpeed-1;
   digitalWrite(25, HIGH);
   flightMode=1;                                                      //setting for takeoff
  }    
  delay(5000);
  if (flightMode==1){                                                  //takeoff
    Serial.println("flmod1");
    delay(500) ;
    digitalWrite(25, LOW);
    Serial.println(masterEngineSpeed);
    engineSpeed1=2+masterEngineSpeed;
    engineSpeed2=2+masterEngineSpeed;
    engineSpeed3=2+masterEngineSpeed;
    engineSpeed4=2+masterEngineSpeed;                               //target altitude must be here !!!! GPS!!!!
    engineConforming;
    Serial.println(engineSpeed1);
    gndProximity=ultrasonic.MeasureInCentimeters();
    delay(50);
    while (abs(gndProximity-masterGndProximity)<100){
      delay(10);
      gndProximity=ultrasonic.MeasureInCentimeters();
      Serial.print("Distance en cm: ");
      Serial.println(gndProximity);
      Serial.print("Différence: ");
      Serial.println(abs(gndProximity-masterGndProximity));
      digitalWrite(25, HIGH);
    }
    Serial.println("1 mètre");
    flightMode=2;
    Serial.println("Stationnaire");
  }
    targetPitch=0;
    while (stab<250)
    {
      Serial.println("Stabilisation");
      stabilisation();
      stab++;
      delay(50);
    }
    while(masterEngineSpeed>45){
      masterEngineSpeed=masterEngineSpeed-1;
      masterEngineConforming;
      delay(200);
    }
    if(!trappeOuverte){
      degoupiller();
      trappeOuverte = true;    
    }
    delay(2000);
    goupiller();

//  if (flightMode==2){
//    Serial.println("flmod2");
//    masterEngineConforming;
//    digitalWrite(25, HIGH);
//    delay(2000);
//    digitalWrite(25, LOW);
//    delay(2000);
//    digitalWrite(25, HIGH);
//    delay(2000);
//    digitalWrite(25, LOW);
//    delay(2000);
//    digitalWrite(25, HIGH);
//    delay(2000);
//    digitalWrite(25, LOW);
//    flightMode=3;
//  }
//  if (flightMode==3){
//    Serial.println("flghtmd3");
//    engineSpeed1=masterEngineSpeed-2;
//    engineSpeed2=masterEngineSpeed-2;
//    engineSpeed3=masterEngineSpeed-2;
//    engineSpeed4=masterEngineSpeed-2;            
//    engineConforming;
//    digitalWrite(25, HIGH);
//    delay(1000);
//    digitalWrite(25, LOW);
//    delay(1000);
//    digitalWrite(25, HIGH);
//    delay(1000);
//    digitalWrite(25, LOW);
//    delay(1000);
//    digitalWrite(25, HIGH);
//    delay(1000);
//    digitalWrite(25, LOW);
//    delay(1000);
//    digitalWrite(25, HIGH);
//    delay(1000);
//    digitalWrite(25, LOW);
//    delay(1000);
//    digitalWrite(25, HIGH);
//    delay(1000);
//    digitalWrite(25, LOW);
//    delay(1000);
//    digitalWrite(25, HIGH);
//    delay(1000);
//    digitalWrite(25, LOW);
//    flightMode=4;
//    masterEngineSpeed=35;            
//    masterEngineConforming;
//    
//  }
}
void attitudeConformation(){
  Serial.println("Altitude Conforming String Activated!");
  //insert gps string here, or ultrasonic, or perhaps earlier in the programm
  if (altitudeChange==false){
    altEngPwr1Mem=engineSpeed1;
    altEngPwr2Mem=engineSpeed2;
    altEngPwr3Mem=engineSpeed3;
    altEngPwr4Mem=engineSpeed4;
  }
  if(abs(targetAltitude-altitude)>10){
    if (targetAltitude>altitude){
      engineSpeed1++;
      engineSpeed2++;
      engineSpeed3++;
      engineSpeed4++;
      altitudeChange=true;
    }
    if (targetAltitude<altitude){
      engineSpeed1=engineSpeed1-1;
      engineSpeed2=engineSpeed2-1;
      engineSpeed3=engineSpeed3-1;
      engineSpeed4=engineSpeed4-1;
      altitudeChange=true;
    }
    delay(1);
  }
  else {
    if (altitudeChange==true){
      engineSpeed1=altEngPwr1Mem;
      engineSpeed2=altEngPwr2Mem;
      engineSpeed3=altEngPwr3Mem;
      engineSpeed4=altEngPwr4Mem;
    }
  }
  stabilisation();
}

void stabilisation() {
  Serial.println("Stabilisation!");
  int stabEngPwr1Mem=engineSpeed1;
  int stabEngPwr2Mem=engineSpeed2;
  int stabEngPwr3Mem=engineSpeed3;
  int stabEngPwr4Mem=engineSpeed4;
   sensors_event_t event;
   bno.getEvent(&event);
   roll=event.orientation.y;
   pitch=(event.orientation.z-(9.3125));
   heading=event.orientation.x;
   Serial.print(pitch);
   Serial.print(",");
   Serial.println(roll);
   if (abs(roll)>2){
    if (roll<(-2)){
      engineSpeed2=engineSpeed2+1;
      engineSpeed3=engineSpeed3+1;
      engineSpeed1=engineSpeed1-1;
      engineSpeed4=engineSpeed4-1;
    }
    if (roll<(-20)){
      engineSpeed2=engineSpeed2+1;
      engineSpeed3=engineSpeed3+1;
      engineSpeed1=engineSpeed1-1;
      engineSpeed4=engineSpeed4-1;
    }
    if (roll<(-30)){
      engineSpeed2=engineSpeed2+1;
      engineSpeed3=engineSpeed3+1;
      engineSpeed1=engineSpeed1-1;
      engineSpeed4=engineSpeed4-1;
      emergency=true;
    }
    if (roll>2){
      engineSpeed1=engineSpeed1+1;
      engineSpeed4=engineSpeed4+1;
      engineSpeed2=engineSpeed2-1;
      engineSpeed3=engineSpeed3-1;
    }
    if (roll>20){
      engineSpeed1=engineSpeed1+1;
      engineSpeed4=engineSpeed4+1;
      engineSpeed2=engineSpeed2-1;
      engineSpeed3=engineSpeed3-1;
    }
    if (roll>30){
      engineSpeed1=engineSpeed1+1;
      engineSpeed4=engineSpeed4+1;
      engineSpeed2=engineSpeed2-1;
      engineSpeed3=engineSpeed3-1;
      emergency=true;
    }
    delay(1);
   }
   if (abs(targetPitch-pitch)>2){
    if ((targetPitch-pitch)<(-2)){
      engineSpeed1=engineSpeed1+1;
      engineSpeed2=engineSpeed2+1;
      engineSpeed3=engineSpeed3-1;
      engineSpeed4=engineSpeed4-1;
    }
    if ((targetPitch-pitch)<(-20)){
      engineSpeed1=engineSpeed1+1;
      engineSpeed2=engineSpeed2+1;
      engineSpeed3=engineSpeed3-1;
      engineSpeed4=engineSpeed4-1;
    }
    if ((targetPitch-pitch)<(-30)){
      engineSpeed1=engineSpeed1+1;
      engineSpeed2=engineSpeed2+1;
      engineSpeed3=engineSpeed3-1;
      engineSpeed4=engineSpeed4-1;
      emergency=true;
    }
    if ((targetPitch-pitch)>2){
      engineSpeed3=engineSpeed3+1;
      engineSpeed4=engineSpeed4+1;
      engineSpeed2=engineSpeed2-1;
      engineSpeed1=engineSpeed1-1;
    }
    if ((targetPitch-pitch)>20){
      engineSpeed3=engineSpeed3+1;
      engineSpeed4=engineSpeed4+1;
      engineSpeed2=engineSpeed2-1;
      engineSpeed1=engineSpeed1-1;
    }
    if ((targetPitch-pitch)>30){
      engineSpeed3=engineSpeed3+1;
      engineSpeed4=engineSpeed4+1;
      engineSpeed2=engineSpeed2-1;
      engineSpeed1=engineSpeed1-1;
      emergency=true;
    }
    delay(1);
   }
   engineSpeed4=engineSpeed4+1;
   engineConforming; 
   engineSpeed1=stabEngPwr1Mem;
   engineSpeed2=stabEngPwr2Mem;
   engineSpeed3=stabEngPwr3Mem;
   engineSpeed4=stabEngPwr4Mem;
}
void ultrasonicTakeoff(){
    long x1,x2,x3,x4,x5;
    Serial.println("tes3");
    x1=ultrasonic.MeasureInCentimeters();
    delay(20);
    x2=ultrasonic.MeasureInCentimeters();
    delay(20);
    x3=ultrasonic.MeasureInCentimeters();
    delay(20);
    x4=ultrasonic.MeasureInCentimeters();
    delay(20);
    x5=ultrasonic.MeasureInCentimeters();
    delay(20);
    gndProximity=(x1+x2+x3+x4+x5)/5;
    masterGndProximity=gndProximity;
    while (abs (gndProximity-masterGndProximity)<2){
       x1=ultrasonic.MeasureInCentimeters();
       Serial.println(x1);
       delay(400);
       if(abs(x1-gndProximity)>10){                          //discarding irrelevant results 1
        Serial.println(abs(x1-gndProximity));
        x1=gndProximity;
       }
       gndProximity=x1;
       masterEngineSpeed++;
       masterEngineConforming;
    }
//    masterEngineSpeed=masterEngineSpeed-1;
//    engineSpeed1=masterEngineSpeed;
//    engineSpeed2=masterEngineSpeed;
//    engineSpeed3=masterEngineSpeed;
//    engineSpeed4=masterEngineSpeed;
//    targetAltitude=100;
//    while (abs(gndProximity-(gndProximity+targetAltitude))>10){
//      Serial.println(abs(gndProximity-(gndProximity+targetAltitude)));
//      attitudeConformation();
//      delay(400);
//    }
    //insert next step!
}

void ultrasonicSustentation(){
   long x1, x2, x3, x4, x5;
   long startTime;
   startTime=millis();
   while ((startTime-millis()<((sustentationTime)*1000))){
    attitudeConformation();
    x1=ultrasonic.MeasureInCentimeters();
    delay(20);
    if(abs(x1-gndProximity)>10){                          //discarding irrelevant results 1
      x1=gndProximity;
    }
    x2=ultrasonic.MeasureInCentimeters();
    delay(20);
    if(abs(x2-gndProximity)>10){                          //discarding irrelevant results 2
      x2=gndProximity;
    }
    x3=ultrasonic.MeasureInCentimeters();
    delay(20);
    if(abs(x3-gndProximity)>10){                          //discarding irrelevant results 3
      x3=gndProximity;
    }
    x4=ultrasonic.MeasureInCentimeters();
    delay(20);
    if(abs(x4-gndProximity)>10){                          //discarding irrelevant results 4
      x4=gndProximity;
    }
    x5=ultrasonic.MeasureInCentimeters();
    delay(20);
    if(abs(x5-gndProximity)>10){                          //discarding irrelevant results 5
      x5=gndProximity;
    }
    gndProximity=(x1+x2+x3+x4+x5)/5;
   }
}

/* Fonctions pour livrer le matériel */
void degoupiller(){
  servoT.write(180);
}

void goupiller(){
  servoT.write(0);
}
