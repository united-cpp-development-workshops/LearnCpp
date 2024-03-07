#include <iostream>

#include "announce.hpp"
#include "workshops/workshop01.hpp"

void Workshop01::run()
{
  ANNOUNCE_WORKSHOP("Workshop 01: Hello World");
  std::cout << "Hello World\n";
}
