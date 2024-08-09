#include "pch.hpp"

#include "IO/_internal/table.hpp"

#include "IO/_internal/prints.hpp"
#include "IO/_internal/types.hpp"
#include "IO/io.hpp"

#include <Foundation/types.hpp>

#include <iostream>

namespace IO::_internal
{
  auto printTypeTable(const Option option) -> fn::none
  {
    // Get type information
    const auto typeRow{getTypeRow(option)};

    // Get column widths
    const auto firstColumnWidth{std::max(
      {fn::str{TYPE_NAME}.length(),
       fn::str{OPTIONAL}.length(),
       fn::str{HEADER}.length(),
       fn::str{STANDARD_SIZE}.length(),
       fn::str{PLATFORM_SIZE}.length(),
       fn::str{SIGNEDNESS}.length(),
       fn::str{MIN_VALUE}.length(),
       fn::str{MAX_VALUE}.length(),
       fn::str{PRECISION}.length(),
       fn::str{SUFFIX}.length()}
    )};
    const auto secondColumnWidth{std::max(
      {typeRow.typeName.length(),
       typeRow.isOptional.length(),
       typeRow.header.length(),
       typeRow.standardSize.length(),
       typeRow.platformSize.length(),
       typeRow.signedness.length(),
       typeRow.minValue.length(),
       typeRow.maxValue.length(),
       typeRow.precision.length(),
       typeRow.literalSuffix.length()}
    )};

    // Print title
    std::cout << "   METRICS: '" << typeRow.typeName << "'\n\n";

    // Print table
    std::cout << "     +-" << fn::str(firstColumnWidth, '-') << "-+-"
              << fn::str(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(TYPE_NAME, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.typeName, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << fn::str(firstColumnWidth, '-') << "-+-"
              << fn::str(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(OPTIONAL, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.isOptional, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << fn::str(firstColumnWidth, '-') << "-+-"
              << fn::str(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(HEADER, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.header, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << fn::str(firstColumnWidth, '-') << "-+-"
              << fn::str(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(STANDARD_SIZE, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.standardSize, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << fn::str(firstColumnWidth, '-') << "-+-"
              << fn::str(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(PLATFORM_SIZE, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.platformSize, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << fn::str(firstColumnWidth, '-') << "-+-"
              << fn::str(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(SIGNEDNESS, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.signedness, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << fn::str(firstColumnWidth, '-') << "-+-"
              << fn::str(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(MIN_VALUE, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.minValue, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << fn::str(firstColumnWidth, '-') << "-+-"
              << fn::str(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(MAX_VALUE, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.maxValue, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << fn::str(firstColumnWidth, '-') << "-+-"
              << fn::str(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(PRECISION, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.precision, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << fn::str(firstColumnWidth, '-') << "-+-"
              << fn::str(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(SUFFIX, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.literalSuffix, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << fn::str(firstColumnWidth, '-') << "-+-"
              << fn::str(secondColumnWidth, '-') << "-+\n";
  }

  auto printTypeTable(const std::set<Option>& options) -> fn::none
  {
    // Max column lengths
    auto maxTypeNameColLen{fn::str{TYPE_NAME}.length()};
    auto maxIsOptionalColLen{fn::str{OPTIONAL}.length()};
    auto maxHeaderColLen{fn::str{HEADER}.length()};
    auto maxStandardSizeColLen{fn::str{STANDARD_SIZE}.length()};
    auto maxPlatformSizeColLen{fn::str{PLATFORM_SIZE}.length()};
    auto maxSignednessColLen{fn::str{SIGNEDNESS}.length()};
    auto maxMinValueColLen{fn::str{MIN_VALUE}.length()};
    auto maxMaxValueColLen{fn::str{MAX_VALUE}.length()};
    auto maxPrecisionColLen{fn::str{PRECISION}.length()};
    auto maxSuffixColLen{fn::str{SUFFIX}.length()};

    for (auto& option : options)
    {
      // Get type information
      const auto typeRow{getTypeRow(option)};

      // Get column widths
      maxTypeNameColLen     = {std::max(maxTypeNameColLen, typeRow.typeName.length())};
      maxIsOptionalColLen   = {std::max(maxIsOptionalColLen, typeRow.isOptional.length())};
      maxHeaderColLen       = {std::max(maxHeaderColLen, typeRow.header.length())};
      maxStandardSizeColLen = {std::max(maxStandardSizeColLen, typeRow.standardSize.length())};
      maxPlatformSizeColLen = {std::max(maxPlatformSizeColLen, typeRow.platformSize.length())};
      maxSignednessColLen   = {std::max(maxSignednessColLen, typeRow.signedness.length())};
      maxMinValueColLen     = {std::max(maxMinValueColLen, typeRow.minValue.length())};
      maxMaxValueColLen     = {std::max(maxMaxValueColLen, typeRow.maxValue.length())};
      maxPrecisionColLen    = {std::max(maxPrecisionColLen, typeRow.precision.length())};
      maxSuffixColLen       = {std::max(maxSuffixColLen, typeRow.literalSuffix.length())};
    }

    // Print title
    std::cout << "   METRICS:";
    const auto optionsEndIt{options.end()};
    for (auto it{options.begin()}; it != optionsEndIt; ++it)
    {
      const auto& typeRow{getTypeRow(*it)};
      if (it == options.begin())
      {
        std::cout << " '" << typeRow.typeName << "'";
      }
      else
      {
        std::cout << ", '" << typeRow.typeName << "'";
      }
    }
    std::cout << "\n\n";

    // Print table header
    std::cout
      << "     +-" << fn::str(maxTypeNameColLen, '-') << "-+-" << fn::str(maxIsOptionalColLen, '-')
      << "-+-" << fn::str(maxHeaderColLen, '-') << "-+-" << fn::str(maxStandardSizeColLen, '-')
      << "-+-" << fn::str(maxPlatformSizeColLen, '-') << "-+-" << fn::str(maxSignednessColLen, '-')
      << "-+-" << fn::str(maxMinValueColLen, '-') << "-+-" << fn::str(maxMaxValueColLen, '-')
      << "-+-" << fn::str(maxPrecisionColLen, '-') << "-+-" << fn::str(maxSuffixColLen, '-')
      << "-+\n";

    std::cout << "     | ";
    printLeftAligned(TYPE_NAME, maxTypeNameColLen);
    std::cout << " | ";
    printLeftAligned(OPTIONAL, maxIsOptionalColLen);
    std::cout << " | ";
    printLeftAligned(HEADER, maxHeaderColLen);
    std::cout << " | ";
    printLeftAligned(STANDARD_SIZE, maxStandardSizeColLen);
    std::cout << " | ";
    printLeftAligned(PLATFORM_SIZE, maxPlatformSizeColLen);
    std::cout << " | ";
    printLeftAligned(SIGNEDNESS, maxSignednessColLen);
    std::cout << " | ";
    printLeftAligned(MIN_VALUE, maxMinValueColLen);
    std::cout << " | ";
    printLeftAligned(MAX_VALUE, maxMaxValueColLen);
    std::cout << " | ";
    printLeftAligned(PRECISION, maxPrecisionColLen);
    std::cout << " | ";
    printLeftAligned(SUFFIX, maxSuffixColLen);
    std::cout << " |\n";

    std::cout
      << "     +-" << fn::str(maxTypeNameColLen, '-') << "-+-" << fn::str(maxIsOptionalColLen, '-')
      << "-+-" << fn::str(maxHeaderColLen, '-') << "-+-" << fn::str(maxStandardSizeColLen, '-')
      << "-+-" << fn::str(maxPlatformSizeColLen, '-') << "-+-" << fn::str(maxSignednessColLen, '-')
      << "-+-" << fn::str(maxMinValueColLen, '-') << "-+-" << fn::str(maxMaxValueColLen, '-')
      << "-+-" << fn::str(maxPrecisionColLen, '-') << "-+-" << fn::str(maxSuffixColLen, '-')
      << "-+\n";

    // Print table rows
    for (auto& option : options)
    {
      // Get type information
      const auto typeRow{getTypeRow(option)};

      std::cout << "     | ";
      printLeftAligned(typeRow.typeName, maxTypeNameColLen);
      std::cout << " | ";
      printLeftAligned(typeRow.isOptional, maxIsOptionalColLen);
      std::cout << " | ";
      printLeftAligned(typeRow.header, maxHeaderColLen);
      std::cout << " | ";
      printLeftAligned(typeRow.standardSize, maxStandardSizeColLen);
      std::cout << " | ";
      printLeftAligned(typeRow.platformSize, maxPlatformSizeColLen);
      std::cout << " | ";
      printLeftAligned(typeRow.signedness, maxSignednessColLen);
      std::cout << " | ";
      printLeftAligned(typeRow.minValue, maxMinValueColLen);
      std::cout << " | ";
      printLeftAligned(typeRow.maxValue, maxMaxValueColLen);
      std::cout << " | ";
      printLeftAligned(typeRow.precision, maxPrecisionColLen);
      std::cout << " | ";
      printLeftAligned(typeRow.literalSuffix, maxSuffixColLen);
      std::cout << " |\n";

      std::cout
        << "     +-" << fn::str(maxTypeNameColLen, '-') << "-+-"
        << fn::str(maxIsOptionalColLen, '-') << "-+-" << fn::str(maxHeaderColLen, '-') << "-+-"
        << fn::str(maxStandardSizeColLen, '-') << "-+-" << fn::str(maxPlatformSizeColLen, '-')
        << "-+-" << fn::str(maxSignednessColLen, '-') << "-+-" << fn::str(maxMinValueColLen, '-')
        << "-+-" << fn::str(maxMaxValueColLen, '-') << "-+-" << fn::str(maxPrecisionColLen, '-')
        << "-+-" << fn::str(maxSuffixColLen, '-') << "-+\n";
    }
  }
} // namespace IO::_internal
