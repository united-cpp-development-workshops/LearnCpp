#include "pch.hpp"

#include "IO/io.hpp"

#include "Math/math.ipp"
#include "Utility/utility.hpp"

#include <Foundation/Support/narrow.ipp>
#include <Foundation/types.hpp>

#include <algorithm>
#include <cmath>
#include <concepts>
#include <cstring>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <ranges>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

namespace
{
  enum class Alignment : fn::u8f
  {
    LEFT,
    RIGHT
  };

  template <typename Type>
  requires std::same_as<Type, fn::i32f> or std::same_as<Type, fn::cdef>
          or std::same_as<Type, fn::cstr>
  auto printAligned(
    const Type&     input,
    const fn::cdef  paddingSymbol,
    const fn::u16f  width,
    const Alignment alignment
  ) -> std::ostream&
  {
    // Find the length of the input
    fn::u16f inputLength{};

    // Check if the input is a character
    if constexpr (std::same_as<Type, fn::cdef>) { inputLength = {1}; }
    else if constexpr (std::same_as<Type, fn::cstr>)
    {
      // Get the length of input
      inputLength = {fn::narrow_cast<fn::u16f>(std::strlen(input))};
    }
    else { inputLength = {Math::NUMBER_LENGTH(input)}; }

    // Calculate the padding
    const fn::u16f padding{width - inputLength};

    // Print padding lambda
    auto printPadding{
      [&paddingSymbol, &padding]() -> fn::none
      {
        for (fn::u16f position{}; position < padding; ++position)
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
    const std::map<fn::i32f, fn::u32f>&  frequencyMap,
    const fn::i32f                       lowerBound,
    const std::pair<fn::u32f, fn::u16f>& xAxisValues,
    const fn::bln                        lastRow,
    const fn::u32f                       y,
    const std::pair<fn::u32f, fn::u16f>& yAxisValues
  ) -> fn::none
  {
    // Print y-axis label and prefix
    printAligned(
      fn::narrow_cast<fn::i32f>(y), ' ', yAxisValues.second, Alignment::RIGHT
    ) << "-|";

    // If y-axis is zero, print the x-axis line
    if (lastRow)
    {
      // Traverse through x-axis with respect to interval
      for ([[maybe_unused]] const auto index :
           std::views::iota(fn::size{0}, frequencyMap.size()))
      {
        // Print the line
        printAligned('|', '-', xAxisValues.second, Alignment::RIGHT);
      }

      // Print x-axis name
      std::cout << "-> " << IO::X_AXIS_NAME;

      // End line row
      std::cout << '\n';

      // Print y-axis label and prefix
      printAligned(
        lowerBound - fn::narrow_cast<fn::i32f>(xAxisValues.first),
        ' ',
        yAxisValues.second + IO::LEFT_MARGIN,
        Alignment::RIGHT
      );

      // Print x-axis labels
      for (const auto& [x, ignored] : frequencyMap)
      {
        // Value is not used
        std::ignore = ignored;

        // print the line
        printAligned(x, ' ', xAxisValues.second, Alignment::RIGHT);
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
        [&y, &yAxisValues](const auto& pair) noexcept -> fn::bln
        {
          return (pair.second >= y) and (pair.second < (y + yAxisValues.first));
        }
      )};

      // Initialize the input between columns to space
      fn::cdef symbolBetweenColumns{' '};

      // Determine if we need to print horizontal grid
      if (iteratorToNextColumnNeedingGrid != frequencyMap.end())
      {
        symbolBetweenColumns = '.';
      }

      // Fill or leave empty current cell based on y value
      if (frequency >= y)
      {
        printAligned(
          '#', symbolBetweenColumns, xAxisValues.second, Alignment::RIGHT
        );
      }
      else
      {
        printAligned(
          '.', symbolBetweenColumns, xAxisValues.second, Alignment::RIGHT
        );
      }
    }
  }

  auto zoomOptionHandler(const std::string_view& option, const fn::bln zoomIn)
    -> std::optional<IO::Option>
  {
    // Using declarations
    using enum IO::Option;

    // If directional zoom is requested
    if (option.length() == IO::DIRECTIONAL_ZOOM_INPUT_LENGTH)
    {
      // Check direction of the zoom
      if (option.find('h') != std::string::npos
          or option.find('H') != std::string::npos)
      {
        return zoomIn ? ZOOM_IN_HORIZONTAL : ZOOM_OUT_HORIZONTAL;
      }

      // Check direction of the zoom
      if (option.find('v') != std::string::npos
          or option.find('V') != std::string::npos)
      {
        return zoomIn ? ZOOM_IN_VERTICAL : ZOOM_OUT_VERTICAL;
      }

      // Wrong input
      std::cout
        << " [X]: Enter 'h' or 'v' for directional zoom, please try again: ";

      // Return empty optional
      return {};
    }

    // If non-directional zoom is requested, the length must be 1
    if (option.length() == 1) { return zoomIn ? ZOOM_IN : ZOOM_OUT; }

    // Wrong input
    std::cout
      << " [X]: Invalid length input for zoom option, please try again: ";

    // Return empty optional
    return {};
  }

  auto resetInputBuffer() -> fn::none
  {
    // Clear input buffer and error flags
    std::cin.clear();
    if (std::cin.rdbuf()->in_avail() > 0)
    {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
} // namespace

namespace IO
{
  auto printWelcome() -> fn::none
  {
    std::cout << " -------------------------< RANDOM CHARTS "
                 ">--------------------------\n";
    std::cout << '\n';
    std::cout << " - Visualize your custom configured random distributions in "
                 "a chart.\n";
    std::cout << " - Get the resulting distribution's statistics in detail.\n";
  }

  auto printInformative() -> fn::none
  {
    std::cout << '\n';
    std::cout
      << " --------------------------------------------------------------"
         "------\n";
    std::cout << '\n';
    std::cout << " CONFIGURATIONS\n";
    std::cout << '\n';
    std::cout << " - You will be asked to input:\n";
    std::cout
      << "   - Sample size: The number of random values to be sampled,\n";
    std::cout << "   - Lower bound: Minimum random value a sample can have,\n";
    std::cout << "   - Upper bound: Maximum random value a sample can have,\n";
    std::cout << "   - Chart sizes: Chart's preferred dimensions.\n";
    std::cout << '\n';
  }

  auto getSamplesCountInput() -> fn::i32f
  {
    resetInputBuffer();

    std::cout << " [i]: Please input the 'Sample size' parameter: ";

    fn::i32f sampleSize{};

    // Loop until valid input
    while (true)
    {
      resetInputBuffer();

      // Assign inputs
      std::cin >> sampleSize;

      // Check if inputs are larger than 0
      if (sampleSize > 0) { break; }

      // Wrong input
      std::cout
        << " [X]: 'Sample size' must be larger than 0, please try again: ";
    }

    return sampleSize;
  }

  auto getLowerBoundInput() -> fn::i32f
  {
    resetInputBuffer();

    std::cout << " [i]: Please input the 'Lower bound' parameter: ";

    fn::i32f lowerBound{};
    std::cin >> lowerBound;

    return lowerBound;
  }

  auto getUpperBoundInput() -> fn::i32f
  {
    resetInputBuffer();

    std::cout << " [i]: Please input the 'Upper bound' parameter: ";

    fn::i32f upperBound{};
    std::cin >> upperBound;

    return upperBound;
  }

  auto getPreferredChartSizeInput() -> std::pair<fn::u16f, fn::u16f>
  {
    resetInputBuffer();

    std::cout
      << " [i]: Please input the 'Chart sizes' parameter (width height): ";

    fn::u16f width{};
    fn::u16f height{};

    // Loop until valid input
    while (true)
    {
      resetInputBuffer();

      // Assign inputs
      std::cin >> width >> height;

      // Check if inputs are larger than 0
      if (width > fn::u16f{0} and height > fn::u16f{0}) { break; }

      // Wrong input
      std::cout
        << " [X]: Width and Height must be larger than 0, please try again: ";
    }

    return {width, height};
  }

  auto printResultsHeader() -> fn::none
  {
    std::cout << '\n';
    std::cout
      << " --------------------------------------------------------------"
         "------\n";
    std::cout << '\n';
    std::cout << " RESULTS\n";
  }

  auto printChart(const Math::ChartFeed& chartFeed) -> fn::none
  {
    std::cout << '\n';
    std::cout << " - Chart:\n";
    std::cout << '\n';

    // Find label width for x-axis
    const fn::u16f xAxisLabelWidth{
      std::ranges::max(
        chartFeed.frequencyMap | std::views::keys
        | std::views::transform(Math::NUMBER_LENGTH)
      )
      + fn::u16f{1}
    };

    // Find the length of first x label
    const auto xFirstLabelLength{Math::NUMBER_LENGTH(
      chartFeed.lowerBound - fn::narrow_cast<fn::i32f>(chartFeed.xAxisInterval)
    )};

    // Find the length of last y label
    const auto yLastLabelLength{
      Math::NUMBER_LENGTH(fn::narrow_cast<fn::i32f>(chartFeed.maxFrequency))
    };

    // Find label width for y-axis
    fn::u16f yAxisLabelWidth{};

    // Compare effective width of x and y label widths
    if ((xFirstLabelLength - fn::u16f{LEFT_MARGIN}) > yLastLabelLength)
    {
      yAxisLabelWidth = {
        Math::NUMBER_LENGTH(chartFeed.lowerBound) - fn::u16f{1}
      };
    }
    else
    {
      yAxisLabelWidth = {
        Math::NUMBER_LENGTH(fn::narrow_cast<fn::i32f>(chartFeed.maxFrequency))
        + fn::u16f{1}
      };
    }

    // Print y-axis name
    printAligned(
      Y_AXIS_NAME,
      ' ',
      yAxisLabelWidth + fn::narrow_cast<fn::u16f>(std::strlen(Y_AXIS_NAME))
        + fn::u16f{1},
      Alignment::RIGHT
    );
    std::cout << '\n';

    // Print y-axis end
    printAligned(
      '^', ' ', yAxisLabelWidth + fn::u16f{LEFT_MARGIN}, Alignment::RIGHT
    );
    std::cout << '\n';

    // Print row by row
    fn::bln  lastRow{false};
    fn::u32f y{chartFeed.maxFrequency};
    while (not lastRow)
    {
      // Check if we are in last row
      if ((fn::narrow_cast<fn::i32f>(y)
           - fn::narrow_cast<fn::i32f>(chartFeed.yAxisInterval))
          < 0)
      {
        lastRow = {true};
      }

      // Print row
      printChartRow(
        chartFeed.frequencyMap,
        chartFeed.lowerBound,
        {chartFeed.xAxisInterval, xAxisLabelWidth},
        lastRow,
        y,
        {chartFeed.yAxisInterval, yAxisLabelWidth}
      );

      // End the row
      std::cout << '\n';

      // Decrement y
      y -= chartFeed.yAxisInterval;
    }
  }

  auto printStatistics(const std::vector<fn::i32f>& values) -> fn::none
  {
    std::cout << '\n';
    std::cout << " - Statistics:\n";

    // Calculate the sum of the values
    const fn::i32f sum{std::accumulate(values.begin(), values.end(), 0)};

    // Calculate the mean of the values
    const fn::f64 mean{sum / fn::narrow_cast<fn::f64>(values.size())};

    // Calculate the variance of the values
    const fn::f64 variance{
      std::accumulate(
        values.begin(),
        values.end(),
        0.0,
        [&mean](const fn::f64 accumulator, const fn::i32f value) noexcept
        -> fn::f64
        {
          return accumulator + std::pow(value - mean, SQUARE);
        }
      )
      / fn::narrow_cast<fn::f64>(values.size())
    };

    // Calculate the standard deviation of the values
    const fn::f64 standardDeviation{std::sqrt(variance)};

    // Calculate the minimum and maximum values
    const auto [min, max]{std::ranges::minmax_element(values)};

    // Print the statistics
    std::cout << "   - Sum: " << sum << '\n';
    std::cout << "   - Mean: " << mean << '\n';
    std::cout << "   - Variance: " << variance << '\n';
    std::cout << "   - Standard deviation: " << standardDeviation << '\n';
    std::cout << "   - Minimum: " << *min << '\n';
    std::cout << "   - Maximum: " << *max << '\n';
  }

  auto printOptionsHeader() -> fn::none
  {
    std::cout << '\n';
    std::cout
      << " --------------------------------------------------------------"
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

  auto getOptionInput() -> Option
  {
    resetInputBuffer();

    std::cout << " [i]: Please input your option: ";

    // Loop until valid input
    while (true)
    {
      resetInputBuffer();

      // Get the option input
      std::string option{};
      std::cin >> option;

      // Check option input
      if (option.find('+') != std::string::npos)
      {
        // Check if zoom in option is valid
        if (const auto zoomOutOpt{zoomOptionHandler(option, true)};
            zoomOutOpt.has_value())
        {
          return zoomOutOpt.value();
        }
        continue;
      }

      // Check option input
      if (option.find('-') != std::string::npos)
      {
        // Check if zoom in option is valid
        if (const auto zoomOutOpt{zoomOptionHandler(option, false)};
            zoomOutOpt.has_value())
        {
          return zoomOutOpt.value();
        }
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

  auto printNoFurtherZoom(const Utility::Direction direction) -> fn::none
  {
    // Using declarations
    using enum Utility::Direction;

    std::cout << " [X]: No further zoom ";
    switch (direction)
    {
    case BOTH:
    {
      std::cout << "in any direction is possible.\n";
      break;
    }
    case HORIZONTAL:
    {
      std::cout << "in horizontal direction is possible.\n";
      break;
    }
    case VERTICAL:
    {
      std::cout << "in vertical direction is possible.\n";
      break;
    }
    }
  }
} // namespace IO
