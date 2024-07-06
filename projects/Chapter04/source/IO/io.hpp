#pragma once

#include "Foundation/types.hpp"

#include <optional>
#include <set>
#include <string>
#include <utility>

namespace IO
{
  enum class Command : fn::u8f
  {
    HELP
  };

  enum class Option : fn::u8f
  {
    HELP
  };

  auto printIntroduction() -> void;
  auto printPrompt() -> void;
  [[nodiscard]]
  auto readInput() -> std::string;
  [[nodiscard]]
  auto parseInput(std::string& input
  ) -> std::optional<std::pair<Command, std::set<Option>>>;
} // namespace IO
