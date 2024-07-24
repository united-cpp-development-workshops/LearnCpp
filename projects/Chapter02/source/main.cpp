#include "pch.hpp"

#include "IO/io.hpp"
#include "Math/math.ipp"
#include "Random/random.hpp"
#include "Utility/utility.hpp"

#include <Foundation/constants.hpp>
#include <Foundation/types.hpp>
#include <Foundation/Utility/log.ipp>
#include <Foundation/Utility/what.ipp>

#include <exception>
#include <map>
#include <tuple>
#include <utility>

auto main() noexcept -> fn::idef
try
{
  // Print introduction
  IO::printWelcome();

  // Main loop
  fn::bln running{true};
  while (running)
  {
    // Print configuration rules
    IO::printInformative();

    // Get user inputs
    const fn::i32f                samplesCount{IO::getSamplesCountInput()};
    const fn::i32f                lowerBound{IO::getLowerBoundInput()};
    const fn::i32f                upperBound{IO::getUpperBoundInput()};
    std::pair<fn::u16f, fn::u16f> preferredChartSize{
      IO::getPreferredChartSizeInput()
    };

    // Distribute randomly
    auto values{Random::distribute(samplesCount, {lowerBound, upperBound})};

    // Print results
    IO::printResultsHeader();
    auto [chartFeed, resultingChartSize]{Math::generateChartFeed(
      values, {lowerBound, upperBound}, preferredChartSize
    )};

    // Remember intervals and frequencyMap to determine if we can zoom further
    fn::u32f                     xAxisInterval{chartFeed.xAxisInterval};
    fn::u32f                     yAxisInterval{chartFeed.yAxisInterval};
    std::map<fn::i32f, fn::u32f> frequencyMap{chartFeed.frequencyMap};

    // Print chart
    IO::printChart(chartFeed);

    // Print Statistics
    IO::printStatistics(values);

    // Options
    running = {Utility::optionsHandler(
      preferredChartSize,
      resultingChartSize,
      frequencyMap,
      {xAxisInterval, yAxisInterval},
      values,
      {lowerBound, upperBound}
    )};
  }

  // Return success
  return fn::EXIT_SUCCESS_CODE;
}
catch (const std::exception& exception)
{
  // Log exception
  fn::elog(fn::WHAT(exception));

  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
catch (...)
{
  // Log unknown exception
  fn::elog(fn::UNKNOWN_EXCEPTION);

  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
