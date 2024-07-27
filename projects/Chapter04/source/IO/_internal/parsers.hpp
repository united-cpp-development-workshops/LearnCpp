#pragma once

#include "IO/io.hpp"

#include <Foundation/types.hpp>

#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace IO::_internal
{
  inline constexpr fn::f32 AUTO_FIX_THRESHOLD{0.75f};
  inline constexpr fn::f32 SUGGEST_THRESHOLD{2.5f};

  [[nodiscard]] auto getCommandMap()
    -> const std::unordered_map<Command, std::string>&;
  [[nodiscard]] auto getOptionMap()
    -> const std::unordered_map<Option, std::string>&;
  [[nodiscard]] auto parseCommand(std::string& token) -> std::optional<Command>;
  [[nodiscard]] auto invalidCommandHandler(const std::string& token
  ) -> std::optional<Command>;
  [[nodiscard]] auto parseOptions(std::istringstream& inputStream
  ) -> std::set<Option>;
  auto invalidOptionHandler(const std::string& token, std::set<Option>& options)
    -> fn::none;
} // namespace IO::_internal
