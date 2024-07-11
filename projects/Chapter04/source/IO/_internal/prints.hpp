#pragma once

#include "Foundation/types.hpp"

#include <string>

namespace IO::_internal
{
  auto printBriefInfo() -> fn::none;
  auto printBriefHelp() -> fn::none;
  auto printInputError(const std::string& message) -> fn::none;
  auto printInputWarning(const std::string& message) -> fn::none;
} // namespace IO::_internal
