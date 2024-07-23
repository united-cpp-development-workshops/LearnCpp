#pragma once

#include <type_traits>

namespace fn::inline Support::_internal
{
  /**
   * @brief Concept that checks if a type is arithmetic.
   */
  template <typename Type>
  concept Arithmetic = std::is_arithmetic_v<Type>;

  /**
   * @brief Concept that checks if a type is non-arithmetic.
   */
  template <typename Type>
  concept NonArithmetic = not Arithmetic<Type>;
} // namespace fn::inline Support::_internal
