#include "IO/io.hpp"
#include "Math/math.hpp"
#include "Random/random.hpp"
#include "Utility/utility.hpp"

#include <cstdlib>
#include <tuple>
#include <utility>
#include <vector>

namespace
{
  auto optionsHandler(
    std::pair<int, int>&    chartSize,
    const std::vector<int>& values,
    int                     lowerBound,
    int                     upperBound
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

          // Zoom in
          const auto [newChartFeed, newChartSize]{Utility::chartZoom(
            true, direction, chartSize, values, lowerBound, upperBound
          )};

          // Update chart size
          chartSize = {newChartSize};

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

          // Zoom in
          const auto [newChartFeed, newChartSize]{Utility::chartZoom(
            false, direction, chartSize, values, lowerBound, upperBound
          )};

          // Update chart size
          chartSize = {newChartSize};

          // Print chart again
          IO::printChart(newChartFeed);
          break;
        }
      case IO::Option::NEW_CHART:
        {
          return false;
        }
      case IO::Option::QUIT:
        {
          return true;
        }
      }
    }
  }
} // namespace

auto main() noexcept -> int
try
{
  // Print introduction
  IO::printWelcome();

  // Main loop
  bool running{true};
  while (running)
  {
    // Print configuration rules
    IO::printInformative();

    // Get user inputs
    const std::size_t   samplesCount{IO::getSamplesCountInput()};
    const int           lowerBound{IO::getLowerBoundInput()};
    const int           upperBound{IO::getUpperBoundInput()};
    std::pair<int, int> chartSize{IO::getChartSizesInput()};

    // Distribute randomly
    auto values{Random::distribute(samplesCount, lowerBound, upperBound)};

    // Print results
    IO::printResultsHeader();
    const auto [chartFeed, ignored]{
      Math::generateChartFeed(values, lowerBound, upperBound, chartSize)
    };

    // Ignore chartSize
    std::ignore = ignored;

    // Print chart
    IO::printChart(chartFeed);

    // Print Statistics
    IO::printStatistics(values);

    // Options
    running = {optionsHandler(chartSize, values, lowerBound, upperBound)};
  }

  // Successful termination
  return EXIT_SUCCESS;
}
catch (...)
{
  // Erroneous termination
  return EXIT_FAILURE;
}
