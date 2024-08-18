#pragma once

#include "Math/_internal/base.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>

namespace Math
{
  [[nodiscard]] constexpr auto NUMBER_LENGTH(fn::i32f number) noexcept -> fn::u16f
  {
    // Check if the number is 0
    if (number == 0)
    {
      return 1;
    }

    // Initialize the count (If negative, add 1)
    fn::u16f count{number < 0 ? fn::u16f{1} : fn::u16f{0}};

    // Count the digits
    while (number != 0)
    {
      number /= _internal::BASE;
      ++count;
    }

    // Return the count
    return count;
  }

  struct Feed
  {
    fn::map<fn::i32f, fn::u32f> frequencies;
    fn::u32f                    maxFrequency{};
    fn::u32f                    xAxisInterval{};
    fn::u32f                    yAxisInterval{};
    fn::i32f                    lowerBound{};
  };

  [[nodiscard]] auto generateFeed(
    const fn::vec<fn::i32f>&            values,
    const fn::pair<fn::i32f, fn::i32f>& bounds,
    const fn::pair<fn::u16f, fn::u16f>& size
  ) -> fn::pair<Feed, fn::pair<fn::u16f, fn::u16f>>;
} // namespace Math
