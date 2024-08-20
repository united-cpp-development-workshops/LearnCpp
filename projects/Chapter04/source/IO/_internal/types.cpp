#include "pch.hpp"

#include "IO/_internal/types.hpp"

#include "IO/io.hpp"

#include <Foundation/concepts.hpp>
#include <Foundation/types.hpp>

#include <format>
#include <iostream>
#include <limits>

namespace IO::_internal
{
  // NOLINTNEXTLINE(readability-function-size)
  auto printBriefTypeInfo(const Option typeName) -> fn::none
  {
    // Using declarations
    using enum Option;

    std::cout << "   EXPLORE: '";

#pragma warning(push)
#pragma warning(disable : 4'061)

    // NOLINTBEGIN(clang-diagnostic-switch-enum)

    switch (typeName)
    {
    case T_NONE:
    {
      std::cout << "void'\n\n";

      std::cout << "     - A void type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Type with an empty set of values.\n";
      std::cout << "     - An incomplete type that cannot be completed.\n";
      return;
    }
    case T_IPTR:
    {
      std::cout << "std::intptr_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Unsigned integer type capable of holding a pointer to 'void'.\n";
      return;
    }
    case T_UPTR:
    {
      std::cout << "std::uintptr_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Signed integer type capable of holding a pointer to 'void'.\n";
      return;
    }
    case T_NPTR:
    {
      std::cout << "std::nullptr_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A type declaration.\n";
      std::cout << "     - Defined in 'cstddef'.\n";
      std::cout << "     - It's the type of the 'nullptr' literal.\n";
      std::cout << "     - It's not itself a pointer type or a pointer to member type.\n";
      return;
    }
    case T_BLN:
    {
      std::cout << "bool'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Capable of holding one of the two values: 'true' or 'false'.\n";
      std::cout << "     - The size of 'bool' is implementation defined.\n";
      return;
    }
    case T_I8:
    {
      std::cout << "std::int8_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Signed integer type with the size of exactly '8' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I16:
    {
      std::cout << "std::int16_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Signed integer type with the size of exactly '16' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I32:
    {
      std::cout << "std::int32_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Signed integer type with the size of exactly '32' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I64:
    {
      std::cout << "std::int64_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Signed integer type with the size of exactly '64' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_U8:
    {
      std::cout << "std::uint8_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Unsigned integer type with the size of exactly '8' bits.\n";
      return;
    }
    case T_U16:
    {
      std::cout << "std::uint16_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Unsigned integer type with the size of exactly '16' bits.\n";
      return;
    }
    case T_U32:
    {
      std::cout << "std::uint32_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Unsigned integer type with the size of exactly '32' bits.\n";
      return;
    }
    case T_U64:
    {
      std::cout << "std::uint64_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Unsigned integer type with the size of exactly '64' bits.\n";
      return;
    }
    case T_I8L:
    {
      std::cout << "std::int_least8_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest signed integer type with the size of at least '8' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I16L:
    {
      std::cout << "std::int_least16_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest signed integer type with the size of at least '16' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I32L:
    {
      std::cout << "std::int_least32_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest signed integer type with the size of at least '32' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I64L:
    {
      std::cout << "std::int_least64_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest signed integer type with the size of at least '64' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_U8L:
    {
      std::cout << "std::uint_least8_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest unsigned integer type with the size of at least '8' bits.\n";
      return;
    }
    case T_U16L:
    {
      std::cout << "std::uint_least16_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest unsigned integer type with the size of at least '16' bits.\n";
      return;
    }
    case T_U32L:
    {
      std::cout << "std::uint_least32_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest unsigned integer type with the size of at least '32' bits.\n";
      return;
    }
    case T_U64L:
    {
      std::cout << "std::uint_least64_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest unsigned integer type with the size of at least '64' bits.\n";
      return;
    }
    case T_I8F:
    {
      std::cout << "std::int_fast8_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest signed integer type with the size of at least '8' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I16F:
    {
      std::cout << "std::int_fast16_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest signed integer type with the size of at least '16' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I32F:
    {
      std::cout << "std::int_fast32_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest signed integer type with the size of at least '32' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I64F:
    {
      std::cout << "std::int_fast64_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest signed integer type with the size of at least '64' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_U8F:
    {
      std::cout << "std::uint_fast8_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest unsigned integer type with the size of at least '8' bits.\n";
      return;
    }
    case T_U16F:
    {
      std::cout << "std::uint_fast16_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest unsigned integer type with the size of at least '16' bits.\n";
      return;
    }
    case T_U32F:
    {
      std::cout << "std::uint_fast32_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest unsigned integer type with the size of at least '64' bits.\n";
      return;
    }
    case T_U64F:
    {
      std::cout << "std::uint_fast64_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest unsigned integer type with the size of at least '64' bits.\n";
      return;
    }
    case T_IDEF:
    {
      std::cout << "int'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Basic signed integer type.\n";
      std::cout << "     - The size of 'int' is implementation defined.\n";
      return;
    }
    case T_UDEF:
    {
      std::cout << "unsigned int'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Basic unsigned integer type.\n";
      std::cout << "     - The size of 'unsigned int' is implementation defined.\n";
      return;
    }
    case T_IMAX:
    {
      std::cout << "std::intmax_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Maximum-size signed integer.\n\n";
      return;
    }
    case T_UMAX:
    {
      std::cout << "std::uintmax_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Maximum-size unsigned integer.\n\n";
      return;
    }
    case T_SIZE:
    {
      std::cout << "std::size_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstddef'.\n";
      std::cout << "     - Unsigned integer returned by the 'sizeof' operator.\n";
      return;
    }
    case T_F32:
    {
      std::cout << "float'\n\n";

      std::cout << "     - A floating-point type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Single precision floating-point type.\n";
      std::cout << "     - Usually IEEE-754 binary32 format.\n";
      return;
    }
    case T_F64:
    {
      std::cout << "double'\n\n";

      std::cout << "     - A floating-point type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Double precision floating-point type.\n";
      std::cout << "     - Usually IEEE-754 binary64 format.\n";
      return;
    }
    case T_FMAX:
    {
      std::cout << "long double'\n\n";

      std::cout << "     - A floating-point type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Extended precision floating-point type.\n";
      std::cout << "     - Does not necessarily map to types mandated by IEEE-754.\n";
      return;
    }
    case T_C8:
    {
      std::cout << "char8_t'\n\n";

      std::cout << "     - A character type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Type for UTF-8 character representation.\n";
      std::cout << "     - It has the same size, signedness, and alignment as 'unsigned char'.\n";
      return;
    }
    case T_C16:
    {
      std::cout << "char16_t'\n\n";

      std::cout << "     - A character type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Type for UTF-16 character representation.\n";
      std::cout
        << "     - It has the same size, signedness, and alignment as 'std::uint_least16_t'.\n";
      return;
    }
    case T_C32:
    {
      std::cout << "char32_t'\n\n";

      std::cout << "     - A character type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Type for UTF-32 character representation.\n";
      std::cout
        << "     - It has the same size, signedness, and alignment as 'std::uint_least32_t'.\n";
      return;
    }
    case T_CDEF:
    {
      std::cout << "char'\n\n";

      std::cout << "     - A character type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Type that can be most efficiently processed on the target system.\n";
      std::cout << "     - The signedness of 'char' is implementation defined.\n";
      return;
    }
    case T_WDEF:
    {
      std::cout << "wchar_t'\n\n";

      std::cout << "     - A character type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Type for wide character representation.\n";
      std::cout << "     - It is considered as defect and removed.\n";
      return;
    }
    default:
    {
      // Should never reach here
      std::cout << "   ERROR: In 'explore' command!\n";
    }
    }

    // NOLINTEND(clang-diagnostic-switch-enum)

#pragma warning(pop)
  }

  // NOLINTNEXTLINE(readability-function-size)
  auto printTypeTips(const Option typeName) -> fn::none
  {
    // Using declarations
    using enum Option;

    std::cout << "   TIPS: '";

#pragma warning(push)
#pragma warning(disable : 4'061)

    // NOLINTBEGIN(clang-diagnostic-switch-enum)

    switch (typeName)
    {
    case T_NONE:
    {
      std::cout << "void'\n\n";

      std::cout << "     - In modern C++, void has only one concrete use case.\n";
      std::cout << "     - It's used as the return type for functions that don't return.\n";
      std::cout << "     - Not advised but it can be used as 'void*' for generic pointers.\n";
      return;
    }
    case T_IPTR:
    {
      std::cout << "std::intptr_t' (optional)\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Useful for performing pointer arithmetic or pointer manipulation.\n";
      std::cout << "     - Use when you need to cast a pointer to an integer type.\n";
      std::cout << "     - This is an optional type, may not be available on all platforms.\n";
      return;
    }
    case T_UPTR:
    {
      std::cout << "std::uintptr_t' (optional)\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Useful when you need an unsigned integer portrayal of a pointer.\n";
      std::cout << "     - Use when you need to cast a pointer to an unsigned integer type.\n";
      std::cout << "     - This is an optional type, may not be available on all platforms.\n";
      return;
    }
    case T_NPTR:
    {
      std::cout << "std::nullptr_t'\n\n";

      std::cout << "     - Include 'cstddef' header to use.\n";
      std::cout << "     - Mostly used when overloading functions.\n";
      std::cout << "     - It can be used as parameter to functions that handle 'nullptr'.\n";
      std::cout << "     - Helps to avoid the accidental misuse of '0' as 'nullptr'.\n";
      std::cout << "     - Helps to avoid implicit pointer casts from integer types.\n";
      return;
    }
    case T_BLN:
    {
      std::cout << "bool'\n\n";

      std::cout << "     - Use for logical operations and conditional statements.\n";
      std::cout << "     - You can use 'bool' as flags or binary states.\n";
      std::cout << "     - Initialize 'bool' variables, they wont be initialized implicitly.\n";
      std::cout << "     - Use boolean expressions directly in conditional statements.\n";
      std::cout << "     - Avoid implicit conversions, use boolean arithmetic when assigning.\n";
      return;
    }
    case T_I8:
    {
      std::cout << "std::int8_t' (optional)\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use when memory constraints at maximum.\n";
      std::cout
        << "     - Don't use it for arithmetic operations, usually it is a character type.\n";
      std::cout << "     - It ensures platform independence, because it's fixed in size.\n";
      std::cout << "     - This is an optional type, may not be available on all platforms.\n";
      return;
    }
    case T_I16:
    {
      std::cout << "std::int16_t' (optional)\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use when memory efficiency is a concern.\n";
      std::cout << "     - Beware for implicit conversions, use explicit cast when needed.\n";
      std::cout << "     - It ensures platform independence, because it's fixed in size.\n";
      std::cout << "     - This is an optional type, may not be available on all platforms.\n";
      return;
    }
    case T_I32:
    {
      std::cout << "std::int32_t' (optional)\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use when portability concerns is at maximum.\n";
      std::cout << "     - Beware for implicit conversions, use explicit cast when needed.\n";
      std::cout << "     - It ensures platform independence, because it's fixed in size.\n";
      std::cout << "     - This is an optional type, may not be available on all platforms.\n";
      return;
    }
    case T_I64:
    {
      std::cout << "std::int64_t' (optional)\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use for large numbers and with portability concerns.\n";
      std::cout << "     - Beware for implicit conversions, use explicit cast when needed.\n";
      std::cout << "     - It ensures platform independence, because it's fixed in size.\n";
      std::cout << "     - This is an optional type, may not be available on all platforms.\n";
      return;
    }
    case T_U8:
    {
      std::cout << "std::uint8_t' (optional)\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use when memory constraints at maximum.\n";
      std::cout
        << "     - Don't use it for arithmetic operations, usually it is a character type.\n";
      std::cout << "     - Don't use unsigned types for arithmetic operations, use signed types.\n";
      std::cout << "     - Beware of the overflows, unsigned types act differently.\n";
      std::cout << "     - It ensures platform independence, because it's fixed in size.\n";
      std::cout << "     - This is an optional type, may not be available on all platforms.\n";
      return;
    }
    case T_U16:
    {
      std::cout << "std::uint16_t' (optional)\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use when memory efficiency is a concern.\n";
      std::cout << "     - Beware for implicit conversions, use explicit cast when needed.\n";
      std::cout << "     - Don't use unsigned types for arithmetic operations, use signed types.\n";
      std::cout << "     - Beware of the overflows, unsigned types act differently.\n";
      std::cout << "     - It ensures platform independence, because it's fixed in size.\n";
      std::cout << "     - This is an optional type, may not be available on all platforms.\n";
      return;
    }
    case T_U32:
    {
      std::cout << "std::uint32_t' (optional)\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use when portability concerns is at maximum.\n";
      std::cout << "     - Beware for implicit conversions, use explicit cast when needed.\n";
      std::cout << "     - Don't use unsigned types for arithmetic operations, use signed types.\n";
      std::cout << "     - Beware of the overflows, unsigned types act differently.\n";
      std::cout << "     - It ensures platform independence, because it's fixed in size.\n";
      std::cout << "     - This is an optional type, may not be available on all platforms.\n";
      return;
    }
    case T_U64:
    {
      std::cout << "std::uint64_t' (optional)\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use for large numbers and with portability concerns.\n";
      std::cout << "     - Beware for implicit conversions, use explicit cast when needed.\n";
      std::cout << "     - Don't use unsigned types for arithmetic operations, use signed types.\n";
      std::cout << "     - Beware of the overflows, unsigned types act differently.\n";
      std::cout << "     - It ensures platform independence, because it's fixed in size.\n";
      std::cout << "     - This is an optional type, may not be available on all platforms.\n";
      return;
    }
    case T_I8L:
    {
      std::cout << "std::int_least8_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout
        << "     - Use when memory constraints at maximum, but exact size doesn't matter.\n";
      std::cout << "     - Don't use it for arithmetic operations, it may be a character type.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_I16L:
    {
      std::cout << "std::int_least16_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout
        << "     - Use when memory efficiency is a concern, but exact size doesn't matter.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_I32L:
    {
      std::cout << "std::int_least32_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use when portability is important, but exact size doesn't matter.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_I64L:
    {
      std::cout << "std::int_least64_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use for large numbers and portability, but exact size doesn't matter.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_U8L:
    {
      std::cout << "std::uint_least8_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout
        << "     - Use when memory constraints at maximum, but exact size doesn't matter.\n";
      std::cout << "     - Don't use it for arithmetic operations, it may be a character type.\n";
      std::cout << "     - Don't use unsigned types for arithmetic operations, use signed types.\n";
      std::cout << "     - Beware of the overflows, unsigned types act differently.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_U16L:
    {
      std::cout << "std::uint_least16_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use when memory efficiency do but exact size doesn't matter.\n";
      std::cout << "     - Don't use unsigned types for arithmetic operations, use signed types.\n";
      std::cout << "     - Beware of the overflows, unsigned types act differently.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_U32L:
    {
      std::cout << "std::uint_least32_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use when portability is important, but exact size doesn't matter.\n";
      std::cout << "     - Don't use unsigned types for arithmetic operations, use signed types.\n";
      std::cout << "     - Beware of the overflows, unsigned types act differently.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_U64L:
    {
      std::cout << "std::uint_least64_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use for large numbers and portability, but exact size doesn't matter.\n";
      std::cout << "     - Don't use unsigned types for arithmetic operations, use signed types.\n";
      std::cout << "     - Beware of the overflows, unsigned types act differently.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_I8F:
    {
      std::cout << "std::int_fast8_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use when memory concerns at maximum, but exact size doesn't matter.\n";
      std::cout << "     - It is optimized for speed, use for arithmetic performance.\n";
      std::cout << "     - Don't use it for arithmetic operations, it may be a character type.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_I16F:
    {
      std::cout << "std::int_fast16_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use when memory efficiency do but exact size doesn't matter.\n";
      std::cout << "     - It is optimized for speed, use for arithmetic performance.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_I32F:
    {
      std::cout << "std::int_fast32_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use when portability is important, but exact size doesn't matter.\n";
      std::cout << "     - It is optimized for speed, use for arithmetic performance.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_I64F:
    {
      std::cout << "std::int_fast64_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use for large numbers and portability, but exact size doesn't matter.\n";
      std::cout << "     - It is optimized for speed, use for arithmetic performance.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_U8F:
    {
      std::cout << "std::uint_fast8_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use when memory concerns at maximum, but exact size doesn't matter.\n";
      std::cout << "     - It is optimized for speed, use for arithmetic performance.\n";
      std::cout << "     - Don't use it for arithmetic operations, it may be a character type.\n";
      std::cout << "     - Don't use unsigned types for arithmetic operations, use signed types.\n";
      std::cout << "     - Beware of the overflows, unsigned types act differently.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_U16F:
    {
      std::cout << "std::uint_fast16_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use when memory efficiency do but exact size doesn't matter.\n";
      std::cout << "     - It is optimized for speed, use for arithmetic performance.\n";
      std::cout << "     - Don't use unsigned types for arithmetic operations, use signed types.\n";
      std::cout << "     - Beware of the overflows, unsigned types act differently.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_U32F:
    {
      std::cout << "std::uint_fast32_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use when portability is important, but exact size doesn't matter.\n";
      std::cout << "     - It is optimized for speed, use for arithmetic performance.\n";
      std::cout << "     - Don't use unsigned types for arithmetic operations, use signed types.\n";
      std::cout << "     - Beware of the overflows, unsigned types act differently.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_U64F:
    {
      std::cout << "std::uint_fast64_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - Use for large numbers and portability, but exact size doesn't matter.\n";
      std::cout << "     - It is optimized for speed, use for arithmetic performance.\n";
      std::cout << "     - Don't use unsigned types for arithmetic operations, use signed types.\n";
      std::cout << "     - Beware of the overflows, unsigned types act differently.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      std::cout << "     - It can be useful for cross-platform code.\n";
      return;
    }
    case T_IDEF:
    {
      std::cout << "int'\n\n";

      std::cout << "     - It's the natural integer type of the platform.\n";
      std::cout
        << "     - When better alternatives exist, there's no concreate reason to use it.\n";
      std::cout << "     - Beware of portability because its size may differ by platform\n";
      std::cout << "     - Commonly 32 bits but it is not guaranteed.\n";
      return;
    }
    case T_UDEF:
    {
      std::cout << "unsigned int'\n\n";

      std::cout << "     - It's the natural unsigned integer type of the platform.\n";
      std::cout
        << "     - When better alternatives exist, there's no concreate reason to use it.\n";
      std::cout << "     - Don't use unsigned types for arithmetic operations, use signed types.\n";
      std::cout << "     - Beware of the overflows, unsigned types act differently.\n";
      std::cout << "     - Beware of portability because its size may differ by platform\n";
      std::cout << "     - Commonly 32 bits but it is not guaranteed.\n";
      return;
    }
    case T_IMAX:
    {
      std::cout << "std::intmax_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - It's simple, use it when you need the largest integer.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      return;
    }
    case T_UMAX:
    {
      std::cout << "std::uintmax_t'\n\n";

      std::cout << "     - Include 'cstdint' header to use.\n";
      std::cout << "     - It's simple, use it when you need the largest unsigned integer.\n";
      std::cout << "     - Don't use unsigned types for arithmetic operations, use signed types.\n";
      std::cout << "     - Beware of the overflows, unsigned types act differently.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      return;
    }
    case T_SIZE:
    {
      std::cout << "std::size_t'\n\n";

      std::cout << "     - Include 'cstddef' header to use.\n";
      std::cout << "     - As the name suggests, use it to represent sizes and indexes.\n";
      std::cout << "     - Don't use unsigned types for arithmetic operations, use signed types.\n";
      std::cout << "     - Beware of the overflows, unsigned types act differently.\n";
      std::cout << "     - Beware of implicit conversions, it may not produce desired results.\n";
      return;
    }
    case T_F32:
    {
      std::cout << "float'\n\n";

      std::cout << "     - Use for floating-point arithmetic operations.\n";
      std::cout << "     - Use when performance concerns are higher than precision concerns.\n";
      std::cout << "     - It's a single precision floating-point type.\n";
      std::cout << "     - Beware floating-point arithmetic is not precise.\n";
      std::cout << "     - Compare floating-point numbers with a tolerance.\n";
      return;
    }
    case T_F64:
    {
      std::cout << "double'\n\n";

      std::cout << "     - Use for precise floating-point arithmetic operations.\n";
      std::cout << "     - Use when precision concerns are higher than performance concerns.\n";
      std::cout << "     - It's a double precision floating-point type.\n";
      std::cout << "     - Beware floating-point arithmetic is not precise.\n";
      std::cout << "     - Compare floating-point numbers with a tolerance.\n";
      return;
    }
    case T_FMAX:
    {
      std::cout << "long double'\n\n";

      std::cout << "     - Use for extended precision floating-point arithmetic operations.\n";
      std::cout << "     - Use it when performance is not a concern.\n";
      std::cout << "     - It's an extended precision floating-point type.\n";
      std::cout << "     - Beware floating-point arithmetic is not precise.\n";
      std::cout << "     - Compare floating-point numbers with a tolerance.\n";
      return;
    }
    case T_C8:
    {
      std::cout << "char8_t'\n\n";

      std::cout << "     - Use it to represent UTF-8 characters.\n";
      std::cout << "     - Don't use double quotes for literals, use single quotes.\n";
      std::cout << "     - Beware of conversions, the may involve encoding conversions.\n";
      std::cout << "     - It may not be compatible with other character types.\n";
      std::cout << "     - Just because it can represent UTF-8, doesn't mean it can handle it.\n";
      std::cout << "     - Don't do arithmetic on fixed size char types, cast them first.\n";
      return;
    }
    case T_C16:
    {
      std::cout << "char16_t'\n\n";

      std::cout << "     - Use it to represent UTF-16 characters.\n";
      std::cout << "     - Don't use double quotes for literals, use single quotes.\n";
      std::cout << "     - Beware of conversions, the may involve encoding conversions.\n";
      std::cout << "     - It may not be compatible with other character types.\n";
      std::cout << "     - Just because it can represent UTF-16, doesn't mean it can handle it.\n";
      std::cout << "     - Don't do arithmetic on fixed size char types, cast them first.\n";
      return;
    }
    case T_C32:
    {
      std::cout << "char32_t'\n\n";

      std::cout << "     - Use it to represent UTF-32 characters.\n";
      std::cout << "     - Don't use double quotes for literals, use single quotes.\n";
      std::cout << "     - Beware of conversions, the may involve encoding conversions.\n";
      std::cout << "     - It may not be compatible with other character types.\n";
      std::cout << "     - Just because it can represent UTF-32, doesn't mean it can handle it.\n";
      std::cout << "     - Don't do arithmetic on fixed size char types, cast them first.\n";
      return;
    }
    case T_CDEF:
    {
      std::cout << "char'\n\n";

      std::cout << "     - Use it to represent ASCII characters.\n";
      std::cout << "     - Don't use double quotes for literals, use single quotes.\n";
      std::cout << "     - Don't do arithmetic on it, it may or may not be signed.\n";
      return;
    }
    case T_WDEF:
    {
      std::cout << "wchar_t'\n\n";

      std::cout << "     - Don't use it, it's considered as a defect, use fixed chars.\n";
      std::cout << "     - It was designed to hold wide characters, but it's not portable.\n";
      std::cout << "     - Don't use double quotes for literals, use single quotes.\n";
      std::cout << "     - Don't do arithmetic on it, it may or may not be signed.\n";
      return;
    }
    default:
    {
      // Should never reach here
      std::cout << "   ERROR: In 'tips' command!\n";
    }
    }

    // NOLINTEND(clang-diagnostic-switch-enum)

#pragma warning(pop)
  }

  // NOLINTNEXTLINE(readability-function-size)
  [[nodiscard]] auto getTypeRow(const Option typeName) -> TypeRow
  {
    // Using declarations
    using enum Option;

#pragma warning(push)
#pragma warning(disable : 4'061)

    // NOLINTBEGIN(clang-diagnostic-switch-enum)

    switch (typeName)
    {
    case T_NONE:
    {
      return TypeRow{
        .typeName{"void"},
        .isOptional{"no"},
        .header{"-"},
        .standardSize{"-"},
        .platformSize{"-"},
        .signedness{"-"},
        .minValue{"-"},
        .maxValue{"-"},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_IPTR:
    {
      // Using declarations
      using Type = fn::iptr;

      return TypeRow{
        .typeName{"std::intptr_t"},
        .isOptional{"yes"},
        .header{"cstdint"},
        .standardSize{">= {ptr} bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_UPTR:
    {
      // Using declarations
      using Type = fn::uptr;

      return TypeRow{
        .typeName{"std::uintptr_t"},
        .isOptional{"yes"},
        .header{"cstdint"},
        .standardSize{">= {ptr} bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_NPTR:
    {
      // Using declarations
      using Type = fn::nptr;

      return TypeRow{
        .typeName{"std::nullptr_t"},
        .isOptional{"no"},
        .header{"cstddef"},
        .standardSize{">= {ptr} bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<fn::uptr>::min())},
        .maxValue{std::to_string(std::numeric_limits<fn::uptr>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_BLN:
    {
      // Using declarations
      using Type = fn::bln;

      return TypeRow{
        .typeName{"bool"},
        .isOptional{"no"},
        .header{"-"},
        .standardSize{std::format(">= {} bits", CHAR_BIT)},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_I8:
    {
      // Using declarations
      using Type = fn::i8;

      return TypeRow{
        .typeName{"std::int8_t"},
        .isOptional{"yes"},
        .header{"cstdint"},
        .standardSize{"= 8 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_I16:
    {
      // Using declarations
      using Type = fn::i16;

      return TypeRow{
        .typeName{"std::int16_t"},
        .isOptional{"yes"},
        .header{"cstdint"},
        .standardSize{"= 16 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_I32:
    {
      // Using declarations
      using Type = fn::i32;

      return TypeRow{
        .typeName{"std::int32_t"},
        .isOptional{"yes"},
        .header{"cstdint"},
        .standardSize{"= 32 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_I64:
    {
      // Using declarations
      using Type = fn::i64;

      return TypeRow{
        .typeName{"std::int64_t"},
        .isOptional{"yes"},
        .header{"cstdint"},
        .standardSize{"= 64 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_U8:
    {
      // Using declarations
      using Type = fn::u8;

      return TypeRow{
        .typeName{"std::uint8_t"},
        .isOptional{"yes"},
        .header{"cstdint"},
        .standardSize{"= 8 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"u"},
      };
    }
    case T_U16:
    {
      // Using declarations
      using Type = fn::u16;

      return TypeRow{
        .typeName{"std::uint16_t"},
        .isOptional{"yes"},
        .header{"cstdint"},
        .standardSize{"= 16 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"u"},
      };
    }
    case T_U32:
    {
      // Using declarations
      using Type = fn::u32;

      return TypeRow{
        .typeName{"std::uint32_t"},
        .isOptional{"yes"},
        .header{"cstdint"},
        .standardSize{"= 32 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"u"},
      };
    }
    case T_U64:
    {
      // Using declarations
      using Type = fn::u64;

      return TypeRow{
        .typeName{"std::uint64_t"},
        .isOptional{"yes"},
        .header{"cstdint"},
        .standardSize{"= 64 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"u"},
      };
    }
    case T_I8L:
    {
      // Using declarations
      using Type = fn::i8l;

      return TypeRow{
        .typeName{"std::int_least8_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 8 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_I16L:
    {
      // Using declarations
      using Type = fn::i16l;

      return TypeRow{
        .typeName{"std::int_least16_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 16 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_I32L:
    {
      // Using declarations
      using Type = fn::i32l;

      return TypeRow{
        .typeName{"std::int_least32_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 32 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_I64L:
    {
      // Using declarations
      using Type = fn::i64l;

      return TypeRow{
        .typeName{"std::int_least64_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 64 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_U8L:
    {
      // Using declarations
      using Type = fn::u8l;

      return TypeRow{
        .typeName{"std::uint_least8_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 8 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"u"},
      };
    }
    case T_U16L:
    {
      // Using declarations
      using Type = fn::u16l;

      return TypeRow{
        .typeName{"std::uint_least16_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 16 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"u"},
      };
    }
    case T_U32L:
    {
      // Using declarations
      using Type = fn::u32l;

      return TypeRow{
        .typeName{"std::uint_least32_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 32 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"u"},
      };
    }
    case T_U64L:
    {
      // Using declarations
      using Type = fn::u64l;

      return TypeRow{
        .typeName{"std::uint_least64_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 64 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"u"},
      };
    }
    case T_I8F:
    {
      // Using declarations
      using Type = fn::i8f;

      return TypeRow{
        .typeName{"std::int_fast8_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 8 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_I16F:
    {
      // Using declarations
      using Type = fn::i16f;

      return TypeRow{
        .typeName{"std::int_fast16_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 16 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_I32F:
    {
      // Using declarations
      using Type = fn::i32f;

      return TypeRow{
        .typeName{"std::int_fast32_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 32 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_I64F:
    {
      // Using declarations
      using Type = fn::i64f;

      return TypeRow{
        .typeName{"std::int_fast64_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 64 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_U8F:
    {
      // Using declarations
      using Type = fn::u8f;

      return TypeRow{
        .typeName{"std::uint_fast8_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 8 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"u"},
      };
    }
    case T_U16F:
    {
      // Using declarations
      using Type = fn::u16f;

      return TypeRow{
        .typeName{"std::uint_fast16_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 16 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"u"},
      };
    }
    case T_U32F:
    {
      // Using declarations
      using Type = fn::u32f;

      return TypeRow{
        .typeName{"std::uint_fast32_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 32 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"u"},
      };
    }
    case T_U64F:
    {
      // Using declarations
      using Type = fn::u64f;

      return TypeRow{
        .typeName{"std::uint_fast64_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 64 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"u"},
      };
    }
    case T_IDEF:
    {
      // Using declarations
      using Type = fn::idef;

      return TypeRow{
        .typeName{"int"},
        .isOptional{"no"},
        .header{"-"},
        .standardSize{">= 16 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_UDEF:
    {
      // Using declarations
      using Type = fn::udef;

      return TypeRow{
        .typeName{"unsigned int"},
        .isOptional{"no"},
        .header{"-"},
        .standardSize{">= 16 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"u"},
      };
    }
    case T_IMAX:
    {
      // Using declarations
      using Type = fn::imax;

      return TypeRow{
        .typeName{"std::intmax_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 64 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"-"},
      };
    }
    case T_UMAX:
    {
      // Using declarations
      using Type = fn::umax;

      return TypeRow{
        .typeName{"std::uintmax_t"},
        .isOptional{"no"},
        .header{"cstdint"},
        .standardSize{">= 64 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"u"},
      };
    }
    case T_SIZE:
    {
      // Using declarations
      using Type = fn::size;

      return TypeRow{
        .typeName{"std::size_t"},
        .isOptional{"no"},
        .header{"cstddef"},
        .standardSize{">= {ptr} bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{"-"},
        .literalSuffix{"zu"},
      };
    }
    case T_F32:
    {
      // Using declarations
      using Type = fn::f32;

      return TypeRow{
        .typeName{"float"},
        .isOptional{"no"},
        .header{"-"},
        .standardSize{">= 32 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::format("~{:.4e}", std::numeric_limits<Type>::min())},
        .maxValue{std::format("~{:.4e}", std::numeric_limits<Type>::max())},
        .precision{std::format("{} digits", std::numeric_limits<Type>::digits10)},
        .literalSuffix{"f"},
      };
    }
    case T_F64:
    {
      // Using declarations
      using Type = fn::f64;

      return TypeRow{
        .typeName{"double"},
        .isOptional{"no"},
        .header{"-"},
        .standardSize{">= 64 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::format("~{:.4e}", std::numeric_limits<Type>::min())},
        .maxValue{std::format("~{:.4e}", std::numeric_limits<Type>::max())},
        .precision{std::format("{} digits", std::numeric_limits<Type>::digits10)},
        .literalSuffix{"-"},
      };
    }
    case T_FMAX:
    {
      // Using declarations
      using Type = fn::fmax;

      return TypeRow{
        .typeName{"long double"},
        .isOptional{"no"},
        .header{"-"},
        .standardSize{">= 64 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::format("~{:.4e}", std::numeric_limits<Type>::min())},
        .maxValue{std::format("~{:.4e}", std::numeric_limits<Type>::max())},
        .precision{std::format("{} digits", std::numeric_limits<Type>::digits10)},
        .literalSuffix{"l"},
      };
    }
    case T_C8:
    {
      // Using declarations
      using Type = fn::c8;

      return TypeRow{
        .typeName{"char8_t"},
        .isOptional{"no"},
        .header{"-"},
        .standardSize{"= 8 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{std::to_string(std::numeric_limits<Type>::digits10)},
        .literalSuffix{"u8"},
      };
    }
    case T_C16:
    {
      // Using declarations
      using Type = fn::c16;

      return TypeRow{
        .typeName{"char16_t"},
        .isOptional{"no"},
        .header{"-"},
        .standardSize{"= 16 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{std::to_string(std::numeric_limits<Type>::digits10)},
        .literalSuffix{"u"},
      };
    }
    case T_C32:
    {
      // Using declarations
      using Type = fn::c32;

      return TypeRow{
        .typeName{"char32_t"},
        .isOptional{"no"},
        .header{"-"},
        .standardSize{"= 32 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{std::to_string(std::numeric_limits<Type>::digits10)},
        .literalSuffix{"U"},
      };
    }
    case T_CDEF:
    {
      // Using declarations
      using Type = fn::cdef;

      return TypeRow{
        .typeName{"char"},
        .isOptional{"no"},
        .header{"-"},
        .standardSize{std::format(">= {} bits", CHAR_BIT)},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{std::to_string(std::numeric_limits<Type>::digits10)},
        .literalSuffix{"-"},
      };
    }
    case T_WDEF:
    {
      // Using declarations
      using Type = fn::wdef;

      return TypeRow{
        .typeName{"wchar_t"},
        .isOptional{"no"},
        .header{"-"},
        .standardSize{">= 32 bits"},
        .platformSize{std::format("{} bits", (sizeof(Type) * CHAR_BIT))},
        .signedness{fn::IsSigned<Type> ? "signed" : "unsigned"},
        .minValue{std::to_string(std::numeric_limits<Type>::min())},
        .maxValue{std::to_string(std::numeric_limits<Type>::max())},
        .precision{std::to_string(std::numeric_limits<Type>::digits10)},
        .literalSuffix{"L"},
      };
    }
    default:
    {
      // Should never reach here
      return TypeRow{
        .typeName{"ERROR"},
        .isOptional{"ERROR"},
        .header{"ERROR"},
        .standardSize{"ERROR"},
        .platformSize{"ERROR"},
        .signedness{"ERROR"},
        .minValue{"ERROR"},
        .maxValue{"ERROR"},
        .precision{"ERROR"},
        .literalSuffix{"ERROR"},
      };
    }
    }

    // NOLINTEND(clang-diagnostic-switch-enum)

#pragma warning(pop)
  }
} // namespace IO::_internal
