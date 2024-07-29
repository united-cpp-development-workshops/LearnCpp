#pragma once

#include <Foundation/types.hpp>

#include <string>

namespace IO::_internal
{
  auto printBriefInfo() -> fn::none;
  auto printBriefHelp() -> fn::none;
  auto printInputError(const std::string& message) -> fn::none;
  auto printInputWarning(const std::string& message) -> fn::none;
  auto printLeftAligned(const std::string& text, fn::size width) -> fn::none;
} // namespace IO::_internal
