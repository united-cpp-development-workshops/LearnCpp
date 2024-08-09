#include "pch.hpp"

#include "Text/text.hpp"

#include "Game/_internal/constants.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>

#include <algorithm>
#include <random>

namespace Text
{
  [[nodiscard]] auto getObfuscatedIndexes(const fn::strv word) -> fn::vec<fn::size>
  {
    // Create the vector
    fn::vec<fn::size> obfuscatedIndexes;

    // Get the word size
    const auto wordSize{word.size()};

    // Loop through the word
    for (fn::size i{}; i < wordSize; ++i)
    {
      if (word.at(i) == Game::_internal::OBFUSCATION_CHARACTER)
      {
        // Add the index to the vector
        obfuscatedIndexes.push_back(i);
      }
    }

    // Shuffle the vector
    std::ranges::shuffle(obfuscatedIndexes, std::default_random_engine{std::random_device{}()});

    // Return the shuffled vector
    return obfuscatedIndexes;
  }
} // namespace Text
