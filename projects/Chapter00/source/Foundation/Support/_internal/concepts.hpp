#pragma once

#include <type_traits>

namespace fn::inline Support::_internal
{
  /**
   * @brief Concept that checks if a type is arithmetic.
   */
  template <typename Id>
  concept Arithmetic = std::is_arithmetic_v<Id>;

  /**
   * @brief Concept that checks if a type is non-arithmetic.
   */
  template <typename Id>
  concept NonArithmetic = not Arithmetic<Id>;
} // namespace fn::inline Support::_internal
