#include "pch.hpp"

#include "IO/io.hpp"

#include <Foundation/constants.hpp>
#include <Foundation/types.hpp>
#include <Foundation/Utility/log.ipp>
#include <Foundation/Utility/what.ipp>

#include <exception>

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
    if (not optional.has_value())
    {
      continue;
    }

    // Destructured input
    const auto& [command, options]{optional.value()};

    // Exit if command is 'exit' and has no options
    if (command == IO::Command::EXIT and options.empty())
    {
      break;
    }

    // Respond
    IO::printResponse(command, options);
  }

  // Return success
  return fn::EXIT_SUCCESS_CODE;
}
catch (const std::exception& exception)
{
  // Log exception
  fn::elog(fn::what(exception));

  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
catch (...)
{
  // Log unknown exception
  fn::elog(fn::UNKNOWN_EXCEPTION);

  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
