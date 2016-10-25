#include <Servo.h>
#include "SimpleTimer.h"
#include "Capteur_ultrason.h"

/* 0 : ferme
 1 : triangle
 2 : ouvert
 */

Capteur_ultrason ultrasonL(10,11);
Capteur_ultrason ultrasonR(12,13);
SimpleTimer timerUltrason;

boolean chronoFini = false;

Servo left;
Servo right;

char mode = 'f';

boolean obstacle = false;
boolean waitingStart = true;

void setup() {

  pinMode(4, INPUT);

  pinMode(52, INPUT);
  pinMode(50, INPUT);
  pinMode(48, INPUT);

  Serial.begin(115200);
  left.write(177);
  left.attach(2);
  delay(400);
  right.write(6);
  right.attach(3);
  delay(400);

  ultrasonL.set_capteur();
  ultrasonR.set_capteur();
  timerUltrason.setInterval(100, pingUltrason);
}

void loop() {

  timerUltrason.run();

  if(waitingStart && digitalRead(4) == LOW){
    waitingStart = false;
    Serial.println('g');
  }

  char c = -1;

  if(Serial.available() > 0) {

    c = Serial.read();
  }

  switch(c) {

  case 's' :
    chronoFini = true;
    break;

  case 'r' : // Lecture du selecteur
    Serial.println(digitalRead(48) * 4 + digitalRead(50) * 2 + digitalRead(52));
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
  if((ultrasonL.get_distance() < 10 || ultrasonR.get_distance() < 10)) {
    if(!obstacle){
      Serial.print('x');
      obstacle = true;
    }
  }
  else{
    if(obstacle)
      Serial.print('o');
    obstacle = false;
  }
}

