class StepperSumo {
  public:
    StepperSumo(int pinDir, int pinStep, int pinSleep);
    wake(); //lance le moteur
    shutdown(); //eteind le moteur pour eviter qu il chauffe
    stepUp(); //met la pin step en HIGH
    stepDown(); //met le pin step en LOW
    dir(bool level);


  private:
    int m_pinDir;
    int m_pinStep;
    int m_pinSleep;

};
