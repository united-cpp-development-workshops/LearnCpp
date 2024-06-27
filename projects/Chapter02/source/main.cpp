#include "pch.hpp"

#include "IO/io.hpp"
#include "Math/math.hpp"
#include "Random/random.hpp"
#include "types.hpp"
#include "Utility/utility.hpp"
#include "wrappers.hpp"

#include <map>
#include <tuple>
#include <utility>

auto main() noexcept -> idef
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
    const size            samplesCount{IO::getSamplesCountInput()};
    const i32f            lowerBound{IO::getLowerBoundInput()};
    const i32f            upperBound{IO::getUpperBoundInput()};
    std::pair<u16f, u16f> preferredChartSize{IO::getPreferredChartSizeInput()};

    // Distribute randomly
    auto values{Random::distribute(samplesCount, lowerBound, upperBound)};

    // Print results
    IO::printResultsHeader();
    auto [chartFeed, resultingChartSize]{Math::generateChartFeed(
      values, lowerBound, upperBound, preferredChartSize
    )};

    // Remember intervals and frequencyMap to determine if we can zoom further
    u32f                 xAxisInterval{chartFeed.xAxisInterval};
    u32f                 yAxisInterval{chartFeed.yAxisInterval};
    std::map<i32f, u32f> frequencyMap{chartFeed.frequencyMap};

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

  // Return success
  return TERMINATE_SUCCESS;
}
catch (...)
{
  // Return failure
  return TERMINATE_FAILURE;
}
