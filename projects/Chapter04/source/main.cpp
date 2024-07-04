#include "pch.hpp"

#include "Foundation/constants.hpp"
#include "Foundation/types.hpp"

#include "IO/io.hpp"

auto main() noexcept -> fn::idef
try
{
  // Print introduction
  IO::printIntroduction();

  // Main loop
  while (true)
  {
    // Print prompt
    IO::printPrompt();

    // Read input
    const auto input{IO::readInput()};

    // Parse input
    IO::parseInput(input);

    // Break
    break;
  }

  // Return success
  return fn::TERMINATE_SUCCESS;
}
catch (...)
{
  // Return failure
  return fn::TERMINATE_FAILURE;
}
