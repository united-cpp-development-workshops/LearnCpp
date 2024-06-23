#pragma once

#include "Math/math.hpp"

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

namespace IO
{
  // NOLINTBEGIN(clang-diagnostic-unused-const-variable)
  constexpr const char* X_AXIS_NAME{"Value"};
  constexpr const char* Y_AXIS_NAME{"Frequency"};
  // NOLINTEND(clang-diagnostic-unused-const-variable)

  enum class Option : std::uint8_t
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
  auto getSamplesCountInput() -> std::size_t;
  [[nodiscard]]
  auto getLowerBoundInput() -> int;
  [[nodiscard]]
  auto getUpperBoundInput() -> int;
  [[nodiscard]]
  auto getChartSizesInput() -> std::pair<int, int>;
  auto printResultsHeader() -> void;
  auto printChart(const Math::ChartFeed& chartFeed) -> void;
  auto printStatistics(const std::vector<int>& values) -> void;
  auto printOptionsHeader() -> void;
  [[nodiscard]]
  auto getOptionInput() -> Option;
} // namespace IO
