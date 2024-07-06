#pragma once

#include "IO/io.hpp"

#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace IO::_internal
{
  [[nodiscard]]
  auto parseCommand(const std::string& input) -> std::optional<Command>;
  [[nodiscard]]
  auto parseOptions(std::istringstream& inputStream) -> std::vector<Option>;
} // namespace IO::_internal
