#include "pch.hpp"

#include "IO/_internal/prints.hpp"

#include <iostream>
#include <string>

namespace IO::_internal
{
  auto printBriefHelp() -> void
  {
    std::cout << "   USAGE: <command> [options]\n";
    std::cout << "   LEARN: Use 'help' command or '--help' option for more "
                 "information.\n\n";
  }

  auto printInputError(const std::string& message) -> void
  {
    std::cerr << " [X]: " << message << '\n';
    printBriefHelp();
  }

  auto printInputWarning(const std::string& message) -> void
  {
    std::cerr << " [!]: " << message << '\n';
  }
} // namespace IO::_internal
