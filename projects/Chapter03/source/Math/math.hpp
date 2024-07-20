#pragma once

#include "Foundation/types.hpp"

#include "Game/game.ipp"

#include <vector>

namespace Math
{
  auto calculateScore(const std::vector<Game::Card>& hand) noexcept -> fn::u16f;
} // namespace Math
