#include "pch.hpp"

#include "Foundation/constants.hpp"
#include "Foundation/types.hpp"

#include <iostream>

auto main() noexcept -> fn::idef
try
{
  // Print Hello World!
  std::cout << "Hello World!\n";

  // Return success
  return fn::TERMINATE_SUCCESS;
}
catch (...)
{
  // Return failure
  return fn::TERMINATE_FAILURE;
}
