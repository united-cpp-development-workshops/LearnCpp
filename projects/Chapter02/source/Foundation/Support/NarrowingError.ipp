#pragma once

#include "Foundation/types.hpp"

#include <exception>

namespace fn::inline Support
{
  /**
   * @class NarrowingError
   * @brief Exception class for narrowing errors.
   * @details The 'NarrowingError' class is a custom exception derived from the
   * 'std::exception' class. It is used to signal errors related to narrowing
   * conversions.
   */
  class NarrowingError : public std::exception
  {
  public:
    /**
     * @brief Get the error message.
     * @returns A constant character string describing the error.
     */
    [[nodiscard]]
    constexpr auto what() const noexcept -> cstr override;
  };
} // namespace fn::inline Support

/*----------------------------------------------------------------------------*\
*| >>>>>>>>>>>>>>>>>>>>>>>>>>>>> Implementation <<<<<<<<<<<<<<<<<<<<<<<<<<<<< |*
\*----------------------------------------------------------------------------*/

namespace fn::inline Support
{
  constexpr auto NarrowingError::what() const noexcept -> cstr
  {
    return "Narrowing error";
  }
} // namespace fn::inline Support
