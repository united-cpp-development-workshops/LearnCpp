#include <cstdlib>
#include <iostream>

auto main() noexcept -> int
try
{
  std::cout << "Hello World\n";
  return EXIT_SUCCESS;
}
catch (...)
{
  return EXIT_FAILURE;
}
