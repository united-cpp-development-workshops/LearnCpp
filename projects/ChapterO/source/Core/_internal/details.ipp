#pragma once

#include "IO/io.ipp"
#include "Random/random.hpp"
#include "Utility/utility.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/Support/narrow.ipp>
#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>

#include <format>
#include <locale>

namespace Core::_internal
{
  /**
   * @brief The operators that can be used in the game.
   */
  enum class Operator : fn::u8f
  {
    AND,
    OR
  };

  /**
   * @brief   Gets the string representation of the operator.
   * @param   guess The operator to get the string for.
   * @returns The string representation of the operator.
   */
  [[nodiscard]] constexpr auto GET_OPERATOR_STR(Operator guess) -> fn::strv;

  /**
   * @brief  Plays the game.
   * @tparam bitCount The number of bits in the bitset.
   * @tparam operandCount The number of operands.
   * @tparam blockSize The block size of bitsets when printing.
   * @throws fn::EnumeratorError If the random operator produces the wrong value.
   */
  template <fn::size bitCount, fn::size blockSize, fn::size operandCount>
  auto play() -> fn::none;
} // namespace Core::_internal

/*------------------------------------------------------------------------------------------------*\
*| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Implementation >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
\*------------------------------------------------------------------------------------------------*/

namespace Core::_internal
{
  [[nodiscard]] constexpr auto GET_OPERATOR_STR(const Operator guess) -> fn::strv
  {
    // Using declarations
    using enum Operator;

    switch (guess)
    {
    case AND:
    {
      return "&";
    }
    case OR:
    {
      return "|";
    }
    default:
    {
      return "INVALID";
    }
    }
  }

