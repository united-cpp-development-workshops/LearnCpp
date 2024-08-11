#include "pch.hpp"

#include "Core/constants.hpp"
#include "Core/crypt.hpp"
#include "IO/io.ipp"

#include <Foundation/constants.hpp>
#include <Foundation/errors.hpp>
#include <Foundation/types.hpp>
#include <Foundation/Utility/log.ipp>
#include <Foundation/Utility/what.ipp>

#include <exception>
#include <iostream>
#include <string>

auto main() noexcept -> fn::idef
try
{
  // Main loop
  while (true)
  {
    // Print app title
    IO::printSectionDivider();
    IO::printAppTitle();
    IO::printSectionDivider();
    IO::printTitle("MAIN MENU");
    IO::printParagraph("Please select an option from the menu below:");
    IO::printMenuOption("Encrypt", "Encrypt a string.", Core::ENCRYPT_OPTION);
    IO::printMenuOption("Decrypt", "Decrypt a string.", Core::DECRYPT_OPTION);
    IO::printMenuOption("Exit   ", "Exit the application.", Core::EXIT_OPTION);

    // Get the user input
    fn::i16l option{};
    IO::printInputPrompt("Enter an option.");
    std::cin >> option;

    // Process the user input
    switch (option)
    {
    case Core::ENCRYPT_OPTION:
    {
      IO::printSectionDivider();
      IO::printTitle("ENCRYPT");
      IO::printParagraph("This option will encrypt a string using a random secret key.");

      // Get the plaintext
      fn::str plaintext{};
      IO::printInputPrompt("Enter the plaintext to encrypt.");
      std::getline(std::cin, plaintext);

      // Inform the user that the plaintext is being encrypted
      IO::printLoadingMessage("Encrypting the plain text...");

      // Encrypt the plaintext
      const auto [ciphertext, secret]{Core::encrypt(plaintext)};

      IO::printSectionDivider();
      IO::printTitle("ENCRYPTED");

      // Print the ciphertext and secret
      IO::printSubtitle("Ciphertext", ciphertext);
      IO::printSubtitle("Secret", secret);
      break;
    }
    case Core::DECRYPT_OPTION:
    {
      IO::printSectionDivider();
      IO::printTitle("DECRYPT");
      IO::printParagraph("This option will decrypt a string using a secret key.");

      // Get the ciphertext
      fn::str ciphertext{};
      IO::printInputPrompt("Enter the ciphertext to decrypt.");
      std::getline(std::cin, ciphertext);

      // Get the secret
      fn::str secret{};
      IO::printInputPrompt("Enter the secret key.");
      std::getline(std::cin, secret);

      // Inform the user that the ciphertext is being decrypted
      IO::printLoadingMessage("Decrypting the cipher text...");

      // Decrypt the ciphertext
      const auto plaintext{Core::decrypt(ciphertext, secret)};

      IO::printSectionDivider();
      IO::printTitle("DECRYPTED");

      // Print the plaintext
      IO::printSubtitle("Plaintext", plaintext);
      break;
    }
    case Core::EXIT_OPTION:
    {
      // Exit the application
      return fn::EXIT_SUCCESS_CODE;
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
catch (const fn::InputError& error)
{
  // Log error
  fn::elog(error);

  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
catch (const std::exception& exception)
{
  // Log exception
  fn::elog(fn::what(exception));

  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
catch (...)
{
  // Log unknown exception
  fn::elog(fn::UNKNOWN_EXCEPTION);

  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
