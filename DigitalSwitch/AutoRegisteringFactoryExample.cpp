#include <iostream>
#include <string>
#include <map>

using namespace std;

class I {
public:
    I() = default;
    virtual ~I() = default;

    virtual void operation() = 0;
};

class Impl : public I {
public:
    void operation() override {
        cout << "Impl Operation" << endl;
    }

    static I* CreateMethod() {
        return new Impl();
    }

    static std::string GetFactoryName() {
        return "IMPL";
    }

private:
    static bool registered;
};

using TCreateMethod = I*(*)();

class IFactory {
public:
    virtual I* Create(const string& name) = 0;
};

class Factory : public IFactory {
public:
    Factory() = default;

    static bool Register(const string& name, TCreateMethod funcCreate);

    I* Create(const string& name) override;

private:
    static map<string, TCreateMethod> createMethods;
};

map<string, TCreateMethod> Factory::createMethods;

bool Factory::Register(const string& name, TCreateMethod funcCreate) {
    if (auto it = Factory::createMethods.find(name); it == Factory::createMethods.end()) {
        Factory::createMethods[name] = funcCreate;
        return true;
    }
    return false;
}

I* Factory::Create(const string& name) {
    if (auto it = Factory::createMethods.find(name); it != Factory::createMethods.end()) {
        return it->second(); // call the createFunc
    }
    return nullptr;
}

bool Impl::registered = Factory::Register(Impl::GetFactoryName(), &Impl::CreateMethod);

int main() {
    Factory factObj;
    IFactory* facPtr = &factObj;
    I* ptr = facPtr->Create("IMPL");
    if (ptr) {
        ptr->operation();
        delete ptr;
    } else {
        cout << "Creation failed!" << endl;
    }
    return 0;
}
