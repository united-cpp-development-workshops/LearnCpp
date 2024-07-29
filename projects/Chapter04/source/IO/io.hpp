#pragma once

#include <Foundation/types.hpp>

#include <optional>
#include <set>
#include <string>
#include <utility>

namespace IO
{
  enum class Command : fn::u8f
  {
    HELP,
    PLATFORM,
    EXPLORE,
    TIPS,
    METRICS,
    COMPARE,
    EXIT
  };

  enum class Option : fn::u8f
  {
    HELP,
    COMPILER,
    LANGUAGE,
    ARCH,
    OS,
    T_ALL,
    T_NONE,
    T_IPTR,
    T_UPTR,
    T_NPTR,
    T_BLN,
    T_I8,
    T_I16,
    T_I32,
    T_I64,
    T_U8,
    T_U16,
    T_U32,
    T_U64,
    T_I8L,
    T_I16L,
    T_I32L,
    T_I64L,
    T_U8L,
    T_U16L,
    T_U32L,
    T_U64L,
    T_I8F,
    T_I16F,
    T_I32F,
    T_I64F,
    T_U8F,
    T_U16F,
    T_U32F,
    T_U64F,
    T_IDEF,
    T_UDEF,
    T_IMAX,
    T_UMAX,
    T_SIZE,
    T_F32,
    T_F64,
    T_FMAX,
    T_C8,
    T_C16,
    T_C32,
    T_CDEF,
    T_WDEF
  };

  auto               printIntroduction() -> fn::none;
  auto               printPrompt() -> fn::none;
  [[nodiscard]] auto readInput() -> std::string;
  [[nodiscard]] auto parseInput(std::string& input
  ) -> std::optional<std::pair<Command, std::set<Option>>>;
  auto printResponse(Command command, const std::set<Option>& options)
    -> fn::none;
} // namespace IO
