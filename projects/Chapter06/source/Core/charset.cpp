#include "pch.hpp"

#include "Core/charset.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>

namespace Core
{
  [[nodiscard]] auto getCharset() -> const fn::vec<fn::cdef>&
  {
    // NOLINTNEXTLINE(clang-diagnostic-exit-time-destructors)
    static const fn::vec s_charset{
      ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',',  '-', '.', '/',
      '0', '1', '2', '3', '4', '5', '6', '7',  '8', '9', ':', ';', '<',  '=', '>', '?',
      '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G',  'H', 'I', 'J', 'K', 'L',  'M', 'N', 'O',
      'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',  'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
      '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g',  'h', 'i', 'j', 'k', 'l',  'm', 'n', 'o',
      'p', 'q', 'r', 's', 't', 'u', 'v', 'w',  'x', 'y', 'z', '{', '|',  '}', '~'
    };

    // Return the character set
    return s_charset;
  }
} // namespace Core
