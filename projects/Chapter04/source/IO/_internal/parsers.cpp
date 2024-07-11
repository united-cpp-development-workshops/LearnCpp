#include "pch.hpp"

#include "IO/_internal/parsers.ipp"

#include "Foundation/types.hpp"

#include "IO/_internal/messages.ipp"
#include "IO/_internal/prints.hpp"
#include "IO/io.hpp"

#include <algorithm>
#include <cctype>
#include <optional>
#include <set>
#include <sstream>
#include <string>

namespace
{
  auto insertOption(IO::Option option, std::set<IO::Option>& options)
    -> fn::none
  {
    // Ensure option is not already present
    if (options.contains(option))
    {
      IO::_internal::printInputWarning(IO::_internal::GET_DUPLICATE_OPTION_MSG(
        IO::_internal::GET_OPTION_STR(option)
      ));
      return;
    }

    // Insert option
    options.insert(option);
  }
} // namespace

namespace IO::_internal
{
  [[nodiscard]]
  auto parseCommand(std::string& input) -> std::optional<Command>
  {
    // All lowercase for case-insensitivity
    std::ranges::transform(input, input.begin(), tolower);

    // Match command
    if (input == GET_COMMAND_STR(Command::HELP)) { return Command::HELP; }
    if (input == GET_COMMAND_STR(Command::PLATFORM))
    {
      return Command::PLATFORM;
    }
    if (input == GET_COMMAND_STR(Command::EXPLORE)) { return Command::EXPLORE; }
    if (input == GET_COMMAND_STR(Command::COMPARE)) { return Command::COMPARE; }
    if (input == GET_COMMAND_STR(Command::EXIT)) { return Command::EXIT; }

    // Print error and return nullopt
    printInputError(GET_INVALID_COMMAND_MSG(input));
    return std::nullopt;
  }

  [[nodiscard]]
  // NOLINTNEXTLINE
  auto parseOptions(std::istringstream& inputStream) -> std::set<Option>
  {
    // Create vector of options
    std::set<Option> options;

    // Loop through tokens
    std::string optionInput;
    while (inputStream >> optionInput)
    {
      // All lowercase for case-insensitivity
      std::ranges::transform(optionInput, optionInput.begin(), tolower);

      // Must start with '--'
      if (not optionInput.starts_with("--"))
      {
        printInputWarning(GET_MISSING_OPTION_PREFIX_MSG());
        continue;
      }

      // Match the option
      if (optionInput == GET_OPTION_STR(Option::HELP))
      {
        insertOption(Option::HELP, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::COMPILER))
      {
        insertOption(Option::COMPILER, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::LANGUAGE))
      {
        insertOption(Option::LANGUAGE, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::ARCH))
      {
        insertOption(Option::ARCH, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::OS))
      {
        insertOption(Option::OS, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_NONE))
      {
        insertOption(Option::T_NONE, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_IPTR))
      {
        insertOption(Option::T_IPTR, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_UPTR))
      {
        insertOption(Option::T_UPTR, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_NPTR))
      {
        insertOption(Option::T_NPTR, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_BLN))
      {
        insertOption(Option::T_BLN, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_I8))
      {
        insertOption(Option::T_I8, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_I16))
      {
        insertOption(Option::T_I16, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_I32))
      {
        insertOption(Option::T_I32, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_I64))
      {
        insertOption(Option::T_I64, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_U8))
      {
        insertOption(Option::T_U8, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_U16))
      {
        insertOption(Option::T_U16, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_U32))
      {
        insertOption(Option::T_U32, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_U64))
      {
        insertOption(Option::T_U64, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_I8L))
      {
        insertOption(Option::T_I8L, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_I16L))
      {
        insertOption(Option::T_I16L, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_I32L))
      {
        insertOption(Option::T_I32L, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_I64L))
      {
        insertOption(Option::T_I64L, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_U8L))
      {
        insertOption(Option::T_U8L, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_U16L))
      {
        insertOption(Option::T_U16L, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_U32L))
      {
        insertOption(Option::T_U32L, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_U64L))
      {
        insertOption(Option::T_U64L, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_I8F))
      {
        insertOption(Option::T_I8F, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_I16F))
      {
        insertOption(Option::T_I16F, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_I32F))
      {
        insertOption(Option::T_I32F, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_I64F))
      {
        insertOption(Option::T_I64F, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_U8F))
      {
        insertOption(Option::T_U8F, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_U16F))
      {
        insertOption(Option::T_U16F, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_U32F))
      {
        insertOption(Option::T_U32F, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_U64F))
      {
        insertOption(Option::T_U64F, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_IDEF))
      {
        insertOption(Option::T_IDEF, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_UDEF))
      {
        insertOption(Option::T_UDEF, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_IMAX))
      {
        insertOption(Option::T_IMAX, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_UMAX))
      {
        insertOption(Option::T_UMAX, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_SIZE))
      {
        insertOption(Option::T_SIZE, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_F32))
      {
        insertOption(Option::T_F32, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_F64))
      {
        insertOption(Option::T_F64, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_FMAX))
      {
        insertOption(Option::T_FMAX, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_C8))
      {
        insertOption(Option::T_C8, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_C16))
      {
        insertOption(Option::T_C16, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_C32))
      {
        insertOption(Option::T_C32, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_CDEF))
      {
        insertOption(Option::T_CDEF, options);
        continue;
      }
      if (optionInput == GET_OPTION_STR(Option::T_WDEF))
      {
        insertOption(Option::T_WDEF, options);
        continue;
      }

      // Print warning
      printInputWarning(GET_INVALID_OPTION_MSG(optionInput));
    }

    // Return all options
    return options;
  }
} // namespace IO::_internal
