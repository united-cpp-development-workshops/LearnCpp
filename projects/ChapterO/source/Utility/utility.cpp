#include "pch.hpp"

#include "Utility/utility.hpp"

#include "Utility/_internal/constants.hpp"

#include <Foundation/Support/narrow.ipp>
#include <Foundation/types.hpp>

#include <cassert>
#include <utility>

namespace Utility
{
  [[nodiscard]] auto formatBlock(fn::str&& tempString, const fn::ptrd blockSize) -> fn::str
  {
    // This method is not complete, check for optimal cases
    assert(
      fn::narrow_cast<fn::ptrd>(
        tempString.length() / blockSize * _internal::DELIMITER.length()
        + (tempString.length() % blockSize)
      )
      == blockSize
    );

    // Move the temporary string
    fn::str string{std::move(tempString)};

    // Loop through the string
    fn::ptrd       blockCount{};
    constexpr auto delimiterLength{fn::narrow_cast<fn::ptrd>(_internal::DELIMITER.length())};
    const auto     stringLength{string.length()};
    for (fn::size index{}; index < stringLength; ++index)
    {
      // If the block count is equal to the block size
      if (blockCount == blockSize)
      {
        // Insert a space
        string.insert(index, _internal::DELIMITER);

        // Reset the block count
        blockCount = {-delimiterLength};
      }

      // Increment the block count
      ++blockCount;
    }

    return string;
  }
} // namespace Utility
