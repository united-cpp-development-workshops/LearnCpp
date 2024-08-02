#pragma once

#include <Foundation/types.hpp>

#include <format>

namespace IO::_internal
{
  // -------------------------------------< Error Messages >------------------------------------- //
  [[nodiscard]] consteval auto NO_INPUT_MSG() noexcept -> fn::strv;
  [[nodiscard]] consteval auto NO_CMD_MSG() noexcept -> fn::strv;
  [[nodiscard]] inline auto    invalidCmdMsg(fn::strv token) -> fn::str;
  [[nodiscard]] inline auto    invalidCmdSuggestMsg(fn::strv token, fn::strv suggestion) -> fn::str;
  [[nodiscard]] inline auto    insufficientOptMsg(fn::strv token) -> fn::str;

  // ------------------------------------< Warning Messages >------------------------------------ //
  [[nodiscard]] consteval auto MISSING_OPT_PREFIX_MSG() noexcept -> fn::strv;
  [[nodiscard]] inline auto    autofixCmdMsg(fn::strv token, fn::strv suggestion) -> fn::str;
  [[nodiscard]] inline auto    autofixOptMsg(fn::strv token, fn::strv suggestion) -> fn::str;
  [[nodiscard]] inline auto    duplicateOptMsg(fn::strv token) -> fn::str;
  [[nodiscard]] inline auto    invalidOptMsg(fn::strv token) -> fn::str;
  [[nodiscard]] inline auto    invalidOptSuggestMsg(fn::strv token, fn::strv suggestion) -> fn::str;
  [[nodiscard]] inline auto    missingOptMsg(fn::strv token) -> fn::str;
  [[nodiscard]] inline auto    discardedOptByLimitMsg(fn::strv token) -> fn::str;
  [[nodiscard]] inline auto    discardedOptMsg(fn::strv token) -> fn::str;
} // namespace IO::_internal

/*------------------------------------------------------------------------------------------------*\
*| >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Implementation <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< |*
\*------------------------------------------------------------------------------------------------*/

namespace IO::_internal
{
  // -------------------------------------< Error Messages >------------------------------------- //

  [[nodiscard]] consteval auto NO_INPUT_MSG() noexcept -> fn::strv
  {
    return "No input was provided.";
  }

  [[nodiscard]] consteval auto NO_CMD_MSG() noexcept -> fn::strv
  {
    return "No command was provided.";
  }

  [[nodiscard]] inline auto invalidCmdMsg(fn::strv token) -> std ::string
  {
    return std::format("Invalid command '{}'.", token);
  }

  [[nodiscard]] inline auto invalidCmdSuggestMsg(fn::strv token, fn::strv suggestion) -> fn::str
  {
    return std::format("Invalid command '{}'. Did you mean '{}'?", token, suggestion);
  }

  [[nodiscard]] inline auto insufficientOptMsg(fn::strv token) -> fn::str
  {
    return std::format("Insufficient options for command '{}'.", token);
  }

  // ------------------------------------< Warning Messages >------------------------------------ //

  [[nodiscard]] consteval auto MISSING_OPT_PREFIX_MSG() noexcept -> fn::strv
  {
    return "Option with the missing prefix '-' was discarded.";
  }

  [[nodiscard]] inline auto autofixCmdMsg(fn::strv token, fn::strv suggestion) -> fn::str
  {
    return std::format("Invalid command '{}'. Closest natcg '{}' was used.", token, suggestion);
  }

  [[nodiscard]] inline auto autofixOptMsg(fn::strv token, fn::strv suggestion) -> fn::str
  {
    return std::format("Invalid option '{}'. Closest match '{}' was used.", token, suggestion);
  }

  [[nodiscard]] inline auto duplicateOptMsg(fn::strv token) -> fn::str
  {
    return std::format("Duplicate option '{}' was discarded.", token);
  }

  [[nodiscard]] inline auto invalidOptMsg(fn::strv token) -> fn::str
  {
    return std::format("Invalid option '{}' was dicarded.", token);
  }

  [[nodiscard]] inline auto invalidOptSuggestMsg(fn::strv token, fn::strv suggestion) -> fn::str
  {
    return std::format("Invalid option '{}' was discarded. Did you mean '{}'?", token, suggestion);
  }

  [[nodiscard]] inline auto missingOptMsg(fn::strv token) -> fn::str
  {
    return std::format("Required option '{}' was not found.", token);
  }

  [[nodiscard]] inline auto discardedOptByLimitMsg(fn::strv token) -> fn::str
  {
    return std::format("Option '{}' was discarded due to limit.", token);
  }

  [[nodiscard]] inline auto discardedOptMsg(fn::strv token) -> fn::str
  {
    return std::format("Unnecessary option '{}' was discarded.", token);
  }
} // namespace IO::_internal
