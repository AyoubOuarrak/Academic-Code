#include "T.hh"
#include "Stack.defs.hh"

#include <iostream>

int f(int n) {
  T t;

  std::cerr << "Prima della costruzione dello stack s." << std::endl;
  Stack s(50);
  std::cerr << std::endl;

  std::cerr << "Prima delle push." << std::endl;
  for (int i = 0; i < n; ++i)
    s.push(t);
  std::cerr << std::endl;

  std::cerr << "Prima della copia di s in s1." << std::endl;
  Stack s1(s);
  std::cerr << std::endl;

  return 0;
}


int main() {
  try {
    f(2);
    f(7);
  }
  catch (...) {
    std::cerr << "Eccezione catturata!" << std::endl;
  }
  return 0;
}
