#pragma once

#include "Foundation/types.hpp"

namespace IO::_internal
{
  [[nodiscard]]
  auto isNotAllowedCharacter(fn::cdef character) noexcept -> fn::bln;
  auto resetInputBuffer() -> fn::none;
} // namespace IO::_internal
