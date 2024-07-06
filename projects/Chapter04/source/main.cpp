#include "pch.hpp"

#include "Foundation/constants.hpp"
#include "Foundation/types.hpp"

#include "IO/io.hpp"

#include <tuple>

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
    auto input{IO::readInput()};

    // Parse input
    const auto optional{IO::parseInput(input)};

    // Check if input is valid
    if (not optional.has_value()) { continue; }

    // Destructured input
    const auto [ignored1, ignored2]{optional.value()};

    // Ignore unused variables
    std::ignore = ignored1;
    std::ignore = ignored2;

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
