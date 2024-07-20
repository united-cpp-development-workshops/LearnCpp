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
    auto input{IO::readInput()};

    // Parse input
    const auto optional{IO::parseInput(input)};

    // Check if input is valid
    if (not optional.has_value()) { continue; }

    // Destructure input
    const auto& [command, options]{optional.value()};

    // Exit if command is 'exit' and has no options
    if (command == IO::Command::EXIT and options.empty()) { break; }

    // Respond
    IO::printResponse(command, options);
  }

  // Return success
  return fn::EXIT_SUCCESS_CODE;
}
catch (...)
{
  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
