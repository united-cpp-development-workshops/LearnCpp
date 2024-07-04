#include "pch.hpp"

#include "IO/io.hpp"

#include "Foundation/types.hpp"

#include "IO/Request/IRequest.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

namespace
{
  auto isNotAllowedCharacter(fn::cdef character) noexcept -> bool
  {
    // Check if character is allowed
    return std::isalnum(character) == 0 and character != '-'
       and character != ' ';
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

  std::cout << " > ";
}

auto IO::readInput() -> std::string
{
  // Read input as string
  std::string input;
  std::cin >> input;

  // Return input
  return input;
}

template <typename Option>
[[nodiscard]]
auto IO::parseInput(const std::string& input) -> Request::IRequest<Option>
{
  // Check if input is empty
  if (input.empty())
  {
    // Print error message
    std::cout << "ERROR: Invalid input. Please try again.\n";
    return;
  }

  // Replace not allowed characters
  std::replace_if(input.begin(), input.end(), isNotAllowedCharacter, ' ');

  // Check if input is 'help'
  if (input == "help")
  {
    // Print help message
    std::cout << "HELP: Use 'explore' command to start exploring types.\n";
    std::cout << "HELP: Use 'exit' command to exit the program.\n";
    return;
  }

  // Check if input is 'explore'
  if (input == "explore")
  {
    // Print explore message
    std::cout << "EXPLORE: Exploring types...\n";
    return;
  }

  // Check if input is 'exit'
  if (input == "exit")
  {
    // Print exit message
    std::cout << "EXIT: Exiting program...\n";
    return;
  }

  // Print error message
  std::cout << "ERROR: Invalid command. Please try again.\n";
}
