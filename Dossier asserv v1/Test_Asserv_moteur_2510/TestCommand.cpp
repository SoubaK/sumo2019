#include "TestMotorBlock.h"
#include "Testcommand.h"

extern MotorBlock M_L;
extern MotorBlock M_R;
extern int asserMode;

extern int rotDir;
extern long rotTarget;

extern int linDir;
extern long linTarget;

extern float distAtAvoid;

float lastTimeKv = 0.0;

extern boolean blocked;
extern float timeBlocked;


boolean rotCommand() {

  M_L.setK(200);
  M_R.setK(200);

    /// distance parcourue depuis lastTime Kv
  float dst = abs( (M_L.encoderPos + M_R.encoderPos)) / 2.0;
  boolean fin = false;

    /// Si la cible est encore loin...  ----------------> une valeur qui sort de nulle part ?
  if(30 < abs(rotTarget - dst)) {

    /// erreur de parcours  ?: distance lineaire parcourue
    float d_rot = M_L.encoderPos - M_R.encoderPos;
    float currTime = millis();

    /// si on a parcouru plus d'1/5 de la distance cible...
    if(dst >= rotTarget * (1.0/5.0)) {

        /// si on ne va pas trop vite, que ce ne fait pas trop longtemps et qu'on est en dessous de la vitesse cible...
      if(abs(M_L.currSpeed) < 0.0005 && abs(M_R.currSpeed) < 0.0005 && (currTime - lastTimeKv) > 100 && abs(M_L.currSpeed) < abs(M_L.targetSpeed) && abs(M_R.currSpeed) < abs(M_R.targetSpeed)){

        /// on change la valeur d'offset
        M_L.addToKv(0.1);       ///-------> des valeurs qui sortent de nulle part
        M_R.addToKv(0.1);
        /// on reinitialise le temps
        lastTimeKv = currTime;

      }
        /// Commande en trapèze FTW (plateau + descente)
      float vit = max(rotTarget - dst, 0.0) * (5.0 / 4.0) * 0.22 / rotTarget + 0.05;  /// ----------->des valeurs qui sortent de nulle part.....
      M_L.setSpeed(vit * rotDir - d_rot/2500.0);  /// ----------->des valeurs qui sortent de nulle part.....
      M_R.setSpeed(vit * rotDir + d_rot/2500.0);  /// ----------->des valeurs qui sortent de nulle part.....

    }
    else {      /// si on est trop loin de la cible, on a une marche
      M_L.setSpeed(0.27 * rotDir - d_rot/2500.0); /// ----------->des valeurs qui sortent de nulle part.....
      M_R.setSpeed(0.27 * rotDir + d_rot/2500.0); /// ----------->des valeurs qui sortent de nulle part.....
    }

  }
  else {        /// si on est trop pres de la cible, on s'arrete
    fin = true;
  }

  /// Si on ne va pas assez vite...
  if(abs(M_L.currSpeed) < 0.0005 && abs(M_R.currSpeed) < 0.0005){
    if(!blocked){                       /// si on n'etait pas bloque, on se bloque
      timeBlocked = millis();
      blocked = true;
    }
  }else{
   blocked = false;                     /// sinon, on n'est plus bloques.----> verifier dans le code full_control comment est utilisee la variable
  }

  /// si on est bloques et que ca fait trop longtemps, on s'arrete.
  if(blocked && millis() - timeBlocked > 1000){
    fin = true;
  }

    /// Si on s'arrete, on reiniitialise les vitesses et offsets, on est debloques.
  if(fin){
    M_L.setKv(1);
    M_R.setKv(1);
    M_L.setSpeed(0);
    M_R.setSpeed(0);
    blocked = false;
    return true;
  }else{
    return false;
  }

}


boolean linCommand() {

  M_L.setK(200);
  M_R.setK(200);

  /// moyenne des distances parcourues par les 2 roues --> distance parcourue
  float dst = abs( (M_R.encoderPos - M_L.encoderPos)) / 2.0;
  boolean fin = false;

  /// si on est suffisamment loin de la cible...
  if(20 < abs(linTarget - dst)) {

    /// erreur de parcours ? : distance de rotation parcourue
    float d_lin = M_R.encoderPos + M_L.encoderPos;
    float currTime = millis();

    /// si on a parcouru plus de 4/5 de la distance...
    if(dst >= linTarget * (4.0/5.0)) {

        /// si on est trop lents, en-dessous de la vitesse cible et que ca fait longtemps depuis lastTimeKv
       if(abs(M_L.currSpeed) < 0.0005 && abs(M_R.currSpeed) < 0.0005 && (currTime - lastTimeKv) > 100 && abs(M_L.currSpeed) < abs(M_L.targetSpeed) && abs(M_R.currSpeed) < abs(M_R.targetSpeed)){
        ///on modifie l'offset et on reinitialise le temps      ------------> des valeurs qui sortent de nulle part
        M_L.addToKv(0.12);
        M_R.addToKv(0.12);
        lastTimeKv = currTime;
      }

        /// Commande en trapèze FTW (plateau puis descente)
      float vit = max(linTarget - dst, 0.0) * (5.0 / 1.0) * 0.36 / linTarget + 0.1; /// ---------> des valeurs qui sortent de nulle part

      float diffK = 250;   ///-----------> des valeurs qui sortent de nulle part

        /// si on est super pres de la cible...
      if(dst >= linTarget * (7.0/8.0))
        diffK = 1000;       ///----------> des valeurs qui sortent de nulle part
      else
        diffK = 250;

        /// faire attention aux signes !!!!!
      M_L.setSpeed(-vit * linDir - d_lin/diffK);
      M_R.setSpeed(vit * linDir - d_lin/diffK);
    }
    else {
      M_L.setSpeed(-0.46 * linDir - d_lin/250.0);
      M_R.setSpeed(0.46 * linDir - d_lin/250.0);
    }
  }
  else {
    fin = true;
  }

  /// si on va trop lentement
  if(abs(M_L.currSpeed) < 0.0005 && abs(M_R.currSpeed) < 0.0005){
    if(!blocked){       /// si on etait pas bloques, on est bloques
      timeBlocked = millis();
      blocked = true;
    }
  }else{
   blocked = false;
  }

  /// Si bloques et que ce fait trop longtemps, on s'arrete
  if(blocked && millis() - timeBlocked > 1000){
    fin = true;
  }

  /// Si on s arrete, on reinitialise les vitesses et offsets, et on est debloques.
  if(fin){
    M_L.setKv(1);
    M_R.setKv(1);
    M_L.setSpeed(0);
    M_R.setSpeed(0);
    blocked = false;
    return true;
  }else{
    return false;
  }
}


boolean avoidCommand() {

    /// distance parcourue
  float dst = abs( (M_R.encoderPos - M_L.encoderPos)) / 2.0;

  /// si on peut reculer
  if(dst > 50) {
    float d_lin = M_R.encoderPos + M_L.encoderPos;
    /// on fait marche arriere en ligne droite
    M_L.setSpeed(0.3 * linDir - d_lin/250.0);
    M_R.setSpeed(-0.3 * linDir - d_lin/250.0);

    return false;
  }
  else {
    /// sinon on s arrete et on attend que l obstacle parte.
    M_L.setSpeed(0);
    M_R.setSpeed(0);
    delay(100);

    return true;
  }
}

