#include "Utility/utility.hpp"

#include "IO/io.hpp"
#include "Math/math.hpp"

#include <algorithm>
#include <cstdint>
#include <GSL/narrow>
#include <map>
#include <optional>
#include <ranges>
#include <tuple>
#include <utility>
#include <vector>

auto Utility::optionsHandler(
  std::pair<std::uint16_t, std::uint16_t>& preferredChartSize,
  std::pair<std::uint16_t, std::uint16_t>& currentChartSize,
  int&                                     xAxisInterval,
  int&                                     yAxisInterval,
  std::map<int, int>&                      frequencyMap,
  const std::vector<int>&                  values,
  int                                      lowerBound,
  int                                      upperBound
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
  bool                      zoomIn,
  const Utility::Direction  direction,
  int                       xAxisInterval,
  int                       yAxisInterval,
  const std::map<int, int>& frequencyMap
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
      const int maxFrequency{
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
      const int maxFrequency{
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
  bool                                     zoomIn,
  Direction                                zoomDirection,
  std::pair<std::uint16_t, std::uint16_t>& preferredChartSize,
  std::pair<std::uint16_t, std::uint16_t>& currentChartSize,
  const std::vector<int>&                  values,
  int                                      lowerBound,
  int                                      upperBound
) -> std::optional<Math::ChartFeed>
{
  // Save old chart sizes
  const std::pair<std::uint16_t, std::uint16_t> oldPreferredChartSize{
    preferredChartSize
  };
  const std::pair<std::uint16_t, std::uint16_t> oldChartSize{currentChartSize};

  // Determine zoom direction
  const std::int16_t zoomConstant{gsl::narrow<std::int16_t>(zoomIn ? 1 : -1)};

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
      preferredChartSize.first += zoomConstant;
    }

    // Increase preferred row count if direction allows it
    if (zoomDirection == Direction::BOTH
        or zoomDirection == Direction::VERTICAL)
    {
      preferredChartSize.second += zoomConstant;
    }

    if (preferredChartSize.first == 0 or preferredChartSize.second == 0)
    {
      preferredChartSize = {oldPreferredChartSize};
      currentChartSize   = {oldChartSize};
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
