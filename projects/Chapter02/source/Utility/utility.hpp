#pragma once

#include "Math/math.ipp"

#include <Foundation/types.hpp>

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

  [[nodiscard]] auto optionsHandler(
    std::pair<fn::u16f, fn::u16f>&       preferredChartSize,
    std::pair<fn::u16f, fn::u16f>&       currentChartSize,
    std::map<fn::i32f, fn::u32f>&        frequencyMap,
    std::pair<fn::u32f&, fn::u32f&>      intervals,
    const std::vector<fn::i32f>&         values,
    const std::pair<fn::i32f, fn::i32f>& bounds
  ) -> fn::bln;
  [[nodiscard]] auto noFurtherZoomHandler(
    fn::bln                              zoomIn,
    Direction                            direction,
    const std::pair<fn::u32f, fn::u32f>& intervals,
    const std::map<fn::i32f, fn::u32f>&  frequencyMap
  ) -> fn::bln;
  [[nodiscard]] auto chartZoom(
    fn::bln                              zoomIn,
    Direction                            zoomDirection,
    std::pair<fn::u16f, fn::u16f>&       preferredChartSize,
    std::pair<fn::u16f, fn::u16f>&       currentChartSize,
    const std::vector<fn::i32f>&         values,
    const std::pair<fn::i32f, fn::i32f>& bounds
  ) -> std::optional<Math::ChartFeed>;
} // namespace Utility
