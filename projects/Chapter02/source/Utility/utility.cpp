#include "pch.hpp"

#include "Utility/utility.hpp"

#include "IO/io.hpp"
#include "Math/math.ipp"

#include <Foundation/types.hpp>

#include <algorithm>
#include <map>
#include <optional>
#include <ranges>
#include <utility>
#include <vector>

namespace
{
  auto zoomHandler(
    const fn::bln                         zoomIn,
    std::pair<fn::u16f, fn::u16f>&        preferredChartSize,
    std::pair<fn::u16f, fn::u16f>&        currentChartSize,
    std::map<fn::i32f, fn::u32f>&         frequencyMap,
    const std::pair<fn::u32f&, fn::u32f&> intervals,
    const std::vector<fn::i32f>&          values,
    const std::pair<fn::i32f, fn::i32f>&  bounds,
    const IO::Option                      option
  ) -> fn::none
  {
    // Using declarations
    using enum IO::Option;

    // Create zoom direction
    Utility::Direction direction{};

    if (option == ZOOM_IN_HORIZONTAL)
    {
      // Set horizontal zoom direction
      direction = {Utility::Direction::HORIZONTAL};
    }
    else if (option == ZOOM_IN_VERTICAL)
    {
      // Set vertical zoom direction
      direction = {Utility::Direction::VERTICAL};
    }
    else
    {
      // Set both zoom direction
      direction = {Utility::Direction::BOTH};
    }

    // Check if we can zoom further
    if (noFurtherZoomHandler(zoomIn, direction, intervals, frequencyMap))
    {
      return;
    }

    // Zoom
    const auto optionalNewChartFeed{chartZoom(
      zoomIn, direction, preferredChartSize, currentChartSize, values, bounds
    )};

    // Check if zoom failed
    if (not optionalNewChartFeed.has_value())
    {
      IO::printNoFurtherZoom(direction);
      return;
    }

    // Success
    const auto& newChartFeed{optionalNewChartFeed.value()};

    // Update intervals
    intervals.first  = {newChartFeed.xAxisInterval};
    intervals.second = {newChartFeed.yAxisInterval};

    // Update frequency map
    frequencyMap = {newChartFeed.frequencyMap};

    // Print chart again
    IO::printChart(newChartFeed);
  }
} // namespace

namespace Utility
{
  [[nodiscard]] auto optionsHandler(
    std::pair<fn::u16f, fn::u16f>&        preferredChartSize,
    std::pair<fn::u16f, fn::u16f>&        currentChartSize,
    std::map<fn::i32f, fn::u32f>&         frequencyMap,
    const std::pair<fn::u32f&, fn::u32f&> intervals,
    const std::vector<fn::i32f>&          values,
    const std::pair<fn::i32f, fn::i32f>&  bounds
  ) -> fn::bln
  {
    // Using declarations
    using enum IO::Option;

    // Options loop
    while (true)
    {
      // Print and get options
      IO::printOptionsHeader();
      const auto option{IO::getOptionInput()};

      // Handle options
      switch (option)
      {
      case ZOOM_IN:
      case ZOOM_IN_HORIZONTAL:
      case ZOOM_IN_VERTICAL:
      {
        zoomHandler(
          true,
          preferredChartSize,
          currentChartSize,
          frequencyMap,
          intervals,
          values,
          bounds,
          option
        );
        break;
      }
      case ZOOM_OUT:
      case ZOOM_OUT_HORIZONTAL:
      case ZOOM_OUT_VERTICAL:
      {
        zoomHandler(
          false,
          preferredChartSize,
          currentChartSize,
          frequencyMap,
          intervals,
          values,
          bounds,
          option
        );
        break;
      }
      case STATISTICS:
      {
        IO::printStatistics(values);
        break;
      }
      case NEW_CHART:
      {
        return true;
      }
      case QUIT:
      {
        return false;
      }
      }
    }
  }

  [[nodiscard]] auto noFurtherZoomHandler(
    const fn::bln                        zoomIn,
    const Direction                      direction,
    const std::pair<fn::u32f, fn::u32f>& intervals,
    const std::map<fn::i32f, fn::u32f>&  frequencyMap
  ) -> fn::bln
  {
    // Can zoom in
    const auto canZoomInHorizontal{intervals.first > 1};
    const auto canZoomInVertical{intervals.second > 1};

    // Can zoom out
    const auto canZoomOutHorizontal{(frequencyMap.size() - 1) > 1};
    const auto canZoomOutVertical{
      (*std::ranges::max_element(std::views::values(frequencyMap))
       / intervals.second)
      > 1
    };

    auto canZoom{true};

    // Check if we can zoom further
    switch (direction)
    {
    case Direction::BOTH:
    {
      // Check if we can zoom in both directions
      if (zoomIn and (not canZoomInHorizontal and not canZoomInVertical))
      {
        canZoom = {false};
      }

      // Check if we can zoom out in both directions
      if (not zoomIn and (not canZoomOutHorizontal and not canZoomOutVertical))
      {
        canZoom = {false};
      }
      break;
    }
    case Direction::HORIZONTAL:
    {
      // Check if we can zoom in in horizontal direction
      if (zoomIn and not canZoomInHorizontal) { canZoom = {false}; }

      // Check if we can zoom out in horizontal direction
      if (not zoomIn and not canZoomOutHorizontal) { canZoom = {false}; }
      break;
    }
    case Direction::VERTICAL:
    {
      // Check if we can zoom in in vertical direction
      if (zoomIn and not canZoomInVertical) { canZoom = {false}; }

      // Check if we can zoom out in vertical direction
      if (not zoomIn and not canZoomOutVertical) { canZoom = {false}; }
      break;
    }
    }

    // Print the message and return true
    if (not canZoom)
    {
      IO::printNoFurtherZoom(direction);
      return true;
    }

    // Return false
    return false;
  }

  [[nodiscard]] auto chartZoom(
    const fn::bln                        zoomIn,
    const Direction                      zoomDirection,
    std::pair<fn::u16f, fn::u16f>&       preferredChartSize,
    std::pair<fn::u16f, fn::u16f>&       currentChartSize,
    const std::vector<fn::i32f>&         values,
    const std::pair<fn::i32f, fn::i32f>& bounds
  ) -> std::optional<Math::ChartFeed>
  {
    // Save old chart sizes
    const std::pair<fn::u16f, fn::u16f> oldPreferredChartSize{preferredChartSize
    };
    const std::pair<fn::u16f, fn::u16f> oldChartSize{currentChartSize};

    // Initialize new chart feed and size
    Math::ChartFeed newChartFeed;

    // Zoom loop
    fn::bln zoomed{false};
    while (not zoomed)
    {
      // Increase preferred column count if direction allows it
      if (zoomDirection == Direction::BOTH
          or zoomDirection == Direction::HORIZONTAL)
      {
        preferredChartSize.first = {
          zoomIn ? (preferredChartSize.first + fn::u16f{1})
                 : (preferredChartSize.first - fn::u16f{1})
        };
      }

      // Increase preferred row count if direction allows it
      if (zoomDirection == Direction::BOTH
          or zoomDirection == Direction::VERTICAL)
      {
        preferredChartSize.first = {
          zoomIn ? (preferredChartSize.first + fn::u16f{1})
                 : (preferredChartSize.first - fn::u16f{1})
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
      const auto [tempChartFeed, resultingChartSize]{
        Math::generateChartFeed(values, bounds, preferredChartSize)
      };

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
} // namespace Utility
