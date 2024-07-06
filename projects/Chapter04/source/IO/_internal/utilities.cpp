#include "pch.hpp"

#include "IO/_internal/utilities.hpp"

#include "Foundation/types.hpp"

#include <cctype>
#include <iostream>
#include <limits>

namespace IO::_internal
{
  [[nodiscard]]
  auto isNotAllowedCharacter(fn::cdef character) noexcept -> fn::bln
  {
    // Check if character is allowed
    return std::isalnum(character) == 0 and character != '-'
       and character != ' ';
  }

  auto resetInputBuffer() -> void
  {
    // Clear input buffer and error flags
    std::cin.clear();
    if (std::cin.rdbuf()->in_avail() > 0)
    {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
} // namespace IO::_internal
