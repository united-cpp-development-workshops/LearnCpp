#include <iostream>

int getValueFromUser()
{
  std::cout << "Enter an integer: ";
  int input{};
  std::cin >> input;
  return input;
}

void printAddition(int fVal, int sVal)
{
  std::cout << fVal << " + " << sVal << " = " << fVal + sVal << '\n';
}
