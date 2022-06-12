class Animale {
public:
    virtual Animale* clone() const = 0; 

    virtual void verso() const = 0;

    virtual ~Animale() { }
};