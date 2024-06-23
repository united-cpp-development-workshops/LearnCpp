#include "Math/math.hpp"

#include <algorithm>
#include <cmath>
#include <GSL/narrow>
#include <map>
#include <ranges>
#include <utility>
#include <vector>

auto Math::generateChartFeed(
  const std::vector<int>& values,
  int                     lowerBound,
  int                     upperBound,
  std::pair<int, int>     chartSize
) -> std::pair<ChartFeed, std::pair<int, int>>
{
  // Calculate x-axis interval respecting column count
  const int xAxisInterval{
    std::max(1, (upperBound - lowerBound) / chartSize.first)
  };

  // Define the frequency map
  std::map<int, int> frequencyMap;

  // Initialize the frequency map
  for (int x{upperBound}; x > lowerBound; x -= xAxisInterval)
  {
    frequencyMap[x] = {0};
  }

  // If lower bound was not set, set it
  frequencyMap[lowerBound] = {0};

  // Count the frequency of each interval
  std::ranges::for_each(
    values,
    [&](int value) -> void
    {
      // Find the key in the frequency map that is closest to the value
      const auto key{*std::ranges::min_element(
        std::views::keys(frequencyMap),
        [&](int lhs, int rhs) noexcept -> bool
        {
          return std::abs(lhs - value) < std::abs(rhs - value);
        }
      )};

      // Increment the frequency of the key
      frequencyMap[key]++;
    }
  );

  // Find the maximum frequency for y-axis scaling
  const int maxFrequency{
    *std::ranges::max_element(std::views::values(frequencyMap))
  };

  // Calculate y-axis interval respecting row count
  const int yAxisInterval{std::max(1, maxFrequency / chartSize.second)};

  // Create ChartFeed
  const ChartFeed chartFeed{
    frequencyMap, maxFrequency, xAxisInterval, yAxisInterval, lowerBound
  };

  // Calculate the chart size with respect to intervals
  const std::pair<int, int> resultingChartSize{
    gsl::narrow<int>(frequencyMap.size()), maxFrequency / yAxisInterval
  };

  return {chartFeed, resultingChartSize};
}
