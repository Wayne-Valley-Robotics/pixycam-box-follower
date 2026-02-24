class Blink
{
private:
    int pin;
    bool state;

public:
    Blink(int pin)
    {
        this->pin = pin;
        this->state = false;
    }

    void changeState()
    {
        state = !state;
    }
};