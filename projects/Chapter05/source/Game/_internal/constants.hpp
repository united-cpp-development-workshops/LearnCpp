#pragma once

#include <Foundation/types.hpp>

namespace Game::_internal
{
  // Main menu options
  inline constexpr fn::i16l PLAY_OPTION{1};
  inline constexpr fn::i16l LEARN_OPTION{2};
  inline constexpr fn::i16l SCORES_OPTION{3};
  inline constexpr fn::i16l EXIT_OPTION{4};

  // Game options
  inline constexpr fn::i16l ASK_LETTER_OPTION{1};
  inline constexpr fn::i16l PASS_OPTION{2};
  inline constexpr fn::i16l GUESS_OPTION{3};

  // Endgame options
  inline constexpr fn::i16l SAVE_OPTION{1};
  inline constexpr fn::i16l PLAY_AGAIN_OPTION{2};
  inline constexpr fn::i16l EXIT_TO_MAIN_MANU{3};

  // Game Rounds
  inline constexpr fn::i16l ROUND_01{1};
  inline constexpr fn::i16l ROUND_02{2};
  inline constexpr fn::i16l ROUND_03{3};
  inline constexpr fn::i16l ROUND_04{4};
  inline constexpr fn::i16l ROUND_05{5};
  inline constexpr fn::i16l ROUND_06{6};
  inline constexpr fn::i16l ROUND_07{7};
  inline constexpr fn::i16l ROUND_08{8};
  inline constexpr fn::i16l ROUND_09{9};
  inline constexpr fn::i16l ROUND_10{10};
  inline constexpr fn::i16l ROUND_11{11};
  inline constexpr fn::i16l ROUND_12{12};
  inline constexpr fn::i16l ROUND_13{13};
  inline constexpr fn::i16l ROUND_XX{13};

  // Word lengths by game rounds
  inline constexpr fn::i16l ROUND_01_WORD_LENGTH{4};
  inline constexpr fn::i16l ROUND_02_WORD_LENGTH{4};
  inline constexpr fn::i16l ROUND_03_WORD_LENGTH{5};
  inline constexpr fn::i16l ROUND_04_WORD_LENGTH{5};
  inline constexpr fn::i16l ROUND_05_WORD_LENGTH{6};
  inline constexpr fn::i16l ROUND_06_WORD_LENGTH{6};
  inline constexpr fn::i16l ROUND_07_WORD_LENGTH{7};
  inline constexpr fn::i16l ROUND_08_WORD_LENGTH{7};
  inline constexpr fn::i16l ROUND_09_WORD_LENGTH{8};
  inline constexpr fn::i16l ROUND_10_WORD_LENGTH{8};
  inline constexpr fn::i16l ROUND_11_WORD_LENGTH{9};
  inline constexpr fn::i16l ROUND_12_WORD_LENGTH{9};
  inline constexpr fn::i16l ROUND_13_WORD_LENGTH{10};
  inline constexpr fn::i16l ROUND_XX_WORD_LENGTH{10};

  // Score constants
  inline constexpr fn::i16l SCORE_COEFFICIENT{100};
  inline constexpr fn::i16l WRONG_GUESS_PENALTY{100};
  inline constexpr fn::i32l MAX_SCORE{
    (ROUND_01_WORD_LENGTH + ROUND_02_WORD_LENGTH + ROUND_03_WORD_LENGTH + ROUND_04_WORD_LENGTH
     + ROUND_05_WORD_LENGTH + ROUND_06_WORD_LENGTH + ROUND_07_WORD_LENGTH + ROUND_08_WORD_LENGTH
     + ROUND_09_WORD_LENGTH + ROUND_10_WORD_LENGTH + ROUND_11_WORD_LENGTH + ROUND_12_WORD_LENGTH
     + ROUND_13_WORD_LENGTH + ROUND_XX_WORD_LENGTH)
    * SCORE_COEFFICIENT
  };

  // Passing
  inline constexpr fn::i16l PASS_RIGHTS{5};

  // Obfuscation character
  inline constexpr fn::cdef OBFUSCATION_CHARACTER{'*'};

  // Scores table headers
  inline constexpr fn::strv USERNAME_HEADER{"USERNAME"};
  inline constexpr fn::strv SCORE_HEADER{"SCORE"};
  inline constexpr fn::strv TIMESTAMP_HEADER{"TIMESTAMP"};
} // namespace Game::_internal
