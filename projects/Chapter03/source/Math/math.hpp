#pragma once

#include "Game/game.ipp"

#include <Foundation/types.hpp>

#include <vector>

namespace Math
{
  [[nodiscard]] auto calculateScore(const std::vector<Game::Card>& hand
  ) noexcept -> fn::u16f;
} // namespace Math
