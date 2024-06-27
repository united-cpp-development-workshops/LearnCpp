#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <GSL/narrow>

// -------------------------------< Integers >------------------------------- //

// Fixed width integers
using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;
using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

// At least width integers
using i8l  = std::int_least8_t;
using i16l = std::int_least16_t;
using i32l = std::int_least32_t;
using i64l = std::int_least64_t;
using u8l  = std::uint_least8_t;
using u16l = std::uint_least16_t;
using u32l = std::uint_least32_t;
using u64l = std::uint_least64_t;

// Fast at least width integers
using i8f  = std::int_fast8_t;
using i16f = std::int_fast16_t;
using i32f = std::int_fast32_t;
using i64f = std::int_fast64_t;
using u8f  = std::uint_fast8_t;
using u16f = std::uint_fast16_t;
using u32f = std::uint_fast32_t;
using u64f = std::uint_fast64_t;

// Platform integers
using idef = int;
using udef = unsigned int;
using imax = std::intmax_t;
using umax = std::uintmax_t;

// Size type
using size = std::size_t;

// --------------------------------< Floats >-------------------------------- //
using f32 = float;
using f64 = double;

// --------------------------------< Chars >--------------------------------- //

// Character types
using c8  = char8_t;
using c16 = char16_t;
using c32 = char32_t;

// Platform chars
using cdef = char;
using wdef = wchar_t;

// -------------------------------< Strings >-------------------------------- //

// C-style strings
using cstr = const cdef*;
using wstr = const wdef*;

// -------------------------------< Wrappers >------------------------------- //

// NOLINTBEGIN(misc-unused-using-decls)

// Narrowing
using gsl::narrow;

// NOLINTEND(misc-unused-using-decls)

// NOLINTBEGIN(clang-diagnostic-unused-const-variable)

// Exit codes
constexpr idef TERMINATE_SUCCESS{EXIT_SUCCESS};
constexpr idef TERMINATE_FAILURE{EXIT_FAILURE};

// NOLINTEND(clang-diagnostic-unused-const-variable)
