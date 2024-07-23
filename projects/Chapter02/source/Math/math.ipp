#pragma once

#include "Math/_internal/base.hpp"

#include <Foundation/types.hpp>

#include <map>
#include <utility>
#include <vector>

namespace Math
{
  constexpr auto NUMBER_LENGTH(fn::i32f number) noexcept -> fn::u16f
  {
    // Check if the number is 0
    if (number == 0) { return 1; }

    // Initialize the count (If negative, add 1)
    fn::u16f count{number < 0 ? fn::u16f{1} : fn::u16f{0}};

    // Count the digits
    while (number != 0)
    {
      number /= _internal::BASE;
      count++;
    }

    // Return the count
    return count;
  }

  struct ChartFeed
  {
    std::map<fn::i32f, fn::u32f> frequencyMap;
    fn::u32f                     maxFrequency{};
    fn::u32f                     xAxisInterval{};
    fn::u32f                     yAxisInterval{};
    fn::i32f                     lowerBound{};
  };

  auto generateChartFeed(
    const std::vector<fn::i32f>&  values,
    fn::i32f                      lowerBound,
    fn::i32f                      upperBound,
    std::pair<fn::u16f, fn::u16f> chartSize
  ) -> std::pair<ChartFeed, std::pair<fn::u16f, fn::u16f>>;
} // namespace Math
