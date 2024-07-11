#include "pch.hpp"

#include "IO/_internal/responses.hpp"

#include "Foundation/types.hpp"

#include "IO/_internal/platform.ipp"
#include "IO/_internal/prints.hpp"
#include "IO/_internal/types.hpp"
#include "IO/io.hpp"

#include <iostream>
#include <set>

namespace
{
  auto printCppTypeOptions() -> fn::none
  {
    std::cout << "     '--none'     - C++ type: 'void'.\n";
    std::cout << "     '--iptr'     - C++ type: 'std::intptr_t'\n";
    std::cout << "     '--uptr'     - C++ type: 'std::uintptr_t'\n";
    std::cout << "     '--nptr'     - C++ type: 'std::nullptr_t'\n";
    std::cout << "     '--bln'      - C++ type: 'bool'.\n";
    std::cout << "     '--i8'       - C++ type: 'std::int8_t'.\n";
    std::cout << "     '--i16'      - C++ type: 'std::int16_t'.\n";
    std::cout << "     '--i32'      - C++ type: 'std::int32_t'.\n";
    std::cout << "     '--i64'      - C++ type: 'std::int64_t'.\n";
    std::cout << "     '--u8'       - C++ type: 'std::uint8_t'.\n";
    std::cout << "     '--u16'      - C++ type: 'std::uint16_t'.\n";
    std::cout << "     '--u32'      - C++ type: 'std::uint32_t'.\n";
    std::cout << "     '--u64'      - C++ type: 'std::uint64_t'.\n";
    std::cout << "     '--i8l'      - C++ type: 'std::int_least8_t'.\n";
    std::cout << "     '--i16l'     - C++ type: 'std::int_least16_t'.\n";
    std::cout << "     '--i32l'     - C++ type: 'std::int_least32_t'.\n";
    std::cout << "     '--i64l'     - C++ type: 'std::int_least64_t'.\n";
    std::cout << "     '--u8l'      - C++ type: 'std::uint_least8_t'.\n";
    std::cout << "     '--u16l'     - C++ type: 'std::uint_least16_t'.\n";
    std::cout << "     '--u32l'     - C++ type: 'std::uint_least32_t'.\n";
    std::cout << "     '--u64l'     - C++ type: 'std::uint_least64_t'.\n";
    std::cout << "     '--i8f'      - C++ type: 'std::int_fast8_t'.\n";
    std::cout << "     '--i16f'     - C++ type: 'std::int_fast16_t'.\n";
    std::cout << "     '--i32f'     - C++ type: 'std::int_fast32_t'.\n";
    std::cout << "     '--i64f'     - C++ type: 'std::int_fast64_t'.\n";
    std::cout << "     '--u8f'      - C++ type: 'std::uint_fast8_t'.\n";
    std::cout << "     '--u16f'     - C++ type: 'std::uint_fast16_t'.\n";
    std::cout << "     '--u32f'     - C++ type: 'std::uint_fast32_t'.\n";
    std::cout << "     '--u64f'     - C++ type: 'std::uint_fast64_t'.\n";
    std::cout << "     '--idef'     - C++ type: 'int'.\n";
    std::cout << "     '--udef'     - C++ type: 'unsigned int'.\n";
    std::cout << "     '--imax'     - C++ type: 'std::intmax_t'.\n";
    std::cout << "     '--umax'     - C++ type: 'std::uintmax_t'.\n";
    std::cout << "     '--size'     - C++ type: 'std::size_t'.\n";
    std::cout << "     '--f32'      - C++ type: 'float'.\n";
    std::cout << "     '--f64'      - C++ type: 'double'.\n";
    std::cout << "     '--fmax'     - C++ type: 'long double'.\n";
    std::cout << "     '--c8'       - C++ type: 'char8_t'.\n";
    std::cout << "     '--c16'      - C++ type: 'char16_t'.\n";
    std::cout << "     '--c32'      - C++ type: 'char32_t'.\n";
    std::cout << "     '--cdef'     - C++ type: 'char'.\n";
    std::cout << "     '--wdef'     - C++ type: 'wchar_t'.\n";
  }
} // namespace

namespace IO::_internal
{
  auto helpResponse(const std::set<Option>& options) -> fn::none
  {
    if (options.contains(Option::HELP))
    {
      std::cout << "   :::::::::::::::::::::::::: How It Works "
                   "::::::::::::::::::::::::::\n\n";

      std::cout << "   COMMAND: 'help'\n\n";

      std::cout << "     - Displays a brief information.\n";
      std::cout << "     - Displays available commands.\n\n";

      std::cout << "   OPTIONS:\n\n";

      std::cout << "     '--help'     - Display this help message.\n";
    }
    else
    {
      printBriefInfo();

      std::cout << "   :::::::::::::::::::::::::: How It Works "
                   "::::::::::::::::::::::::::\n\n";

      std::cout << "   COMMANDS:\n\n";

      std::cout << "     'help'         - Display available commands.\n";
      std::cout << "     'platform'     - Display platform information.\n";
      std::cout << "     'explore'      - Explore a fundamental C++ type.\n";
      std::cout << "     'compare'      - Compare fundamental C++ types.\n";
      std::cout << "     'exit'         - Exit the program.\n";
    }
  }

