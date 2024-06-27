#include <iostream>
//contract , interface , abstraction
class IPrintableDevice{
     public:
     virtual void print()=0;
};
class IScanner{
   public:
   virtual void scan()=0;
};
class D
{
    private:
        int val;
    protected:
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
        PS(int x,IScanner *sAddress,IPrintableDevice *pAddress) :
        D(x), sObj{sAddress},pObj{pAddress} { std::cout << "PS Constructor" << std::endl;

        }
        ~PS() { std::cout << "PS destructor called " << std::endl;}
        void print(){
            pObj.print();
        }
        void scan(){
            sObj.scan();
        }
};
void printTask(IPrintableDevice* ptr)
{
    ptr->print();
}
template<typename T>
void print(T* ptr){
     ptr->print();
}

void scanTask(IScanner* sptr)
{
    sptr->scan();
}
int main()
{
    P pObj;
    S sObj;
    PS psObj{10,&pObj,&sObj};
    printTask(&pObj);
    printTask(&psObj);
    scanTask(&sObj);
    scanTask(&psObj);
    return 0;
}
