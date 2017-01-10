#include "MotorBlock.h"


MotorBlock::MotorBlock(int dir, int pwm, int brake, int pinA, int pinB) {
  float K = 500;
  double targetSpeed = 0.3;
}

void MotorBlock::init() {
  pinMode(dir, OUTPUT);
  pinMode(pwm, OUTPUT);
  pinMode(brake, OUTPUT);
}

void MotorBlock::run() {
  speed_encoder = 2 * 3.1415926535 * 29 * nbTopsDone / timer_asser;
  nbTopsDone = 0;
  //timer_asser = 0;


  cmd = (targetSpeed - speed_encoder) * K;

  /// Saturation
  cmd = constrain(cmd, -255, 255);

  ///digitalWrite(dir, cmd > 0 ? LOW:HIGH);
  analogWrite(pwm, cmd);
}

int MotorBlock::getPinA(){
  return (pinA);  
}

void coder() {
  if digitalRead(M_R.getPinA() == M_R.getPinB()) {
    encoderPos--;
    nbTopsDone--;

  }
  else {
    encoderPos++;
    nbTopsDone++;
  }
}

int MotorBlock::getPinB() {
  return (pinB);
}

