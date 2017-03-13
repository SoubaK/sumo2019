
#include "AsservissementMascart.h"
#define K_incre 1
#define R 1
#define J 1
#define L 1
#define Ke 1
#define Kc 1
#define Ti1 1
#define Ti2 1
#define Tau_e L/R
#define Te 1
#define Tau_m R*J/(Ke*Kc)
#define K1 1
#define K2 1




AsservissementMascart::MotorBlock(int dir, int pwm, int brake, int pinA, int pinB) {
  targetSpeed = 0.3;
  m_dir = dir;
  m_pwm = pwm;
  m_brake = brake;
  m_pinA = pinA;
  m_pinB = pinB;

  m_Kth = 8*K_incre*Ke*Ti1*Ti2;
  m_th0 = Te*Te + 2*Te*(Tau_e * Tau_m) + 4*Tau_e*Tau_m;
  m_th1 = (-Te*Te - 4*Tau_e*Tau_m - 6*Te*(Tau_e+Tau_m));
  m_th2 = (-2*Te*Te - 8*Tau_e*Tau_m + 8*Te*(Tau_e + Tau_m));
  m_th3 = (2*Te*Te + 8*Tau_e*Tau_m - 8*Te*(Tau_e+Tau_m));
  m_th4 = Te*Te + 4*Tau_e*Tau_m + 6*Te*(Tau_e*Tau_m);
  m_th5 = -Te*Te - 4*Tau_e*Tau_m - 2*Te*(Tau_e+Tau_m);

  m_K1u = Ke*Ti1*Ti2;
  m_1u0 = Te*Te + 2*Te*(Tau_e+Tau_m) + 4*Tau_e*Tau_m;
  m_1u1 = -Te*Te - 20*Tau_e*Tau_m - 6*Te*(Tau_e+Tau_m);
  m_1u2 = -2*Te*Te + 40 * Tau_e*Tau_m + 4*Te*(Tau_e+Tau_m);
  m_1u3 = 2*Te*Te - 40*Tau_e*Tau_m + 4*Te*(Tau_e+Tau_m);
  m_1u4 = Te*Te - 6*Te*(Tau_e+Tau_m) + 20*Tau_e*Tau_m;
  m_1u5 = -Te*Te + 2*Te*(Tau_e+Tau_m) - 4*Tau_e*Tau_m;

  m_K2u = K1*K2*K_incre*Te*Te*Te;
  m_2u0 = Te*Te + 2*Te(Ti1+Ti2) + 4*Ti1*Ti2;
  m_2u1 = 5*Te*Te + 4*Ti1*Ti2 + 6*Te*(Ti1+Ti2);
  m_2u2 = 10*Te*Te + 8*Te*(Ti1+Ti2) - 8*Ti1*Ti2;
  m_2u3 = 10* Te*Te - 8*Ti1*Ti2 + 8*Te*(Ti1+Ti2);
  m_2u4 = 4*Te*Te + 8*Te*(Ti1+Ti2) + 16*Ti1*Ti2;
  m_2u5 = Te*Te + 2*Te*(Ti1+Ti2) + 4*Ti1*Ti2;

}

void MotorBlock::init() {
  pinMode(m_dir, OUTPUT);
  pinMode(m_pwm, OUTPUT);
  pinMode(m_brake, OUTPUT);
  attachInterrupt(m_pinA, coder, CHANGE);
  umot_precedentes = [0,0,0,0,0];
  theta_precedents = [0,0,0,0,0];
}

void MotorBlock::run(double theta_increment) {
  //speed_encoder = 2 * 3.1415926535 * 29 * m_nbTopsDone / timer_asser;
  //m_nbTopsDone = 0;
  //timer_asser = 0;

    theta_current = theta_increment + theta_precedents[0];

  //cmd = (targetSpeed - speed_encoder) * K;
    umot_current = 1/(m_K1u*m_1u0+m_K2u*m_1u0)*(
                                m_Kth* (m_th0* theta_current + m_th1*theta_precedents[0] + m_th2*theta_precedents[1]
                                        + m_th3*theta_precedents[2] + m_th4*theta_precedents[3]+ m_th5 * theta_precedents[4])
                              - (m_K1u*(m_1u1*umot_precedentes[0] + m_1u2*umot_precedentes[1] + m_1u3*umot_precedentes[2]
                                        + m_1u4*umot_precedentes[3] + m_1u5*umot_precedentes[4])
                                 + m_K2u*(m_2u1*umot_precedentes[0] + m_2u2*umot_precedentes[1] + m_2u3*umot_precedentes[2]
                                        + m_2u4*umot_precedentes[3] + m_2u5*umot_precedentes[4])
                                 )
                              );

  /// Saturation
  cmd = constrain(umot_current, -255, 255);

    // on update les buffers
    for(int i=0;i<4;i++){
        umot_precedentes[4-i] = umot_precedentes[4-i-1];
        theta_precedentes[4-i] = theta_precedents[4-i-1];
    }
    theta_precedentes[0] = theta_current;
    umot_precedentes[0] = umot_current;

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
