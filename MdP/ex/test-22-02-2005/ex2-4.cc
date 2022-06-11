#include <iostream>
class ZooAnimal {
public:
    ZooAnimal()
    {
        std::cout << "Constructor ZooAnimal" << std::endl;
    }
    virtual void print()
    {
        std::cout << "ZooAnimal::print" << std::endl;
    }
    virtual ~ZooAnimal() { }
};

class Bear : virtual public ZooAnimal {
public:
    Bear()
    {
        std::cout << "Constructor Bear" << std::endl;
    }
    void print()
    {
        std::cout << "Bear::print" << std::endl;
    }
    virtual ~Bear() { }
};

class Raccoon : virtual public ZooAnimal {
public:
    Raccoon()
    {
        std::cout << "Constructor Raccoon" << std::endl;
    }
    virtual ~Raccoon() { }
};

class Endangered {
public:
    Endangered()
    {
        std::cout << "Constructor Endangered" << std::endl;
    }
    void print()
    {
        std::cout << "Endangered::print" << std::endl;
    }
    virtual ~Endangered() { }
};

class Panda : public Endangered, public Bear, public Raccoon {
public:
    Panda()
    {
        std::cout << "Constructor Panda" << std::endl;
    }
    void print()
    {
        std::cout << "Panda::print" << std::endl;
    }
    virtual ~Panda() { }
};

//Ex 4
#include <vector>

template<typename T>
T average(std::vector<T> values) {
	T sum = 0;
	for (T val : values)
		sum += val;
	return sum / values.size();
}

template<typename ITER, typename T>
T average(ITER first, ITER last) {
	int count = 0;
	T sum = 0;
	while (first != last) {
		++count;
		sum += *first;
		++first
	}
	return sum/count;
}

//////////////////////////

int main()
{
    Panda ying_yang;
    ying_yang.print();
	// Constructor Endangered
	// Constructor ZooAnimal	<- NO questo viene costruito all'inizio prima di Endangered (quindi i costruttori nell'ereditariatà multipla nons ono chiamati in ordine...?)
	// Constructor Bear
	// Constructor ZooAnimal	<- NO: ZooAnimal viene costruito una sola volta nonostante sia Bear sia Raccoon siano sue sottoclassi
	// Constructor Raccoon
	// Constructor Panda
	// Panda::print

	std::cout << "------------" << std::endl;

    Bear b = ying_yang;
    b.print();
	// Constructor ZooAnimal 	<- NO
	// Constructor Bear			<- NO
	// Bear::print
	
	std::cout << "------------" << std::endl;

    ZooAnimal* pz = &ying_yang;
    pz->print();
	//Panda::print 				<- Corretto, ma ereditarietà multipla? come fa a decidere?

	std::cout << "------------" << std::endl;

    Endangered& re = ying_yang;
    re.print();
	//Endangered::print			<- Corretto: non è virtual quindi no RTI

	std::cout << "------------" << std::endl;

    return 0;
}
