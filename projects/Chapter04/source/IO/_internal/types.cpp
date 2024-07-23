#include "pch.hpp"

#include "IO/_internal/types.hpp"

#include "IO/io.hpp"

#include <Foundation/types.hpp>

#include <iostream>
#include <stdexcept>

namespace IO::_internal
{
  // NOLINTNEXTLINE(readability-function-size)
  auto printBriefTypeInfo(Option type) -> fn::none
  {
    // Using declarations
    using enum Option;

    std::cout << "   EXPLORE: '";

    // NOLINTBEGIN(clang-diagnostic-switch-enum)
    switch (type)
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
      std::cout << "     - Unsigned integer type capable of holding a pointer "
                   "to 'void'.\n";
      return;
    }
    case T_UPTR:
    {
      std::cout << "std::uintptr_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Signed integer type capable of holding a pointer to "
                   "'void'.\n";
      return;
    }
    case T_NPTR:
    {
      std::cout << "std::nullptr_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A type declaration.\n";
      std::cout << "     - Defined in 'cstddef'.\n";
      std::cout << "     - It's the type of the 'nullptr' literal.\n";
      std::cout << "     - It's not itself a pointer type or a pointer to "
                   "member type.\n";
      return;
    }
    case T_BLN:
    {
      std::cout << "bool'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Capable of holding one of the two values: 'true' or "
                   "'false'.\n";
      std::cout << "     - The size of 'bool' is implementation defined.\n";
      return;
    }
    case T_I8:
    {
      std::cout << "std::int8_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout
        << "     - Signed integer type with the width of exactly '8' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I16:
    {
      std::cout << "std::int16_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout
        << "     - Signed integer type with the width of exactly '16' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I32:
    {
      std::cout << "std::int32_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout
        << "     - Signed integer type with the width of exactly '32' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I64:
    {
      std::cout << "std::int64_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout
        << "     - Signed integer type with the width of exactly '64' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_U8:
    {
      std::cout << "std::uint8_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout
        << "     - Unsigned integer type with the width of exactly '8' bits.\n";
      return;
    }
    case T_U16:
    {
      std::cout << "std::uint16_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Unsigned integer type with the width of exactly "
                   "'16' bits.\n";
      return;
    }
    case T_U32:
    {
      std::cout << "std::uint32_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Unsigned integer type with the width of exactly "
                   "'32' bits.\n";
      return;
    }
    case T_U64:
    {
      std::cout << "std::uint64_t' (optional)\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Unsigned integer type with the width of exactly "
                   "'64' bits.\n";
      return;
    }
    case T_I8L:
    {
      std::cout << "std::int_least8_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest signed integer type with width of at least "
                   "'8' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I16L:
    {
      std::cout << "std::int_least16_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest signed integer type with width of at least "
                   "'16' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I32L:
    {
      std::cout << "std::int_least32_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest signed integer type with width of at least "
                   "'32' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I64L:
    {
      std::cout << "std::int_least64_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest signed integer type with width of at least "
                   "'64' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_U8L:
    {
      std::cout << "std::uint_least8_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest unsigned integer type with width of at "
                   "least '8' bits.\n";
      return;
    }
    case T_U16L:
    {
      std::cout << "std::uint_least16_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest unsigned integer type with width of at "
                   "least '16' bits.\n";
      return;
    }
    case T_U32L:
    {
      std::cout << "std::uint_least32_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest unsigned integer type with width of at "
                   "least '32' bits.\n";
      return;
    }
    case T_U64L:
    {
      std::cout << "std::uint_least64_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Smallest unsigned integer type with width of at "
                   "least '64' bits.\n";
      return;
    }
    case T_I8F:
    {
      std::cout << "std::int_fast8_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest signed integer type with width of at least "
                   "'8' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I16F:
    {
      std::cout << "std::int_fast16_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest signed integer type with width of at least "
                   "'16' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I32F:
    {
      std::cout << "std::int_fast32_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest signed integer type with width of at least "
                   "'32' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_I64F:
    {
      std::cout << "std::int_fast64_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest signed integer type with width of at least "
                   "'64' bits.\n";
      std::cout << "     - Uses 2's complement for negative values.\n";
      return;
    }
    case T_U8F:
    {
      std::cout << "std::uint_fast8_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest unsigned integer type with width of at "
                   "least '8' bits.\n";
      return;
    }
    case T_U16F:
    {
      std::cout << "std::uint_fast16_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest unsigned integer type with width of at "
                   "least '16' bits.\n";
      return;
    }
    case T_U32F:
    {
      std::cout << "std::uint_fast32_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest unsigned integer type with width of at "
                   "least '64' bits.\n";
      return;
    }
    case T_U64F:
    {
      std::cout << "std::uint_fast64_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Fastest unsigned integer type with width of at "
                   "least '64' bits.\n";
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
      std::cout
        << "     - The size of 'unsigned int' is implementation defined.\n";
      return;
    }
    case T_IMAX:
    {
      std::cout << "std::intmax_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Maximum-width signed integer.\n\n";
      return;
    }
    case T_UMAX:
    {
      std::cout << "std::uintmax_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstdint'.\n";
      std::cout << "     - Maximum-width unsigned integer.\n\n";
      return;
    }
    case T_SIZE:
    {
      std::cout << "std::size_t'\n\n";

      std::cout << "     - An integral type.\n";
      std::cout << "     - A typedef.\n";
      std::cout << "     - Defined in header 'cstddef'.\n";
      std::cout
        << "     - Unsigned integer returned by the 'sizeof' operator.\n";
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
      std::cout
        << "     - Does not necessarily map to types mandated by IEEE-754.\n";
      return;
    }
    case T_C8:
    {
      std::cout << "char8_t'\n\n";

      std::cout << "     - A character type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Type for UTF-8 character representation.\n";
      std::cout << "     - It has the same size, signedness, and alignment as "
                   "'unsigned char'.\n";
      return;
    }
    case T_C16:
    {
      std::cout << "char16_t'\n\n";

      std::cout << "     - A character type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Type for UTF-16 character representation.\n";
      std::cout << "     - It has the same size, signedness, and alignment as "
                   "'std::uint_least16_t'.\n";
      return;
    }
    case T_C32:
    {
      std::cout << "char32_t'\n\n";

      std::cout << "     - A character type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Type for UTF-32 character representation.\n";
      std::cout << "     - It has the same size, signedness, and alignment as "
                   "'std::uint_least32_t'.\n";
      return;
    }
    case T_CDEF:
    {
      std::cout << "char'\n\n";

      std::cout << "     - A character type.\n";
      std::cout << "     - A C++ keyword.\n";
      std::cout << "     - Type that can be most efficiently processed on the "
                   "target system.\n";
      std::cout
        << "     - The signedness of 'char' is implementation defined.\n";
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
  }
} // namespace IO::_internal
