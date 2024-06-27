#include <iostream>
//contract , interface , abstraction
//Abstract Class
//These interfaces define pure virtual functions that must be implemented by derived classes.
class IPrintableDevice{
     public:
     virtual void print()=0;
};

//Abstract Class
//These interfaces define pure virtual functions that must be implemented by derived classes.
class IScanner{
   public:
   virtual void scan()=0;
};
class D
{
    private:
        int val;
    protected:
        //Protected Constructors
        //Used in the D class to ensure it can only be instantiated by derived classes.
        D(int x) { val = x; std::cout << "D Constructor, val = " << val << std::endl;}
    public:
        ~D() { std::cout << "D destructor called " << std::endl;}
        void printVal() { std::cout << "Val in D = " << val << std::endl;}
};
class P : public D,public IPrintableDevice
{
    public:
        P() : D(1) { std::cout << "P Constructor" << std::endl;}
        ~P() { std::cout << "P destructor called " << std::endl;}
        void print() { std::cout << "Printing..." << std::endl;}
};
class S : public D,public IScanner
{
    public:
        S() : D(2)
        { std::cout << "S Constructor" << std::endl;}
        ~S() { std::cout << "S destructor called " << std::endl;}
        void scan() { std::cout << "Scanning..." << std::endl;}
};
class PS : public D,public IPrintableDevice,public IScanner
{
    IScanner* sObj;
    IPrintableDevice* pObj;
    public:
        //Dependency Injection
        //Constructor Injection: Used in the PS class to inject dependencies
        PS(int x,IScanner *sAddress,IPrintableDevice *pAddress) :
        D(x), sObj{sAddress},pObj{pAddress} { std::cout << "PS Constructor" << std::endl;

        }
        ~PS() { std::cout << "PS destructor called " << std::endl;}
        //Delegation
        //PS class delegates the print and scan tasks to the injected objects
        void print(){
            pObj->print();
        }
        //Delegation
        //PS class delegates the print and scan tasks to the injected objects
        void scan(){
            sObj->scan();
        }
};

//Runtime Polymorphism: Achieved through virtual functions and pointers to base classes.
void printTask(IPrintableDevice* ptr)
{
    ptr->print();
}

template<typename T>
void print(T* ptr){
     ptr->print();
}

//Runtime Polymorphism: Achieved through virtual functions and pointers to base classes.
void scanTask(IScanner* sptr)
{
    sptr->scan();
}

int main()
{
    P pObj;
    S sObj;
    PS psObj{10,&sObj,&pObj};
    printTask(&pObj);
    printTask(&psObj);
    scanTask(&sObj);
    scanTask(&psObj);
    return 0;
}
