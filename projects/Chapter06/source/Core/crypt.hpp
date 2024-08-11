#pragma once

#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>

namespace Core
{
  /**
   * @brief   Encrypts a plaintext string using a random secret key.
   * @details The encryption algorithm is a variation of the Caesar cipher. This function generates
   *          a random secret key and uses it to encrypt the plaintext.
   * @param   plaintext The plaintext to encrypt.
   * @returns A pair containing the ciphertext and the secret key.
   * @throws  fn::InputError If the plaintext contains an invalid character.
   */
  [[nodiscard]] auto encrypt(fn::strv plaintext) -> fn::pair<fn::str, fn::str>;

  /**
   * @brief   Decrypts a ciphertext string using a secret key.
   * @details The decryption algorithm is a variation of the Caesar cipher. This function uses the
   *          secret key to decrypt the ciphertext.
   * @param   ciphertext The ciphertext to decrypt.
   * @param   secret     The secret key to use for decryption.
   * @returns The decrypted plaintext.
   * @throws  fn::InputError If the ciphertext contains an invalid character.
   */
  [[nodiscard]] auto decrypt(fn::strv ciphertext, fn::strv secret) -> fn::str;
} // namespace Core
