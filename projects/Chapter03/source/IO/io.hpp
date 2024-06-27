#pragma once

#include "Game/game.hpp"
#include "types.hpp"

#include <string>
#include <vector>

namespace IO
{
  enum class PlayerChoice : u8f
  {
    HIT,
    STAND
  };

  auto getPlayerBet(u32f& playerBank) -> u32f;
  auto printHand(
    const std::string&             holder,
    const std::vector<Game::Card>& hand,
    bool                           hideFirstCard,
    u16f                           adjustedHandTotal
  ) -> void;
  auto getPlayerChoice() -> PlayerChoice;
} // namespace IO
