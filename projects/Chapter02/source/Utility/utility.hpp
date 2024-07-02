#pragma once

#include "Foundation/types.hpp"

#include "Math/math.ipp"

#include <map>
#include <optional>
#include <utility>
#include <vector>

namespace Utility
{
  enum class Direction : fn::u8f
  {
    BOTH,
    HORIZONTAL,
    VERTICAL
  };

  auto optionsHandler(
    std::pair<fn::u16f, fn::u16f>& preferredChartSize,
    std::pair<fn::u16f, fn::u16f>& currentChartSize,
    fn::u32f&                      xAxisInterval,
    fn::u32f&                      yAxisInterval,
    std::map<fn::i32f, fn::u32f>&  frequencyMap,
    const std::vector<fn::i32f>&   values,
    fn::i32f                       lowerBound,
    fn::i32f                       upperBound
  ) -> fn::bln;
  auto noFurtherZoomHandler(
    fn::bln                             zoomIn,
    Direction                           direction,
    fn::u32f                            xAxisInterval,
    fn::u32f                            yAxisInterval,
    const std::map<fn::i32f, fn::u32f>& frequencyMap
  ) -> fn::bln;
  auto chartZoom(
    fn::bln                        zoomIn,
    Direction                      zoomDirection,
    std::pair<fn::u16f, fn::u16f>& preferredChartSize,
    std::pair<fn::u16f, fn::u16f>& currentChartSize,
    const std::vector<fn::i32f>&   values,
    fn::i32f                       lowerBound,
    fn::i32f                       upperBound
  ) -> std::optional<Math::ChartFeed>;
} // namespace Utility
