#include "pch.hpp"

#include <Foundation/constants.hpp>
#include <Foundation/types.hpp>
#include <Foundation/Utility/log.ipp>
#include <Foundation/Utility/what.ipp>

#include <exception>
#include <iostream>

namespace
{
  [[nodiscard]] constexpr auto GCD(fn::i32l number1, fn::i32l number2) noexcept -> fn::i32l
  {
    while (number2 != 0)
    {
      const auto tempNumber2{number2};
      number2 = {number1 % number2};
      number1 = {tempNumber2};
    }
    return number1;
  }
} // namespace

auto main() noexcept -> fn::idef
try
{
  // Print title
  std::cout << "---------------< Aspect Ratio Calculator >---------------\n\n";

  // Get the width from the user
  std::cout << "Enter the width: ";
  fn::i32l width{};
  std::cin >> width;

  // Get the height from the user
  std::cout << "Enter the height: ";
  fn::i32l height{};
  std::cin >> height;

  // If width or height is 0 then error out
  if (width == 0 or height == 0)
  {
    throw fn::InputError{"Witdh/Height must'not be zero!"};
  }

  // Calculate greatest common divisor
  const auto gcd{GCD(width, height)};

  // Calculate and print the aspect ratio
  std::cout << "Aspect Ratio of " << width << "x" << height << " is " << (width / gcd) << ":"
            << (height / gcd) << '\n';

  // Return success
  return fn::EXIT_SUCCESS_CODE;
}
catch (const fn::InputError& error)
{
  // Log error
  fn::elog(error);

  // Return failure
  return fn::EXIT_FAILURE_CODE;
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
