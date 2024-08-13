#pragma once

#include <Foundation/types.hpp>

namespace Utility
{
  [[nodiscard]] auto formatBlock(fn::str&& tempString, const fn::ptrd blockSize) -> fn::str;
} // namespace Utility
