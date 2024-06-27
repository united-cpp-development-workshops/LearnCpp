#pragma once

#include "Game/game.hpp"
#include "types.hpp"

#include <vector>

namespace Math
{
  auto calculateHandTotal(const std::vector<Game::Card>& hand) noexcept -> u16f;
} // namespace Math
