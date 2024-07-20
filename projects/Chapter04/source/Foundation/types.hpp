#pragma once

#include <cstddef>
#include <cstdint>
#include <variant>

namespace fn
{
  /*--------------------------------------------------------------------------*\
  *| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Void >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
  \*--------------------------------------------------------------------------*/

  /**
   * @brief A type that represents the absence of a value.
   */
  using none = void;

  /*--------------------------------------------------------------------------*\
  *| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Pointers >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
  \*--------------------------------------------------------------------------*/

  /**
   * @brief A type that represents a signed integer large enough to hold a
   * pointer.
   */
  using iptr = std::intptr_t;

  /**
   * @brief A type that represents an unsigned integer large enough to hold a
   * pointer.
   */
  using uptr = std::uintptr_t;

  /**
   * @brief A type that represents a null pointer.
   */
  using nptr = std::nullptr_t;

  /*--------------------------------------------------------------------------*\
  *| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Booleans >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
  \*--------------------------------------------------------------------------*/

  /**
   * @brief A type that represents a boolean value.
   */
  using bln = bool;

  /*--------------------------------------------------------------------------*\
  *| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Integers >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
  \*--------------------------------------------------------------------------*/

  /**
   * @brief A type that represents a signed integer with exactly 8 bits in size.
   */
  using i8 = std::int8_t;

  /**
   * @brief A type that represents a signed integer with exactly 16 bits in
   * size.
   */
  using i16 = std::int16_t;

  /**
   * @brief A type that represents a signed integer with exactly 32 bits in
   * size.
   */
  using i32 = std::int32_t;

  /**
   * @brief A type that represents a signed integer with exactly 64 bits in
   * size.
   */
  using i64 = std::int64_t;

  /**
   * @brief A type that represents an unsigned integer with exactly 8 bits in
   * size.
   */
  using u8 = std::uint8_t;

  /**
   * @brief A type that represents an unsigned integer with exactly 16 bits in
   * size.
   */
  using u16 = std::uint16_t;

  /**
   * @brief A type that represents an unsigned integer with exactly 32 bits in
   * size.
   */
  using u32 = std::uint32_t;

  /**
   * @brief A type that represents an unsigned integer with exactly 64 bits in
   * size.
   */
  using u64 = std::uint64_t;

  /**
   * @brief A type that represents a signed integer with at least 8 bits in
   * size.
   */
  using i8l = std::int_least8_t;

  /**
   * @brief A type that represents a signed integer with at least 16 bits in
   * size.
   */
  using i16l = std::int_least16_t;

  /**
   * @brief A type that represents a signed integer with at least 32 bits in
   * size.
   */
  using i32l = std::int_least32_t;

  /**
   * @brief A type that represents a signed integer with at least 64 bits in
   * size.
   */
  using i64l = std::int_least64_t;

  /**
   * @brief A type that represents an unsigned integer with at least 8 bits in
   * size.
   */
  using u8l = std::uint_least8_t;

  /**
   * @brief A type that represents an unsigned integer with at least 16 bits in
   * size.
   */
  using u16l = std::uint_least16_t;

  /**
   * @brief A type that represents an unsigned integer with at least 32 bits in
   * size.
   */
  using u32l = std::uint_least32_t;

  /**
   * @brief A type that represents an unsigned integer with at least 64 bits in
   * size.
   */
  using u64l = std::uint_least64_t;

  /**
   * @brief A type that represents the fastest signed integer with at least 8
   * bits in size.
   */
  using i8f = std::int_fast8_t;

  /**
   * @brief A type that represents the fastest signed integer with at least 16
   * bits in size.
   */
  using i16f = std::int_fast16_t;

  /**
   * @brief A type that represents the fastest signed integer with at least 32
   * bits in size.
   */
  using i32f = std::int_fast32_t;

  /**
   * @brief A type that represents the fastest signed integer with at least 64
   * bits in size.
   */
  using i64f = std::int_fast64_t;

  /**
   * @brief A type that represents the fastest unsigned integer with at least 8
   * bits in size.
   */
  using u8f = std::uint_fast8_t;

  /**
   * @brief A type that represents the fastest unsigned integer with at least 16
   * bits in size.
   */
  using u16f = std::uint_fast16_t;

  /**
   * @brief A type that represents the fastest unsigned integer with at least 32
   * bits in size.
   */
  using u32f = std::uint_fast32_t;

  /**
   * @brief A type that represents the fastest unsigned integer with at least 64
   * bits in size.
   */
  using u64f = std::uint_fast64_t;

  /**
   * @brief A type that represents platform-specific signed integer.
   */
  using idef = int;

  /**
   * @brief A type that represents platform-specific unsigned integer.
   */
  using udef = unsigned int;

  /**
   * @brief A type that represents the largest signed integer.
   */
  using imax = std::intmax_t;

  /**
   * @brief A type that represents the largest unsigned integer.
   */
  using umax = std::uintmax_t;

  /**
   * @brief A type that represents the size of an object.
   */
  using size = std::size_t;

  /*--------------------------------------------------------------------------*\
  *| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Floats >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
  \*--------------------------------------------------------------------------*/

  /**
   * @brief A type that represents platform-specific single-precision
   * floating-point number.
   */
  using f32 = float;

  /**
   * @brief A type that represents platform-specific double-precision
   * floating-point number.
   */
  using f64 = double;

  /**
   * @brief A type that represents platform-specific largest floating-point
   * number.
   */
  using fmax = long double;

  /*--------------------------------------------------------------------------*\
  *| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Chars >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
  \*--------------------------------------------------------------------------*/

  /**
   * @brief A type that represents a character with exactly 8 bits in size.
   */
  using c8 = char8_t;

  /**
   * @brief A type that represents a character with exactly 16 bits in size.
   */
  using c16 = char16_t;

  /**
   * @brief A type that represents a character with exactly 32 bits in size.
   */
  using c32 = char32_t;

  /**
   * @brief A type that represents platform-specific character.
   */
  using cdef = char;

  /**
   * @brief A type that represents platform-specific wide character.
   */
  using wdef = wchar_t;

  /*--------------------------------------------------------------------------*\
  *| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Strings >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
  \*--------------------------------------------------------------------------*/

  /**
   * @brief A type that represents a constant pointer to a character with
   * exactly 8 bits in size.
   */
  using c8str = const c8*;

  /**
   * @brief A type that represents a constant pointer to a character with
   * exactly 16 bits in size.
   */
  using c16str = const c16*;

  /**
   * @brief A type that represents a constant pointer to a character with
   * exactly 32 bits in size.
   */
  using c32str = const c32*;

  /**
   * @brief A type that represents a constant pointer to a platform-specific
   * character.
   */
  using cstr = const cdef*;

  /**
   * @brief A type that represents a constant pointer to a platform-specific
   * wide character.
   */
  using wstr = const wdef*;

  /*--------------------------------------------------------------------------*\
  *| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Others >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
  \*--------------------------------------------------------------------------*/

  /**
   * @brief A type that represents a unit value.
   */
  using unit = std::monostate;
} // namespace fn
