#pragma once

#include <Foundation/types.hpp>

namespace IO::_internal
{
  auto printBriefInfo() -> fn::none;
  auto printBriefHelp() -> fn::none;
  auto printInputError(fn::strv message) -> fn::none;
  auto printInputWarning(fn::strv message) -> fn::none;
  auto printLeftAligned(fn::strv text, fn::size width) -> fn::none;
} // namespace IO::_internal
