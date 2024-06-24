#include "IO/io.hpp"
#include "Math/math.hpp"
#include "Random/random.hpp"
#include "Utility/utility.hpp"

#include <cstdint>
#include <cstdlib>
#include <map>
#include <tuple>
#include <utility>

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
    const std::size_t samplesCount{IO::getSamplesCountInput()};
    const int         lowerBound{IO::getLowerBoundInput()};
    const int         upperBound{IO::getUpperBoundInput()};
    std::pair<std::uint16_t, std::uint16_t> preferredChartSize{
      IO::getPreferredChartSizeInput()
    };

    // Distribute randomly
    auto values{Random::distribute(samplesCount, lowerBound, upperBound)};

    // Print results
    IO::printResultsHeader();
    auto [chartFeed, resultingChartSize]{Math::generateChartFeed(
      values, lowerBound, upperBound, preferredChartSize
    )};

    // Remember intervals and frequencyMap to determine if we can zoom further
    int                xAxisInterval{chartFeed.xAxisInterval};
    int                yAxisInterval{chartFeed.yAxisInterval};
    std::map<int, int> frequencyMap{chartFeed.frequencyMap};

    // Print chart
    IO::printChart(chartFeed);

    // Print Statistics
    IO::printStatistics(values);

    // Options
    running = {Utility::optionsHandler(
      preferredChartSize,
      resultingChartSize,
      xAxisInterval,
      yAxisInterval,
      frequencyMap,
      values,
      lowerBound,
      upperBound
    )};
  }

  // Successful termination
  return EXIT_SUCCESS;
}
catch (...)
{
  // Erroneous termination
  return EXIT_FAILURE;
}
