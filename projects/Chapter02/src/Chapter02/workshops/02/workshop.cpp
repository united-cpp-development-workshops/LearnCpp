#include "Chapter02/workshops/02/workshop.hpp"

#include <Base/announce.hpp>

#include <iostream>

// Forward declarations
static int  getValueFromUser();
static void printAddition(int fVal, int sVal);

void Workshop02::run()
{
  ANNOUNCE_WORKSHOP("Workshop 02: Function With Parameters");
  printAddition(getValueFromUser(), getValueFromUser());
}

static int getValueFromUser()
{
  std::cout << "Enter an integer: ";
  int input{};
  std::cin >> input;
  return input;
}

static void printAddition(int fVal, int sVal)
{
  std::cout << fVal << " + " << sVal << " = " << fVal + sVal << '\n';
}
