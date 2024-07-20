#pragma once

#include "Foundation/types.hpp"

#include <algorithm>
#include <span>

// NOLINTBEGIN(cppcoreguidelines-avoid-c-arrays, hicpp-avoid-c-arrays,
// modernize-avoid-c-arrays)

namespace fn::_internal::Exception
{
  /**
   * @brief A fixed-length string that represents the name of an exception.
   * @tparam length The length of the name.
   */
  template <size length>
  struct Name
  {
  public:
    /*------------------------------------------------------------------------*\
    *| [public]: Constructors                                                 |*
    \*------------------------------------------------------------------------*/

    Name(const Name&) noexcept = delete;
    Name(Name&&) noexcept      = delete;
    Name() noexcept            = delete;

    /**
     * @brief Constructs a name from a C-style string.
     * @param name The C-style string.
     */
    constexpr explicit Name(const cdef (&name)[length]) noexcept;

    /*------------------------------------------------------------------------*\
    *| [public]: Destructor                                                   |*
    \*------------------------------------------------------------------------*/

    ~Name() noexcept = default;

    /*------------------------------------------------------------------------*\
    *| [public]: Operators                                                    |*
    \*------------------------------------------------------------------------*/

    auto operator=(const Name&) noexcept -> Name& = delete;
    auto operator=(Name&&) noexcept -> Name&      = delete;

    /*------------------------------------------------------------------------*\
    *| [public]: Fields                                                       |*
    \*------------------------------------------------------------------------*/

    cdef value[length]{};
  };
} // namespace fn::_internal::Exception

/*----------------------------------------------------------------------------*\
*| <<<<<<<<<<<<<<<<<<<<<<<<<<<<< Implementation >>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
\*----------------------------------------------------------------------------*/

namespace fn::_internal::Exception
{
  /*--------------------------------------------------------------------------*\
  *| [public]: Constructors                                                   |*
  \*--------------------------------------------------------------------------*/

  template <size length>
  constexpr Name<length>::Name(const cdef (&name)[length]) noexcept
  {
    std::copy_n(name, length, std::span<cdef>{value}.begin());
  }
} // namespace fn::_internal::Exception

// NOLINTEND(cppcoreguidelines-avoid-c-arrays, hicpp-avoid-c-arrays,
// modernize-avoid-c-arrays)
