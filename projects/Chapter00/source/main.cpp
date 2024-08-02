#include "pch.hpp"

#include <Foundation/constants.hpp>
#include <Foundation/types.hpp>
#include <Foundation/Utility/log.ipp>
#include <Foundation/Utility/what.ipp>

#include <exception>
#include <iostream>

namespace
{
  [[nodiscard]] consteval auto GET_VERSION_STRING() noexcept -> fn::strv
  {
    /*--< Note >-----------------------------------------------------------------------------------*
    |   The __cplusplus macro (defined by the compiler) indicates the version of the C++ standard  |
    | that is being used.                                                                          |
    |   In MSVC, by default, the __cpluslplus macro is not set to the correct value. To fix this   |
    | issue, you need to add the following flag as argument to the compiler's command-line:        |
    | /Zc:__cplusplus.                                                                             |
    *---------------------------------------------------------------------------------------------*/

#ifdef __cplusplus
  #if __cplusplus >= 202'612L
    return "C++26";
  #elif __cplusplus >= 202'302L
    return "C++23";
  #elif __cplusplus >= 202'002L
    return "C++20";
  #elif __cplusplus >= 201'703L
    return "C++17";
  #elif __cplusplus >= 201'402L
    return "C++14";
  #elif __cplusplus >= 201'103L
    return "C++11";
  #elif __cplusplus >= 199'711L
    return "Pre-C++11";
  #else
    return "Unknown C++ standard";
  #endif
#else
    return "__cplusplus macro not defined";
#endif
  }
} // namespace

auto main() noexcept -> fn::idef
try
{
  // Print the cpp standard version
  std::cout << "C++ Standard: " << GET_VERSION_STRING() << '\n';

  // Return success
  return fn::EXIT_SUCCESS_CODE;
}
catch (const std::exception& exception)
{
  // Log exception
  fn::elog(fn::what(exception));

  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
catch (...)
{
  // Log unknown exception
  fn::elog(fn::UNKNOWN_EXCEPTION);

  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
