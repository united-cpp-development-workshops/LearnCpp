#include "pch.hpp"

#include "Game/Card.hpp"

#include <Foundation/types.hpp>

#include <utility>

namespace Game
{
  // Constructors
  Card::Card(fn::str&& suit, const fn::u16f value, const fn::cdef rank) noexcept
    : m_suit{std::move(suit)}
    , m_value{value}
    , m_rank{rank}
    , m_isAce{rank == 'A'}
  {}

  // Accessors
  [[nodiscard]] auto Card::getSuit() const noexcept -> const fn::str&
  {
    return m_suit;
  }

  [[nodiscard]] auto Card::getValue() const noexcept -> fn::u16f
  {
    return m_value;
  }

  [[nodiscard]] auto Card::getRank() const noexcept -> fn::cdef
  {
    return m_rank;
  }

  [[nodiscard]] auto Card::isAce() const noexcept -> fn::bln
  {
    return m_isAce;
  }

  // Mutators
  auto Card::setValue(const fn::u16f value) noexcept -> fn::none
  {
    m_value = {value};
  }
} // namespace Game
