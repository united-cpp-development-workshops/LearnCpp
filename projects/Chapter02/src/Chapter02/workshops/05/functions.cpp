#include "Chapter02/workshops/05/functions.hpp"

#include <iostream>

int getValueFromUserHpp()
{
  std::cout << "Enter an integer: ";
  int input{};
  std::cin >> input;
  return input;
}

void printAdditionHpp(int fVal, int sVal)
{
  std::cout << fVal << " + " << sVal << " = " << fVal + sVal << '\n';
}
