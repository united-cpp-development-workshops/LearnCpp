#include "pch.hpp"

#include "Foundation/constants.hpp"
#include "Foundation/types.hpp"

#include <iostream>
#include <string>

namespace
{
  constexpr fn::i32l CPPRE_CODE{199'711L};
  constexpr fn::i32l CPP11_CODE{201'103L};
  constexpr fn::i32l CPP14_CODE{201'402L};
  constexpr fn::i32l CPP17_CODE{201'703L};
  constexpr fn::i32l CPP20_CODE{202'002L};
  constexpr fn::i32l CPP23_CODE{202'302L};
  constexpr fn::i32l CPP26_CODE{202'612L};

  constexpr auto GET_VERSION_STRING(fn::i32l versionCode) -> std::string
  {
    switch (versionCode)
    {
    case CPPRE_CODE: return "Pre-C++11";
    case CPP11_CODE: return "C++11";
    case CPP14_CODE: return "C++14";
    case CPP17_CODE: return "C++17";
    case CPP20_CODE: return "C++20";
    case CPP23_CODE: return "C++23";
    case CPP26_CODE: return "C++26";
    default        : return "Unknown C++ standard";
    }
  }
} // namespace

auto main() noexcept -> fn::idef
try
{
  // Get cpp standard version
  constexpr fn::i32l CPP_STANDARD{__cplusplus};

  // Print the cpp standard version
  std::cout << "C++ Standard: " << GET_VERSION_STRING(CPP_STANDARD) << '\n';

  // Return success
  return fn::EXIT_SUCCESS_CODE;
}
catch (...)
{
  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
