#pragma once

#include "IO/_internal/details.ipp"
#include "Model/Entry.hpp"

#include <Foundation/types.hpp>

#include <format>
#include <iostream>
#include <locale>
#include <tuple>

namespace IO
{
  /**
   * @brief Prints a title to the console.
   * @param title Title to print.
   */
  inline auto printTitle(fn::strv title) -> fn::none;

  /**
   * @brief Prints a subtitle and message to the console
   * @param subtitle Subtitle to print.
   * @param message Message to print.
   */
  inline auto printSubtitle(fn::strv subtitle, fn::strv message) -> fn::none;

  /**
   * @brief Prints a section divider.
   */
  inline auto printSectionDivider() -> fn::none;

  /**
   * @brief Prints a paragraph to the console.
   * @param paragraph Paragraph to print.
   */
  inline auto printParagraph(fn::strv paragraph) -> fn::none;

  /**
   * @brief Prints a message to the console, resets the input bugger and prompts the user for input.
   * @param message Message to print.
   */
  inline auto printInputPrompt(fn::strv message) -> fn::none;

  /**
   * @brief Prints a menu option to the console
   * @param option Option to print.
   * @param code The code of the option.
   */
  inline auto printMenuOption(fn::strv option, fn::strv description, fn::i16l code) -> fn::none;

  /**
   * @brief Prints a message to the console.
   * @param message Message to print.
   */
  inline auto printInfoMessage(fn::strv message) -> fn::none;

  /**
   * @brief Prints a warning message to the console.
   * @param message Message to print.
   */
  inline auto printWarningMessage(fn::strv message) -> fn::none;

  /**
   * @brief Prints an error message to the console.
   * @param message Message to print.
   */
  inline auto printErrorMessage(fn::strv message) -> fn::none;

  /**
   * @brief Prints a loading message to the console.
   * @param message Message to print.
   */
  inline auto printLoadingMessage(fn::strv message) -> fn::none;

  /**
   * @brief Prints an entry to the console.
   * @param obfuscatedWord Obfuscated word to print.
   * @param definitions Definitions of the word.
   */
  inline auto printEntry(fn::strv obfuscatedWord, const fn::vec<fn::str>& definitions) -> fn::none;
} // namespace IO

/*------------------------------------------------------------------------------------------------*\
*| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Implementation >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
\*------------------------------------------------------------------------------------------------*/

namespace IO
{
  inline auto printTitle(const fn::strv title) -> fn::none
  {
    // Print the subtitle
    std::cout << "     [" << title << "]\n";
    std::cout << "     ";

    // Print the divider
    const auto dividerLength{title.length() + fn::str{"[]"}.length()};
    for (fn::size i{}; i < dividerLength; ++i)
    {
      std::cout << '-';
    }

    // Print empty line
    std::cout << "\n\n";
  }

  inline auto printSubtitle(const fn::strv subtitle, const fn::strv message) -> fn::none
  {
    // Print the subtitle.
    std::cout << "     " << subtitle << ": " << message << "\n\n";
  }

  inline auto printSectionDivider() -> fn::none
  {
    // Print a section divider.
    std::cout << "\n     >----------< a game of words >----------<\n\n";
  }

  inline auto printParagraph(const fn::strv paragraph) -> fn::none
  {
    // Print the paragraph.
    std::cout << "     " << paragraph << "\n\n";
  }

  inline auto printInputPrompt(const fn::strv message) -> fn::none
  {
    // Reset the input buffer
    _internal::resetInputBuffer();

    // Print divider
    std::cout << "\n     ";
    const auto dividerLength{message.length() + fn::str{"[i]: "}.length()};
    for (fn::size i{}; i < dividerLength; ++i)
    {
      std::cout << '`';
    }

    // Print empty line
    std::cout << '\n';

    // Print the message.
    std::cout << "     [i]: " << message << '\n';

    // Print the prompt.
    std::cout << "     [>]: ";
  }

  inline auto printMenuOption(
    const fn::strv option, const fn::strv description, const fn::i16l code
  ) -> fn::none
  {
    // Print the option.
    std::cout << "     [" << code << "]: " << option << " | " << description << '\n';
  }

  inline auto printInfoMessage(const fn::strv message) -> fn::none
  {
    // Print the message.
    std::cout << "     [i]: " << message << '\n';
  }

  inline auto printWarningMessage(const fn::strv message) -> fn::none
  {
    // Print the message.
    std::cout << "     [!]: " << message << '\n';
  }

  inline auto printErrorMessage(const fn::strv message) -> fn::none
  {
    // Print the message.
    std::cout << "     [X]: " << message << '\n';
  }

  inline auto printLoadingMessage(const fn::strv message) -> fn::none
  {
    // Print the message.
    std::cout << "     [~]: " << message << '\n';
  }

  inline auto printEntry(const fn::strv obfuscatedWord, const fn::vec<fn::str>& definitions)
    -> fn::none
  {
    // Lambda to print the word view's decoration
    const auto printDecoration{
      [&obfuscatedWord]() -> fn::none
      {
        // Print the word view's decoration
        std::cout << "     +";
        for (const fn::cdef character : obfuscatedWord)
        {
          // Ignore the character
          std::ignore = character;

          // Print
          std::cout << "---+";
        }

        // Print empty line
        std::cout << '\n';
      }
    };

    // Print the word view's first line
    printDecoration();

    // Print the word view's second line
    std::cout << "     |";
    for (const fn::cdef character : obfuscatedWord)
    {
      std::cout << std::format(" {} |", std::toupper(character, std::locale()));
    }

    // Print empty line
    std::cout << '\n';

    // Print the word view's third line
    printDecoration();

    // Print empty line
    std::cout << '\n';

    // Print subtitle
    printSubtitle("DEFINITIONS", "");

    // Print the definitions
    for (const auto& definition : definitions)
    {
      std::cout << "     [?]: " << definition << '\n';
    }
  }
} // namespace IO
