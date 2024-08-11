#pragma once

#include <Foundation/types.hpp>

namespace Core
{
  // Option constants
  inline constexpr fn::i16l ENCRYPT_OPTION{1};
  inline constexpr fn::i16l DECRYPT_OPTION{2};
  inline constexpr fn::i16l EXIT_OPTION{3};

  // Secret constants
  inline constexpr fn::i16l SECRET_SIZE{16};
} // namespace Core
