#pragma once

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>

namespace Text
{
  /**
   * @brief   Get the shuffled indexes of the obfuscation characters in a word.
   * @param   word Word to search.
   * @returns Vector of shuffled indexes of obfuscation characters in the word.
   */
  [[nodiscard]] auto getObfuscatedIndexes(fn::strv word) -> fn::vec<fn::size>;
} // namespace Text
