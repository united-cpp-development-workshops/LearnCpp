#pragma once

#include "Foundation/types.hpp"

#include "Game/game.hpp"

#include <string>
#include <vector>

namespace IO
{
  enum class PlayerChoice : fn::u8f
  {
    HIT,
    STAND
  };

  auto getPlayerBet(fn::u32f& playerBank) -> fn::u32f;
  auto printHand(
    const std::string&             holder,
    const std::vector<Game::Card>& hand,
    fn::bln                        hideFirstCard,
    fn::u16f                       adjustedHandTotal
  ) -> void;
  auto getPlayerChoice() -> PlayerChoice;
} // namespace IO
