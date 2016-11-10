class BaseRoulante {
  public:
    BaseRoulante (float largeur, float diamRoue, int nbrStep, float freqStep, int pinStepGauche, int pinDirGauche, int pinSleepGauche, int pinStepDroite, int pinDirDroite, int pinSleepDroite);
    ligneDroite(bool dir, float distance); //distance en centimetre
    rotation(bool trigo, float degres); //trigo = 1 si rotation dans sens trigo
    sleep(); //eteint la base roulante
    wake(); //reveille la base roulante

  private:
    float m_largeur; //en mm
    float m_diamRoue; //en mm
    int m_nbrStep;
    float m_freqStep;
    float m_dureeStep;
    StepperSumo m_stepperGauche;
    StepperSumo m_stepperDroite;
};
