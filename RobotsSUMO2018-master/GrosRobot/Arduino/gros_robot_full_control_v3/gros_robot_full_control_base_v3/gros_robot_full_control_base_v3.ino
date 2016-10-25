#include <Arduino.h>
#include "SimpleTimer.h"
#include "MotorBlock.h"
#include "interrupts.h"

#include "serialUtil.h"
#include "command.h"


enum Mode { 
  WAITING, ROT, LIN, AVOID };

//SimpleTimer timerDebug;
SimpleTimer timerAsser;


MotorBlock M_L(12,9,3, 21, 7);
MotorBlock M_R(13,8,11, 2, 4);


boolean finChrono = false;


int rotDir = 1, linDir = 1;
long rotTarget = 0, linTarget = 0;
Mode mode = WAITING;
boolean blocked = false;
float timeBlocked = 0;


char tempBuffer[10];
boolean reading = false;
int i = 0;
boolean cmdAvailable = false;

enum AvoidMode { FRONT, BACK};
AvoidMode avoidMode = FRONT;
float distAtAvoid = 0.0;


void setup() {
  M_L.init();
  M_R.init();

  attachInterrupt(2, coderL, CHANGE);
  attachInterrupt(0, coderR, CHANGE);
  Serial.begin(115200);
  //timerDebug.setInterval(100, serialDebug);
  timerAsser.setInterval(20, asser);
  
  pinMode(53, OUTPUT);
  digitalWrite(53, LOW);

}

void loop() {

  //timerDebug.run();
  timerAsser.run();
  boolean rotDone = false, linDone = false, avoidDone = false;

  readSerial();

  if(cmdAvailable && tempBuffer[0] == 's') {
    finChrono = true;
    M_L.setSpeed(0);
    M_R.setSpeed(0);
    cmdAvailable = false;
  }

  if(!finChrono){

    switch(mode) {

    case WAITING :
      if(cmdAvailable) {
        
        if(tempBuffer[0] == 'r'){
          Serial.print('a');
          cmdAvailable = false;
        }else{
          boolean ok = getTarget();

          if(ok) {
            mode = ROT;
            cmdAvailable = false; 
          }
        }      
      }
      break;


    case ROT :

      cmdAvailable = false; // On ignore toutes les commandes en cours

      rotDone = rotCommand();

      if(rotDone) {
        M_L.encoderPos = 0;
        M_R.encoderPos = 0;
        mode = LIN;
      }
      break;


    case LIN :

      if(cmdAvailable) {

        

        if(tempBuffer[0] == 'x' && linDir == 1){
          cmdAvailable = false;
          digitalWrite(53, HIGH);
          mode = AVOID;
          distAtAvoid = abs( (M_R.encoderPos - M_L.encoderPos)) / 2.0;
          avoidMode = FRONT;
          M_L.setSpeed(0);
          M_R.setSpeed(0);
          delay(500);
          break;
        }else if(tempBuffer[0] == 'y' && linDir == -1){
          digitalWrite(53, HIGH);
          cmdAvailable = false;
          mode = AVOID;
          distAtAvoid = abs( (M_R.encoderPos - M_L.encoderPos)) / 2.0;
          avoidMode = BACK;
          M_L.setSpeed(0);
          M_R.setSpeed(0);
          delay(500);
          break;
        }

      }
      linDone = linCommand();

      if(linDone) {
        Serial.println("k");
        M_L.encoderPos = 0;
        M_R.encoderPos = 0;
        mode = WAITING;
      }
      break;



    case AVOID :
      if(avoidMode == FRONT){
          
        avoidDone = avoidCommand();

        if(avoidDone || (cmdAvailable && tempBuffer[0] == 'o')) {
          M_L.encoderPos = 0;
          M_R.encoderPos = 0;
          mode = LIN;
          if(cmdAvailable && tempBuffer[0] == 'o')
            cmdAvailable = false;
        }
      
      }else if(avoidMode == BACK){
          
        avoidDone = avoidCommand();

        if(avoidDone || (cmdAvailable && tempBuffer[0] == 'p')) {
          M_L.encoderPos = 0;
          M_R.encoderPos = 0;
          mode = LIN;
          if(cmdAvailable && tempBuffer[0] == 'o')
            cmdAvailable = false;
        }
        
      }
      break;

    default:
      break;
    }
  }else{
    M_L.setSpeed(0);
    M_R.setSpeed(0);
  }
}


void asser(){
  
  M_L.run();
  M_R.run();

}


void serialDebug()
{
  //Serial.println(String((int)(1000*M_L.currSpeed)) + "/" + String((int)(1000*M_L.targetSpeed)) + " " + String((int)(1000*M_R.currSpeed)) + "/" + String((int)(1000*M_R.targetSpeed)));
  //Serial.println(String((int)M_L.cmdDEBUG));
  //Serial.println(blocked);
}








