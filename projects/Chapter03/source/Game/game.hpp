#pragma once

#include <Foundation/types.hpp>

namespace Game
{
  // Constants
  inline constexpr fn::u16f PLAYER_COUNT{2};
  inline constexpr fn::u32f PLAYER_STARTING_BANK{1'000};
  inline constexpr fn::u16f COURT_CARD_VALUE{10};
  inline constexpr fn::u16f ACE_HIGH_VALUE{11};
  inline constexpr fn::u16f ACE_LOW_VALUE{1};
  inline constexpr fn::size DECK_COUNT{6};
  inline constexpr fn::f64  SHUFFLE_THRESHOLD{0.5};
  inline constexpr fn::u16f BLACKJACK{21};
  inline constexpr fn::u16f DEALER_STAND{17};
  inline constexpr fn::u16f MIN_BET{10};
  inline constexpr fn::u16f WIN_MULTIPLIER{2};

  auto play() -> fn::none;
} // namespace Game
