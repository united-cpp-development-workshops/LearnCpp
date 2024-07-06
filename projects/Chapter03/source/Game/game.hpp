#pragma once

#include "Foundation/types.hpp"

#include <iostream>
#include <string>

namespace Game
{
  // Constants
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

  struct Card
  {
  public:
    // Constructors
    Card(std::string suit, fn::cdef rank, fn::u8f value) noexcept;

    // Accessors
    [[nodiscard]]
    auto getSuit() const noexcept -> const std::string&;
    [[nodiscard]]
    auto getRank() const noexcept -> fn::cdef;
    [[nodiscard]]
    auto getValue() const noexcept -> fn::u8f;
    [[nodiscard]]
    auto isAce() const noexcept -> fn::bln;

    // Mutators
    auto setValue(fn::u8f value) noexcept -> void;

  private:
    // Fields
    std::string m_suit;
    fn::cdef    m_rank;
    fn::u8f     m_value;
    fn::bln     m_isAce;

    // Friends
    friend auto operator<<(std::ostream& os, const Card& card) -> std::ostream&;
  };

  auto play() -> void;
} // namespace Game
