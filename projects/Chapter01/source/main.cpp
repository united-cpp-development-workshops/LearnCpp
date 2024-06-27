#include "pch.hpp"

#include "types.hpp"
#include "wrappers.hpp"

#include <cassert>
#include <iostream>

namespace
{
  constexpr auto GCD(u32l number1, u32l number2) -> u32l
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

auto main() noexcept -> idef
try
{
  // Print title
  std::cout << "Aspect Ratio Calculator\n";

  // Get the width from the user
  std::cout << "Enter the width: ";
  u32l width{};
  std::cin >> width;

  // Get the height from the user
  std::cout << "Enter the height: ";
  u32l height{};
  std::cin >> height;

  // Calculate greatest common divisor
  const auto gcd{GCD(width, height)};

  // Assert that the greatest common divisor is not zero
  assert(gcd != 0);

  // Calculate and print the aspect ratio
  std::cout << "Aspect Ratio of " << width << "x" << height << " is "
            << width / gcd << ":" << height / gcd << '\n';

  // Return success
  return TERMINATE_SUCCESS;
}
catch (...)
{
  // Return failure
  return TERMINATE_FAILURE;
}
