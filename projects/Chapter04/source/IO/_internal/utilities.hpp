#pragma once

#include "Foundation/types.hpp"

namespace IO::_internal
{
  [[nodiscard]]
  auto isNotAllowedCharacter(fn::cdef character) noexcept -> fn::bln;
  auto resetInputBuffer() -> void;
} // namespace IO::_internal
