#include "pch.hpp"

#include "Math/math.hpp"

#include "Game/game.hpp"
#include "types.hpp"

#include <numeric>
#include <vector>

auto Math::calculateHandTotal(const std::vector<Game::Card>& hand
) noexcept -> u16f
{
  return std::accumulate(
    hand.begin(),
    hand.end(),
    u16f{0},
    [](u16f total, const Game::Card& card) noexcept -> u16f
    {
      return total + card.getValue();
    }
  );
}
