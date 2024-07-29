#pragma once

#include "IO/io.hpp"

#include <Foundation/types.hpp>

namespace IO::_internal
{
  inline constexpr fn::cstr TYPE_NAME{"TYPE"};
  inline constexpr fn::cstr OPTIONAL{"OPTIONAL"};
  inline constexpr fn::cstr HEADER{"HEADER"};
  inline constexpr fn::cstr STANDARD_SIZE{"SIZE: STANDARD"};
  inline constexpr fn::cstr PLATFORM_SIZE{"SIZE: PLATFORM"};
  inline constexpr fn::cstr SIGNEDNESS{"SIGNEDNESS"};
  inline constexpr fn::cstr MIN_VALUE{"MIN VALUE"};
  inline constexpr fn::cstr MAX_VALUE{"MAX VALUE"};
  inline constexpr fn::cstr PRECISION{"PRECISSION"};
  inline constexpr fn::cstr SUFFIX{"SUFFIX"};

  auto printTypeTable(Option option) -> fn::none;
  auto printTypeTable(const std::set<Option>& options) -> fn::none;
} // namespace IO::_internal
