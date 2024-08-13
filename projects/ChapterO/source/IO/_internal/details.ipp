#pragma once

#include <Foundation/types.hpp>

#include <iostream>

namespace IO::_internal
{
  /**
   * @brief Resets the input buffer.
   */
  inline auto resetInputBuffer() -> fn::none;
} // namespace IO::_internal

/*------------------------------------------------------------------------------------------------*\
*| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Implementation >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
\*------------------------------------------------------------------------------------------------*/

namespace IO::_internal
{
  inline auto resetInputBuffer() -> fn::none
  {
    // Clear error flags.
    std::cin.clear();

    // Clear the input buffer.
    if (std::cin.rdbuf()->in_avail() > 0)
    {
      // Ignore the rest of the input buffer.
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
} // namespace IO::_internal
