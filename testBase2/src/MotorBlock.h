#ifndef MotorBlock_h
#define MotorBlock_h

#include "Arduino.h"

class MotorBlock
{
  public:
    MotorBlock(int dir, int pwm, int brake, int pinA, int pinB);
    void init();
    void run();

  private:
    static void coder();

    int m_dir;
    int m_pwm;
    int m_brake;
    int m_pinA;
    int m_pinB;
    int m_nbTopsDone = 0, m_encoderPos;

    double targetSpeed;
    double speed_encoder;

    float cmd;
    float K;

    float timer_asser = 0.02; // timer_asser est le temps pass� entre chaque avance des roues. On les lance a intervalles constants

};

#endif // MotorBlock_h