  template <fn::size bitCount, fn::size blockSize, fn::size operandCount>
  auto play() -> fn::none
  {
    // Using declarations
    using enum Operator;

    // Create computer vectors to store the operands and operators
    fn::vec<fn::bitset<bitCount>> cLeftOperands{};
    fn::vec<fn::bitset<bitCount>> cRightOperands{};
    fn::vec<Operator>             cOperators{};

    // Calculate the max unsigned value achievable with bit count
    constexpr fn::size MAX_VALUE{(fn::size{1} << bitCount) - 1};

    // Fill the bitsets with random values
    IO::printLoadingMessage("Loading...");
    fn::bln isFirstBitset{true};
    for ([[maybe_unused]] fn::size i{}; i < operandCount; ++i)
    {
      if (isFirstBitset)
      {
        // Add the first operand to the left operands
        cLeftOperands.emplace_back(Random::generateRandomInRange(0, MAX_VALUE));
        isFirstBitset = {false};
      }
      else
      {
        // Add the rest of the operands to the right operands
        cRightOperands.emplace_back(Random::generateRandomInRange(0, MAX_VALUE));
      }
    }

    IO::printSectionDivider();
    IO::printTitle("PLAY");

    // Perform operations
    IO::printParagraph("The following operations are performed:");
    for (fn::size i{}; i < (operandCount - 1); ++i)
    {
      // Select a random operation
      switch (const auto operation{Random::generateRandomInRange(0, 1)};
              static_cast<Operator>(operation))
      {
      case AND:
      {
        // Perform the operation
        cOperators.push_back(AND);
        cLeftOperands.push_back(cLeftOperands.back() bitand cRightOperands.at(i));
        break;
      }
      case OR:
      {
        // Perform the operation
        cOperators.push_back(OR);
        cLeftOperands.push_back(cLeftOperands.back() bitor cRightOperands.at(i));
        break;
      }
      default:
      {
        throw fn::EnumeratorError{"Invalid enumerator!", "Check random range!"};
      }
      }

      // Print the operation
      IO::printOption(
        std::format("Step {}", (i + 1)),
        std::format(
          "R{} ? {} = R{}",
          i,
          Utility::formatBlock(cRightOperands.at(i).to_string(), blockSize),
          (i + 1)
        ),
        fn::narrow_cast<fn::i16l>(i + 1)
      );
    }

    IO::printSectionDivider();
    IO::printTitle("GUESS");
    IO::printParagraph("Guess the operators. Here are the facts:");

    IO::printSubtitle("FACTS", "");
    IO::printInfoMessage(
      std::format("R0 = {}", Utility::formatBlock(cLeftOperands.front().to_string(), blockSize))
    );
    IO::printInfoMessage(std::format(
      "R{} = {}",
      (cLeftOperands.size() - 1),
      Utility::formatBlock(cLeftOperands.back().to_string(), blockSize)
    ));

    // Create user vectors to store the operands and operators
    fn::vec<fn::bitset<bitCount>> uLeftOperands{};
    fn::vec<fn::bitset<bitCount>> uRightOperands{};
    fn::vec<Operator>             uOperators{};

    // Initialize the initial state
    uLeftOperands.push_back(cLeftOperands.front());
    uRightOperands.insert(uRightOperands.begin(), cRightOperands.begin(), cRightOperands.end());

    // Guess the operations
    for (fn::size i{}; i < (operandCount - 1); ++i)
    {
      IO::printSectionDivider();
      IO::printSubtitle("STEP", std::format("{}", (i + 1)));
      IO::printParagraph("Guess the operator. Here is the current state:");

      // Print the last state
      for (fn::size j{}; j < i; ++j)
      {
        IO::printOption(
          std::format("Step {}", j + 1),
          std::format(
            "{} {} {} = {}",
            Utility::formatBlock(uLeftOperands.at(j).to_string(), blockSize),
            GET_OPERATOR_STR(uOperators.at(j)),
            Utility::formatBlock(uRightOperands.at(j).to_string(), blockSize),
            Utility::formatBlock(uLeftOperands.at(j + 1).to_string(), blockSize)
          ),
          fn::narrow_cast<fn::i16l>(j + 1)
        );
      }

      // Print the current state
      IO::printOption(
        std::format("Step {}", (i + 1)),
        std::format(
          "{} ? {} = R{}",
          Utility::formatBlock(uLeftOperands.at(i).to_string(), blockSize),
          Utility::formatBlock(uRightOperands.at(i).to_string(), blockSize),
          (i + 1)
        ),
        fn::narrow_cast<fn::i16l>(i + 1)
      );

      fn::bln isValidInput{false};
      while (not isValidInput)
      {
        // Get the user input
        fn::str guess{};
        IO::printInputPrompt("Enter the operator. ('&', '|')");
        std::cin >> guess;

        // Convert the guess to lowercase
        std::ranges::transform(
          guess,
          guess.begin(),
          [](const char c)
          {
            return std::toupper(c, std::locale());
          }
        );

        // Check the user input
        if (guess == GET_OPERATOR_STR(AND) or guess == "AND")
        {
          // Perform the operation
          uOperators.push_back(AND);
          uLeftOperands.push_back(uLeftOperands.back() bitand uRightOperands.at(i));
          isValidInput = {true};
        }
        else if (guess == GET_OPERATOR_STR(OR) or guess == "OR")
        {
          // Perform the operation
          uOperators.push_back(OR);
          uLeftOperands.push_back(uLeftOperands.back() bitor uRightOperands.at(i));
          isValidInput = {true};
        }
        else
        {
          // Print error message
          IO::printErrorMessage("Invalid operator, try again.");
        }
      }
    }

    IO::printSectionDivider();

    // Validate user guess
    if (uLeftOperands.back() == cLeftOperands.back())
    {
      IO::printSubtitle("CORRECT", "Your guess was correct!");
    }
    else
    {
      IO::printSubtitle("INCORRECT", "Your guess was incorrect!");
    }

    // Print the user solution
    IO::printParagraph("Here is your solution:");
    for (fn::size i{}; i < (operandCount - 1); ++i)
    {
      IO::printOption(
        std::format("Step {}", (i + 1)),
        std::format(
          "{} {} {} = {}",
          Utility::formatBlock(uLeftOperands.at(i).to_string(), blockSize),
          GET_OPERATOR_STR(uOperators.at(i)),
          Utility::formatBlock(uRightOperands.at(i).to_string(), blockSize),
          Utility::formatBlock(uLeftOperands.at(i + 1).to_string(), blockSize)
        ),
        fn::narrow_cast<fn::i16l>(i + 1)
      );
    }

    IO::printEmpty();

    // Print the computer solution
    IO::printParagraph("Here is the computer's solution:");
    for (fn::size i{}; i < (operandCount - 1); ++i)
    {
      IO::printOption(
        std::format("Step {}", (i + 1)),
        std::format(
          "{} {} {} = {}",
          Utility::formatBlock(cLeftOperands.at(i).to_string(), blockSize),
          GET_OPERATOR_STR(cOperators.at(i)),
          Utility::formatBlock(cRightOperands.at(i).to_string(), blockSize),
          Utility::formatBlock(cLeftOperands.at(i + 1).to_string(), blockSize)
        ),
        fn::narrow_cast<fn::i16l>(i + 1)
      );
    }
  }
} // namespace Core::_internal
