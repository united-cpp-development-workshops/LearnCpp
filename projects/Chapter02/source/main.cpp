#include "pch.hpp"

#include "IO/io.hpp"
#include "Math/math.ipp"
#include "Random/random.hpp"
#include "Utility/utility.hpp"

#include <Foundation/constants.hpp>
#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>
#include <Foundation/Utility/log.ipp>
#include <Foundation/Utility/what.ipp>

#include <exception>

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
    const fn::i32f               samplesCount{IO::getSamplesCountInput()};
    const fn::i32f               lowerBound{IO::getLowerBoundInput()};
    const fn::i32f               upperBound{IO::getUpperBoundInput()};
    fn::pair<fn::u16f, fn::u16f> preferredSize{IO::getSizeInput()};

    // Distribute randomly
    auto values{Random::distribute(samplesCount, {lowerBound, upperBound})};

    // Print results
    IO::printResultsHeader();
    auto [feed, resultingSize]{Math::generateFeed(values, {lowerBound, upperBound}, preferredSize)};

    // Remember intervals and frequencies to determine if we can zoom further
    fn::u32f                    xAxisInterval{feed.xAxisInterval};
    fn::u32f                    yAxisInterval{feed.yAxisInterval};
    fn::map<fn::i32f, fn::u32f> frequencies{feed.frequencies};

    // Print chart
    IO::printChart(feed);

    // Print Statistics
    IO::printStatistics(values);

    // Options
    running = {Utility::optionsHandler(
      preferredSize,
      resultingSize,
      frequencies,
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
  fn::elog(fn::what(exception));

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
