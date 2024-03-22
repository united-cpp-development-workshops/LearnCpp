#include "Chapter00/workshops/02/workshop.hpp"

#include <Base/announce.hpp>

#include <iostream>

constexpr int  numStandards{7};
constexpr long stdCode[numStandards]{
  199'711L, 201'103L, 201'402L, 201'703L, 202'002L, 202'302L, 202'612L
};
const char* stdName[numStandards]{
  "Pre-C++11", "C++11", "C++14", "C++17", "C++20", "C++23", "C++26"
};

static long getCPPStandard()
{
  // Visual Studio is non-conforming in support for __cplusplus (unless you set
  // a specific compiler flag, which you probably haven't) In Visual Studio 2015
  // or newer we can use _MSVC_LANG instead See
  // https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/
#if defined(MSVC_LANG)
  return _MSVC_LANG;
#elif defined(_MSC_VER)
  // If we're using an older version of Visual Studio, bail out
  return 1;
#else
  // __cplusplus is the intended way to query the language standard code (as
  // defined by the language standards)
  return __cplusplus;
#endif
}

void Workshop02::run()
{
  ANNOUNCE_WORKSHOP("Workshop 02: C++ Standard Query");
  const long standard{getCPPStandard()};
  if (standard == 1)
  {
    std::cout << "Error: Unable to determine your language standard.  Sorry.\n";
  }
  std::cout << "Your compiler is using language standard: ";
  for (std::size_t i{}; i < numStandards; ++i)
  {
    if (standard <= stdCode[i])
    {
      std::cout << stdName[i];
      // If the reported version is between two standard codes, this must be a
      // preview / experimental support
      if (standard < stdCode[i])
      {
        std::cout << " (preview)";
      }
      break;
    }
  }
  std::cout << '\n';
}
