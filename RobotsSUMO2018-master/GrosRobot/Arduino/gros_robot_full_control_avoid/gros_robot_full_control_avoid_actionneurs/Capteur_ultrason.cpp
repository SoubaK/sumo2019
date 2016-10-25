#include"Capteur_ultrason.h"
#include "Arduino.h"
#define VITESSE 340 //vitesse du son 340 m/s
Capteur_ultrason::Capteur_ultrason(int pin_trig,int pin_echo)
{ 
    m_pin_trig = pin_trig;
    m_pin_echo = pin_echo;
}

void Capteur_ultrason::set_capteur()
{
    pinMode(m_pin_trig, OUTPUT);
    pinMode(m_pin_echo, INPUT);
    digitalWrite(m_pin_trig, LOW);  
}

int Capteur_ultrason::get_distance()
{
 // 1. Un état haut de 10 microsecondes est mis sur la broche "Trig"
   digitalWrite(m_pin_trig, HIGH);
   delayMicroseconds(10); //on attend 10 µs
   // 2. On remet à l’état bas la broche Trig
   digitalWrite(m_pin_trig, LOW);

   // 3. On lit la durée d’état haut sur la broche "Echo"
   unsigned long duree = pulseIn(m_pin_echo, HIGH, 30000);

   if(duree == 0)
   {
      // si la durée est supérieure à 30ms, l'onde est perdue
      return 1000;
   }
   else
   {
      // 4. On divise cette durée par deux pour n'avoir qu'un trajet
      duree = duree/2;

      // 5. On calcule la distance avec la formule d=v*t
      float temps = duree/1000000.0; //on met en secondes
      float distance = temps*VITESSE*100; //on multiplie par la vitesse, d=t*v

      return distance;
   }


      
} 
