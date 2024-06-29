#pragma once

#include "Foundation/types.hpp"

#include "Math/math.ipp"
#include "Utility/utility.hpp"

#include <utility>
#include <vector>

namespace IO
{
  inline constexpr fn::cstr X_AXIS_NAME{"Value"};
  inline constexpr fn::cstr Y_AXIS_NAME{"Frequency"};

  enum class Option : fn::u8f
  {
    ZOOM_IN,
    ZOOM_IN_HORIZONTAL,
    ZOOM_IN_VERTICAL,
    ZOOM_OUT,
    ZOOM_OUT_HORIZONTAL,
    ZOOM_OUT_VERTICAL,
    NEW_CHART,
    QUIT
  };

  auto printWelcome() -> void;
  auto printInformative() -> void;
  [[nodiscard]]
  auto getSamplesCountInput() -> fn::size;
  [[nodiscard]]
  auto getLowerBoundInput() -> fn::i32f;
  [[nodiscard]]
  auto getUpperBoundInput() -> fn::i32f;
  [[nodiscard]]
  auto getPreferredChartSizeInput() -> std::pair<fn::u16f, fn::u16f>;
  auto printResultsHeader() -> void;
  auto printChart(const Math::ChartFeed& chartFeed) -> void;
  auto printStatistics(const std::vector<fn::i32f>& values) -> void;
  auto printOptionsHeader() -> void;
  [[nodiscard]]
  auto getOptionInput() -> Option;
  auto printNoFurtherZoom(Utility::Direction direction) -> void;
} // namespace IO
