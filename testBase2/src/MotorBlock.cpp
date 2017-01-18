#include "MotorBlock.h"

MotorBlock::MotorBlock(int dir, int pwm, int brake, int pinA, int pinB) {
  K = 500;
  targetSpeed = 0.3;
  m_dir = dir;
  m_pwm = pwm;
  m_brake = brake;
  m_pinA = pinA;
  m_pinB = pinB;
}

void MotorBlock::init() {
  pinMode(m_dir, OUTPUT);
  pinMode(m_pwm, OUTPUT);
  pinMode(m_brake, OUTPUT);
  attachInterrupt(m_pinA, coder, CHANGE);
}

void MotorBlock::run() {
  speed_encoder = 2 * 3.1415926535 * 29 * m_nbTopsDone / timer_asser;
  m_nbTopsDone = 0;
  //timer_asser = 0;


  cmd = (targetSpeed - speed_encoder) * K;

  /// Saturation
  cmd = constrain(cmd, -255, 255);

  ///digitalWrite(dir, cmd > 0 ? LOW:HIGH);
  analogWrite(m_pwm, cmd);
}

static void MotorBlock::coder() {
  if (digitalRead(this.m_pinA) == digitalRead(this.m_pinB)) {
    this.m_encoderPos--;
    m_nbTopsDone--;

  }
  else {
    m_encoderPos++;
    m_nbTopsDone++;
  }
}
