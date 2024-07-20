#pragma once

#include "Foundation/concepts.hpp"

#include "Foundation/types.hpp"

#include <concepts>

namespace fn::_internal::Exception::_internal
{
  /**
   * @brief Concept to check if a type can be a Context.
   */
  template <typename Type>
  concept IsContext = std::same_as<Type, unit>
                   or (IsMovable<Type> and IsPrintable<Type>);
} // namespace fn::_internal::Exception::_internal
