#pragma once

#include "IO/io.hpp"

#include <Foundation/types.hpp>

#include <set>

namespace IO::_internal
{
  [[nodiscard]] auto validateRequest(Command command, std::set<Option>& options)
    -> fn::bln;
} // namespace IO::_internal
