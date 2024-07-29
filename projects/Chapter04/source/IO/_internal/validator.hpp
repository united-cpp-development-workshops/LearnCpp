#pragma once

#include "IO/io.hpp"

#include <Foundation/types.hpp>

#include <set>
#include <utility>

namespace IO::_internal
{
  inline constexpr fn::u16f COMPARE_MIN_OPTIONS{2};

  [[nodiscard]] auto getCommandPriorityOptions(const IO::Command command
  ) -> std::set<IO::Option>;
  [[nodiscard]] auto getCommandRules(const IO::Command command
  ) -> std::pair<std::set<IO::Option>, std::pair<fn::u16f, fn::u16f>>;
  [[nodiscard]] auto validateRequest(Command command, std::set<Option>& options)
    -> fn::bln;
} // namespace IO::_internal
