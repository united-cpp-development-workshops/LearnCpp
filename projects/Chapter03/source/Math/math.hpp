#pragma once

#include "Foundation/types.hpp"

#include "Game/game.hpp"

#include <vector>

namespace Math
{
  auto calculateHandTotal(const std::vector<Game::Card>& hand
  ) noexcept -> fn::u16f;
} // namespace Math
