#pragma once

#include <Foundation/types.hpp>

namespace Random
{
  /**
   * @brief   Returns a random number.
   * @param   min The min value.
   * @param   max The max value.
   * @returns The random number.
   */
  [[nodiscard]] auto generateRandomInRange(fn::size min, fn::size max) -> fn::size;
} // namespace Random
