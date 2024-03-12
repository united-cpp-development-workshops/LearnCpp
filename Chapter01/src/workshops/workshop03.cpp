#include "workshops/workshop03.hpp"

#include "announce.hpp"

void Workshop03::run()
{
  ANNOUNCE_WORKSHOP("Workshop 03: Multiply");
  std::cout << "Enter an integer: ";
  int input{};
  std::cin >> input;
  std::cout << "The double of " << input << " is " << input * 2 << ".\n";
  std::cout << "The triple of " << input << " is " << input * 3 << ".\n";
}
