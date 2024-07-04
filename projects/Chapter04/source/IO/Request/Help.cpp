#include "pch.hpp"

#include "IO/Request/Help.hpp"

#include <iostream>
#include <utility>
#include <vector>

namespace IO::Request
{
  /*--------------------------------------------------------------------------*\
  *| [public]: Methods                                                        |*
  \*--------------------------------------------------------------------------*/

  auto Help::printResponse() -> void
  {
    // Print general help
    std::cout << "General help\n";
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Mutators                                                       |*
  \*--------------------------------------------------------------------------*/

  auto Help::setOptions(std::vector<HelpOption>&& options) noexcept -> void
  {
    // move options into m_options
    m_options = std::move(options);
  }
} // namespace IO::Request
