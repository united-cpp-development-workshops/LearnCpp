#include "pch.hpp"

#include "IO/io.hpp"

#include "Foundation/types.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <optional>
#include <set>
#include <string>
#include <utility>

namespace
{
  auto isNotAllowedCharacter(fn::cdef character) noexcept -> fn::bln
  {
    // Check if character is allowed
    return std::isalnum(character) == 0 and character != '-'
       and character != ' ';
  }

  auto printInvalidInput() -> void
  {
    std::cout
      << " [X]: Invalid input! Use 'help' command or '--help' option.\n";
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
} // namespace

auto IO::printIntroduction() -> void
{
  std::cout << "---------------------------> Types Explorer "
               "<---------------------------\n\n";

  std::cout << " - Explore fundamental types of C++.\n";
  std::cout << " - Learn about the sizes, ranges, and properties of "
               "fundamental types.\n";
  std::cout << " - Observe the behavior of fundamental types in various "
               "contexts.\n";
  std::cout << " - Discover fundamental type aliases in Foundation header.\n\n";

  std::cout << "   :::::::::::::::::::::::::: How It Works "
               "::::::::::::::::::::::::::\n\n";

  std::cout << "   USAGE: <command> [options]\n";
  std::cout << "   LEARN: Use 'help' command or '--help' option for more "
               "information.\n\n";
}

auto IO::printPrompt() -> void
{
  std::cout << "---------------------------------------------------------------"
               "---------\n\n";

  std::cout << " [>]: ";
}

[[nodiscard]]
auto IO::readInput() -> std::string
{
  // Reset input buffer
  resetInputBuffer();

  // Read input as string
  std::string input;
  std::getline(std::cin, input);

  // Return input
  return input;
}

[[nodiscard]]
auto IO::parseInput(std::string& input
) -> std::optional<std::pair<Command, std::set<Option>>>
{
  // Check if input is empty
  if (input.empty())
  {
    // Print error message
    printInvalidInput();
    return std::nullopt;
  }

  // Replace not allowed characters
  std::replace_if(input.begin(), input.end(), isNotAllowedCharacter, ' ');

  // Reduce input to having no consecutive spaces one after another
  input.erase(
    std::unique(
      input.begin(),
      input.end(),
      [](fn::cdef a, fn::cdef b) noexcept -> fn::bln
      {
        return a == ' ' and b == ' ';
      }
    ),
    input.end()
  );

  // TEST:
  return std::nullopt;
}
