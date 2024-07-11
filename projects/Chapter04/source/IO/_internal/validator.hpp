#pragma once

#include "Foundation/types.hpp"

#include "IO/io.hpp"

#include <set>

namespace IO::_internal
{
  [[nodiscard]]
  auto validateRequest(Command command, std::set<Option>& options) -> fn::bln;
} // namespace IO::_internal
