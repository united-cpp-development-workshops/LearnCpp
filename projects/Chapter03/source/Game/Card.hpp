#pragma once

#include <Foundation/types.hpp>

#include <ostream>
#include <string>

namespace Game
{
  class Card
  {
  public:
    // Constructors
    Card(std::string&& suit, fn::cdef rank, fn::u8f value) noexcept;

    // Accessors
    [[nodiscard]] auto getSuit() const noexcept -> const std::string&;
    [[nodiscard]] auto getRank() const noexcept -> fn::cdef;
    [[nodiscard]] auto getValue() const noexcept -> fn::u16f;
    [[nodiscard]] auto isAce() const noexcept -> fn::bln;

    // Mutators
    auto setValue(fn::u8f value) noexcept -> fn::none;

  private:
    // Fields
    std::string m_suit;
    fn::cdef    m_rank;
    fn::u16f    m_value;
    fn::bln     m_isAce;

    // Friends
    friend auto operator<<(std::ostream& os, const Card& card) -> std::ostream&
    {
      os << '[' << card.getSuit() << card.getRank() << ']';
      return os;
    }
  };
} // namespace Game
