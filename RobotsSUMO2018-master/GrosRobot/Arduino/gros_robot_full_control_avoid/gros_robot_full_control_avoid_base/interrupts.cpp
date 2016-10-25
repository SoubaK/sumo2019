#include <Arduino.h>
//#include "digitalWriteFast.h"
#include "MotorBlock.h"
#include "interrupts.h"

extern MotorBlock M_L;
extern MotorBlock M_R;

void coderL()
{
  if (digitalRead(M_L.pinA) == digitalRead(M_L.pinB)) {
    M_L.encoderPos--;
    M_L.currDirection = -1;
  } else {
    M_L.encoderPos++;
    M_L.currDirection = 1;
  }
  
  M_L.prevTime = M_L.currTime;
  M_L.currTime = millis();
}

void coderR()
{
  if (digitalRead(M_R.pinA) == digitalRead(M_R.pinB)) {
    M_R.encoderPos++;
    M_R.currDirection = 1;
  } else {
    M_R.encoderPos--;
    M_R.currDirection = -1;
  }
  
  M_R.prevTime = M_R.currTime;
  M_R.currTime = millis();
}
