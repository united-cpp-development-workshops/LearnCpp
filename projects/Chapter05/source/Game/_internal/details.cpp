#include "pch.hpp"

#include "Game/_internal/details.hpp"

#include "Game/_internal/constants.hpp"
#include "IO/io.ipp"

#include <Foundation/errors.hpp>
#include <Foundation/Support/narrow.ipp>
#include <Foundation/types.hpp>

#include <algorithm>
#include <format>
#include <iostream>
#include <locale>

namespace Game::_internal
{
  [[nodiscard]] auto getRoundWordLength(const fn::i16l round) -> fn::i16l
  {
    // Round word length map
    // NOLINTNEXTLINE(clang-diagnostic-exit-time-destructors)
    static const fn::umap<fn::i16l, fn::i16l> s_roundWordLengthMap{
      {ROUND_01, ROUND_01_WORD_LENGTH},
      {ROUND_02, ROUND_02_WORD_LENGTH},
      {ROUND_03, ROUND_03_WORD_LENGTH},
      {ROUND_04, ROUND_04_WORD_LENGTH},
      {ROUND_05, ROUND_05_WORD_LENGTH},
      {ROUND_06, ROUND_06_WORD_LENGTH},
      {ROUND_07, ROUND_07_WORD_LENGTH},
      {ROUND_08, ROUND_08_WORD_LENGTH},
      {ROUND_09, ROUND_09_WORD_LENGTH},
      {ROUND_10, ROUND_10_WORD_LENGTH},
      {ROUND_11, ROUND_11_WORD_LENGTH},
      {ROUND_12, ROUND_12_WORD_LENGTH},
      {ROUND_13, ROUND_13_WORD_LENGTH},
      {ROUND_XX, ROUND_XX_WORD_LENGTH}
    };

    // Find the word length for the given round
    if (const auto it{s_roundWordLengthMap.find(round)}; it != s_roundWordLengthMap.end())
    {
      // Return the word length
      return it->second;
    }

    // Round not found
    throw fn::StateError{"Round not found!", std::format("Round was '{}'.", round)};
  }

  auto handleGuess(const fn::strv word, fn::str& obfuscatedWord, fn::i16f& score) -> fn::none
  {
    // Make a guess
    fn::str guess;
    IO::printInputPrompt("Enter your guess.");
    std::getline(std::cin, guess);

    // Convert the guess to lowercase
    std::ranges::transform(
      guess,
      guess.begin(),
      [](const char c)
      {
        return std::tolower(c, std::locale());
      }
    );

    // Copy word to a mutable string
    fn::str wordLc{word};

    // Convert the word to lowercase
    std::ranges::transform(
      wordLc,
      wordLc.begin(),
      [](const char c)
      {
        return std::tolower(c, std::locale());
      }
    );

    // Check if the guess is correct
    if (guess == wordLc)
    {
      // Calculate score
      score += fn::narrow_cast<fn::i16f>(std::ranges::count(obfuscatedWord, OBFUSCATION_CHARACTER))
             * SCORE_COEFFICIENT;

      // Update the obfuscated word
      obfuscatedWord = word;

      // Print the message
      IO::printInfoMessage("Congratulations! You guessed the word!");

      // Exit the loop
      return;
    }

    // Calculate score
    score -= WRONG_GUESS_PENALTY;

    // Print the message
    IO::printWarningMessage("Wrong guess! Try again.");
  }
} // namespace Game::_internal
