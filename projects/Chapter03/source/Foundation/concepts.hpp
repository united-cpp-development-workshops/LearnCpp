#pragma once

#include <concepts>
#include <ostream>
#include <type_traits>

namespace fn
{
  /**
   * @brief Concept that checks if a type is arithmetic.
   */
  template <typename Type>
  concept IsArithmetic = std::is_arithmetic_v<Type>;

  /**
   * @brief Concept that checks if a type is non-arithmetic.
   */
  template <typename Type>
  concept IsNonArithmetic = not IsArithmetic<Type>;

  /**
   * @brief Concept that checks if a type is printable.
   */
  template <typename Type>
  concept IsPrintable = requires(Type type, std::ostream& os) {
    { os << type } -> std::same_as<std::ostream&>;
  };

  /**
   * @brief Concept that checks if a type is movable.
   */
  template <typename Type>
  concept IsMovable = std::movable<Type>;
} // namespace fn
