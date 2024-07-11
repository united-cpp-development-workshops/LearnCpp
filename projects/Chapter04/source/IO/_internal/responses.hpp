#pragma once

#include "Foundation/types.hpp"

#include "IO/io.hpp"

#include <set>

namespace IO::_internal
{
  auto helpResponse(const std::set<Option>& options) -> fn::none;
  auto platformResponse(const std::set<Option>& options) -> fn::none;
  auto exploreResponse(const std::set<Option>& options) -> fn::none;
  auto compareResponse(const std::set<Option>& options) -> fn::none;
  auto exitResponse(const std::set<Option>& options) -> fn::none;
} // namespace IO::_internal
