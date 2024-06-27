#pragma once

#include "foundation.hpp"
#include "Math/math.hpp"
#include "Utility/utility.hpp"

#include <utility>
#include <vector>

namespace IO
{
  // NOLINTBEGIN(clang-diagnostic-unused-const-variable)

  constexpr cstr X_AXIS_NAME{"Value"};
  constexpr cstr Y_AXIS_NAME{"Frequency"};

  // NOLINTEND(clang-diagnostic-unused-const-variable)

  enum class Option : u8f
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
  auto getSamplesCountInput() -> size;
  [[nodiscard]]
  auto getLowerBoundInput() -> i32f;
  [[nodiscard]]
  auto getUpperBoundInput() -> i32f;
  [[nodiscard]]
  auto getPreferredChartSizeInput() -> std::pair<u16f, u16f>;
  auto printResultsHeader() -> void;
  auto printChart(const Math::ChartFeed& chartFeed) -> void;
  auto printStatistics(const std::vector<i32f>& values) -> void;
  auto printOptionsHeader() -> void;
  [[nodiscard]]
  auto getOptionInput() -> Option;
  auto printNoFurtherZoom(Utility::Direction direction) -> void;
} // namespace IO
