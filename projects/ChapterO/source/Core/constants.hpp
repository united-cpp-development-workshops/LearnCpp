#pragma once

#include <Foundation/types.hpp>

namespace Core
{
  // Main menu option constants
  inline constexpr fn::i16l PLAY_OPTION{1};
  inline constexpr fn::i16l LEARN_OPTION{2};
  inline constexpr fn::i16l EXIT_OPTION{3};

  // Difficulty option constants
  inline constexpr fn::i16l EASY_OPTION{1};
  inline constexpr fn::i16l MEDIUM_OPTION{2};
  inline constexpr fn::i16l HARD_OPTION{3};
  inline constexpr fn::i16l ABSURD_OPTION{4};

  // Bit count constants
  inline constexpr fn::size EASY_BIT_COUNT{4};
  inline constexpr fn::size MEDIUM_BIT_COUNT{6};
  inline constexpr fn::size HARD_BIT_COUNT{8};
  inline constexpr fn::size ABSURD_BIT_COUNT{16};

  // Bitset block size constants
  inline constexpr fn::size EASY_BLOCK_SIZE{2};
  inline constexpr fn::size MEDIUM_BLOCK_SIZE{3};
  inline constexpr fn::size HARD_BLOCK_SIZE{4};
  inline constexpr fn::size ABSURD_BLOCK_SIZE{4};

  // Operand count constants
  inline constexpr fn::size EASY_OPERAND_COUNT{4};
  inline constexpr fn::size MEDIUM_OPERAND_COUNT{6};
  inline constexpr fn::size HARD_OPERAND_COUNT{8};
  inline constexpr fn::size ABSURD_OPERAND_COUNT{10};
} // namespace Core
