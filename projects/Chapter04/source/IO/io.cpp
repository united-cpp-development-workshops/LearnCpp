#include "pch.hpp"

#include "IO/io.hpp"

#include "IO/_internal/messages.hpp"
#include "IO/_internal/parsers.hpp"
#include "IO/_internal/prints.hpp"
#include "IO/_internal/utilities.hpp"

#include <algorithm>
#include <iostream>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <utility>

namespace
{
  auto getUnknownOptionWarning(const std::string& option) -> std::string
  {
    return "Unknown option '" + option + "' was found and discarded!";
  }
} // namespace

namespace IO
{
  auto printIntroduction() -> void
  {
    std::cout << "---------------------------> Types Explorer "
                 "<---------------------------\n\n";

    std::cout << " - Explore fundamental types of C++.\n";
    std::cout << " - Learn about the sizes, ranges, and properties of "
                 "fundamental types.\n";
    std::cout << " - Observe the behavior of fundamental types in various "
                 "contexts.\n";
    std::cout
      << " - Discover fundamental type aliases in Foundation header.\n\n";

    std::cout << "   :::::::::::::::::::::::::: How It Works "
                 "::::::::::::::::::::::::::\n\n";

    _internal::printBriefHelp();
  }

  auto printPrompt() -> void
  {
    std::cout << "\n-----------------------------------------------------------"
                 "-------------\n\n";

    std::cout << " [>]: ";
  }

  [[nodiscard]]
  auto readInput() -> std::string
  {
    // Reset input buffer
    _internal::resetInputBuffer();

    // Read input as string
    std::string input;
    std::getline(std::cin, input);

    // Return input
    return input;
  }

  [[nodiscard]]
  auto parseInput(std::string& input
  ) -> std::optional<std::pair<Command, std::set<Option>>>
  {
    // Check if input is empty
    if (input.empty())
    {
      // Print error message
      _internal::printInputError(_internal::GET_NO_INPUT_MSG());
      return std::nullopt;
    }

    // Replace not allowed characters
    std::replace_if(
      input.begin(), input.end(), _internal::isNotAllowedCharacter, ' '
    );

    // Create input stream
    std::istringstream inputStream{input};

    // Parse command
    std::string commandInput;
    if (not(inputStream >> commandInput))
    {
      // Print error message
      _internal::printInputError(_internal::GET_NO_COMMAND_MSG());
      return std::nullopt;
    }

    // Get command optional
    const auto commandOptional{_internal::parseCommand(commandInput)};

    // Return if error. (error message printed in parser)
    if (not commandOptional.has_value()) { return std::nullopt; }

    // Get command
    const auto command{commandOptional.value()};

    // Parse options
    const auto options{_internal::parseOptions(inputStream)};

    // TEST:
    return std::nullopt;
  }
} // namespace IO
