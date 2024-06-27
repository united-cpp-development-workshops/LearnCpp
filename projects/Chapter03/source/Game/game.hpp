#pragma once

#include "types.hpp"

#include <iostream>
#include <string>

namespace Game
{
  // Constants
  inline constexpr u32f PLAYER_STARTING_BANK{1'000};
  inline constexpr u8f  COURT_CARD_VALUE{10};
  inline constexpr u8f  ACE_HIGH_VALUE{11};
  inline constexpr u8f  ACE_LOW_VALUE{1};
  inline constexpr size DECK_COUNT{6};
  inline constexpr f64  SHUFFLE_THRESHOLD{0.5};
  inline constexpr u8f  BLACKJACK{21};
  inline constexpr u8f  DEALER_STAND{17};
  inline constexpr u8f  MIN_BET{10};
  inline constexpr u8f  WIN_MULTIPLIER{2};

  struct Card
  {
  public:
    // Constructors
    Card(std::string suit, cdef rank, u8f value) noexcept;

    // Accessors
    [[nodiscard]]
    auto getSuit() const noexcept -> const std::string&;
    [[nodiscard]]
    auto getRank() const noexcept -> cdef;
    [[nodiscard]]
    auto getValue() const noexcept -> u8f;
    [[nodiscard]]
    auto isAce() const noexcept -> bool;

    // Mutators
    auto setValue(u8f value) noexcept -> void;

  private:
    // Fields
    std::string m_suit;
    cdef        m_rank;
    u8f         m_value;
    bool        m_isAce;

    // Friends
    friend auto operator<<(std::ostream& os, const Card& card) -> std::ostream&;
  };

  auto play() -> void;
} // namespace Game
