#include "pch.hpp"

#include "IO/_internal/prints.hpp"

#include <Foundation/types.hpp>

#include <format>
#include <iostream>

namespace IO::_internal
{
  auto printBriefInfo() -> fn::none
  {
    std::cout << " - Explore fundamental types of C++.\n";
    std::cout << " - Learn about the sizes, ranges and properties of fundamental types.\n";
    std::cout << " - Compare fundamental types of C++.\n\n";
  }

  auto printBriefHelp() -> fn::none
  {
    std::cout << "\n   USAGE: <command> [options]\n";
    std::cout << "   LEARN: Use 'help' command or '-help' option for more information.\n";
  }

  auto printInputError(const fn::strv message) -> fn::none
  {
    std::cerr << " [X]: " << message << '\n';
    printBriefHelp();
  }

  auto printInputWarning(const fn::strv message) -> fn::none
  {
    std::cerr << " [!]: " << message << '\n';
  }

  auto printLeftAligned(const fn::strv text, const fn::size width) -> fn::none
  {
    std::cout << std::format("{:<{}}", text, width);
  }
} // namespace IO::_internal
