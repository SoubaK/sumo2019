#include <Arduino.h>
#include "MotorBlock.h"

MotorBlock::MotorBlock(int dir,int brake,int pwm, int encoderA, int encoderB) : D(dir), B(brake), P(pwm), pinA(encoderA), pinB(encoderB), encoderPos(0), /*currTime(1), prevTime(0),*/ currSpeed(0), currDirection(1)
{}

void MotorBlock::init()
{
  pinMode(D, OUTPUT); //Init Direction
  pinMode(B, OUTPUT); //Init Frein 
  pinMode(P, OUTPUT); //Init PWM 
}

void MotorBlock::brake()
{
  digitalWrite(B, HIGH);
  analogWrite(P, 1);
}

void MotorBlock::unbrake()
{
  digitalWrite(B, LOW);
}

void MotorBlock::run(double targetSpeed)
{
  dbg_targetSpeed = targetSpeed;
  currSpeed = nbTopsDone * 0.3330 / (50);
  nbTopsDone = 0;
  float cmd = (targetSpeed - currSpeed) * 500;
  
  // Offset
  cmd += ((cmd > 0) - (cmd < 0)) * OFFSET;
  
  // Saturation
  cmd = constrain(cmd, -255, 255);
  
  cmdDEBUG = cmd;
  
  
  digitalWrite(D, cmd > 0 ? LOW : HIGH);

  analogWrite(P, abs(cmd));
}
