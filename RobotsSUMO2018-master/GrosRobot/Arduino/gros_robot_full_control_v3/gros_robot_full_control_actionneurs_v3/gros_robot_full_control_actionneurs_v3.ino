#include <Servo.h>
#include "SimpleTimer.h"
#include "Capteur_ultrason.h"
#include "poissons.h"

/* 0 : ferme
 1 : triangle
 2 : ouvert
 */

Capteur_ultrason ultrasonL(10,11);
Capteur_ultrason ultrasonR(12,13);
Capteur_ultrason ultrasonB(8,9);
SimpleTimer timerUltrason;
float lastL = 0.0;
float lastR = 0.0;
float lastB = 0.0;

boolean chronoFini = false, poissonsOff = false;

Servo left;
Servo right;

char mode = 'f';

boolean obstacle = false, obstacleAR = false, obstacleAV = false;
boolean waitingStart = true;

char side = 0;


// Poissons
Servo servoSortie;
Servo servoBase;
boolean poissonsDeploye = false;



void setup() {

  pinMode(4, INPUT);

  pinMode(52, INPUT);
  pinMode(50, INPUT);
  pinMode(48, INPUT);

  Serial.begin(115200);
  left.write(177);
  left.attach(37);
  delay(400);
  right.write(6);
  right.attach(36);
  delay(400);
  
  // Poissons
  initPoissons();
  

  ultrasonL.set_capteur();
  ultrasonR.set_capteur();
  ultrasonB.set_capteur();
  timerUltrason.setInterval(100, pingUltrason);
}

void loop() {

  timerUltrason.run();

  if(waitingStart && digitalRead(4) == LOW){
    waitingStart = false;
    Serial.println('m');
  }

  char c = -1;

  if(Serial.available() > 0) {

    c = Serial.read();
  }

  switch(c) {

  case 's' :
    chronoFini = true;
    break;
    
  case 'd' :
    poissonsOff = true;
  break;

  case 'r' : // Lecture du selecteur
    if(digitalRead(53) == HIGH)
      side = 'g';
    else
      side = 'd';
    Serial.println(String(digitalRead(48) * 4 + digitalRead(50) * 2 + digitalRead(52)) + side);
    break;
    
  case 'p' :
    if(!poissonsDeploye && !poissonsOff){
      deployerPoissons();
      Serial.println('k');
      poissonsDeploye = true;
    }
    break;
    
  case 'q':
     if(poissonsDeploye && !poissonsOff){
      rangerPoissons();
      Serial.println('k');
      poissonsDeploye = false;
    }
    break;

  case 'f' :
    if(!chronoFini){
      if(mode == 't'){
        right.write(70);
        delay(500);
        left.write(177);
        delay(500);
        right.write(6);
      }
      else{
        left.write(177);
        delay(500);
        right.write(6);
      }
      mode = 'f';
    }
    break;

  case 't' :
    if(!chronoFini){
      if(mode == 'f'){
        right.write(70);
        delay(500);
        left.write(125);
        delay(500);
        right.write(55);
      }
      else if(mode == 'o'){
        left.write(125);
        delay(500);
        right.write(55);
      }
      mode = 't';
    }
    break;

  case 'o':
    if(!chronoFini){
      right.write(100);
      delay(500);
      left.write(80);
      mode = 'o';
    }
    break;
   

  default:
    break;

  }

}
void pingUltrason() {
  float dL=ultrasonL.get_distance();
  delay(1);
  float dR=ultrasonR.get_distance();
  delay(1);
  float dB=ultrasonB.get_distance();
  
  float meanL = (lastL + dL) / 2.0;
  float meanR = (lastR + dR) / 2.0;
  float meanB = (lastB + dB) / 2.0;
  
  lastL = dL;
  lastR = dR;
  lastB = dB;
  
  //Serial.println(String((long)(meanL))+" "+String((long)(meanR))+" "+String((long)(meanB)));
  
  
  if( ((mode == 'o') && (meanL < 20 || meanR < 20)) ||  ((mode == 'f') && (meanL < 10 || meanR < 10)) ){
    if(!obstacleAV){
      Serial.print('x');
      obstacleAV = true;
    }
  }
  else{
    if(obstacleAV){
      Serial.print('o');
      obstacleAV = false;
    }
  }
  
  if(meanB < 15) {
    if(!obstacleAR){
      Serial.print('y');
      obstacleAR = true;
    }
  }
  else{
    if(obstacleAR){
      Serial.print('p');
      obstacleAR = false;
    }
  }
}