  auto platformResponse(const std::set<Option>& options) -> fn::none
  {
    if (options.contains(Option::HELP))
    {
      std::cout << "   :::::::::::::::::::::::::: How It Works "
                   "::::::::::::::::::::::::::\n\n";

      std::cout << "   COMMAND: 'platform'\n\n";

      std::cout << "     - Displays information about the platform.\n\n";

      std::cout << "   OPTIONS:\n\n";

      std::cout << "     '--help'         - Display this help message.\n";
      std::cout
        << "     '--compiler'     - Display only the compiler information.\n";
      std::cout
        << "     '--language'     - Display only the language standard.\n";
      std::cout << "     '--arch'         - Display only the architecture "
                   "information.\n";
      std::cout << "     '--os'           - Display only the operating system "
                   "information.\n";
    }
    else if (options.empty())
    {
      std::cout << "   COMPILER: '" << GET_COMPILER_STR(GET_COMPILER()) << " v"
                << GET_COMPILER_VER_STR(GET_COMPILER()) << "'\n\n";

      std::cout << "   LANGUAGE: '" << GET_LANGUAGE_STD_STR() << "'\n\n";

      std::cout << "   ARCHITECTURE: '"
                << GET_ARCHITECTURE_STR(GET_ARCHITECTURE()) << "'\n\n";

      std::cout << "   OPERATING SYSTEM: '"
                << GET_OPERATING_SYSTEM_STR(GET_OPERATING_SYSTEM()) << "'\n";
    }
    else
    {
      // New line controller
      auto needsNewLine{false};
      if (options.contains(Option::COMPILER))
      {
        std::cout << "   COMPILER: '" << GET_COMPILER_STR(GET_COMPILER())
                  << " v" << GET_COMPILER_VER_STR(GET_COMPILER()) << "'\n";

        needsNewLine = {true};
      }
      if (options.contains(Option::LANGUAGE))
      {
        if (needsNewLine) { std::cout << '\n'; }

        std::cout << "   LANGUAGE: '" << GET_LANGUAGE_STD_STR() << "'\n";

        needsNewLine = {true};
      }
      if (options.contains(Option::ARCH))
      {
        if (needsNewLine) { std::cout << '\n'; }

        std::cout << "   ARCHITECTURE: '"
                  << GET_ARCHITECTURE_STR(GET_ARCHITECTURE()) << "'\n";

        needsNewLine = {true};
      }
      if (options.contains(Option::OS))
      {
        if (needsNewLine) { std::cout << '\n'; }

        std::cout << "   OPERATING SYSTEM: '"
                  << GET_OPERATING_SYSTEM_STR(GET_OPERATING_SYSTEM()) << "'\n";
      }
    }
  }

  auto exploreResponse(const std::set<Option>& options) -> fn::none
  {
    if (options.contains(Option::HELP))
    {
      std::cout << "   :::::::::::::::::::::::::: How It Works "
                   "::::::::::::::::::::::::::\n\n";

      std::cout << "   COMMAND: 'explore'\n\n";

      std::cout << "     - Explore fundamental types of C++.\n";
      std::cout << "     - Learn about the sizes, ranges and properties of "
                   "fundamental types.\n\n";

      std::cout << "   OPTIONS:\n\n";

      std::cout << "     '--help'     - Display this help message.\n";
      printCppTypeOptions();
    }
    else { printBriefTypeInfo(*options.begin()); }
  }

  auto compareResponse(const std::set<Option>& options) -> fn::none
  {
    if (options.contains(Option::HELP))
    {
      std::cout << "   :::::::::::::::::::::::::: How It Works "
                   "::::::::::::::::::::::::::\n\n";

      std::cout << "   COMMAND: 'compare'\n\n";

      std::cout << "     - Compare two or more fundamental C++ types.\n";
      std::cout << "     - Learn about their differences in size, range and "
                   "property.\n\n";

      std::cout << "   OPTIONS:\n\n";

      std::cout << "     '--help'     - Display this help message.\n";
      printCppTypeOptions();
    }
    else { std::cout << "NOT YET IMPLEMENTED"; }
  }

  auto exitResponse(const std::set<Option>& options) -> fn::none
  {
    if (options.contains(Option::HELP))
    {
      std::cout << "   :::::::::::::::::::::::::: How It Works "
                   "::::::::::::::::::::::::::\n\n";

      std::cout << "   COMMAND: 'exit'\n\n";

      std::cout << "     - Exits the program.\n\n";

      std::cout << "   OPTIONS:\n\n";

      std::cout << "     '--help'     - Display this help message.\n";
    }
    else
    {
      throw std::logic_error{
        "Exit command wihtout options must have been handled earlier!"
      };
    }
  }
} // namespace IO::_internal
