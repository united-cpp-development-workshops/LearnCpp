#pragma once

#include "IO/io.hpp"

#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace IO::_internal
{
  [[nodiscard]]
  auto getCommandMap() -> const std::unordered_map<Command, std::string>&;
  [[nodiscard]]
  auto getOptionMap() -> const std::unordered_map<Option, std::string>&;
  [[nodiscard]]
  auto parseCommand(std::string& input) -> std::optional<Command>;
  [[nodiscard]]
  auto parseOptions(std::istringstream& inputStream) -> std::set<Option>;
} // namespace IO::_internal
