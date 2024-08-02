#pragma once

#include <Foundation/types.hpp>

namespace IO::_internal
{
  [[nodiscard]] auto editDistance(fn::strv subject, fn::strv candidate) -> fn::f32;
} // namespace IO::_internal
