#pragma once

#include "IO/Request/IRequest.hpp"

#include <string>

namespace IO
{
  auto printIntroduction() -> void;
  auto printPrompt() -> void;
  [[nodiscard]]
  auto readInput() -> std::string;

  template <typename Option>
  [[nodiscard]]
  auto parseInput(const std::string& input) -> Request::IRequest<Option>;
} // namespace IO
