#pragma once

#include "foundation.hpp"
#include "Math/math.hpp"

#include <map>
#include <optional>
#include <utility>
#include <vector>

namespace Utility
{
  enum class Direction : u8f
  {
    BOTH,
    HORIZONTAL,
    VERTICAL
  };

  auto optionsHandler(
    std::pair<u16f, u16f>&   preferredChartSize,
    std::pair<u16f, u16f>&   currentChartSize,
    u32f&                    xAxisInterval,
    u32f&                    yAxisInterval,
    std::map<i32f, u32f>&    frequencyMap,
    const std::vector<i32f>& values,
    i32f                     lowerBound,
    i32f                     upperBound
  ) -> bool;
  auto noFurtherZoomHandler(
    bool                        zoomIn,
    Direction                   direction,
    u32f                        xAxisInterval,
    u32f                        yAxisInterval,
    const std::map<i32f, u32f>& frequencyMap
  ) -> bool;
  auto chartZoom(
    bool                     zoomIn,
    Direction                zoomDirection,
    std::pair<u16f, u16f>&   preferredChartSize,
    std::pair<u16f, u16f>&   currentChartSize,
    const std::vector<i32f>& values,
    i32f                     lowerBound,
    i32f                     upperBound
  ) -> std::optional<Math::ChartFeed>;
} // namespace Utility
