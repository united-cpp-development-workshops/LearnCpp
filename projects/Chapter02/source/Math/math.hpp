#pragma once

#include "types.hpp"

#include <map>
#include <utility>
#include <vector>

namespace
{
  constexpr i32f BASE{10};
} // namespace

namespace Math
{
  constexpr auto NUMBER_LENGTH(i32f number) -> u16f
  {
    // Check if the number is 0
    if (number == 0) { return 1; }

    // Initialize the count (If negative, add 1
    u16f count{number < 0 ? u16f{1} : u16f{0}};

    // Count the digits
    while (number != 0)
    {
      number /= BASE;
      count++;
    }

    // Return the count
    return count;
  }

  struct ChartFeed
  {
    std::map<i32f, u32f> frequencyMap;
    u32f                 maxFrequency{};
    u32f                 xAxisInterval{};
    u32f                 yAxisInterval{};
    i32f                 lowerBound{};
  };

  auto generateChartFeed(
    const std::vector<i32f>& values,
    i32f                     lowerBound,
    i32f                     upperBound,
    std::pair<u16f, u16f>    chartSize
  ) -> std::pair<ChartFeed, std::pair<u16f, u16f>>;
} // namespace Math
