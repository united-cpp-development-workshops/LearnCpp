#include "pch.hpp"

#include "Random/random.hpp"

#include "Core/charset.hpp"

#include <Foundation/types.hpp>

#include <random>

namespace Random
{
  [[nodiscard]] auto generateRandomString(const fn::size size) -> fn::str
  {
    // Get the character set
    const auto& charset{Core::getCharset()};

    // Create a random engine and distribution
    std::default_random_engine              randomEngine{std::random_device{}()};
    std::uniform_int_distribution<fn::size> randomDistribution{0, charset.size() - 1};

    // Create a random string
    fn::str randomString(size, '\0');

    // Fill the string with random characters
    for (auto& c : randomString)
    {
      c = {charset.at(randomDistribution(randomEngine))};
    }

    // Return the random string
    return randomString;
  }
} // namespace Random
