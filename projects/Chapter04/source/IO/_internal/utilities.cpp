#include "pch.hpp"

#include "IO/_internal/utilities.hpp"

#include <Foundation/types.hpp>

#include <iostream>
#include <limits>
#include <locale>

namespace IO::_internal
{
  [[nodiscard]] auto isNotAllowedCharacter(const fn::cdef character) -> fn::bln
  {
    // Check if character is allowed
    return std::isalnum(character, std::locale()) == 0 and character != '-' and character != ' ';
  }

  auto resetInputBuffer() -> fn::none
  {
    // Clear input buffer and error flags
    std::cin.clear();
    if (std::cin.rdbuf()->in_avail() > 0)
    {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
} // namespace IO::_internal
