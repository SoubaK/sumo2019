#ifndef AsservissementMascart_h
#define AsservissementMascart_h

#include "Arduino.h"

class AsservissementMascart
{
  public:
    AsservissementMascart(int dir, int pwm, int brake, int pinA, int pinB);
    void init();
    void run(double theta_increment);

  private:
    static void coder();

    int m_dir;
    int m_pwm;
    int m_brake;
    int m_pinA;
    int m_pinB;
    int m_nbTopsDone = 0, m_encoderPos;
    double umot_precedentes[5];
    double theta_precedents[5];

    double targetSpeed;
    double speed_encoder;

    float m_Kth;
    float m_th0;
    float m_th1;
    float m_th2;
    float m_th3;
    float m_th4;
    float m_th5;

    float m_K1u;
    float m_1u0;
    float m_1u1;
    float m_1u2;
    float m_1u3;
    float m_1u4;
    float m_1u5;

    float m_K2u;
    float m_2u0;
    float m_2u1;
    float m_2u2;
    float m_2u3;
    float m_2u4;
    float m_2u5;

    double umot_current;
    double theta_current;

    float cmd;
    float K;

    float timer_asser = 0.02; // timer_asser est le temps passe entre chaque avance des roues. On les lance a intervalles constants

};

#endif // MotorBlock_h
