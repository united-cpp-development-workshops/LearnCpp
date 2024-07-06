#include "pch.hpp"

#include "Foundation/types.hpp"

#include "IO/_internal/messages.hpp"

#include <string>

namespace IO::_internal
{
  // ---------------------------< Error Messages >--------------------------- //

  [[nodiscard]]
  constexpr auto GET_NO_INPUT_MSG() noexcept -> fn::cstr
  {
    return "No input was provided.";
  }

  [[nodiscard]]
  constexpr auto GET_NO_COMMAND_MSG() noexcept -> fn::cstr
  {
    return "No command was provided.";
  }

  [[nodiscard]]
  constexpr auto GET_INVALID_COMMAND_MSG(const std::string& token
  ) -> std::string
  {
    return std::string{"Invalid command: '" + token + "'."};
  }

  // --------------------------< Warning Messages >-------------------------- //

  [[nodiscard]]
  constexpr auto GET_OPTION_MISSING_PREFIX_MSG() noexcept -> fn::cstr
  {
    return "Option with the missing prefix '--' was found and discarded.";
  }
} // namespace IO::_internal
