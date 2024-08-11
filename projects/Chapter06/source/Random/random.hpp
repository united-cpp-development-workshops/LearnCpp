#pragma once

#include <Foundation/types.hpp>

namespace Random
{
  /**
   * @brief   Returns a random string of the specified size.
   * @param   size The size of the string to generate.
   * @returns The random string.
   */
  [[nodiscard]] auto generateRandomString(fn::size size) -> fn::str;
} // namespace Random
