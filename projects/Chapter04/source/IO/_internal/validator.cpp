#include "pch.hpp"

#include "IO/_internal/validator.hpp"

#include "IO/_internal/messages.ipp"
#include "IO/_internal/parsers.hpp"
#include "IO/_internal/prints.hpp"
#include "IO/io.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/errors.hpp>
#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>

#include <algorithm>
#include <limits>

namespace IO::_internal
{
  [[nodiscard]] auto getCommandPriorityOptions(const IO::Command command) -> fn::set<IO::Option>
  {
    // Using declarations
    using enum IO::Command;

    switch (command)
    {
    case HELP:
    case PLATFORM:
    case EXPLORE:
    case TIPS:
    case METRICS:
    {
      return {IO::Option::HELP};
    }
    case COMPARE:
    {
      return {IO::Option::HELP, IO::Option::T_ALL};
    }
    case EXIT:
    {
      return {IO::Option::HELP};
    }
    }

    // Should never reach here
    throw fn::EnumeratorError{};
  }

  [[nodiscard]] auto getCommandRules(const IO::Command command
  ) -> fn::pair<fn::set<IO::Option>, fn::pair<fn::u16f, fn::u16f>>
  {
    // Using declarations
    using enum IO::Option;

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
        {COMPILER, LANGUAGE, ARCH, OS},
        {{0}, std::numeric_limits<fn::u16f>::max()}
      };
    }
    case IO::Command::EXPLORE:
    case IO::Command::TIPS:
    case IO::Command::METRICS:
    {
      return {
        {T_NONE, T_IPTR, T_UPTR, T_NPTR, T_BLN,  T_I8,   T_I16,  T_I32,  T_I64,  T_U8,   T_U16,
         T_U32,  T_U64,  T_I8L,  T_I16L, T_I32L, T_I64L, T_U8L,  T_U16L, T_U32L, T_U64L, T_I8F,
         T_I16F, T_I32F, T_I64F, T_U8F,  T_U16F, T_U32F, T_U64F, T_IDEF, T_UDEF, T_IMAX, T_UMAX,
         T_SIZE, T_F32,  T_F64,  T_FMAX, T_C8,   T_C16,  T_C32,  T_CDEF, T_WDEF},
        {{1}, {1}}
      };
    }
    case IO::Command::COMPARE:
    {
      return {
        {T_NONE, T_IPTR, T_UPTR, T_NPTR, T_BLN,  T_I8,   T_I16,  T_I32,  T_I64,  T_U8,   T_U16,
         T_U32,  T_U64,  T_I8L,  T_I16L, T_I32L, T_I64L, T_U8L,  T_U16L, T_U32L, T_U64L, T_I8F,
         T_I16F, T_I32F, T_I64F, T_U8F,  T_U16F, T_U32F, T_U64F, T_IDEF, T_UDEF, T_IMAX, T_UMAX,
         T_SIZE, T_F32,  T_F64,  T_FMAX, T_C8,   T_C16,  T_C32,  T_CDEF, T_WDEF},
        {IO::_internal::COMPARE_MIN_OPTIONS, std::numeric_limits<fn::u16f>::max()}
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
    throw fn::EnumeratorError{};
  }

  [[nodiscard]] auto validateRequest(const Command command, fn::set<Option>& options) -> fn::bln
  {
    // Create options set for sanitization
    fn::set<Option> sanitizedOptions;

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
        if (std::ranges::find(options, commandOption) == options.end())
        {
          continue;
        }

        // Check limits
        if ((sanitizedOptions.size() + 1) <= countLimits.second)
        {
          // Remove command option from options and add to sanitized options
          options.erase(commandOption);
          sanitizedOptions.insert(commandOption);
        }
        else
        {
          // Print warning message
          printInputWarning(discardedOptByLimitMsg(getOptionMap().find(commandOption)->second));

          // Remove command option from options
          options.erase(commandOption);
        }
      }

      // Check if command options are in limit
      if (sanitizedOptions.size() < countLimits.first)
      {
        // Print warning message
        printInputError(insufficientOptMsg(getCommandMap().find(command)->second));

        // Return false
        return false;
      }
    }

    // Give warnings about discarded options
    for (const auto& option : options)
    {
      // Print warning message
      printInputWarning(discardedOptMsg(getOptionMap().find(option)->second));
    }

    // Move sanitized options to options and return true
    options = {std::move(sanitizedOptions)};
    return true;
  }
} // namespace IO::_internal
