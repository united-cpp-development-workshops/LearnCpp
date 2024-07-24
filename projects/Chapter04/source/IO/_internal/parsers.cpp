#include "pch.hpp"

#include "IO/_internal/parsers.hpp"

#include "IO/_internal/messages.ipp"
#include "IO/_internal/prints.hpp"
#include "IO/io.hpp"

#include <algorithm>
#include <cctype>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>

namespace IO::_internal
{
  [[nodiscard]] auto getCommandMap()
    -> const std::unordered_map<Command, std::string>&
  {
    // Using declarations
    using enum Command;

    // Command map
    // NOLINTNEXTLINE(clang-diagnostic-exit-time-destructors)
    static const std::unordered_map<Command, std::string> s_commandMap{
      {HELP,     "help"    },
      {PLATFORM, "platform"},
      {EXPLORE,  "explore" },
      {COMPARE,  "compare" },
      {EXIT,     "exit"    }
    };

    // Return command map
    return s_commandMap;
  }

  [[nodiscard]] auto getOptionMap()
    -> const std::unordered_map<Option, std::string>&
  {
    // Using declarations
    using enum Option;

    // Option map
    // NOLINTNEXTLINE(clang-diagnostic-exit-time-destructors)
    static const std::unordered_map<Option, std::string> s_optionMap{
      {HELP,     "help"    },
      {COMPILER, "compiler"},
      {LANGUAGE, "language"},
      {ARCH,     "arch"    },
      {OS,       "os"      },
      {T_NONE,   "none"    },
      {T_IPTR,   "iptr"    },
      {T_UPTR,   "uptr"    },
      {T_NPTR,   "nptr"    },
      {T_BLN,    "bln"     },
      {T_I8,     "i8"      },
      {T_I16,    "i16"     },
      {T_I32,    "i32"     },
      {T_I64,    "i64"     },
      {T_U8,     "u8"      },
      {T_U16,    "u16"     },
      {T_U32,    "u32"     },
      {T_U64,    "u64"     },
      {T_I8L,    "i8l"     },
      {T_I16L,   "i16l"    },
      {T_I32L,   "i32l"    },
      {T_I64L,   "i64l"    },
      {T_U8L,    "u8l"     },
      {T_U16L,   "u16l"    },
      {T_U32L,   "u32l"    },
      {T_U64L,   "u64l"    },
      {T_I8F,    "i8f"     },
      {T_I16F,   "i16f"    },
      {T_I32F,   "i32f"    },
      {T_I64F,   "i64f"    },
      {T_U8F,    "u8f"     },
      {T_U16F,   "u16f"    },
      {T_U32F,   "u32f"    },
      {T_U64F,   "u64f"    },
      {T_IDEF,   "idef"    },
      {T_UDEF,   "udef"    },
      {T_IMAX,   "imax"    },
      {T_UMAX,   "umax"    },
      {T_SIZE,   "size"    },
      {T_F32,    "f32"     },
      {T_F64,    "f64"     },
      {T_FMAX,   "fmax"    },
      {T_C8,     "c8"      },
      {T_C16,    "c16"     },
      {T_C32,    "c32"     },
      {T_CDEF,   "cdef"    },
      {T_WDEF,   "wdef"    }
    };

    // Return option map
    return s_optionMap;
  }

  [[nodiscard]] auto parseCommand(std::string& input) -> std::optional<Command>
  {
    // Reduce verbosity with "using enum" directives.
    using enum Command;

    // All lowercase for case-insensitivity
    std::ranges::transform(input, input.begin(), std::tolower);

    // Get command map
    const auto& commandMap{getCommandMap()};

    // Check if command was found
    if (const auto& it{std::ranges::find(
          commandMap,
          input,
          &std::unordered_map<Command, std::string>::value_type::second
        )};
        it != commandMap.end())
    {
      // Return command
      return it->first;
    }

    // Print error and return nullopt
    printInputError(GET_INVALID_COMMAND_MSG(input));
    return std::nullopt;
  }

  [[nodiscard]] auto parseOptions(std::istringstream& inputStream
  ) -> std::set<Option>
  {
    // Reduce verbosity with "using enum" directives.
    using enum Option;

    // Create vector of options
    std::set<Option> options;

    // Loop through tokens
    std::string optionInput;
    while (inputStream >> optionInput)
    {
      // All lowercase for case-insensitivity
      std::ranges::transform(optionInput, optionInput.begin(), std::tolower);

      // Must start with '--'
      if (not optionInput.starts_with("--"))
      {
        printInputWarning(GET_MISSING_OPTION_PREFIX_MSG());
        continue;
      }

      // Get option map
      const auto& optionMap{getOptionMap()};

      // Check if option was found
      if (const auto& it{std::ranges::find(
            optionMap,
            optionInput.substr(2),
            &std::unordered_map<Option, std::string>::value_type::second
          )};
          it != optionMap.end())
      {
        // Ensure option is not already present
        if (options.contains(it->first))
        {
          IO::_internal::printInputWarning(
            IO::_internal::GET_DUPLICATE_OPTION_MSG(it->second)
          );
          continue;
        }

        // Insert option
        options.insert(it->first);
        continue;
      }

      // Print warning
      printInputWarning(GET_INVALID_OPTION_MSG(optionInput));
    }

    // Return all options
    return options;
  }
} // namespace IO::_internal
