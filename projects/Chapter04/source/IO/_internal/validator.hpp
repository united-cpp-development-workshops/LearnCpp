#pragma once

#include "IO/io.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>

namespace IO::_internal
{
  inline constexpr fn::u16f COMPARE_MIN_OPTIONS{2};

  [[nodiscard]] auto getCommandPriorityOptions(const IO::Command command) -> fn::set<IO::Option>;
  [[nodiscard]] auto getCommandRules(const IO::Command command
  ) -> fn::pair<fn::set<IO::Option>, fn::pair<fn::u16f, fn::u16f>>;
  [[nodiscard]] auto validateRequest(Command command, fn::set<Option>& options) -> fn::bln;
} // namespace IO::_internal
