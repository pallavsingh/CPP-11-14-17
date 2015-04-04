#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

template<typename T>
class Data final {
  private:
    T  value1, value2, count;
  public :
    static int counter; 

    Data( ): value1(0), value2(0) {
       ++counter; count = counter;  
       cout << "Default Constructor called" << endl;
    }
  
    Data(int i, int j): value1(i), value2(j) { 
       ++counter; count = counter; 
       cout << "Parameterized Constructor called" << endl;
    }
  
   ~Data() noexcept {
       --counter; 
       cout << "Destructor : Data called ::"; 
       cout << "value of deleted Object counter   " << count << endl; 
    }
  
    Data(const Data && rhs): value1(move(rhs.value1)), value2(move(rhs.value2)) {}

    Data (const Data & rhs) noexcept{
       value1 = rhs.value1;
       value2 = rhs.value2;
       count  = counter;
       ++counter;
       cout << " Copy Constructor Called " << endl;
    }
  
    const Data & operator = (const Data & rhs) throw() {
       if(this != &rhs){
          value1 = rhs.value1;
          value2 = rhs.value2;
          count  = rhs.count;
          ++counter;
          cout << " Datassignment Operator Called " << endl;
       }
       return *this;
    }

    bool operator <(const Data & rhs)const noexcept { 
       return (value1 < rhs.value1);
    }

    bool operator != (const Data & rhs) noexcept {
       return (value1 != rhs.value1);
    }

    bool operator == (const Data & rhs) noexcept {
       return (value1 == rhs.value1);
    }

    friend ostream & operator << (ostream & out, const Data<uint32_t> & rhs);

    int getValueP() const noexcept {
      return value1;
    }
};

template< >
int Data<uint32_t>::counter = 0;

ostream & operator << (ostream & out, const Data<uint32_t> & rhs){
   out << "Value of value1  " << rhs.value1 << "    ";
   out << "Value of value2  " << rhs.value2 << "    ";
   out << "Value of Object Counter count = " << rhs.count;
   out << endl;
   return out;
}

template<typename T>
bool remove_condition(const Data<T> & rhs) { 
     return (rhs.getValueP() == 4 ); 
}


int main()
{
  // Here parameterized Constructor for Data called.
  // 10 times copy constructor for Data will be called.
  // destructor for Data will be called.
  vector<Data<uint32_t> > V(10, Data<uint32_t>(10,20));
  
  for(auto const & iter: V)
     cout<< iter << endl;     

  cout << " Size of Vector  " << V.size();
  cout << " Capacity of Vector " << V.capacity();
  cout << endl << endl << endl;
 
  V.resize(5);
  for (auto const & iter : V)
     cout<< iter << endl;     

  cout << " Size of Vector  " << V.size();
  cout << " Capacity of Vector " << V.capacity();
  cout << endl << endl << endl;
 
   for (unsigned i = 0; i < V.size(); ++i){
       V.at(i)= Data<uint32_t>(11, 22);
       cout << V.at(i) << endl << endl;
   }

  // Diffrence between at() and [] operator in STL
  // cout << V.at(100) << endl << endl;
 
  // Here output is undefined behaviour
  cout << V[100]    << endl << endl;

  // Here first Copy constructor for these 5 element are called
  // Here destructor will be called for these 5 element in first Vector
  // Finally 5 destructor will be called in Final vector
  vector<Data<uint32_t> >(V).swap(V);

  cout << " Size of Vector  " << V.size();
  cout << " Capacity of Vector " << V.capacity();
  cout << endl << endl << endl;

 // when we goes out of scope 10 times destructor will be called.
  V.erase(V.begin(), V.end());

  V.push_back(Data<uint32_t>(1,2));
  V.push_back(Data<uint32_t>(1,3));
  V.push_back(Data<uint32_t>(1,4));
  V.push_back(Data<uint32_t>(5,43));
  V.push_back(Data<uint32_t>(5,44));
  V.push_back(Data<uint32_t>(5,54));
  V.push_back(Data<uint32_t>(3,21));
  V.push_back(Data<uint32_t>(3,22));
  V.push_back(Data<uint32_t>(3,23));
  V.push_back(Data<uint32_t>(4,31));
  V.push_back(Data<uint32_t>(4,32));
  V.push_back(Data<uint32_t>(2,10));
  V.push_back(Data<uint32_t>(2,11));
  V.push_back(Data<uint32_t>(2,12));

  ////////////////////////////////////////////////////////////////

  sort(V.begin(), V.end());
  cout <<"Datafter Sorting the data "<<endl;
  for (auto const & iter : V)
      cout<< iter << endl;     

  ////////////////////////////////////////////////////////////////
 
  V.erase(remove_if(V.begin(), V.end(), remove_condition<uint32_t>), V.end());

  cout << "Datafter Calling erase Data(1, 100) " << endl;
  for (auto const & iter : V)
      cout<< iter << endl;     

  ///////////////////////////////////////////////////////////////

  return 0;
}

