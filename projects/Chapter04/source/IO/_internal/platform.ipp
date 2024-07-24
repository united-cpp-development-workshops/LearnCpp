#pragma once

#include <Foundation/errors.hpp>
#include <Foundation/types.hpp>

#include <format>
#include <string>

namespace IO::_internal
{
  enum class Compiler : fn::u8f
  {
    UNKNOWN,
    MSVC,
    CLANG,
    GCC
  };

  enum class Architecture : fn::u8f
  {
    UNKNOWN,
    X86,
    X64,
    ARM32,
    ARM64
  };

  enum class OperatingSystem : fn::u8f
  {
    UNKNOWN,
    WINDOWS,
    MACOS,
    LINUX
  };

  [[nodiscard]] constexpr auto COMPILER() noexcept -> Compiler;
  [[nodiscard]] constexpr auto COMPILER_STR(Compiler compiler) -> fn::cstr;
  [[nodiscard]] constexpr auto COMPILER_VER_STR(Compiler compiler
  ) -> std::string;
  [[nodiscard]] constexpr auto LANGUAGE_STD_STR() -> std::string;
  [[nodiscard]] constexpr auto ARCHITECTURE() -> Architecture;
  [[nodiscard]] constexpr auto ARCHITECTURE_STR(Architecture architecture
  ) -> fn::cstr;
  [[nodiscard]] constexpr auto OPERATING_SYSTEM() -> OperatingSystem;
  [[nodiscard]] constexpr auto OPERATING_SYSTEM_STR(
    OperatingSystem operatingSystem
  ) -> fn::cstr;
} // namespace IO::_internal

/*----------------------------------------------------------------------------*\
*| >>>>>>>>>>>>>>>>>>>>>>>>>>>>> Implementation <<<<<<<<<<<<<<<<<<<<<<<<<<<<< |*
\*----------------------------------------------------------------------------*/

namespace IO::_internal
{
  [[nodiscard]] constexpr auto COMPILER() noexcept -> Compiler
  {
    // Using declarations
    using enum Compiler;

#if defined(_MSC_VER) && !defined(__clang__) // Clang-cl also defines _MSC_VER
    return MSVC;
#elif defined(__clang__)
    return CLANG;
#elif defined(__GNUC__)
    return GCC
#else
    return UNKNOWN;
#endif
  }

  [[nodiscard]] constexpr auto COMPILER_STR(const Compiler compiler) -> fn::cstr
  {
    // Using declarations
    using enum Compiler;

    switch (compiler)
    {
    case UNKNOWN: return "Unknown";
    case MSVC   : return "Microsoft Visual C++";
    case CLANG  : return "Clang";
    case GCC    : return "GNU Compiler Collection";
    }

    // Should never reach here
    throw fn::EnumeratorError{};
  }

  [[nodiscard]] constexpr auto COMPILER_VER_STR(const Compiler compiler
  ) -> std::string
  {
    // Using declarations
    using enum Compiler;

    switch (compiler)
    {
    case UNKNOWN: return {""};
    case MSVC:
    {
      constexpr fn::u16l MSVC_VER_FIRST_DOT{2};
      constexpr fn::u16l MSVC_VER_SECOND_DOT{5};

#ifdef _MSC_FULL_VER
      std::string version{std::to_string(_MSC_FULL_VER)};
#else
      std::string version{"000000000"};
#endif

      version.insert(version.begin() + MSVC_VER_FIRST_DOT, '.');
      version.insert(version.begin() + MSVC_VER_SECOND_DOT, '.');

      // Return version string
      return version;
    }
    case CLANG:
    {
#ifdef __clang_major__
      constexpr fn::u16f MAJOR{__clang_major__};
#else
      constexpr fn::u16f MAJOR{};
#endif

#ifdef __clang_minor__
      constexpr fn::u16f MINOR{__clang_minor__};
#else
      constexpr fn::u16f MINOR{};
#endif

#ifdef __clang_patchlevel__
      constexpr fn::u16f PATCH{__clang_patchlevel__};
#else
      constexpr fn::u16f PATCH{};
#endif

      // Return version string
      return {std::format("{}.{}.{}", MAJOR, MINOR, PATCH)};
    }
    case GCC:
    {
#ifdef __GNUC__
      constexpr fn::u16f MAJOR{__GNUC__};
#else
      constexpr fn::u16f MAJOR{};
#endif

#ifdef __GNUC_MINOR__
      constexpr fn::u16f MINOR{__GNUC_MINOR__};
#else
      constexpr fn::u16f MINOR{};
#endif

#ifdef __GNUC_PATCHLEVEL__
      constexpr fn::u16f PATCH{__GNUC_PATCHLEVEL__};
#else
      constexpr fn::u16f PATCH{};
#endif

      // Return version string
      return {std::format("{}{}.{}", MAJOR, MINOR, PATCH)};
    }
    }

    // Should never reach here
    throw fn::EnumeratorError{};
  }

