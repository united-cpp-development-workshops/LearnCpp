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
      {std::string{TYPE_NAME}.length(),
       std::string{OPTIONAL}.length(),
       std::string{HEADER}.length(),
       std::string{STANDARD_SIZE}.length(),
       std::string{PLATFORM_SIZE}.length(),
       std::string{SIGNEDNESS}.length(),
       std::string{MIN_VALUE}.length(),
       std::string{MAX_VALUE}.length(),
       std::string{PRECISION}.length(),
       std::string{SUFFIXES}.length()}
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
       typeRow.literalSuffixes.length()}
    )};

    // Print title
    std::cout << "   METRICS: '" << typeRow.typeName << "'\n\n";

    // Print table
    std::cout << "     +-" << std::string(firstColumnWidth, '-') << "-+-"
              << std::string(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(TYPE_NAME, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.typeName, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << std::string(firstColumnWidth, '-') << "-+-"
              << std::string(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(OPTIONAL, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.isOptional, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << std::string(firstColumnWidth, '-') << "-+-"
              << std::string(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(HEADER, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.header, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << std::string(firstColumnWidth, '-') << "-+-"
              << std::string(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(STANDARD_SIZE, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.standardSize, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << std::string(firstColumnWidth, '-') << "-+-"
              << std::string(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(PLATFORM_SIZE, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.platformSize, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << std::string(firstColumnWidth, '-') << "-+-"
              << std::string(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(SIGNEDNESS, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.signedness, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << std::string(firstColumnWidth, '-') << "-+-"
              << std::string(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(MIN_VALUE, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.minValue, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << std::string(firstColumnWidth, '-') << "-+-"
              << std::string(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(MAX_VALUE, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.maxValue, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << std::string(firstColumnWidth, '-') << "-+-"
              << std::string(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(PRECISION, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.precision, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << std::string(firstColumnWidth, '-') << "-+-"
              << std::string(secondColumnWidth, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(SUFFIXES, firstColumnWidth);
    std::cout << " | ";
    printLeftAligned(typeRow.literalSuffixes, secondColumnWidth);
    std::cout << " |\n";

    std::cout << "     +-" << std::string(firstColumnWidth, '-') << "-+-"
              << std::string(secondColumnWidth, '-') << "-+\n";
  }

  auto printTypeTable(const std::set<Option>& options) -> fn::none
  {
    // Max column lengths
    auto maxTypeNameColumnLength{std::string{TYPE_NAME}.length()};
    auto maxIsOptionalColumnLength{std::string{OPTIONAL}.length()};
    auto maxHeaderColumnLength{std::string{HEADER}.length()};
    auto maxStandardSizeColumnLength{std::string{STANDARD_SIZE}.length()};
    auto maxPlatformSizeColumnLength{std::string{PLATFORM_SIZE}.length()};
    auto maxSignednessColumnLength{std::string{SIGNEDNESS}.length()};
    auto maxMinValueColumnLength{std::string{MIN_VALUE}.length()};
    auto maxMaxValueColumnLength{std::string{MAX_VALUE}.length()};
    auto maxPrecisionColumnLength{std::string{PRECISION}.length()};
    auto maxLiteralSuffixesColumnLength{std::string{SUFFIXES}.length()};

    for (auto& option : options)
    {
      // Get type information
      const auto typeRow{getTypeRow(option)};

      // Get column widths
      maxTypeNameColumnLength = {
        std::max(maxTypeNameColumnLength, typeRow.typeName.length())
      };
      maxIsOptionalColumnLength = {
        std::max(maxIsOptionalColumnLength, typeRow.isOptional.length())
      };
      maxHeaderColumnLength = {
        std::max(maxHeaderColumnLength, typeRow.header.length())
      };
      maxStandardSizeColumnLength = {
        std::max(maxStandardSizeColumnLength, typeRow.standardSize.length())
      };
      maxPlatformSizeColumnLength = {
        std::max(maxPlatformSizeColumnLength, typeRow.platformSize.length())
      };
      maxSignednessColumnLength = {
        std::max(maxSignednessColumnLength, typeRow.signedness.length())
      };
      maxMinValueColumnLength = {
        std::max(maxMinValueColumnLength, typeRow.minValue.length())
      };
      maxMaxValueColumnLength = {
        std::max(maxMaxValueColumnLength, typeRow.maxValue.length())
      };
      maxPrecisionColumnLength = {
        std::max(maxPrecisionColumnLength, typeRow.precision.length())
      };
      maxLiteralSuffixesColumnLength = {std::max(
        maxLiteralSuffixesColumnLength, typeRow.literalSuffixes.length()
      )};
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
      else { std::cout << ", '" << typeRow.typeName << "'"; }
    }
    std::cout << "\n\n";

    // Print table header
    std::cout
      << "     +-" << std::string(maxTypeNameColumnLength, '-') << "-+-"
      << std::string(maxIsOptionalColumnLength, '-') << "-+-"
      << std::string(maxHeaderColumnLength, '-') << "-+-"
      << std::string(maxStandardSizeColumnLength, '-') << "-+-"
      << std::string(maxPlatformSizeColumnLength, '-') << "-+-"
      << std::string(maxSignednessColumnLength, '-') << "-+-"
      << std::string(maxMinValueColumnLength, '-') << "-+-"
      << std::string(maxMaxValueColumnLength, '-') << "-+-"
      << std::string(maxPrecisionColumnLength, '-') << "-+-"
      << std::string(maxLiteralSuffixesColumnLength, '-') << "-+\n";

    std::cout << "     | ";
    printLeftAligned(TYPE_NAME, maxTypeNameColumnLength);
    std::cout << " | ";
    printLeftAligned(OPTIONAL, maxIsOptionalColumnLength);
    std::cout << " | ";
    printLeftAligned(HEADER, maxHeaderColumnLength);
    std::cout << " | ";
    printLeftAligned(STANDARD_SIZE, maxStandardSizeColumnLength);
    std::cout << " | ";
    printLeftAligned(PLATFORM_SIZE, maxPlatformSizeColumnLength);
    std::cout << " | ";
    printLeftAligned(SIGNEDNESS, maxSignednessColumnLength);
    std::cout << " | ";
    printLeftAligned(MIN_VALUE, maxMinValueColumnLength);
    std::cout << " | ";
    printLeftAligned(MAX_VALUE, maxMaxValueColumnLength);
    std::cout << " | ";
    printLeftAligned(PRECISION, maxPrecisionColumnLength);
    std::cout << " | ";
    printLeftAligned(SUFFIXES, maxLiteralSuffixesColumnLength);
    std::cout << " |\n";

    std::cout
      << "     +-" << std::string(maxTypeNameColumnLength, '-') << "-+-"
      << std::string(maxIsOptionalColumnLength, '-') << "-+-"
      << std::string(maxHeaderColumnLength, '-') << "-+-"
      << std::string(maxStandardSizeColumnLength, '-') << "-+-"
      << std::string(maxPlatformSizeColumnLength, '-') << "-+-"
      << std::string(maxSignednessColumnLength, '-') << "-+-"
      << std::string(maxMinValueColumnLength, '-') << "-+-"
      << std::string(maxMaxValueColumnLength, '-') << "-+-"
      << std::string(maxPrecisionColumnLength, '-') << "-+-"
      << std::string(maxLiteralSuffixesColumnLength, '-') << "-+\n";

    // Print table rows
    for (auto& option : options)
    {
      // Get type information
      const auto typeRow{getTypeRow(option)};

      std::cout << "     | ";
      printLeftAligned(typeRow.typeName, maxTypeNameColumnLength);
      std::cout << " | ";
      printLeftAligned(typeRow.isOptional, maxIsOptionalColumnLength);
      std::cout << " | ";
      printLeftAligned(typeRow.header, maxHeaderColumnLength);
      std::cout << " | ";
      printLeftAligned(typeRow.standardSize, maxStandardSizeColumnLength);
      std::cout << " | ";
      printLeftAligned(typeRow.platformSize, maxPlatformSizeColumnLength);
      std::cout << " | ";
      printLeftAligned(typeRow.signedness, maxSignednessColumnLength);
      std::cout << " | ";
      printLeftAligned(typeRow.minValue, maxMinValueColumnLength);
      std::cout << " | ";
      printLeftAligned(typeRow.maxValue, maxMaxValueColumnLength);
      std::cout << " | ";
      printLeftAligned(typeRow.precision, maxPrecisionColumnLength);
      std::cout << " | ";
      printLeftAligned(typeRow.literalSuffixes, maxLiteralSuffixesColumnLength);
      std::cout << " |\n";

      std::cout
        << "     +-" << std::string(maxTypeNameColumnLength, '-') << "-+-"
        << std::string(maxIsOptionalColumnLength, '-') << "-+-"
        << std::string(maxHeaderColumnLength, '-') << "-+-"
        << std::string(maxStandardSizeColumnLength, '-') << "-+-"
        << std::string(maxPlatformSizeColumnLength, '-') << "-+-"
        << std::string(maxSignednessColumnLength, '-') << "-+-"
        << std::string(maxMinValueColumnLength, '-') << "-+-"
        << std::string(maxMaxValueColumnLength, '-') << "-+-"
        << std::string(maxPrecisionColumnLength, '-') << "-+-"
        << std::string(maxLiteralSuffixesColumnLength, '-') << "-+\n";
    }
  }
} // namespace IO::_internal
