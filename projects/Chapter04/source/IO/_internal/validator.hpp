#pragma once

#include "IO/io.hpp"

#include <Foundation/types.hpp>

#include <set>

namespace IO::_internal
{
  inline constexpr fn::u16f COMPARE_MIN_OPTIONS{2};

  [[nodiscard]] auto validateRequest(Command command, std::set<Option>& options)
    -> fn::bln;
} // namespace IO::_internal