  [[nodiscard]] constexpr auto LANGUAGE_STD_STR() -> std::string
  {
    constexpr fn::i32l CPPRE_CODE{199'711L};
    constexpr fn::i32l CPP11_CODE{201'103L};
    constexpr fn::i32l CPP14_CODE{201'402L};
    constexpr fn::i32l CPP17_CODE{201'703L};
    constexpr fn::i32l CPP20_CODE{202'002L};
    constexpr fn::i32l CPP23_CODE{202'302L};
    constexpr fn::i32l CPP26_CODE{202'612L};

    switch (__cplusplus)
    {
    case CPPRE_CODE: return {"Pre-C++11"};
    case CPP11_CODE: return {"C++11"};
    case CPP14_CODE: return {"C++14"};
    case CPP17_CODE: return {"C++17"};
    case CPP20_CODE: return {"C++20"};
    case CPP23_CODE: return {"C++23"};
    case CPP26_CODE: return {"C++26"};
    default        : return {"Unknown C++ standard"};
    }
  }

  [[nodiscard]] constexpr auto ARCHITECTURE() -> Architecture
  {
    // Using declarations
    using enum Compiler;

    // NOLINTBEGIN(bugprone-branch-clone)
    switch (COMPILER())
    {
    case UNKNOWN: return Architecture::UNKNOWN;
    case MSVC:
    {
#if defined(_M_IX86)
      return Architecture::X86;
#elif defined(_M_X64)
      return Architecture::X64;
#elif defined(_M_ARM)
      return Architecture::ARM32;
#elif defined(_M_ARM64)
      return Architecture::ARM64;
#else
      return Architecture::UNKNOWN;
#endif
    }
    case CLANG:
    case GCC:
    {
#if defined(__i386__)
      return Architecture::X86;
#elif defined(__x86_64__)
      return Architecture::X64;
#elif defined(__arm__)
      return Architecture::ARM32;
#elif defined(__aarch64__)
      return Architecture::ARM64;
#else
      return Architecture::UNKNOWN;
#endif
    }
    }
    // NOLINTEND(bugprone-branch-clone)

    // Should never reach here
    throw fn::EnumeratorError{};
  }

  [[nodiscard]] constexpr auto ARCHITECTURE_STR(const Architecture architecture
  ) -> fn::cstr
  {
    // Using declarations
    using enum Architecture;

    switch (architecture)
    {
    case UNKNOWN: return "Unknown";
    case X86    : return "x86";
    case X64    : return "x64";
    case ARM32  : return "ARM32";
    case ARM64  : return "ARM64";
    }

    // Should never reach here
    throw fn::EnumeratorError{};
  }

  [[nodiscard]] constexpr auto OPERATING_SYSTEM() -> OperatingSystem
  {
    // Using declarations
    using enum Compiler;

    switch (COMPILER())
    {
    case UNKNOWN: return OperatingSystem::UNKNOWN;
    case MSVC:
    case CLANG:
    case GCC:
    {
#if defined(_WIN32)
      return OperatingSystem::WINDOWS;
#elif defined(__APPLE__)
      return OperatingSystem::MACOS;
#elif defined(__linux__)
      return OperatingSystem::LINUX;
#else
      return OperatingSystem::UNKNOWN;
#endif
    }
    }

    // Should never reach here
    throw fn::EnumeratorError{};
  }

  [[nodiscard]] constexpr auto OPERATING_SYSTEM_STR(
    const OperatingSystem operatingSystem
  ) -> fn::cstr
  {
    // Using declarations
    using enum OperatingSystem;

    switch (operatingSystem)
    {
    case UNKNOWN: return "Unknown";
    case WINDOWS: return "Windows";
    case MACOS  : return "macOS";
    case LINUX  : return "Linux";
    }

    // Should never reach here
    throw fn::EnumeratorError{};
  }

} // namespace IO::_internal
