#include "Utility/utility.hpp"

#include "Math/math.hpp"

#include <utility>
#include <vector>

auto Utility::chartZoom(
  bool                       zoomIn,
  Direction                  zoomDirection,
  const std::pair<int, int>& chartSize,
  const std::vector<int>&    values,
  int                        lowerBound,
  int                        upperBound
) -> std::pair<Math::ChartFeed, std::pair<int, int>>
{
  // Determine zoom direction
  const int zoomConstant{zoomIn ? 1 : -1};

  // Initialize new chart feed and size
  Math::ChartFeed     newChartFeed;
  std::pair<int, int> newChartSize{chartSize};

  // Zoom loop
  bool zoomed{false};
  while (not zoomed)
  {
    // Increase preferred column count if direction allows it
    if (zoomDirection == Direction::BOTH
        or zoomDirection == Direction::HORIZONTAL)
    {
      newChartSize.first += zoomConstant;
    }

    // Increase preferred row count if direction allows it
    if (zoomDirection == Direction::BOTH
        or zoomDirection == Direction::VERTICAL)
    {
      newChartSize.second += zoomConstant;
    }

    // Generate chart feed and size
    const auto [tempChartFeed, resultingChartSize]{
      Math::generateChartFeed(values, lowerBound, upperBound, newChartSize)
    };

    // Check if zoomed
    if (resultingChartSize.first > chartSize.first
        or resultingChartSize.second > chartSize.second)
    {
      zoomed       = {true};
      newChartFeed = {tempChartFeed};
    }
  }

  // Return new chart feed and size
  return {newChartFeed, newChartSize};
}
