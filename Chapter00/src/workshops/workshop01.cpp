#include "workshops/workshop01.hpp"

#include "announce.hpp"

void Workshop01::run()
{
  ANNOUNCE_WORKSHOP("Workshop 01: Hello World");
  std::cout << "Hello World\n";
}
