#include "pch.hpp"

#include "Foundation/constants.hpp"
#include "Foundation/types.hpp"

#include <cassert>
#include <iostream>

namespace
{
  constexpr auto GCD(fn::i32l number1, fn::i32l number2) -> fn::i32l
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

  // Calculate greatest common divisor
  const auto gcd{GCD(width, height)};

  // Assert that the greatest common divisor is not zero
  assert(gcd != 0);

  // Calculate and print the aspect ratio
  std::cout << "Aspect Ratio of " << width << "x" << height << " is "
            << width / gcd << ":" << height / gcd << '\n';

  // Return success
  return fn::EXIT_SUCCESS_CODE;
}
catch (...)
{
  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
