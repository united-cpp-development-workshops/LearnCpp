#include "pch.hpp"

#include "Random/random.hpp"

#include <Foundation/Support/narrow.ipp>
#include <Foundation/types.hpp>

#include <algorithm>
#include <random>
#include <utility>
#include <vector>

namespace Random
{
  [[nodiscard]] auto distribute(
    const fn::i32f numberOfElements, const std::pair<fn::i32f, fn::i32f>& bounds
  ) -> std::vector<fn::i32f>
  {
    // Create a vector of random numbers
    std::vector<fn::i32f> values(fn::narrow_cast<fn::size>(numberOfElements));

    // Generate random tooling
    std::default_random_engine randomEngine{std::random_device{}()};
    std::uniform_int_distribution<fn::i32f> distribution{
      bounds.first, bounds.second
    };

    // Fill the vector with random numbers
    std::ranges::generate(
      values,
      [&distribution, &randomEngine]() -> fn::i32f
      {
        return distribution(randomEngine);
      }
    );

    // Return the vector of random numbers
    return values;
  }
} // namespace Random
