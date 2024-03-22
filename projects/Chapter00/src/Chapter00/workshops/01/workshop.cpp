#include "Chapter00/workshops/01/workshop.hpp"

#include <Base/announce.hpp>

#include <iostream>

void Workshop01::run()
{
  ANNOUNCE_WORKSHOP("Workshop 01: Hello World");
  std::cout << "Hello World\n";
}
