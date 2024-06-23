#pragma once

#include <map>
#include <utility>
#include <vector>

namespace
{
  constexpr int BASE{10};
} // namespace

namespace Math
{
  constexpr auto NUMBER_LENGTH(int number) noexcept -> int
  {
    // Check if the number is 0
    if (number == 0) { return 1; }

    // Initialize the count (If negative, add 1
    int count{number < 0 ? 1 : 0};

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
    std::map<int, int> frequencyMap;
    int                maxFrequency{};
    int                xAxisInterval{};
    int                yAxisInterval{};
    int                lowerBound{};
  };

  auto generateChartFeed(
    const std::vector<int>& values,
    int                     lowerBound,
    int                     upperBound,
    std::pair<int, int>     chartSize
  ) -> std::pair<ChartFeed, std::pair<int, int>>;
} // namespace Math
