#include "pch.hpp"

#include "foundation.hpp"

#include <iostream>

auto main() noexcept -> idef
try
{
  // Print Hello World!
  std::cout << "Hello World!\n";

  // Return success
  return TERMINATE_SUCCESS;
}
catch (...)
{
  // Return failure
  return TERMINATE_FAILURE;
}
