#include "IO/io.hpp"

#include "Math/math.hpp"

#include <algorithm>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <GSL/narrow>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <ranges>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace
{
  enum class Alignment : std::uint8_t
  {
    LEFT,
    RIGHT
  };

  template <typename T>
  requires std::same_as<T, int> or std::same_as<T, char>
          or std::same_as<T, const char*>
  auto printAligned(
    const T& input, char paddingSymbol, int width, Alignment alignment
  ) -> std::ostream&
  {
    // Find the length of the input
    int inputLength{};

    // Check if the input is a character
    if constexpr (std::same_as<T, char>) { inputLength = {1}; }
    else if constexpr (std::same_as<T, const char*>)
    {
      // Get the length of input
      inputLength = {gsl::narrow<int>(std::strlen(input))};
    }
    else { inputLength = {Math::NUMBER_LENGTH(input)}; }

    // Calculate the padding
    const int padding{width - inputLength};

    // Print padding lambda
    auto printPadding{
      [&paddingSymbol, &padding]() -> void
      {
        for (int position{0}; position < padding; position++)
        {
          std::cout << paddingSymbol;
        }
      }
    };

    // Print input based on alignment
    switch (alignment)
    {
    case Alignment::LEFT:
      {
        std::cout << input;
        printPadding();
        break;
      }
    case Alignment::RIGHT:
      {
        printPadding();
        std::cout << input;
        break;
      }
    }

    // Return output stream
    return std::cout;
  }

  auto printChartRow(
    const std::map<int, int>& frequencyMap,
    int                       lowerBound,
    int                       xAxisInterval,
    int                       xAxisLabelWidth,
    bool                      lastRow,
    int                       y,
    int                       yAxisInterval,
    int                       yAxisLabelWidth
  ) -> void
  {
    // Print y-axis label and prefix
    printAligned(y, ' ', yAxisLabelWidth, Alignment::RIGHT) << "-|";

    // If y-axis is zero, print the x-axis line
    if (lastRow)
    {
      // Traverse through x-axis with respect to interval
      for (const auto& ignored : frequencyMap)
      {
        // Pair is not used
        std::ignore = ignored;

        // print the line
        printAligned('|', '-', xAxisLabelWidth, Alignment::RIGHT);
      }

      // Print x-axis name
      std::cout << "-> " << IO::X_AXIS_NAME;

      // End line row
      std::cout << '\n';

      // Print y-axis label and prefix
      printAligned(
        lowerBound - xAxisInterval, ' ', yAxisLabelWidth + 2, Alignment::RIGHT
      );

      // Print x-axis labels
      for (const auto& [x, ignored] : frequencyMap)
      {
        // Value is not used
        std::ignore = ignored;

        // print the line
        printAligned(x, ' ', xAxisLabelWidth, Alignment::RIGHT);
      }

      // Exit the function as we've handled the zero y-axis case
      return;
    }

    // Traverse through x-axis with respect to interval
    for (const auto& [x, frequency] : frequencyMap)
    {
      // Determine if we need to print horizontal grid
      const auto& iteratorToNextColumnNeedingGrid{std::ranges::find_if(
        frequencyMap.find(x),
        frequencyMap.end(),
        [&](const auto& pair) noexcept -> bool
        {
          return pair.second >= y and pair.second < y + yAxisInterval;
        }
      )};

      // Initialize the input between columns to space
      char symbolBetweenColumns{' '};

      // Determine if we need to print horizontal grid
      if (iteratorToNextColumnNeedingGrid != frequencyMap.end())
      {
        symbolBetweenColumns = '.';
      }

      // Fill or leave empty current cell based on y value
      if (frequency >= y)
      {
        printAligned(
          '#', symbolBetweenColumns, xAxisLabelWidth, Alignment::RIGHT
        );
      }
      else
      {
        printAligned(
          '.', symbolBetweenColumns, xAxisLabelWidth, Alignment::RIGHT
        );
      }
    }
  }

  auto zoomOptionHandler(const std::string& option, bool zoomIn)
    -> std::optional<IO::Option>
  {
    // If directional zoom is requested, the length must be 2
    if (option.length() == 2)
    {
      // Check direction of the zoom
      if (option.find('h') != std::string::npos
          or option.find('H') != std::string::npos)
      {
        return zoomIn ? IO::Option::ZOOM_IN_HORIZONTAL
                      : IO::Option::ZOOM_OUT_HORIZONTAL;
      }

      // Check direction of the zoom
      if (option.find('v') != std::string::npos
          or option.find('V') != std::string::npos)
      {
        return zoomIn ? IO::Option::ZOOM_IN_VERTICAL
                      : IO::Option::ZOOM_OUT_VERTICAL;
      }

      // Wrong input
      std::cout
        << " [X]: Enter 'h' or 'v' for directional zoom, please try again: ";
      return {};
    }

    // If non-directional zoom is requested, the length must be 1
    if (option.length() == 1)
    {
      return zoomIn ? IO::Option::ZOOM_IN : IO::Option::ZOOM_OUT;
    }

    // Wrong input
    std::cout
      << " [X]: Invalid length input for zoom option, please try again: ";
    return {};
  }

} // namespace

