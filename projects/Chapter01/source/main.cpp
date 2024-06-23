#include <cstdlib>
#include <iostream>

namespace
{
  constexpr auto GCD(int number1, int number2) noexcept -> int
  {
    while (number2 != 0)
    {
      const auto temp = number2;
      number2         = number1 % number2;
      number1         = temp;
    }
    return number1;
  }
} // namespace

auto main() noexcept -> int
try
{
  std::cout << "Aspect Ratio Calculator\n";

  // Get the width from the user
  std::cout << "Enter the width: ";
  int width{};
  std::cin >> width;

  // Get the height from the user
  std::cout << "Enter the height: ";
  int height{};
  std::cin >> height;

  // Calculate greatest common divisor
  const auto gcd = GCD(width, height);

  // Calculate and print the aspect ratio
  std::cout << "Aspect Ratio of " << width << "x" << height << " is "
            << width / gcd << ":" << height / gcd << '\n';

  return EXIT_SUCCESS;
}
catch (...)
{
  return EXIT_FAILURE;
}
