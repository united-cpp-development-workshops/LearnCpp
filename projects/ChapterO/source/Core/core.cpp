#include "pch.hpp"

#include "Core/core.hpp"

#include "Core/_internal/details.ipp"
#include "Core/constants.hpp"
#include "IO/io.ipp"

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>

#include <iostream>

namespace Core
{
  auto learn() -> fn::none
  {
    IO::printSectionDivider();
    IO::printTitle("LEARN");
    IO::printParagraph("The game is simple, guess the equation steps.");
    IO::printInfoMessage("You'll be given an equation involving bit manipulations.");
    IO::printInfoMessage("You will know the operands and the final result.");
    IO::printInfoMessage("In each step of the equation, you'll guess the operator.");
    IO::printInfoMessage("If your result is correct, you win!");
    IO::printInfoMessage("There are three difficulty levels, start from easy.");
    IO::printInfoMessage("Have fun!");
  }

  auto run() -> fn::none
  {
    while (true)
    {
      IO::printSectionDivider();
      IO::printTitle("DIFFICULTY");
      IO::printParagraph("Select a difficulty option from the menu below:");
      IO::printOption("Easy  ", "Fewer bits, fewer operations.", Core::EASY_OPTION);
      IO::printOption("Medium", "Average bits, average operations.", Core::MEDIUM_OPTION);
      IO::printOption("Hard  ", "More bits, more operations.", Core::HARD_OPTION);
      IO::printOption("Absurd", "A lot of bits, a lot of operations.", Core::ABSURD_OPTION);

      fn::i16l option{};
      IO::printInputPrompt("Enter an option.");
      std::cin >> option;

      switch (option)
      {
      case Core::EASY_OPTION:
      {
        // Play the game in easy difficulty
        _internal::play<EASY_BIT_COUNT, EASY_BLOCK_SIZE, EASY_OPERAND_COUNT>();
        return;
      }
      case Core::MEDIUM_OPTION:
      {
        // Play the game in medium difficulty
        _internal::play<MEDIUM_BIT_COUNT, MEDIUM_BLOCK_SIZE, MEDIUM_OPERAND_COUNT>();
        return;
      }
      case Core::HARD_OPTION:
      {
        // Play the game in hard difficulty
        _internal::play<HARD_BIT_COUNT, HARD_BLOCK_SIZE, HARD_OPERAND_COUNT>();
        return;
      }
      case Core::ABSURD_OPTION:
      {
        // Play the game in hard difficulty
        _internal::play<ABSURD_BIT_COUNT, ABSURD_BLOCK_SIZE, ABSURD_OPERAND_COUNT>();
        return;
      }
      default:
      {
        // Input was invalid print error message
        IO::printErrorMessage("Invalid option, try again.");
        break;
      }
      }
    }
  }
} // namespace Core