auto IO::printWelcome() -> void
{
  std::cout << " -------------------------< RANDOM CHARTS "
               ">--------------------------\n";
  std::cout << '\n';
  std::cout
    << " - Visualize your custom configured random distributions in a chart.\n";
  std::cout << " - Get the resulting distribution's statistics in detail.\n";
}

auto IO::printInformative() -> void
{
  std::cout << '\n';
  std::cout << " --------------------------------------------------------------"
               "------\n";
  std::cout << '\n';
  std::cout << " CONFIGURATIONS\n";
  std::cout << '\n';
  std::cout << " - You will be asked to input:\n";
  std::cout << "   - Sample size: The number of random values to be sampled,\n";
  std::cout << "   - Lower bound: Minimum random value a sample can have,\n";
  std::cout << "   - Upper bound: Maximum random value a sample can have,\n";
  std::cout << "   - Chart sizes: Chart's preferred dimensions.\n";
  std::cout << '\n';
}

auto IO::getSamplesCountInput() -> std::size_t
{
  std::cout << " [i]: Please input the 'Sample size' parameter: ";

  std::size_t sampleSize{};
  std::cin >> sampleSize;

  return sampleSize;
}

auto IO::getLowerBoundInput() -> int
{
  std::cout << " [i]: Please input the 'Lower bound' parameter: ";

  int lowerBound{};
  std::cin >> lowerBound;

  return lowerBound;
}

auto IO::getUpperBoundInput() -> int
{
  std::cout << " [i]: Please input the 'Upper bound' parameter: ";

  int upperBound{};
  std::cin >> upperBound;

  return upperBound;
}

auto IO::getChartSizesInput() -> std::pair<int, int>
{
  std::cout
    << " [i]: Please input the 'Chart sizes' parameter (width height): ";

  int width{};
  int height{};
  std::cin >> width >> height;

  return {width, height};
}

auto IO::printResultsHeader() -> void
{
  std::cout << '\n';
  std::cout << " --------------------------------------------------------------"
               "------\n";
  std::cout << '\n';
  std::cout << " RESULTS\n";
}

auto IO::printChart(const Math::ChartFeed& chartFeed) -> void
{
  std::cout << '\n';
  std::cout << " - Chart:\n";
  std::cout << '\n';

  // Find label width for x-axis
  const int xAxisLabelWidth{
    std::ranges::max(
      chartFeed.frequencyMap | std::views::keys
      | std::views::transform(Math::NUMBER_LENGTH)
    )
    + 1
  };

  // Find label width for y-axis
  int yAxisLabelWidth{};

  // Determine if lower bound or max frequency is longer in length
  if (Math::NUMBER_LENGTH(chartFeed.lowerBound - chartFeed.xAxisInterval) - 2
      > Math::NUMBER_LENGTH(chartFeed.maxFrequency))
  {
    yAxisLabelWidth = {Math::NUMBER_LENGTH(chartFeed.lowerBound) - 1};
  }
  else { yAxisLabelWidth = {Math::NUMBER_LENGTH(chartFeed.maxFrequency) + 1}; }

  // Print y-axis name
  printAligned(
    Y_AXIS_NAME,
    ' ',
    yAxisLabelWidth + gsl::narrow<int>(std::strlen(Y_AXIS_NAME)) + 1,
    Alignment::RIGHT
  );
  std::cout << '\n';

  // Print y-axis end
  printAligned('^', ' ', yAxisLabelWidth + 2, Alignment::RIGHT);
  std::cout << '\n';

  // Print row by row
  bool lastRow{false};
  for (int y{chartFeed.maxFrequency}; y >= 0; y -= chartFeed.yAxisInterval)
  {
    // Check if we are in last row
    if (y - chartFeed.yAxisInterval < 0) { lastRow = {true}; }

    // Print row
    printChartRow(
      chartFeed.frequencyMap,
      chartFeed.lowerBound,
      chartFeed.xAxisInterval,
      xAxisLabelWidth,
      lastRow,
      y,
      chartFeed.yAxisInterval,
      yAxisLabelWidth
    );

    // End the row
    std::cout << '\n';
  }
}

