#pragma once

#include "Foundation/_internal/Exception/Exception.ipp"
#include "Foundation/_internal/Exception/Name.ipp"
#include "Foundation/types.hpp"

// -----------------------------< Alias Macros >----------------------------- //
#define EXCEPTION fn::_internal::Exception::Exception
#define NAME      fn::_internal::Exception::Name

// NOLINTBEGIN(bugprone-throw-keyword-missing,
// clang-diagnostic-ctad-maybe-unsupported)

namespace fn
{
  /**
   * @brief An exception type for errors related to unexpected enumerated
   * values.
   * @remark Use this exception to signal that an unexpected value was found
   * in an enumeration.
   */
  using EnumValueError = EXCEPTION<NAME{"EnumValueError"}, unit>;

  /**
   * @brief An exception type for errors related to narrowing conversions.
   * @details This exception is thrown by the @ref fn::narrow_cast function when
   * a narrowing conversion is detected.
   * @attention Only use this exception in catch blocks as it is not meant to
   * be thrown by the user.
   */
  using NarrowingError = EXCEPTION<NAME{"NarrowingError"}, unit>;
} // namespace fn

// NOLINTEND(bugprone-throw-keyword-missing,
// clang-diagnostic-ctad-maybe-unsupported)

// -----------------------------< Alias Macros >----------------------------- //
#undef EXCEPTION
#undef NAME
