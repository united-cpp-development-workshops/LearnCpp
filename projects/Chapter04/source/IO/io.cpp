#include "pch.hpp"

#include "IO/io.hpp"

#include "IO/_internal/messages.ipp"
#include "IO/_internal/parsers.hpp"
#include "IO/_internal/prints.hpp"
#include "IO/_internal/responses.hpp"
#include "IO/_internal/utilities.hpp"
#include "IO/_internal/validator.hpp"

#include <Foundation/types.hpp>

#include <algorithm>
#include <iostream>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace IO
{
  auto printIntroduction() -> fn::none
  {
    std::cout << "---------------------------< Types Explorer "
                 ">---------------------------\n\n";

    _internal::printBriefInfo();

    std::cout << "   :::::::::::::::::::::::::: How It Works "
                 "::::::::::::::::::::::::::\n";

    _internal::printBriefHelp();
  }

  auto printPrompt() -> fn::none
  {
    std::cout << "\n-----------------------------------------------------------"
                 "-------------\n\n";

    std::cout << " [>]: ";
  }

  [[nodiscard]] auto readInput() -> std::string
  {
    // Reset input buffer
    _internal::resetInputBuffer();

    // Read input as string
    std::string input;
    std::getline(std::cin, input);

    // Return input
    return input;
  }

  [[nodiscard]] auto parseInput(std::string& input
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
    std::ranges::replace_if(input, _internal::isNotAllowedCharacter, ' ');

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
    auto options{_internal::parseOptions(inputStream)};

    // Return if valid request
    return _internal::validateRequest(command, options)
           ? std::make_optional(
               std::pair<Command, std::set<Option>>(command, options)
             )
           : std::nullopt;
  }

  auto printResponse(Command command, const std::set<Option>& options)
    -> fn::none
  {
    // Using declarations
    using enum Command;

    // Print one empty line
    std::cout << '\n';

    // Respond based on command
    switch (command)
    {
    case HELP:
    {
      _internal::helpResponse(options);
      return;
    }
    case PLATFORM:
    {
      _internal::platformResponse(options);
      return;
    }
    case EXPLORE:
    {
      _internal::exploreResponse(options);
      return;
    }
    case COMPARE:
    {
      _internal::compareResponse(options);
      return;
    }
    case EXIT:
    {
      _internal::exitResponse(options);
      return;
    }
    }
  }
} // namespace IO
