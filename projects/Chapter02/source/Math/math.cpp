#include "pch.hpp"

#include "Math/math.ipp"

#include "Foundation/Support/narrowing.ipp"
#include "Foundation/types.hpp"

#include <algorithm>
#include <cmath>
#include <map>
#include <ranges>
#include <utility>
#include <vector>

auto Math::generateChartFeed(
  const std::vector<fn::i32f>&  values,
  fn::i32f                      lowerBound,
  fn::i32f                      upperBound,
  std::pair<fn::u16f, fn::u16f> chartSize
) -> std::pair<ChartFeed, std::pair<fn::u16f, fn::u16f>>
{
  // Calculate x-axis interval respecting column count
  const fn::u32f xAxisInterval{std::max(
    fn::u32f{1},
    fn::narrow_cast<fn::u32f>(upperBound - lowerBound) / chartSize.first
  )};

  // Define the frequency map
  std::map<fn::i32f, fn::u32f> frequencyMap;

  // Initialize the frequency map
  for (fn::i32f x{upperBound}; x > lowerBound;
       x -= fn::narrow_cast<fn::i32f>(xAxisInterval))
  {
    frequencyMap[x] = {0};
  }

  // If lower bound was not set, set it
  frequencyMap[lowerBound] = {0};

  // Count the frequency of each interval
  std::ranges::for_each(
    values,
    [&](fn::i32f value) -> void
    {
      // Find the key in the frequency map that is closest to the value
      const auto key{*std::ranges::min_element(
        std::views::keys(frequencyMap),
        [&](fn::i32f lhs, fn::i32f rhs) noexcept -> bool
        {
          return std::abs(lhs - value) < std::abs(rhs - value);
        }
      )};

      // Increment the frequency of the key
      frequencyMap[key]++;
    }
  );

  // Find the maximum frequency for y-axis scaling
  const fn::u32f maxFrequency{
    *std::ranges::max_element(std::views::values(frequencyMap))
  };

  // Calculate y-axis interval respecting row count
  const fn::u32f yAxisInterval{
    std::max(fn::u32f{1}, maxFrequency / chartSize.second)
  };

  // Create ChartFeed
  const ChartFeed chartFeed{
    frequencyMap, maxFrequency, xAxisInterval, yAxisInterval, lowerBound
  };

  // Calculate the chart size with respect to intervals
  const std::pair<fn::u16f, fn::u16f> resultingChartSize{
    fn::narrow_cast<fn::u16f>(frequencyMap.size()), maxFrequency / yAxisInterval
  };

  // Return the chart feed and the resulting chart size
  return {chartFeed, resultingChartSize};
}
