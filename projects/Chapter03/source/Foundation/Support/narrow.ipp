#pragma once

#include "Foundation/concepts.hpp"
#include "Foundation/errors.hpp"
#include "Foundation/types.hpp"

namespace fn::Support
{
  /**
   * @brief Implementation of Guidelines Support Library's @b narrow function
   * that runs on arithmetic types.
   * @param[in] value The value to cast.
   * @tparam To The type to cast to.
   * @tparam From The type to cast from.
   * @returns The casted value.
   * @throws NarrowingError If the value or sign changed during the cast.
   * @attention Must be preferred over static_cast for narrowing conversions.
   */
  template <IsArithmetic To, IsArithmetic From>
  constexpr auto narrow_cast(From value) -> To;

  /**
   * @brief Implementation of Guidelines Support Library's @b narrow function
   * that runs on non-arithmetic types.
   * @param[in] value The value to cast.
   * @tparam To The type to cast to.
   * @tparam From The type to cast from.
   * @returns The casted value.
   * @throws NarrowingError If the value changed during the cast.
   * @attention Must be preferred over static_cast for narrowing conversions.
   */
  template <IsNonArithmetic To, IsNonArithmetic From>
  constexpr auto narrow_cast(From value) -> To;
} // namespace fn::Support

/*----------------------------------------------------------------------------*\
*| <<<<<<<<<<<<<<<<<<<<<<<<<<<<< Implementation >>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
\*----------------------------------------------------------------------------*/

namespace fn::Support
{
#pragma warning(push)
#pragma warning(disable : 26'467 26'472)

  template <IsArithmetic To, IsArithmetic From>
  constexpr auto narrow_cast(From value) -> To
  {
    // Check if signedness is different
    constexpr fn::bln
      DIFFERENT_SIGNEDNESS{std::is_signed_v<To> != std::is_signed_v<From>};

    // Static cast the value
    const auto castedValue{static_cast<To>(value)};

    // Throw error if the value or sign changed
    if (static_cast<From>(castedValue) != value
        or (DIFFERENT_SIGNEDNESS and ((castedValue < To{}) != (value < From{}))))
    {
      throw NarrowingError{};
    }

    // Return the casted value
    return castedValue;
  }

  template <IsNonArithmetic To, IsNonArithmetic From>
  constexpr auto narrow_cast(From value) -> To
  {
    // Static cast the value
    const auto castedValue{static_cast<To>(value)};

    // Throw error if the value changed
    if (static_cast<From>(castedValue) != value) { throw NarrowingError{}; }

    // Return the casted value
    return castedValue;
  }

#pragma warning(pop)
} // namespace fn::Support

/*----------------------------------------------------------------------------*\
*| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Promotes >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
\*----------------------------------------------------------------------------*/

// NOLINTBEGIN(misc-unused-using-decls)

namespace fn
{
  using Support::narrow_cast;
} // namespace fn

// NOLINTEND(misc-unused-using-decls)
