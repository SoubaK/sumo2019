#ifndef POISSONS_H
#define POISSONS_H


#define PIN_POISSONS_CABLE_1 27
#define PIN_POISSONS_CABLE_2 29
#define PIN_POISSONS_CABLE_PWM 3
#define PIN_POISSONS_AIMANTS_1 23
#define PIN_POISSONS_AIMANTS_2 25
#define PIN_POISSONS_AIMANTS_PWM 2
#define PIN_POISSONS_SORTIE 38
#define PIN_POISSONS_BASE 39

void commandeServo(Servo servo, int angleDebut, int angleFin, int delai);
void moteurAimants(int sens, int delai, int pwm);
void moteurCable(int sens, int delai, int pwm);
void initPoissons();
void deployerPoissons();
void rangerPoissons();

#endif
