#include <iostream>
//lazy-evaluated, thread-safe in c11
class Singleton {
public:
  static Singleton& getInstance() {
    static Singleton mIntance;
    return mIntance;
  }
private:
  Singleton() {std::cout << "construct" << std::endl;}
  Singleton(const Singleton&) = delete;
  Singleton&  operator=(const Singleton&) = delete;

};

int main() {
  Singleton& m1 = Singleton::getInstance();
  return 0;
}
