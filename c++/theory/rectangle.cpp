class rectangle {
private:
    //Field (Attributi) Stato interno dell'oggetto
    int length; 
    int width;

public:
    //Costruttori:
    //Inizializzazione di oggetti della classe
    // = stato iniziale di questi oggetti
    rectangle() {
        length = 0;
        width = 0;
    }

    rectangle(int length, int width) {
        this->length = length;
        this->width = width;
    }

    //Methods (metodi) -> Servizi
    int perimeter() {
        return 2 * length + 2 * width;
    }

    int area() {
        return length * width;
    }
    //...
};