#pragma once

#include <Foundation/types.hpp>

namespace Game::_internal
{
  /**
   * @brief   Gets the question word length for a given round.
   * @param   round Round to get the question word length for.
   * @returns The question word length for the given round.
   * @throws  fn::StateError If the round is not found.
   */
  [[nodiscard]] auto getRoundWordLength(fn::i16l round) -> fn::i16l;

  /**
   * @brief Gets the user guess and manages score.
   * @param word Original word to compare against.
   * @param obfuscatedWord The obfuscated word to be updated.
   * @param score The score to be updated.
   */
  auto handleGuess(fn::strv word, fn::str& obfuscatedWord, fn::i16f& score) -> fn::none;
} // namespace Game::_internal
