#include "pch.hpp"

#include "Utility/utility.hpp"

#include "IO/io.hpp"
#include "Math/math.ipp"

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>

#include <algorithm>
#include <ranges>

namespace
{
  auto zoomHandler(
    const fn::bln                        isZoomIn,
    fn::pair<fn::u16f, fn::u16f>&        preferredSize,
    fn::pair<fn::u16f, fn::u16f>&        currentSize,
    fn::map<fn::i32f, fn::u32f>&         frequencies,
    const fn::pair<fn::u32f&, fn::u32f&> intervals,
    const fn::vec<fn::i32f>&             values,
    const fn::pair<fn::i32f, fn::i32f>&  bounds,
    const IO::Option                     option
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
    if (noFurtherZoomHandler(isZoomIn, direction, intervals, frequencies))
    {
      return;
    }

    // Zoom
    const auto newFeedOpt{zoom(isZoomIn, direction, preferredSize, currentSize, values, bounds)};

    // Check if zoom failed
    if (not newFeedOpt.has_value())
    {
      IO::printNoFurtherZoom(direction);
      return;
    }

    // Success
    const auto& newFeed{newFeedOpt.value()};

    // Update intervals
    intervals.first  = {newFeed.xAxisInterval};
    intervals.second = {newFeed.yAxisInterval};

    // Update frequency map
    frequencies = {newFeed.frequencies};

    // Print chart again
    IO::printChart(newFeed);
  }
} // namespace

namespace Utility
{
  [[nodiscard]] auto optionsHandler(
    fn::pair<fn::u16f, fn::u16f>&        preferredSize,
    fn::pair<fn::u16f, fn::u16f>&        currentSize,
    fn::map<fn::i32f, fn::u32f>&         frequencies,
    const fn::pair<fn::u32f&, fn::u32f&> intervals,
    const fn::vec<fn::i32f>&             values,
    const fn::pair<fn::i32f, fn::i32f>&  bounds
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
          true, preferredSize, currentSize, frequencies, intervals, values, bounds, option
        );
        break;
      }
      case ZOOM_OUT:
      case ZOOM_OUT_HORIZONTAL:
      case ZOOM_OUT_VERTICAL:
      {
        zoomHandler(
          false, preferredSize, currentSize, frequencies, intervals, values, bounds, option
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
    const fn::bln                       isZoomIn,
    const Direction                     direction,
    const fn::pair<fn::u32f, fn::u32f>& intervals,
    const fn::map<fn::i32f, fn::u32f>&  frequencies
  ) -> fn::bln
  {
    // Can zoom in
    const auto canZoomInHorizontal{intervals.first > 1};
    const auto canZoomInVertical{intervals.second > 1};

    // Can zoom out
    const auto canZoomOutHorizontal{(frequencies.size() - 1) > 1};
    const auto canZoomOutVertical{
      (*std::ranges::max_element(std::views::values(frequencies)) / intervals.second) > 1
    };

    auto canZoom{true};

    // Check if we can zoom further
    switch (direction)
    {
    case Direction::BOTH:
    {
      // Check if we can zoom in both directions
      if (isZoomIn and (not canZoomInHorizontal and not canZoomInVertical))
      {
        canZoom = {false};
      }

      // Check if we can zoom out in both directions
      if (not isZoomIn and (not canZoomOutHorizontal and not canZoomOutVertical))
      {
        canZoom = {false};
      }
      break;
    }
    case Direction::HORIZONTAL:
    {
      // Check if we can zoom in in horizontal direction
      if (isZoomIn and not canZoomInHorizontal)
      {
        canZoom = {false};
      }

      // Check if we can zoom out in horizontal direction
      if (not isZoomIn and not canZoomOutHorizontal)
      {
        canZoom = {false};
      }
      break;
    }
    case Direction::VERTICAL:
    {
      // Check if we can zoom in in vertical direction
      if (isZoomIn and not canZoomInVertical)
      {
        canZoom = {false};
      }

      // Check if we can zoom out in vertical direction
      if (not isZoomIn and not canZoomOutVertical)
      {
        canZoom = {false};
      }
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

  [[nodiscard]] auto zoom(
    const fn::bln                       isZoomIn,
    const Direction                     zoomDirection,
    fn::pair<fn::u16f, fn::u16f>&       preferredSize,
    fn::pair<fn::u16f, fn::u16f>&       currentSize,
    const fn::vec<fn::i32f>&            values,
    const fn::pair<fn::i32f, fn::i32f>& bounds
  ) -> fn::opt<Math::Feed>
  {
    // Save old chart sizes
    const fn::pair<fn::u16f, fn::u16f> oldPreferredSize{preferredSize};
    const fn::pair<fn::u16f, fn::u16f> oldSize{currentSize};

    // Initialize new chart feed and size
    Math::Feed newFeed;

    // Zoom loop
    fn::bln zoomed{false};
    while (not zoomed)
    {
      // Increase preferred column count if direction allows it
      if (zoomDirection == Direction::BOTH or zoomDirection == Direction::HORIZONTAL)
      {
        preferredSize.first = {
          isZoomIn ? (preferredSize.first + fn::u16f{1}) : (preferredSize.first - fn::u16f{1})
        };
      }

      // Increase preferred row count if direction allows it
      if (zoomDirection == Direction::BOTH or zoomDirection == Direction::VERTICAL)
      {
        preferredSize.first = {
          isZoomIn ? (preferredSize.first + fn::u16f{1}) : (preferredSize.first - fn::u16f{1})
        };
      }

      if (preferredSize.first == 0 or preferredSize.second == 0)
      {
        preferredSize = {oldPreferredSize};
        currentSize   = {oldSize};

        // Return empty optional
        return {};
      }

      // Generate chart feed and size
      const auto [tempFeed, resultingChartSize]{Math::generateFeed(values, bounds, preferredSize)};

      // If no change occurred, zoom again
      if (currentSize == resultingChartSize)
      {
        continue;
      }

      // Check if zoomed
      if (resultingChartSize.first > preferredSize.first
          or resultingChartSize.second > preferredSize.second)
      {
        zoomed      = {true};
        newFeed     = {tempFeed};
        currentSize = {resultingChartSize};
      }
    }

    // Return new chart feed
    return newFeed;
  }
} // namespace Utility
