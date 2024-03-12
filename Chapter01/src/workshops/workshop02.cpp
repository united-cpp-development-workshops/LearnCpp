#include "workshops/workshop02.hpp"

#include "announce.hpp"

// Disable warning C4700: uninitialized local variable 'x' used
#pragma warning(disable:4700)
void Workshop02::run()
{
  ANNOUNCE_WORKSHOP("Workshop 02: Uninitialized Variables & Undefined Behavior");
  int x;
  std::cout << "Uninitialized variable x: " << x << '\n';
  std::cout << "Size of an int: " << sizeof(int) << '\n';
}
#pragma warning(default:4700)
