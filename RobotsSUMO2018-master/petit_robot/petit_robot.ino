#include "Capteur_ultrason.h"
#include <Servo.h>



//Declaration des pins de commande
int dirPinDroite = 14;
int stepperPinDroite = 15;
int dirPinGauche = 19;
int stepperPinGauche = 20;
int sleepPinGauche = 16;
int sleepPinDroite = 21;
int selCotePin = 18;
int startPin = 17;

int distSeuil = 10; //distance min avant l'aret de robot en cm

//variables pour le declanchement du parasol
bool parasolFerme;
double tempsZero;

//Declaration des capteur ultrason
Capteur_ultrason captGauche(2, 3);
Capteur_ultrason captDroite (4, 5);
Capteur_ultrason captArriere (6, 7);

//Duree des steps moteur
int dureeStep = 6000;

//Declaration du servo moteur du parasol
Servo servoParasol;

void setup() {

  //Initialisation des pins de commande du moteur
  pinMode(dirPinGauche, OUTPUT);
  pinMode(stepperPinGauche, OUTPUT);
  pinMode(stepperPinDroite, OUTPUT);
  pinMode(dirPinDroite, OUTPUT);
  pinMode(sleepPinGauche, OUTPUT);
  pinMode(sleepPinDroite, OUTPUT);

  //Initialisation des pins de selection du cote et de demarrage
  pinMode(selCotePin, INPUT);
  pinMode(startPin, INPUT);

  //Initialisation des capteurs ultrason
  captGauche.set_capteur();
  captDroite.set_capteur();
  captArriere.set_capteur();

  //Attente du signal de demarrage
  bool start = digitalRead (startPin);
  digitalWrite (sleepPinGauche, LOW);
  digitalWrite (sleepPinDroite, LOW);

  while (not start) {
    start = digitalRead (startPin);
  }

  //Initialisation des variables commandant le parasol
  tempsZero = millis();
  parasolFerme = true;

  //Mise en route des moteurs
  digitalWrite (sleepPinGauche, HIGH);
  digitalWrite (sleepPinDroite, HIGH);


  //Lancement du deplacemnt pour aller fermer les portes
  int cote = digitalRead (selCotePin);
  if (cote == 0) { //cote gauche
    coteGauche();
  }

  else { //cote droit
    coteDroit();
  }

  //Une fois que le robot a ferme les portes on attend la fin des 90 secondes

  //On coupe les moteurs
  digitalWrite (sleepPinGauche, LOW);
  digitalWrite (sleepPinDroite, LOW);



  while (millis() - tempsZero <  92000) {
    digitalWrite (sleepPinGauche, LOW);
    digitalWrite (sleepPinDroite, LOW);
  }

  //Declaration de la pin du servo du parasol
  servoParasol.attach(8);
  ouvertureDuParasol();
}



void loop () {

}


void ligneDroite(int nbrSteps, bool dir, bool capt) { //dir=true => on avance
  digitalWrite(dirPinDroite, dir);
  digitalWrite(dirPinGauche, not dir);
  delay(50);
  int stepCapt = 0;
  double decomptCapteur = millis();
  for (int i = 0; i < nbrSteps; i++) {
    digitalWrite(stepperPinDroite, HIGH);
    digitalWrite(stepperPinGauche, HIGH);
    delayMicroseconds(dureeStep);
    digitalWrite(stepperPinDroite, LOW);
    digitalWrite(stepperPinGauche, LOW);
    delayMicroseconds(dureeStep);

    if (capt) {
      if (millis() - decomptCapteur > 300) {
        pingCapteurs(dir);
        decomptCapteur = millis();
      }
      digitalWrite (sleepPinGauche, HIGH);
      digitalWrite (sleepPinDroite, HIGH);
    }
  }
}

void quartDeTour(bool sensTrigo) {
  digitalWrite(dirPinDroite, sensTrigo);
  digitalWrite(dirPinGauche, sensTrigo);
  delay(50);
  for (int i = 0; i < 105; i++) {
    digitalWrite(stepperPinDroite, HIGH);
    digitalWrite(stepperPinGauche, HIGH);
    delayMicroseconds(dureeStep);
    digitalWrite(stepperPinDroite, LOW);
    digitalWrite(stepperPinGauche, LOW);
    delayMicroseconds(dureeStep);
  }
}


void fermerPorte() {

}

void coteGauche() {
  ligneDroite(96, true, true);
  quartDeTour(true);
  ligneDroite(356, true, true);
  ligneDroite (300, true, false);
  ligneDroite(150, false, true);
  quartDeTour(false);
  ligneDroite(278, true, true);
  quartDeTour(true);
  ligneDroite(60, true, true);
  ligneDroite (300, true, false);
  ligneDroite(90, false, true);
}

void coteDroit() {
  ligneDroite(96, true, true);
  quartDeTour(false);
  ligneDroite(356, true, true);
  ligneDroite (300, true, false);
  ligneDroite(150, false, true);
  quartDeTour(true);
  ligneDroite(278, true, true);
  quartDeTour(false);
  ligneDroite(60, true, true);
  ligneDroite (300, true, false);
  ligneDroite(90, false, true);
}

void ouvertureDuParasol() {
  servoParasol.writeMicroseconds(800);
  delay (2000);
  servoParasol.writeMicroseconds(2400);
  delay (2000);

}

void pingCapteurs(bool avance) {
  if (avance) {
    while (((captGauche.get_distance() < distSeuil) || (captDroite.get_distance() < distSeuil))) {
      if (millis() - tempsZero > 91000) {
        servoParasol.attach(8);
        ouvertureDuParasol();
        while (1) {
          digitalWrite (sleepPinGauche, LOW);
          digitalWrite (sleepPinDroite, LOW);
        }
      }
    }
  }
  else {
    while (captArriere.get_distance() < distSeuil) {
      if (millis() - tempsZero > 91000) {
        servoParasol.attach(8);
        ouvertureDuParasol();
        while (1) {
          digitalWrite (sleepPinGauche, LOW);
          digitalWrite (sleepPinDroite, LOW);
        }
      }
    }
  }
}

