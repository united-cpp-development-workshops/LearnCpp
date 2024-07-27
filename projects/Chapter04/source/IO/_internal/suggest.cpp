#include "pch.hpp"

#include "suggest.hpp"

#include <Foundation/Support/narrow.ipp>
#include <Foundation/types.hpp>

#include <algorithm>
#include <numeric>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace
{
  [[nodiscard]] auto keyDistance(const fn::cdef key1, const fn::cdef key2)
    -> fn::f32
  {
    static const std::unordered_map keyMap{
      // Row 0
      std::pair{'1', std::pair{0, 0} },
      std::pair{'2', std::pair{1, 0} },
      std::pair{'3', std::pair{2, 0} },
      std::pair{'4', std::pair{3, 0} },
      std::pair{'5', std::pair{4, 0} },
      std::pair{'6', std::pair{5, 0} },
      std::pair{'7', std::pair{6, 0} },
      std::pair{'8', std::pair{7, 0} },
      std::pair{'9', std::pair{8, 0} },
      std::pair{'0', std::pair{9, 0} },
      std::pair{'-', std::pair{10, 0}},
      // Row 1
      std::pair{'q', std::pair{0, 1} },
      std::pair{'w', std::pair{1, 1} },
      std::pair{'e', std::pair{2, 1} },
      std::pair{'r', std::pair{3, 1} },
      std::pair{'t', std::pair{4, 1} },
      std::pair{'y', std::pair{5, 1} },
      std::pair{'u', std::pair{6, 1} },
      std::pair{'i', std::pair{7, 1} },
      std::pair{'o', std::pair{8, 1} },
      std::pair{'p', std::pair{9, 1} },
      // Row 2
      std::pair{'a', std::pair{0, 2} },
      std::pair{'s', std::pair{1, 2} },
      std::pair{'d', std::pair{2, 2} },
      std::pair{'f', std::pair{3, 2} },
      std::pair{'g', std::pair{4, 2} },
      std::pair{'h', std::pair{5, 2} },
      std::pair{'j', std::pair{6, 2} },
      std::pair{'k', std::pair{7, 2} },
      std::pair{'l', std::pair{8, 2} },
      // Row 3
      std::pair{'z', std::pair{0, 3} },
      std::pair{'x', std::pair{1, 3} },
      std::pair{'c', std::pair{2, 3} },
      std::pair{'v', std::pair{3, 3} },
      std::pair{'b', std::pair{4, 3} },
      std::pair{'n', std::pair{5, 3} },
      std::pair{'m', std::pair{6, 3} }
    };

    // Get the coordinates of the keys
    const auto& [x1, y1]{keyMap.at(key1)};
    const auto& [x2, y2]{keyMap.at(key2)};

    // Calculate x and y distances
    const auto xDistance{std::abs(x1 - x2)};
    const auto yDistance{std::abs(y1 - y2)};

    // Calculate distance using eucledian distance
    const auto distance{std::sqrt(fn::narrow_cast<fn::f32>(
      (xDistance * xDistance) + (yDistance * yDistance)
    ))};

    // Normalize and return the distance
    return std::clamp(((distance / std::sqrt(109.0f)) + 0.5f), 0.05f, 1.0f);
  }
} // namespace

namespace IO::_internal
{
  [[nodiscard]] auto editDistance(
    std::string_view subject, std::string_view candidate
  ) -> fn::f32
  {
    // Find the common prefix of the strings
    fn::size commonPrefixLength{};
    while (
      commonPrefixLength < std::min(subject.length(), candidate.length())
      and subject.at(commonPrefixLength) == candidate.at(commonPrefixLength)
    )
    {
      ++commonPrefixLength;
    }

    // Eliminate the common prefix
    subject.remove_prefix(commonPrefixLength);
    candidate.remove_prefix(commonPrefixLength);

    // Find the common suffix of the strings
    fn::size commonSuffixLength{};
    while (commonSuffixLength < std::min(subject.length(), candidate.length())
           and subject.at(subject.length() - commonSuffixLength - 1)
                 == candidate.at(candidate.length() - commonSuffixLength - 1))
    {
      ++commonSuffixLength;
    }

    // Eliminate the common suffix
    subject.remove_suffix(commonSuffixLength);
    candidate.remove_suffix(commonSuffixLength);

    // Get the resulting lengths
    const auto subjectLength{subject.length()};
    const auto candidateLength{candidate.length()};

    // Initialize the matrix
    std::vector matrix{
      subjectLength + 1, std::vector<fn::f32>(candidateLength + 1)
    };

    // Initialize the first row with iota
    for (fn::size i{}; i <= subjectLength; ++i)
    {
      matrix.at(i).at(0) = {fn::narrow_cast<fn::f32>(i)};
    }

    // Initialize the first column with iota
    std::iota(matrix.at(0).begin(), matrix.at(0).end(), 0.0f);

    // Fill the matrix
    for (fn::size y{1}; y <= candidateLength; ++y)
    {
      for (fn::size x{1}; x <= subjectLength; ++x)
      {
        // Get previous costs
        auto subCost{matrix.at(x - 1).at(y - 1)};
        auto delCost{matrix.at(x).at(y - 1)};
        auto insCost{matrix.at(x - 1).at(y)};

        // Check if the characters are the same
        if (subject.at(x - 1) == candidate.at(y - 1))
        {
          // Assign the previous cheapest cost
          matrix.at(x).at(y) = {std::min({subCost, delCost, insCost})};
        }
        else
        {
          // Calculate new costs
          subCost += keyDistance(subject.at(x - 1), candidate.at(y - 1));
          delCost += 1.0f;
          insCost += 1.0f;

          // Assign the cheapest cost
          matrix.at(x).at(y) = {std::min({subCost, delCost, insCost})};
        }
      }
    }

    // Return the edit distance
    return matrix.at(subjectLength).at(candidateLength);
  }
} // namespace IO::_internal
