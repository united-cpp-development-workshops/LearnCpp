#pragma once

#include <type_traits>

namespace fn::inline Support::Internal
{
  /**
   * @brief Concept that checks if a type is arithmetic.
   */
  template <typename T>
  concept Arithmetic = std::is_arithmetic_v<T>;

  /**
   * @brief Concept that checks if a type is non-arithmetic.
   */
  template <typename T>
  concept NonArithmetic = not Arithmetic<T>;
} // namespace fn::inline Support::Internal
