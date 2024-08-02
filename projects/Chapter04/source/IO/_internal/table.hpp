#pragma once

#include "IO/io.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>

namespace IO::_internal
{
  inline constexpr fn::strv TYPE_NAME{"TYPE"};
  inline constexpr fn::strv OPTIONAL{"OPTIONAL"};
  inline constexpr fn::strv HEADER{"HEADER"};
  inline constexpr fn::strv STANDARD_SIZE{"SIZE: STANDARD"};
  inline constexpr fn::strv PLATFORM_SIZE{"SIZE: PLATFORM"};
  inline constexpr fn::strv SIGNEDNESS{"SIGNEDNESS"};
  inline constexpr fn::strv MIN_VALUE{"MIN VALUE"};
  inline constexpr fn::strv MAX_VALUE{"MAX VALUE"};
  inline constexpr fn::strv PRECISION{"PRECISSION"};
  inline constexpr fn::strv SUFFIX{"SUFFIX"};

  auto printTypeTable(Option option) -> fn::none;
  auto printTypeTable(const fn::set<Option>& options) -> fn::none;
} // namespace IO::_internal
