#pragma once

#include "Foundation/types.hpp"

#include <string>

namespace IO::_internal
{
  // ---------------------------< Error Messages >--------------------------- //
  [[nodiscard]]
  constexpr auto GET_NO_INPUT_MSG() noexcept -> fn::cstr;
  [[nodiscard]]
  constexpr auto GET_NO_COMMAND_MSG() noexcept -> fn::cstr;
  [[nodiscard]]
  constexpr auto GET_INVALID_COMMAND_MSG(const std::string& token
  ) -> std ::string;

  // --------------------------< Warning Messages >-------------------------- //
  [[nodiscard]]
  constexpr auto GET_OPTION_MISSING_PREFIX_MSG() noexcept -> fn::cstr;
} // namespace IO::_internal
