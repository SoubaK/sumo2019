#ifndef MotorBlock_h
#define MotorBlock_h

#define OFFSET 60

class MotorBlock
{
  public:
    MotorBlock(int dir,int brake,int pwm, int encoderA, int encoderB);

    /// regle les paramertres des pins dir, brake et pwm
    void init();

    ///
    void run();

    /// ???????? cette fonction sort de nulle part...
    void coderInterrupt();

    /// Initialise la vitesse cible
    void setSpeed(double targetSpeedRequired);

    ///Initialise la variable Kv.
    void setKv(float requiredKv);

    ///Initialise la variable K.
    void setK(float requiredK);

    /// Incremente Kv de delta
    void addToKv(float delta);


    /// position mesuree sur un encodeur
    volatile long encoderPos;

    /// nb de pulses mesures par un encodeur
    volatile long nbTopsDone;

    int pinA;
    int pinB;

    /// vitesse actuelle
    double currSpeed;

    /// vitesse cible
    double targetSpeed;

    /// ????
    float cmdDEBUG;
    /// offset
    float offset;
    /// constante. Utilite ???????????????
    float Kv;
    /// constante. Utilite ???????????????
    float K;

    /// Autres noms des pins   (ce sont des noms locaux)
  private:
    int D;      /// pin dir
    int B;      /// pin brake
    int P;      /// pin pwm
};


#endif
