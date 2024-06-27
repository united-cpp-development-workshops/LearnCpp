#include "pch.hpp"

#include "Math/math.hpp"

#include "foundation.hpp"

#include <algorithm>
#include <cmath>
#include <map>
#include <ranges>
#include <utility>
#include <vector>

auto Math::generateChartFeed(
  const std::vector<i32f>& values,
  i32f                     lowerBound,
  i32f                     upperBound,
  std::pair<u16f, u16f>    chartSize
) -> std::pair<ChartFeed, std::pair<u16f, u16f>>
{
  // Calculate x-axis interval respecting column count
  const u32f xAxisInterval{
    std::max(u32f{1}, narrow<u32f>(upperBound - lowerBound) / chartSize.first)
  };

  // Define the frequency map
  std::map<i32f, u32f> frequencyMap;

  // Initialize the frequency map
  for (i32f x{upperBound}; x > lowerBound; x -= narrow<i32f>(xAxisInterval))
  {
    frequencyMap[x] = {0};
  }

  // If lower bound was not set, set it
  frequencyMap[lowerBound] = {0};

  // Count the frequency of each interval
  std::ranges::for_each(
    values,
    [&](i32f value) -> void
    {
      // Find the key in the frequency map that is closest to the value
      const auto key{*std::ranges::min_element(
        std::views::keys(frequencyMap),
        [&](i32f lhs, i32f rhs) noexcept -> bool
        {
          return std::abs(lhs - value) < std::abs(rhs - value);
        }
      )};

      // Increment the frequency of the key
      frequencyMap[key]++;
    }
  );

  // Find the maximum frequency for y-axis scaling
  const u32f maxFrequency{
    *std::ranges::max_element(std::views::values(frequencyMap))
  };

  // Calculate y-axis interval respecting row count
  const u32f yAxisInterval{std::max(u32f{1}, maxFrequency / chartSize.second)};

  // Create ChartFeed
  const ChartFeed chartFeed{
    frequencyMap, maxFrequency, xAxisInterval, yAxisInterval, lowerBound
  };

  // Calculate the chart size with respect to intervals
  const std::pair<u16f, u16f> resultingChartSize{
    narrow<u16f>(frequencyMap.size()), maxFrequency / yAxisInterval
  };

  // Return the chart feed and the resulting chart size
  return {chartFeed, resultingChartSize};
}
