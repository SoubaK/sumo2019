#include <Arduino.h>
#include "SimpleTimer.h"
#include "MotorBlock.h"
#include "interrupts.h"

#include "serialUtil.h"
#include "command.h"


enum Mode { 
  WAITING, ROT, LIN, AVOID };

//SimpleTimer timerDebug;


MotorBlock M_L(12,9,3, 21, 7);
MotorBlock M_R(13,8,11, 2, 4);


boolean finChrono = false;


int rotDir = 1, linDir = 1;
long rotTarget = 0, linTarget = 0;
Mode mode = WAITING;


char tempBuffer[10];
boolean reading = false;
int i = 0;
boolean cmdAvailable = false;


void setup() {
  M_L.init();
  M_R.init();

  attachInterrupt(2, coderL, CHANGE);
  attachInterrupt(0, coderR, CHANGE);
  Serial.begin(115200);
  //timerDebug.setInterval(200, serialDebug);

}

void loop() {

  //timerDebug.run();
  boolean rotDone = false, linDone = false, avoidDone = false;

  readSerial();

  if(cmdAvailable && tempBuffer[0] == 's') {
    finChrono = true;
    M_L.brake();
    M_R.brake();
    cmdAvailable = false;
  }

  if(!finChrono){

    switch(mode) {

    case WAITING :
      if(cmdAvailable) {

        boolean ok = getTarget();

        if(ok) {
          mode = ROT;
          M_L.unbrake();
          M_R.unbrake();
        }
        cmdAvailable = false;    
      }
      break;


    case ROT :

      cmdAvailable = false;

      rotDone = rotCommand();

      if(rotDone) {
        M_L.encoderPos = 0;
        M_R.encoderPos = 0;
        mode = LIN;
      }
      break;


    case LIN :

      if(cmdAvailable) {

        cmdAvailable = false;

        if(tempBuffer[0] == 'x'){
          mode = AVOID;
          M_L.brake();
          M_R.brake();
          delay(500);
          M_L.unbrake();
          M_R.unbrake();
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
      cmdAvailable = false;
      avoidDone = avoidCommand();

      if(avoidDone) {
        M_L.encoderPos = 0;
        M_R.encoderPos = 0;
        mode = LIN;
      }

      break;

    default:
      break;
    }
  }
}





void serialDebug()
{
  //Serial.println(String(M_L.encoderPos) + " " + String(M_R.encoderPos));
  Serial.println(String((int)M_L.cmdDEBUG));
}








