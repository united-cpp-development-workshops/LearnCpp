#include "pch.hpp"

#include "Core/crypt.hpp"

#include "Core/charset.hpp"
#include "Core/constants.hpp"
#include "Random/random.hpp"

#include <Foundation/errors.hpp>
#include <Foundation/Support/narrow.ipp>
#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>

#include <algorithm>
#include <cassert>
#include <format>
#include <iterator>

namespace Core
{
  [[nodiscard]] auto encrypt(const fn::strv plaintext) -> fn::pair<fn::str, fn::str>
  {
    // Generate a random secret key
    const auto secret{Random::generateRandomString(SECRET_SIZE)};

    // Get the character set
    const auto& charset{getCharset()};

    // Create the ciphertext
    fn::str ciphertext{};

    // Get the size of the plaintext
    const auto plaintextSize{plaintext.size()};

    // Reserve the memory for the ciphertext
    ciphertext.reserve(plaintextSize);

    for (fn::size index{}; index < plaintextSize; ++index)
    {
      // ---------- PLAINTEXT CHARACTER ---------- //

      // Get the plaintext character
      const auto& pChar{plaintext.at(index)};

      // Get the iterator for the plaintext character in the charset
      const auto pcIt{std::ranges::find(charset, pChar)};

      // Check if the charset includes the plaintext character
      if (pcIt == charset.end())
      {
        throw fn::InputError{
          "Plaintext contains an invalid character!", std::format("Character was '{}'.", pChar)
        };
      }

      // Get the distance for the plaintext character in the charset
      const auto pDistance{std::distance(charset.begin(), pcIt)};

      // ---------- SECRET CHARACTER ---------- //

      // Calculate the index of the secret character
      const auto& sChar{secret.at((index + secret.size()) % secret.size())};

      // Get the iterator for the secret character in the charset
      const auto scIt{std::ranges::find(charset, sChar)};

      // Assert that the charset includes the secret character
      assert(scIt != charset.end());

      // Get the distance for the secret character in the charset
      const auto sDistance{std::distance(charset.begin(), scIt)};

      // ---------- CIPHERTEXT CHARACTER ---------- //

      // Encrypt the plaintext character
      ciphertext += charset.at(
        (fn::narrow_cast<fn::size>(pDistance) + fn::narrow_cast<fn::size>(sDistance)
         + charset.size())
        % charset.size()
      );
    }

    // Return the ciphertext and the secret key
    return {ciphertext, secret};
  }

  [[nodiscard]] auto decrypt(const fn::strv ciphertext, const fn::strv secret) -> fn::str
  {
    // Get the character set
    const auto& charset{getCharset()};

    // Create the plaintext
    fn::str plaintext{};

    // Get the size of the ciphertext
    const auto ciphertextSize{ciphertext.size()};

    // Reserve the memory for the plaintext
    plaintext.reserve(ciphertextSize);

    for (fn::size index{}; index < ciphertextSize; ++index)
    {
      // ---------- CIPHERTEXT CHARACTER ---------- //

      // Get the ciphertext character
      const auto& cChar{ciphertext.at(index)};

      // Get the iterator for the ciphertext character in the charset
      const auto ccIt{std::ranges::find(charset, cChar)};

      // Check if the charset includes the ciphertext character
      if (ccIt == charset.end())
      {
        throw fn::InputError{
          "Ciphertext contains an invalid character!", std::format("Character was '{}'.", cChar)
        };
      }

      // Get the distance for the ciphertext character in the charset
      const auto cDistance{std::distance(charset.begin(), ccIt)};

      // ---------- SECRET CHARACTER ---------- //

      // Calculate the index of the secret character
      const auto& sChar{secret.at((index + secret.size()) % secret.size())};

      // Get the iterator for the secret character in the charset
      const auto scIt{std::ranges::find(charset, sChar)};

      // Assert that the charset includes the secret character
      assert(scIt != charset.end());

      // Get the distance for the secret character in the charset
      const auto sDistance{std::distance(charset.begin(), scIt)};

      // ---------- PLAINTEXT CHARACTER ---------- //

      // Decrypt the ciphertext character
      plaintext += charset.at(
        ((fn::narrow_cast<fn::size>(cDistance) - fn::narrow_cast<fn::size>(sDistance))
         + charset.size())
        % charset.size()
      );
    }
    return plaintext;
  }
} // namespace Core
