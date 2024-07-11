#pragma once

#include "IO/io.hpp"

#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>

namespace IO::_internal
{
  [[nodiscard]]
  constexpr auto GET_COMMAND_STR(Command input) -> std::string;
  [[nodiscard]]
  constexpr auto GET_OPTION_STR(Option input) -> std::string;
  [[nodiscard]]
  auto parseCommand(std::string& input) -> std::optional<Command>;
  [[nodiscard]]
  auto parseOptions(std::istringstream& inputStream) -> std::set<Option>;
} // namespace IO::_internal

/*----------------------------------------------------------------------------*\
*| >>>>>>>>>>>>>>>>>>>>>>>>>>>>> Implementation <<<<<<<<<<<<<<<<<<<<<<<<<<<<< |*
\*----------------------------------------------------------------------------*/

namespace IO::_internal
{
  [[nodiscard]]
  constexpr auto GET_COMMAND_STR(Command input) -> std::string
  {
    switch (input)
    {
    case Command::HELP    : return "help";
    case Command::PLATFORM: return "platform";
    case Command::EXPLORE : return "explore";
    case Command::COMPARE : return "compare";
    case Command::EXIT    : return "exit";
    }

    // Should never reach here
    throw std::logic_error{"Invalid command!"};
  }

  [[nodiscard]]
  constexpr auto GET_OPTION_STR(Option input) -> std::string
  {
    switch (input)
    {
    case Option::HELP    : return "--help";
    case Option::COMPILER: return "--compiler";
    case Option::LANGUAGE: return "--language";
    case Option::ARCH    : return "--arch";
    case Option::OS      : return "--os";
    case Option::T_NONE  : return "--none";
    case Option::T_IPTR  : return "--iptr";
    case Option::T_UPTR  : return "--uptr";
    case Option::T_NPTR  : return "--nptr";
    case Option::T_BLN   : return "--bln";
    case Option::T_I8    : return "--i8";
    case Option::T_I16   : return "--i16";
    case Option::T_I32   : return "--i32";
    case Option::T_I64   : return "--i64";
    case Option::T_U8    : return "--u8";
    case Option::T_U16   : return "--u16";
    case Option::T_U32   : return "--u32";
    case Option::T_U64   : return "--u64";
    case Option::T_I8L   : return "--i8l";
    case Option::T_I16L  : return "--i16l";
    case Option::T_I32L  : return "--i32l";
    case Option::T_I64L  : return "--i64l";
    case Option::T_U8L   : return "--u8l";
    case Option::T_U16L  : return "--u16l";
    case Option::T_U32L  : return "--u32l";
    case Option::T_U64L  : return "--u64l";
    case Option::T_I8F   : return "--i8f";
    case Option::T_I16F  : return "--i16f";
    case Option::T_I32F  : return "--i32f";
    case Option::T_I64F  : return "--i64f";
    case Option::T_U8F   : return "--u8f";
    case Option::T_U16F  : return "--u16f";
    case Option::T_U32F  : return "--u32f";
    case Option::T_U64F  : return "--u64f";
    case Option::T_IDEF  : return "--idef";
    case Option::T_UDEF  : return "--udef";
    case Option::T_IMAX  : return "--imax";
    case Option::T_UMAX  : return "--umax";
    case Option::T_SIZE  : return "--size";
    case Option::T_F32   : return "--f32";
    case Option::T_F64   : return "--f64";
    case Option::T_FMAX  : return "--fmax";
    case Option::T_C8    : return "--c8";
    case Option::T_C16   : return "--c16";
    case Option::T_C32   : return "--c32";
    case Option::T_CDEF  : return "--cdef";
    case Option::T_WDEF  : return "--wdef";
    }

    // Should never reach here
    throw std::logic_error{"Invalid option!"};
  }
} // namespace IO::_internal
