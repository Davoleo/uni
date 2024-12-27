#include <iostream>

class Base {
public:
    Base()
    {
        std::cout << "Constructor Base::Base()" << std::endl;
    }
    virtual void f(int)
    {
        std::cout << "Base::f(int)" << std::endl;
    }
    virtual void f(double)
    {
        std::cout << "Base::f(double)" << std::endl;
    }
    virtual void g(int)
    {
        std::cout << "Base::g(int)" << std::endl;
    }
    virtual ~Base()
    {
        std::cout << "Destructor Base::~Base()" << std::endl;
    }
};
class Derived : public Base {
public:
    Derived()
    {
        std::cout << "Constructor Derived::Derived()" << std::endl;
    }
    void f(char c)
    {
        std::cout << "Derived::f(char)" << std::endl;
    }
    void g(int)
    {
        std::cout << "Derived::g(int)" << std::endl;
    }
    ~Derived()
    {
        std::cout << "Destructor Derived::~Derived()" << std::endl;
    }
};
int main()
{
    Base b; 		//Constructor Base::Base()
    Derived d;  	//Constructor Base::Base()
					//Constructor Derived::Derived()
    Base& rb = b;
    Base* pb = &d;
    std::cout << "=== 1 ===" << std::endl; //=== 1 ===
    b.f(1);			//Base::f(int)
    rb.f('a');		//Base::f(int)
    rb.g(1);		//Base::g(int)
    std::cout << "=== 2 ===" << std::endl; //=== 2 ===
    d.f(1);			//Derived::f(char)  [hiding dei metodi base]
    d.f(1.0);		//Derived::f(char)	[hiding]
    d.g(3.3);		//Derived::g(int)	[hiding]
    std::cout << "=== 3 ===" << std::endl; //=== 3 ===
    pb->f(1.0);		//Base::f(double)
    pb->f('a');		//Base::f(int)
    pb->g(3.3);		//Derived::g(int) [OVERRIDING]
    return 0;
}
//Destructor Derived::~Derived()
//Destructor Base::~Base()
//Destructor Base::~Base()