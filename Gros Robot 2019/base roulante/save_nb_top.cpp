
void coderL()

/// lecture de l'encoder gauche, sens positif = roue qui recule

{
  if (digitalRead(M_L.pinA) == digitalRead(M_L.pinB)) {     /// si égalité sens positif de la roue, sinon autre sens, M_L= objet moteur gauche
    M_L.nb_top--;
  } else {
    M_L.nb_top++;
  }
}

void coderR()

/// lecture de l'encoder droite, sens positif = roue qui avance

{
  if (digitalRead(M_R.pinA) == digitalRead(M_R.pinB)) {     /// si égalité sens positif de la roue, sinon autre sens, M_R= objet moteur droite
    M_R.nb_top++;
  } else {
    M_R.nb_top--;
  }
}
