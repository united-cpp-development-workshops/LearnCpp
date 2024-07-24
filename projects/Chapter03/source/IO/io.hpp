#pragma once

#include "Game/Card.hpp"

#include <Foundation/types.hpp>

#include <string>
#include <vector>

namespace IO
{
  enum class PlayerChoice : fn::u8f
  {
    HIT,
    STAND
  };

  auto printHand(
    const std::string&             holder,
    const std::vector<Game::Card>& hand,
    fn::bln                        hideFirstCard,
    fn::u16f                       adjustedHandTotal
  ) -> fn::none;
  [[nodiscard]] auto getPlayerBet(fn::u32f& playerBank) -> fn::u32f;
  [[nodiscard]] auto getPlayerChoice() -> PlayerChoice;
} // namespace IO
