#include "Chapter02/workshops/01/workshop.hpp"

#include <Base/announce.hpp>

#include <iostream>

static int getValueFromUser()
{
  std::cout << "Enter an integer: ";
  int input{};
  std::cin >> input;
  return input;
}

void Workshop01::run()
{
  ANNOUNCE_WORKSHOP("Workshop 01: A Basic Function");
  const int firstVal{getValueFromUser()};
  const int secondVal{getValueFromUser()};
  std::cout << firstVal << " + " << secondVal << " = " << firstVal + secondVal
            << '\n';
}
