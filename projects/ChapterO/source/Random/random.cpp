#include "pch.hpp"

#include "Random/random.hpp"

#include <Foundation/types.hpp>

#include <random>

namespace Random
{
  [[nodiscard]] auto generateRandomInRange(const fn::size min, const fn::size max) -> fn::size
  {
    // Create a random engine and distribution
    std::default_random_engine              randomEngine{std::random_device{}()};
    std::uniform_int_distribution<fn::size> randomDistribution{min, max};

    // Return the random string
    return randomDistribution(randomEngine);
  }
} // namespace Random
