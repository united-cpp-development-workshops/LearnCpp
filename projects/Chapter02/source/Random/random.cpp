#include "Random/random.hpp"

#include <algorithm>
#include <cstddef>
#include <random>
#include <vector>

auto Random::distribute(
  std::size_t numberOfElements, int lowerBound, int upperBound
) -> std::vector<int>
{
  // Create a vector of random numbers
  std::vector<int> values(numberOfElements);

  // Generate random tooling
  std::random_device                 randomDevice;
  std::default_random_engine         randomEngine{randomDevice()};
  std::uniform_int_distribution<int> distribution{lowerBound, upperBound};

  // Fill the vector with random numbers
  std::generate(
    values.begin(),
    values.end(),
    [&]
    {
      return distribution(randomEngine);
    }
  );

  // Return the vector of random numbers
  return values;
}
