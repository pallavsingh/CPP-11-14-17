#include <iostream>
using namespace std;

class Base {
    public :
    virtual void func1() const noexcept;
    virtual void func2() const noexcept;
    virtual void func3() const noexcept final;
};

void Base::func1() const noexcept { cout << "Base Class : Func1" << endl; }
void Base::func2() const noexcept { cout << "Base Class : Func2" << endl; }
void Base::func3() const noexcept { cout << "Base Class : Func3" << endl; } 

class Mid : public Base{
    public :
    virtual void func1() const noexcept override;
    virtual void func2() const noexcept override final;
};

void Mid::func1() const noexcept { cout << "Mid Class : Func1" << endl; }
void Mid::func2() const noexcept { cout << "Mid Class : Func2" << endl; }

class Derived final : public Mid {
    public :
    virtual void func1() const noexcept override final;
    /* virtual void func2() const noexcept override; */
};

void Derived::func1()  const noexcept { cout << "Derived Class : Func1" << endl; }

/* class Derived1 : public Derived{}; */

int main(){
    Base * ptr = nullptr;
    ptr = new Derived();
    ptr->func2();
    ptr->func3();
}

