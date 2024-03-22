#include "Chapter01/workshops/02/workshop.hpp"

#include <Base/announce.hpp>

#include <iostream>

// Disable warning C4700: uninitialized local variable 'x' used
#pragma warning(disable : 4'700)

void Workshop02::run()
{
  ANNOUNCE_WORKSHOP("Workshop 02: Uninitialized Variables & Undefined Behavior"
  );
  int x;
  std::cout << "Uninitialized variable x: " << x << '\n';
  std::cout << "Size of an int: " << sizeof(int) << '\n';
}

#pragma warning(default : 4'700)
