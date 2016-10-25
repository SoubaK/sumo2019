#include <Arduino.h>
#include "MotorBlock.h"
#include "interrupts.h"

extern MotorBlock M_L;
extern MotorBlock M_R;

void coderL()
{
  if (digitalRead(M_L.pinA) == digitalRead(M_L.pinB)) {
    M_L.encoderPos--;
    M_L.nbTopsDone--;
    M_L.currDirection = -1;
  } else {
    M_L.encoderPos++;
    M_L.nbTopsDone++;
    M_L.currDirection = 1;
  }
}

void coderR()
{
  if (digitalRead(M_R.pinA) == digitalRead(M_R.pinB)) {
    M_R.encoderPos++;
    M_R.nbTopsDone++;
    M_R.currDirection = 1;
  } else {
    M_R.encoderPos--;
    M_R.nbTopsDone--;
    M_R.currDirection = -1;
  }
}
