#pragma once

#include "Game/Card.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>

namespace IO
{
  enum class PlayerChoice : fn::u8f
  {
    HIT,
    STAND
  };

  auto printHand(
    fn::strv                   holder,
    const fn::vec<Game::Card>& hand,
    fn::bln                    hideFirstCard,
    fn::u16f                   adjustedHandTotal
  ) -> fn::none;
  [[nodiscard]] auto getPlayerBet(fn::u32f& playerBank) -> fn::u32f;
  [[nodiscard]] auto getPlayerChoice() -> PlayerChoice;
} // namespace IO
