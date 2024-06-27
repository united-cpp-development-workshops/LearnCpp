#include "pch.hpp"

#include "Utility/utility.hpp"

#include "foundation.hpp"
#include "IO/io.hpp"
#include "Math/math.hpp"

#include <algorithm>
#include <map>
#include <optional>
#include <ranges>
#include <tuple>
#include <utility>
#include <vector>

auto Utility::optionsHandler(
  std::pair<u16f, u16f>&   preferredChartSize,
  std::pair<u16f, u16f>&   currentChartSize,
  u32f&                    xAxisInterval,
  u32f&                    yAxisInterval,
  std::map<i32f, u32f>&    frequencyMap,
  const std::vector<i32f>& values,
  i32f                     lowerBound,
  i32f                     upperBound
) -> bool
{
  // Options loop
  while (true)
  {
    // Print and get options
    IO::printOptionsHeader();
    const IO::Option option{IO::getOptionInput()};

    // Handle options
    switch (option)
    {
    case IO::Option::ZOOM_IN:
    case IO::Option::ZOOM_IN_HORIZONTAL:
    case IO::Option::ZOOM_IN_VERTICAL:
    {
      // Set zoom direction
      auto direction{Utility::Direction::BOTH};

      if (option == IO::Option::ZOOM_IN_HORIZONTAL)
      {
        // Set horizontal zoom direction
        direction = {Utility::Direction::HORIZONTAL};
      }
      else if (option == IO::Option::ZOOM_IN_VERTICAL)
      {
        // Set vertical zoom direction
        direction = {Utility::Direction::VERTICAL};
      }

      // Check if we can zoom further
      if (noFurtherZoomHandler(
            true, direction, xAxisInterval, yAxisInterval, frequencyMap
          ))
      {
        break;
      }

      // Zoom
      const auto optionalNewChartFeed{Utility::chartZoom(
        true,
        direction,
        preferredChartSize,
        currentChartSize,
        values,
        lowerBound,
        upperBound
      )};

      // Check if zoom failed
      if (not optionalNewChartFeed.has_value())
      {
        IO::printNoFurtherZoom(direction);
        break;
      }

      // Success
      const auto& newChartFeed{optionalNewChartFeed.value()};

      // Update intervals
      xAxisInterval = {newChartFeed.xAxisInterval};
      yAxisInterval = {newChartFeed.yAxisInterval};

      // Update frequency map
      frequencyMap = {newChartFeed.frequencyMap};

      // Print chart again
      IO::printChart(newChartFeed);
      break;
    }
    case IO::Option::ZOOM_OUT:
    case IO::Option::ZOOM_OUT_HORIZONTAL:
    case IO::Option::ZOOM_OUT_VERTICAL:
    {
      // Set zoom direction
      auto direction{Utility::Direction::BOTH};

      if (option == IO::Option::ZOOM_OUT_HORIZONTAL)
      {
        // Set horizontal zoom direction
        direction = {Utility::Direction::HORIZONTAL};
      }
      else if (option == IO::Option::ZOOM_OUT_VERTICAL)
      {
        // Set vertical zoom direction
        direction = {Utility::Direction::VERTICAL};
      }

      // Check if we can zoom further
      if (noFurtherZoomHandler(
            false, direction, xAxisInterval, yAxisInterval, frequencyMap
          ))
      {
        break;
      }

      // Zoom
      const auto optionalNewChartFeed{Utility::chartZoom(
        false,
        direction,
        preferredChartSize,
        currentChartSize,
        values,
        lowerBound,
        upperBound
      )};

      // Check if zoom failed
      if (not optionalNewChartFeed.has_value())
      {
        IO::printNoFurtherZoom(direction);
        break;
      }

      // Success
      const auto& newChartFeed{optionalNewChartFeed.value()};

      // Update intervals
      xAxisInterval = {newChartFeed.xAxisInterval};
      yAxisInterval = {newChartFeed.yAxisInterval};

      // Update frequency map
      frequencyMap = {newChartFeed.frequencyMap};

      // Print chart again
      IO::printChart(newChartFeed);
      break;
    }
    case IO::Option::NEW_CHART:
    {
      return true;
    }
    case IO::Option::QUIT:
    {
      return false;
    }
    }
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
auto Utility::noFurtherZoomHandler(
  bool                        zoomIn,
  const Utility::Direction    direction,
  u32f                        xAxisInterval,
  u32f                        yAxisInterval,
  const std::map<i32f, u32f>& frequencyMap
) -> bool
{
  // Check if we can zoom further
  switch (direction)
  {
  case Utility::Direction::BOTH:
  {
    if (zoomIn)
    {
      // Check if we can zoom in both directions
      if (xAxisInterval <= 1 and yAxisInterval <= 1)
      {
        IO::printNoFurtherZoom(direction);
        return true;
      }
    }
    else
    {
      // Find max frequency
      const u32f maxFrequency{
        *std::ranges::max_element(std::views::values(frequencyMap))
      };

      // Check if we can zoom out in both directions
      if (frequencyMap.size() <= 2 and (maxFrequency / yAxisInterval) <= 1)
      {
        IO::printNoFurtherZoom(direction);
        return true;
      }
    }
    break;
  }
  case Utility::Direction::HORIZONTAL:
  {
    if (zoomIn)
    {
      // Check if we can zoom in in horizontal direction
      if (xAxisInterval <= 1)
      {
        IO::printNoFurtherZoom(direction);
        return true;
      }
    }
    else
    {
      // Check if we can zoom out in horizontal direction
      if (frequencyMap.size() <= 2)
      {
        IO::printNoFurtherZoom(direction);
        return true;
      }
    }
    break;
  }
  case Utility::Direction::VERTICAL:
  {
    if (zoomIn)
    {
      // Check if we can zoom in in vertical direction
      if (yAxisInterval <= 1)
      {
        IO::printNoFurtherZoom(direction);
        return true;
      }
    }
    else
    {
      // Find max frequency
      const u32f maxFrequency{
        *std::ranges::max_element(std::views::values(frequencyMap))
      };

      // Check if we can zoom out in vertical direction
      if ((maxFrequency / yAxisInterval) <= 1)
      {
        IO::printNoFurtherZoom(direction);
        return true;
      }
    }
    break;
  }
  }
  return false;
}

auto Utility::chartZoom(
  bool                     zoomIn,
  Direction                zoomDirection,
  std::pair<u16f, u16f>&   preferredChartSize,
  std::pair<u16f, u16f>&   currentChartSize,
  const std::vector<i32f>& values,
  i32f                     lowerBound,
  i32f                     upperBound
) -> std::optional<Math::ChartFeed>
{
  // Save old chart sizes
  const std::pair<u16f, u16f> oldPreferredChartSize{preferredChartSize};
  const std::pair<u16f, u16f> oldChartSize{currentChartSize};

  // Initialize new chart feed and size
  Math::ChartFeed newChartFeed;

  // Zoom loop
  bool zoomed{false};
  while (not zoomed)
  {
    // Increase preferred column count if direction allows it
    if (zoomDirection == Direction::BOTH
        or zoomDirection == Direction::HORIZONTAL)
    {
      preferredChartSize.first = {
        zoomIn ? preferredChartSize.first + u16f{1}
               : preferredChartSize.first - u16f{1}
      };
    }

    // Increase preferred row count if direction allows it
    if (zoomDirection == Direction::BOTH
        or zoomDirection == Direction::VERTICAL)
    {
      preferredChartSize.first = {
        zoomIn ? preferredChartSize.first + u16f{1}
               : preferredChartSize.first - u16f{1}
      };
    }

    if (preferredChartSize.first == 0 or preferredChartSize.second == 0)
    {
      preferredChartSize = {oldPreferredChartSize};
      currentChartSize   = {oldChartSize};

      // Return empty optional
      return {};
    }

    // Generate chart feed and size
    const auto [tempChartFeed, resultingChartSize]{Math::generateChartFeed(
      values, lowerBound, upperBound, preferredChartSize
    )};

    // If no change occurred, zoom again
    if (currentChartSize == resultingChartSize) { continue; }

    // Check if zoomed
    if (resultingChartSize.first > preferredChartSize.first
        or resultingChartSize.second > preferredChartSize.second)
    {
      zoomed           = {true};
      newChartFeed     = {tempChartFeed};
      currentChartSize = {resultingChartSize};
    }
  }

  // Return new chart feed
  return newChartFeed;
}
