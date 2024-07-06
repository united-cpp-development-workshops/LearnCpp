#pragma once

#include <string>

namespace IO::_internal
{
  auto printBriefHelp() -> void;
  auto printInputError(const std::string& message) -> void;
  auto printInputWarning(const std::string& message) -> void;
} // namespace IO::_internal
