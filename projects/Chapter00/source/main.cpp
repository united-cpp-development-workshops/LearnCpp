#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

namespace
{
  constexpr auto GET_VERSION_STRING(std::int32_t cppStandard) -> std::string
  {
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,
    // readability-magic-numbers)
    switch (cppStandard)
    {
      case 199'711L: return "Pre-C++11";
      case 201'103L: return "C++11";
      case 201'402L: return "C++14";
      case 201'703L: return "C++17";
      case 202'002L: return "C++20";
      case 202'302L: return "C++23";
      case 202'612 : return "C++26";
      default      : return "Unknown C++ standard";
    }
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,
    // readability-magic-numbers)
  }
} // namespace

auto main() noexcept -> int
try
{
  // Get cpp standard version
  constexpr std::int32_t CPP_STANDARD{__cplusplus};

  // Print the cpp standard version
  std::cout << "C++ Standard: " << GET_VERSION_STRING(CPP_STANDARD) << '\n';

  return EXIT_SUCCESS;
}
catch (...)
{
  return EXIT_FAILURE;
}
