#include "pch.hpp"

#include "IO/io.hpp"

#include "IO/_internal/messages.ipp"
#include "IO/_internal/parsers.hpp"
#include "IO/_internal/prints.hpp"
#include "IO/_internal/responses.hpp"
#include "IO/_internal/utilities.hpp"
#include "IO/_internal/validator.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>

#include <algorithm>
#include <iostream>
#include <sstream>

namespace IO
{
  auto printIntroduction() -> fn::none
  {
    std::cout << "---------------------------< Types Explorer >---------------------------\n\n";

    _internal::printBriefInfo();

    std::cout << "   :::::::::::::::::::::::::: How It Works ::::::::::::::::::::::::::\n";

    _internal::printBriefHelp();
  }

  auto printPrompt() -> fn::none
  {
    std::cout << "\n------------------------------------------------------------------------\n\n";

    std::cout << " [>]: ";
  }

  [[nodiscard]] auto readInput() -> fn::str
  {
    // Reset input buffer
    _internal::resetInputBuffer();

    // Read input as string
    fn::str input;
    std::getline(std::cin, input);

    // Return input
    return input;
  }

  [[nodiscard]] auto parseInput(fn::str& input) -> fn::opt<fn::pair<Command, fn::set<Option>>>
  {
    // Check if input is empty
    if (input.empty())
    {
      // Print error message
      _internal::printInputError(_internal::NO_INPUT_MSG());
      return fn::nopt;
    }

    // Replace not allowed characters
    std::ranges::replace_if(input, _internal::isNotAllowedCharacter, ' ');

    // Create input stream
    std::istringstream inputStream{input};

    // Parse command
    fn::str commandInput;
    if (not(inputStream >> commandInput))
    {
      // Print error message
      _internal::printInputError(_internal::NO_CMD_MSG());
      return fn::nopt;
    }

    // Get command optional
    const auto commandOptional{_internal::parseCommand(commandInput)};

    // Return if error. (error message printed in parser)
    if (not commandOptional.has_value())
    {
      return fn::nopt;
    }

    // Get command
    const auto command{commandOptional.value()};

    // Parse options
    auto options{_internal::parseOptions(inputStream)};

    // Return if valid request
    return _internal::validateRequest(command, options)
           ? fn::opt{fn::pair<Command, fn::set<Option>>(command, options)}
           : fn::nopt;
  }

  auto printResponse(const Command command, const fn::set<Option>& options) -> fn::none
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
    case TIPS:
    {
      _internal::tipsResponse(options);
      return;
    }
    case METRICS:
    {
      _internal::metricsResponse(options);
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
