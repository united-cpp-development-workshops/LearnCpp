#pragma once

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>

namespace Core
{
  /**
   * @brief   Returns the character set used by the Caesar cipher.
   * @returns The character set.
   */
  [[nodiscard]] auto getCharset() -> const fn::vec<fn::cdef>&;
} // namespace Core
