#include "pch.hpp"

#include "Random/random.hpp"

#include "foundation.hpp"

#include <algorithm>
#include <random>
#include <vector>

auto Random::distribute(size numberOfElements, i32f lowerBound, i32f upperBound)
  -> std::vector<i32f>
{
  // Create a vector of random numbers
  std::vector<i32f> values(numberOfElements);

  // Generate random tooling
  std::random_device                  randomDevice;
  std::default_random_engine          randomEngine{randomDevice()};
  std::uniform_int_distribution<i32f> distribution{lowerBound, upperBound};

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
