#pragma once
#include "Math/math.hpp"

#include <cstdint>
#include <utility>
#include <vector>

namespace Utility
{
  enum class Direction : std::uint8_t
  {
    BOTH,
    HORIZONTAL,
    VERTICAL
  };

  auto chartZoom(
    bool                       zoomIn,
    Direction                  zoomDirection,
    const std::pair<int, int>& chartSize,
    const std::vector<int>&    values,
    int                        lowerBound,
    int                        upperBound
  ) -> std::pair<Math::ChartFeed, std::pair<int, int>>;
} // namespace Utility
