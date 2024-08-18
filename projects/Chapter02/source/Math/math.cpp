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
  [[nodiscard]] auto generateFeed(
    const fn::vec<fn::i32f>&            values,
    const fn::pair<fn::i32f, fn::i32f>& bounds,
    const fn::pair<fn::u16f, fn::u16f>& size
  ) -> fn::pair<Feed, fn::pair<fn::u16f, fn::u16f>>
  {
    // Calculate x-axis interval respecting column count
    const fn::u32f xAxisInterval{
      std::max(fn::u32f{1}, fn::narrow_cast<fn::u32f>(bounds.second - bounds.first) / size.first)
    };

    // Define the frequency map
    fn::map<fn::i32f, fn::u32f> frequencies;

    // Initialize the frequency map
    for (fn::i32f x{bounds.second}; x > bounds.first; x -= fn::narrow_cast<fn::i32f>(xAxisInterval))
    {
      frequencies[x] = {0};
    }

    // If lower bound was not set, set it
    frequencies[bounds.first] = {0};

    // Count the frequency of each interval
    std::ranges::for_each(
      values,
      [&frequencies](const fn::i32f value) -> fn::none
      {
        // Find the key in the frequency map that is closest to the value
        const auto key{*std::ranges::min_element(
          std::views::keys(frequencies),
          [&value](const fn::i32f lhs, const fn::i32f rhs) noexcept -> fn::bln
          {
            return std::abs(lhs - value) < std::abs(rhs - value);
          }
        )};

        // Increment the frequency of the key
        ++frequencies[key];
      }
    );

    // Find the maximum frequency for y-axis scaling
    const fn::u32f maxFrequency{*std::ranges::max_element(std::views::values(frequencies))};

    // Calculate y-axis interval respecting row count
    const fn::u32f yAxisInterval{std::max(fn::u32f{1}, maxFrequency / size.second)};

    // Create Feed
    const Feed feed{frequencies, maxFrequency, xAxisInterval, yAxisInterval, bounds.first};

    // Calculate the chart size with respect to intervals
    const fn::pair<fn::u16f, fn::u16f> resultingSize{
      fn::narrow_cast<fn::u16f>(frequencies.size()), maxFrequency / yAxisInterval
    };

    // Return the chart feed and the resulting chart size
    return {feed, resultingSize};
  }
} // namespace Math
