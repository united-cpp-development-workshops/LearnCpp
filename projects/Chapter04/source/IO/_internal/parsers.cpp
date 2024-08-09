#include "pch.hpp"

#include "IO/_internal/parsers.hpp"

#include "IO/_internal/messages.ipp"
#include "IO/_internal/prints.hpp"
#include "IO/_internal/suggest.hpp"
#include "IO/io.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/utilities.hpp>

#include <algorithm>
#include <locale>
#include <sstream>

namespace IO::_internal
{
  [[nodiscard]] auto getCommandMap() -> const fn::umap<Command, fn::str>&
  {
    // Using declarations
    using enum Command;

    // Command map
    // NOLINTNEXTLINE(clang-diagnostic-exit-time-destructors)
    static const fn::umap<Command, fn::str> s_commandMap{
      {HELP,     "help"    },
      {PLATFORM, "platform"},
      {EXPLORE,  "explore" },
      {TIPS,     "tips"    },
      {METRICS,  "metrics" },
      {COMPARE,  "compare" },
      {EXIT,     "exit"    }
    };

    // Return command map
    return s_commandMap;
  }

  [[nodiscard]] auto getOptionMap() -> const fn::umap<Option, fn::str>&
  {
    // Using declarations
    using enum Option;

    // Option map
    // NOLINTNEXTLINE(clang-diagnostic-exit-time-destructors)
    static const fn::umap<Option, fn::str> s_optionMap{
      {HELP,     "help"    },
      {COMPILER, "compiler"},
      {LANGUAGE, "language"},
      {ARCH,     "arch"    },
      {OS,       "os"      },
      {T_ALL,    "all"     },
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

  [[nodiscard]] auto parseCommand(fn::str& token) -> fn::opt<Command>
  {
    // All lowercase for case-insensitivity
    std::ranges::transform(
      token,
      token.begin(),
      [](const fn::cdef character) -> fn::cdef
      {
        return std::tolower(character, std::locale());
      }
    );

    // Get command map
    const auto& commandMap{getCommandMap()};

    // Check if command was found
    if (const auto& it{
          std::ranges::find(commandMap, token, &fn::umap<Command, fn::str>::value_type::second)
        };
        it != commandMap.end())
    {
      // Return command
      return it->first;
    }

    return invalidCmdHandler(token);
  }

  [[nodiscard]] auto invalidCmdHandler(const fn::strv token) -> fn::opt<Command>
  {
    // Get command map
    const auto& commandMap{getCommandMap()};

    // Find the closest command
    if (const auto closest{std::ranges::min_element(
          commandMap,
          [&token](const auto& a, const auto& b) -> fn::f32
          {
            return editDistance(a.second, token) < editDistance(b.second, token);
          }
        )};
        closest != commandMap.end())
    {
      // Find distance
      const auto distance{editDistance(closest->second, token)};

      if (distance < AUTO_FIX_THRESHOLD)
      {
        printInputWarning(autofixCmdMsg(token, closest->second));
        return closest->first;
      }

      if (distance < SUGGEST_THRESHOLD)
      {
        printInputError(invalidCmdSuggestMsg(token, closest->second));
      }
      else
      {
        printInputError(invalidCmdMsg(token));
      }
    }
    else
    {
      printInputError(invalidCmdMsg(token));
    }

    return std::nullopt;
  }

  [[nodiscard]] auto parseOptions(std::istringstream& inputStream) -> fn::set<Option>
  {
    // Reduce verbosity with "using enum" directives.
    using enum Option;

    // Create vector of options
    fn::set<Option> options;

    // Loop through tokens
    fn::str token;
    while (inputStream >> token)
    {
      // All lowercase for case-insensitivity
      std::ranges::transform(
        token,
        token.begin(),
        [](const fn::cdef character) -> fn::cdef
        {
          return std::tolower(character, std::locale());
        }
      );

      // Must start with '-'
      if (not token.starts_with("-"))
      {
        printInputWarning(MISSING_OPT_PREFIX_MSG().data());
        continue;
      }

      // Remove leading '-'
      token.erase(
        token.begin(),
        std::ranges::find_if_not(
          token,
          [](const fn::cdef c) -> fn::bln
          {
            return c == '-';
          }
        )
      );

      // Get option map
      const auto& optionMap{getOptionMap()};

      // Check if option was found
      if (const auto& it{
            std::ranges::find(optionMap, token, &fn::umap<Option, fn::str>::value_type::second)
          };
          it != optionMap.end())
      {
        // Ensure option is not already present
        if (options.contains(it->first))
        {
          IO::_internal::printInputWarning(IO::_internal::duplicateOptMsg(it->second));
          continue;
        }

        // Insert option
        options.insert(it->first);
      }
      else
      {
        invalidOptHandler(token, options);
      }
    }

    // Return all options
    return options;
  }

  auto invalidOptHandler(const fn::strv token, fn::set<Option>& options) -> fn::none
  {
    // Get option map
    const auto& optionMap{getOptionMap()};

    // Find the closest option
    if (const auto closest{std::ranges::min_element(
          optionMap,
          [&token](const auto& a, const auto& b) -> fn::f32
          {
            return editDistance(a.second, token) < editDistance(b.second, token);
          }
        )};
        closest != optionMap.end())
    {
      // Find distance
      const auto distance{editDistance(closest->second, token)};

      if (distance < AUTO_FIX_THRESHOLD)
      {
        // Ensure option is not already present to use it
        if (options.contains(closest->first))
        {
          // Suggest but discard
          printInputWarning(invalidOptSuggestMsg(token, closest->second));
        }
        else
        {
          // Warn and use closest option
          printInputWarning(autofixOptMsg(token, closest->second));

          // Insert closest option
          options.insert(closest->first);
        }
      }
      else if (distance < SUGGEST_THRESHOLD)
      {
        printInputWarning(invalidOptSuggestMsg(token, closest->second));
      }
      else
      {
        printInputWarning(invalidOptMsg(token));
      }
    }
    else
    {
      printInputWarning(invalidOptMsg(token));
    }
  }
} // namespace IO::_internal
