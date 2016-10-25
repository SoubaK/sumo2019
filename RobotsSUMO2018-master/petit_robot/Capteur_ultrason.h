class Capteur_ultrason
{
    public:
    Capteur_ultrason(int pin_trig,int pin_echo);
    void set_capteur();
    int get_distance();  

    private:
    int m_pin_trig;
    int m_pin_echo;
  
};
