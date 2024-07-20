#include "pch.hpp"

#include "Math/math.hpp"

#include "Foundation/types.hpp"

#include "Game/game.ipp"

#include <numeric>
#include <vector>

auto Math::calculateScore(const std::vector<Game::Card>& hand
) noexcept -> fn::u16f
{
  return std::accumulate(
    hand.begin(),
    hand.end(),
    fn::u16f{0},
    [](fn::u16f total, const Game::Card& card) noexcept
    {
      return total + card.getValue();
    }
  );
}