auto IO::printStatistics(const std::vector<int>& values) -> void
{
  std::cout << '\n';
  std::cout << " - Statistics:\n";

  // Calculate the sum of the values
  const int sum{std::accumulate(values.begin(), values.end(), 0)};

  // Calculate the mean of the values
  const double mean{sum / gsl::narrow<double>(values.size())};

  // Calculate the variance of the values
  const double variance{
    std::accumulate(
      values.begin(),
      values.end(),
      0.0,
      [mean](double accumulator, int value) noexcept -> double
      {
        return accumulator + std::pow(value - mean, 2);
      }
    )
    / gsl::narrow<double>(values.size())
  };

  // Calculate the standard deviation of the values
  const double standardDeviation{std::sqrt(variance)};

  // Calculate the minimum and maximum values
  const auto [min, max]{
    std::ranges::minmax_element(values.begin(), values.end())
  };

  // Print the statistics
  std::cout << "   - Sum: " << sum << '\n';
  std::cout << "   - Mean: " << mean << '\n';
  std::cout << "   - Variance: " << variance << '\n';
  std::cout << "   - Standard deviation: " << standardDeviation << '\n';
  std::cout << "   - Minimum: " << *min << '\n';
  std::cout << "   - Maximum: " << *max << '\n';
}

auto IO::printOptionsHeader() -> void
{
  std::cout << '\n';
  std::cout << " --------------------------------------------------------------"
               "------\n";
  std::cout << '\n';
  std::cout << " OPTIONS\n";
  std::cout << '\n';
  std::cout << " - You may choose from the following options:\n";
  std::cout << "   - Zoom in   (+): Zoom in to chart,\n";
  std::cout << "     - Add 'h' or 'v' for directional zoom, Ex: '+h'\n";
  std::cout << "   - Zoom out  (-): Zoom out from chart,\n";
  std::cout << "     - Add 'h' or 'v' for directional zoom, Ex: '-v'\n";
  std::cout << "   - New chart (n): Generate a new distribution,\n";
  std::cout << "   - Quit app  (q): Quit the application.\n";
  std::cout << '\n';
}

auto IO::getOptionInput() -> Option
{
  std::cout << " [i]: Please input your option: ";

  // Loop until valid input
  while (true)
  {
    // Clear input buffer and error flags
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Get the option input
    std::string option{};
    std::cin >> option;

    // Check option input
    if (option.find('+') != std::string::npos)
    {
      const std::optional<Option> zoomInOpt{zoomOptionHandler(option, true)};

      // Check if zoom in option is valid
      if (zoomInOpt.has_value()) { return zoomInOpt.value(); }
      continue;
    }

    // Check option input
    if (option.find('-') != std::string::npos)
    {
      const std::optional<Option> zoomOutOpt{zoomOptionHandler(option, false)};

      // Check if zoom in option is valid
      if (zoomOutOpt.has_value()) { return zoomOutOpt.value(); }
      continue;
    }

    // Check option input
    if (option == "n" or option == "N") { return Option::NEW_CHART; }

    // Check option input
    if (option == "q" or option == "Q") { return Option::QUIT; }

    // Wrong input
    std::cout << " [X]: Invalid option input, please try again: ";
  }
}
