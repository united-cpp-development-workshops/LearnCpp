#include "pch.hpp"

#include "Math/math.ipp"

#include <Foundation/containers.hpp>
#include <Foundation/Support/narrow.ipp>
#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>

#include <algorithm>
#include <cmath>
#include <ranges>

namespace Math
{
  [[nodiscard]] auto generateChartFeed(
    const fn::vec<fn::i32f>&            values,
    const fn::pair<fn::i32f, fn::i32f>& bounds,
    const fn::pair<fn::u16f, fn::u16f>& chartSize
  ) -> fn::pair<ChartFeed, fn::pair<fn::u16f, fn::u16f>>
  {
    // Calculate x-axis interval respecting column count
    const fn::u32f xAxisInterval{std::max(
      fn::u32f{1}, fn::narrow_cast<fn::u32f>(bounds.second - bounds.first) / chartSize.first
    )};

    // Define the frequency map
    fn::map<fn::i32f, fn::u32f> frequencyMap;

    // Initialize the frequency map
    for (fn::i32f x{bounds.second}; x > bounds.first; x -= fn::narrow_cast<fn::i32f>(xAxisInterval))
    {
      frequencyMap[x] = {0};
    }

    // If lower bound was not set, set it
    frequencyMap[bounds.first] = {0};

    // Count the frequency of each interval
    std::ranges::for_each(
      values,
      [&frequencyMap](const fn::i32f value) -> fn::none
      {
        // Find the key in the frequency map that is closest to the value
        const auto key{*std::ranges::min_element(
          std::views::keys(frequencyMap),
          [&value](const fn::i32f lhs, const fn::i32f rhs) noexcept -> fn::bln
          {
            return std::abs(lhs - value) < std::abs(rhs - value);
          }
        )};

        // Increment the frequency of the key
        ++frequencyMap[key];
      }
    );

    // Find the maximum frequency for y-axis scaling
    const fn::u32f maxFrequency{*std::ranges::max_element(std::views::values(frequencyMap))};

    // Calculate y-axis interval respecting row count
    const fn::u32f yAxisInterval{std::max(fn::u32f{1}, maxFrequency / chartSize.second)};

    // Create ChartFeed
    const ChartFeed chartFeed{
      frequencyMap, maxFrequency, xAxisInterval, yAxisInterval, bounds.first
    };

    // Calculate the chart size with respect to intervals
    const fn::pair<fn::u16f, fn::u16f> resultingChartSize{
      fn::narrow_cast<fn::u16f>(frequencyMap.size()), maxFrequency / yAxisInterval
    };

    // Return the chart feed and the resulting chart size
    return {chartFeed, resultingChartSize};
  }
} // namespace Math
