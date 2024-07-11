#include "pch.hpp"

#include "IO/_internal/validator.hpp"

#include "Foundation/types.hpp"

#include "IO/_internal/messages.ipp"
#include "IO/_internal/parsers.ipp"
#include "IO/_internal/prints.hpp"
#include "IO/io.hpp"

#include <algorithm>
#include <limits>
#include <set>
#include <utility>

namespace
{
  [[nodiscard]]
  auto getCommandPriorityOptions(IO::Command command) -> std::set<IO::Option>
  {
    switch (command)
    {
    case IO::Command::HELP:
    case IO::Command::PLATFORM:
    case IO::Command::EXPLORE:
    case IO::Command::COMPARE:
    case IO::Command::EXIT:
    {
      return {IO::Option::HELP};
    }
    }

    // Should never reach here
    throw std::logic_error{"Invalid command!"};
  }

  [[nodiscard]]
  auto getCommandRules(IO::Command command
  ) -> std::pair<std::set<IO::Option>, std::pair<fn::u16f, fn::u16f>>
  {
    switch (command)
    {
    case IO::Command::HELP:
    {
      return {
        {},
        {{0}, {0}}
      };
    }
    case IO::Command::PLATFORM:
    {
      return {
        {IO::Option::COMPILER,
         IO::Option::LANGUAGE,
         IO::Option::ARCH,
         IO::Option::OS},
        {{0}, std::numeric_limits<fn::u16f>::max()}
      };
    }
    case IO::Command::EXPLORE:
    {
      return {
        {IO::Option::T_NONE, IO::Option::T_IPTR, IO::Option::T_UPTR,
         IO::Option::T_NPTR, IO::Option::T_BLN,  IO::Option::T_I8,
         IO::Option::T_I16,  IO::Option::T_I32,  IO::Option::T_I64,
         IO::Option::T_U8,   IO::Option::T_U16,  IO::Option::T_U32,
         IO::Option::T_U64,  IO::Option::T_I8L,  IO::Option::T_I16L,
         IO::Option::T_I32L, IO::Option::T_I64L, IO::Option::T_U8L,
         IO::Option::T_U16L, IO::Option::T_U32L, IO::Option::T_U64L,
         IO::Option::T_I8F,  IO::Option::T_I16F, IO::Option::T_I32F,
         IO::Option::T_I64F, IO::Option::T_U8F,  IO::Option::T_U16F,
         IO::Option::T_U32F, IO::Option::T_U64F, IO::Option::T_IDEF,
         IO::Option::T_UDEF, IO::Option::T_IMAX, IO::Option::T_UMAX,
         IO::Option::T_SIZE, IO::Option::T_F32,  IO::Option::T_F64,
         IO::Option::T_FMAX, IO::Option::T_C8,   IO::Option::T_C16,
         IO::Option::T_C32,  IO::Option::T_CDEF, IO::Option::T_WDEF},
        {{1}, {1}}
      };
    }
    case IO::Command::COMPARE:
    {
      return {
        {IO::Option::T_NONE, IO::Option::T_IPTR, IO::Option::T_UPTR,
         IO::Option::T_NPTR, IO::Option::T_BLN,  IO::Option::T_I8,
         IO::Option::T_I16,  IO::Option::T_I32,  IO::Option::T_I64,
         IO::Option::T_U8,   IO::Option::T_U16,  IO::Option::T_U32,
         IO::Option::T_U64,  IO::Option::T_I8L,  IO::Option::T_I16L,
         IO::Option::T_I32L, IO::Option::T_I64L, IO::Option::T_U8L,
         IO::Option::T_U16L, IO::Option::T_U32L, IO::Option::T_U64L,
         IO::Option::T_I8F,  IO::Option::T_I16F, IO::Option::T_I32F,
         IO::Option::T_I64F, IO::Option::T_U8F,  IO::Option::T_U16F,
         IO::Option::T_U32F, IO::Option::T_U64F, IO::Option::T_IDEF,
         IO::Option::T_UDEF, IO::Option::T_IMAX, IO::Option::T_UMAX,
         IO::Option::T_SIZE, IO::Option::T_F32,  IO::Option::T_F64,
         IO::Option::T_FMAX, IO::Option::T_C8,   IO::Option::T_C16,
         IO::Option::T_C32,  IO::Option::T_CDEF, IO::Option::T_WDEF},
        {{2}, std::numeric_limits<fn::u16f>::max()}
      };
    }
    case IO::Command::EXIT:
    {
      return {
        {},
        {{0}, {0}}
      };
    }
    }

    // Should never reach here
    throw std::logic_error{"Invalid command!"};
  }
} // namespace

namespace IO::_internal
{
  [[nodiscard]]
  auto validateRequest(Command command, std::set<Option>& options) -> fn::bln
  {
    // Create options set for sanitization
    std::set<Option> sanitizedOptions;

    // Get priority options
    const auto priorityOptions{getCommandPriorityOptions(command)};

    // Traverse priority options
    fn::bln hasPriorityOptions{false};
    for (const auto& priorityOption : priorityOptions)
    {
      // Check if priority option is present
      if (std::ranges::find(options, priorityOption) != options.end())
      {
        // Set has priority option to true
        hasPriorityOptions = {true};

        // Remove priority option from options and add to sanitized options
        options.erase(priorityOption);
        sanitizedOptions.insert(priorityOption);
      }
    }

    // If priority option present, we discard all other options
    if (not hasPriorityOptions)
    {
      // Get command rules
      const auto [commandOptions, countLimits]{getCommandRules(command)};

      // Traverse command options
      for (const auto& commandOption : commandOptions)
      {
        // Check if command option is present
        const fn::bln commandOptionFound{
          std::ranges::find(options, commandOption) != options.end()
        };

        // Check limits
        if (sanitizedOptions.size() + 1 <= countLimits.second
            and commandOptionFound)
        {
          // Remove command option from options and add to sanitized options
          options.erase(commandOption);
          sanitizedOptions.insert(commandOption);
        }
        else if (commandOptionFound)
        {
          // Print warning message
          printInputWarning(
            GET_DISCARDED_OPTION_BY_LIMIT_MSG(GET_OPTION_STR(commandOption))
          );

          // Remove command option from options
          options.erase(commandOption);
        }
      }

      // Check if command options are in limit
      if (sanitizedOptions.size() < countLimits.first)
      {
        // Print warning message
        printInputError(GET_INSUFFICIENT_OPTIONS_MSG(GET_COMMAND_STR(command)));

        // Return false
        return false;
      }
    }

    // Give warnings about discarded options
    for (const auto& option : options)
    {
      // Print warning message
      printInputWarning(GET_DISCARDED_OPTION_MSG(GET_OPTION_STR(option)));
    }

    // Move sanitized options to options and return true
    options = {std::move(sanitizedOptions)};
    return true;
  }
} // namespace IO::_internal
