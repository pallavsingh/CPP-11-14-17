#include <iostream>
#include <utility>
using namespace std;
 
struct A {
   double x;
};

const A* a = new A{0};
 
// type of x3 is double (declared type)
decltype( a->x ) x3;       

// The inner parentheses cause the statement to be evaluated as an expression instead of a member access.
// type of x4 is const double& (lvalue expression)
decltype((a->x)) x4 = x3;  
 
//forward function template, which support perfect forwarding.
template<typename T1, typename T2>
auto Plus(T1&& t1, T2&& t2) -> decltype(forward<T1>(t1) + forward<T2>(t2)) {
   return forward<T1>(t1) + forward<T2>(t2);
}

class userdefined_data{
// For Friend Function Scope resoltuion specifier donot Matter
   friend userdefined_data operator+(const userdefined_data& x1, const userdefined_data& x2){
      return userdefined_data(x1.m_data + x2.m_data);
   }

public:
   userdefined_data(int data) : m_data(data) {}
   int Dump() const { return m_data;}
private:
   int m_data;
};

int main() {
    int i = 33;
    decltype(i) j = i*2;
    std::cout << "i = " << i << ", " << "j = " << j << '\n';

    const int && fx(); 
    decltype(fx()) k = i + j; // const int && ; An rvalue reference to a const int. 
    std::cout << "k = " << k << '\n';
 
    auto f = [](int a, int b) -> int {
       return a*b;
    };
 
    decltype(f) f2 = f; // the type of a lambda function is unique and unnamed
    i = f(2, 2);
    j = f2(3, 3);
 
    std::cout << "i = " << i << ", " << "j = " << j << '\n';

   // Integer 
   i = 4;
   cout << " Plus(i, 9) = " << Plus(i, 9) << endl;

   // Floating point
   float dx = 4.0;
   float dy = 9.5;
   cout << " Plus(dx, dy) = " << Plus(dx, dy) << endl;

   // String      
   string hello = "Hello, ";
   string world = "world!";
   cout << Plus(hello, world) << endl;

   // Custom type
   userdefined_data x1(20);
   userdefined_data x2(22);
   userdefined_data x3 = Plus(x1, x2);
   cout << "x3.Dump() = " << x3.Dump() << endl;
}
