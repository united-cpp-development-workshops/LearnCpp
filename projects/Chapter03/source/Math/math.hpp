#pragma once

#include "Game/Card.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>

namespace Math
{
  [[nodiscard]] auto calculateScore(const fn::vec<Game::Card>& hand) noexcept -> fn::u16f;
} // namespace Math
