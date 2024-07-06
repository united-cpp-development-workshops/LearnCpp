#include "pch.hpp"

#include "IO/_internal/parsers.hpp"

#include "IO/_internal/messages.hpp"
#include "IO/_internal/prints.hpp"
#include "IO/io.hpp"

#include <algorithm>
#include <cctype>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace
{
  [[nodiscard]]
  auto getCommandString(IO::Command input) -> std::string
  {
    switch (input)
    {
    case IO::Command::HELP: return "help";
    }
  }

  [[nodiscard]]
  auto getOptionString(IO::Option input) -> std::string
  {
    switch (input)
    {
    case IO::Option::HELP: return "help";
    }
  }
} // namespace

namespace IO::_internal
{
  [[nodiscard]]
  auto parseCommand(const std::string& input) -> std::optional<Command>
  {
    // All lowercase for case-insensitivity
    std::transform(input.begin(), input.end(), input.begin(), tolower);

    if (input == getCommandString(Command::HELP)) { return Command::HELP; }

    // Print error and return nullopt
    printInputError(GET_INVALID_COMMAND_MSG(input));
    return std::nullopt;
  }

  [[nodiscard]]
  auto parseOptions(std::istringstream& inputStream) -> std::vector<Option>
  {
    std::vector<Option> options;
    std::string         optionInput;
    while (inputStream >> optionInput)
    {
      // All lowercase for case-insensitivity
      std::transform(
        optionInput.begin(), optionInput.end(), optionInput.begin(), tolower
      );

      // Must start with '--'
      if (not optionInput.starts_with("--"))
      {
        printInputWarning(GET_OPTION_MISSING_PREFIX_MSG());
        continue;
      }

      if (optionInput == getOptionString(Option::HELP))
      {
        options.push_back(Option::HELP);
        continue;
      }
    }

    return options;
  }
} // namespace IO::_internal
