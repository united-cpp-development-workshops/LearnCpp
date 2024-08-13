#include "pch.hpp"

#include "Core/constants.hpp"
#include "Core/core.hpp"
#include "IO/io.ipp"

#include <Foundation/constants.hpp>
#include <Foundation/errors.hpp>
#include <Foundation/types.hpp>
#include <Foundation/Utility/log.ipp>
#include <Foundation/Utility/what.ipp>

#include <exception>
#include <iostream>

auto main() noexcept -> fn::idef
try
{
  // Main loop
  while (true)
  {
    // Print app title
    IO::printSectionDivider();
    IO::printAppTitle();
    IO::printSectionDivider();
    IO::printTitle("MAIN MENU");
    IO::printParagraph("Select an option from the menu below:");
    IO::printOption("Play ", "Start playing.", Core::PLAY_OPTION);
    IO::printOption("Learn", "Learn the game.", Core::LEARN_OPTION);
    IO::printOption("Exit ", "Exit the application.", Core::EXIT_OPTION);

    // Get the user input
    fn::i16l option{};
    IO::printInputPrompt("Enter an option.");
    std::cin >> option;

    // Process the user input
    switch (option)
    {
    case Core::PLAY_OPTION:
    {
      // Run the game
      Core::run();
      break;
    }
    case Core::LEARN_OPTION:
    {
      // Run the game
      Core::learn();
      break;
    }
    case Core::EXIT_OPTION:
    {
      // Exit the application
      return fn::EXIT_SUCCESS_CODE;
    }
    default:
    {
      // Input was invalid print error message
      IO::printErrorMessage("Invalid option, try again.");
      break;
    }
    }
  }
}
catch (const fn::InputError& error)
{
  // Log error
  fn::elog(error);

  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
catch (const fn::EnumeratorError& error)
{
  // Log error
  fn::elog(error);

  // Return failure
  return fn::EXIT_FAILURE_CODE;
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
