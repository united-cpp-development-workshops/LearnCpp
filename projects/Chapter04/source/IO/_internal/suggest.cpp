#include "pch.hpp"

#include "suggest.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/Support/narrow.ipp>
#include <Foundation/types.hpp>

#include <algorithm>
#include <numeric>

namespace
{
  [[nodiscard]] auto keyDistance(const fn::cdef key1, const fn::cdef key2) -> fn::f32
  {
    static const fn::umap s_keyMap{
      // Row 0
      fn::pair{'1', fn::pair{0, 0} },
      fn::pair{'2', fn::pair{1, 0} },
      fn::pair{'3', fn::pair{2, 0} },
      fn::pair{'4', fn::pair{3, 0} },
      fn::pair{'5', fn::pair{4, 0} },
      fn::pair{'6', fn::pair{5, 0} },
      fn::pair{'7', fn::pair{6, 0} },
      fn::pair{'8', fn::pair{7, 0} },
      fn::pair{'9', fn::pair{8, 0} },
      fn::pair{'0', fn::pair{9, 0} },
      fn::pair{'-', fn::pair{10, 0}},
      // Row 1
      fn::pair{'q', fn::pair{0, 1} },
      fn::pair{'w', fn::pair{1, 1} },
      fn::pair{'e', fn::pair{2, 1} },
      fn::pair{'r', fn::pair{3, 1} },
      fn::pair{'t', fn::pair{4, 1} },
      fn::pair{'y', fn::pair{5, 1} },
      fn::pair{'u', fn::pair{6, 1} },
      fn::pair{'i', fn::pair{7, 1} },
      fn::pair{'o', fn::pair{8, 1} },
      fn::pair{'p', fn::pair{9, 1} },
      // Row 2
      fn::pair{'a', fn::pair{0, 2} },
      fn::pair{'s', fn::pair{1, 2} },
      fn::pair{'d', fn::pair{2, 2} },
      fn::pair{'f', fn::pair{3, 2} },
      fn::pair{'g', fn::pair{4, 2} },
      fn::pair{'h', fn::pair{5, 2} },
      fn::pair{'j', fn::pair{6, 2} },
      fn::pair{'k', fn::pair{7, 2} },
      fn::pair{'l', fn::pair{8, 2} },
      // Row 3
      fn::pair{'z', fn::pair{0, 3} },
      fn::pair{'x', fn::pair{1, 3} },
      fn::pair{'c', fn::pair{2, 3} },
      fn::pair{'v', fn::pair{3, 3} },
      fn::pair{'b', fn::pair{4, 3} },
      fn::pair{'n', fn::pair{5, 3} },
      fn::pair{'m', fn::pair{6, 3} }
    };

    // Get the coordinates of the keys
    const auto& [x1, y1]{s_keyMap.at(key1)};
    const auto& [x2, y2]{s_keyMap.at(key2)};

    // Calculate x and y distances
    const auto xDistance{std::abs(x1 - x2)};
    const auto yDistance{std::abs(y1 - y2)};

    // Calculate distance using Euclidian distance
    const auto distance{
      std::sqrt(fn::narrow_cast<fn::f32>((xDistance * xDistance) + (yDistance * yDistance)))
    };

    // Normalize and return the distance
    return std::clamp(((distance / std::sqrt(109.0f)) + 0.5f), 0.05f, 1.0f);
  }
} // namespace

namespace IO::_internal
{
  [[nodiscard]] auto editDistance(fn::strv subject, fn::strv candidate) -> fn::f32
  {
    // Find the common prefix of the strings
    fn::size commonPrefixLength{};
    while (commonPrefixLength < std::min(subject.length(), candidate.length())
           and subject.at(commonPrefixLength) == candidate.at(commonPrefixLength))
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
    fn::vec matrix{subjectLength + 1, fn::vec<fn::f32>(candidateLength + 1)};

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
