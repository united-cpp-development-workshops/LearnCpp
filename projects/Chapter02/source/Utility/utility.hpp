#pragma once
#include "Math/math.hpp"

#include <cstdint>
#include <map>
#include <optional>
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

  auto optionsHandler(
    std::pair<std::uint16_t, std::uint16_t>& preferredChartSize,
    std::pair<std::uint16_t, std::uint16_t>& currentChartSize,
    int&                                     xAxisInterval,
    int&                                     yAxisInterval,
    std::map<int, int>&                      frequencyMap,
    const std::vector<int>&                  values,
    int                                      lowerBound,
    int                                      upperBound
  ) -> bool;

  auto noFurtherZoomHandler(
    bool                      zoomIn,
    Direction                 direction,
    int                       xAxisInterval,
    int                       yAxisInterval,
    const std::map<int, int>& frequencyMap
  ) -> bool;

  auto chartZoom(
    bool                                     zoomIn,
    Direction                                zoomDirection,
    std::pair<std::uint16_t, std::uint16_t>& preferredChartSize,
    std::pair<std::uint16_t, std::uint16_t>& currentChartSize,
    const std::vector<int>&                  values,
    int                                      lowerBound,
    int                                      upperBound
  ) -> std::optional<Math::ChartFeed>;
} // namespace Utility
