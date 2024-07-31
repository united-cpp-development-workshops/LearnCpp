#pragma once

#include <Foundation/types.hpp>

#include <string>

namespace IO::_internal
{
  // ---------------------------< Error Messages >--------------------------- //
  [[nodiscard]] consteval auto NO_INPUT_MSG() noexcept -> fn::cstr;
  [[nodiscard]] consteval auto NO_COMMAND_MSG() noexcept -> fn::cstr;

  [[nodiscard]] inline auto invalidCommandMsg(const std::string& token
  ) -> std::string;
  [[nodiscard]] inline auto invalidCommandSuggesetMsg(
    const std::string& token, const std::string& suggestion
  ) -> std::string;
  [[nodiscard]] inline auto insufficientOptionsMsg(const std::string& token
  ) -> std::string;

  // --------------------------< Warning Messages >-------------------------- //
  [[nodiscard]] consteval auto MISSING_OPTION_PREFIX_MSG() noexcept -> fn::cstr;

  [[nodiscard]] inline auto autofixCommandMsg(
    const std::string& token, const std::string& suggestion
  ) -> std::string;
  [[nodiscard]] inline auto autofixOptionMsg(
    const std::string& token, const std::string& suggestion
  ) -> std::string;
  [[nodiscard]] inline auto duplicateOptionMsg(const std::string& token
  ) -> std::string;
  [[nodiscard]] inline auto invalidOptionMsg(const std::string& token
  ) -> std::string;
  [[nodiscard]] inline auto invalidOptionSuggestMsg(
    const std::string& token, const std::string& suggestion
  ) -> std::string;
  [[nodiscard]] inline auto missingOptionMsg(const std::string& token
  ) -> std::string;
  [[nodiscard]] inline auto discardedOptionByLimitMsg(const std::string& token
  ) -> std::string;
  [[nodiscard]] inline auto discardedOptionMsg(const std::string& token
  ) -> std::string;
} // namespace IO::_internal

/*----------------------------------------------------------------------------*\
*| >>>>>>>>>>>>>>>>>>>>>>>>>>>>> Implementation <<<<<<<<<<<<<<<<<<<<<<<<<<<<< |*
\*----------------------------------------------------------------------------*/

namespace IO::_internal
{
  // ---------------------------< Error Messages >--------------------------- //

  [[nodiscard]] consteval auto NO_INPUT_MSG() noexcept -> fn::cstr
  {
    return "No input was provided.";
  }

  [[nodiscard]] consteval auto NO_COMMAND_MSG() noexcept -> fn::cstr
  {
    return "No command was provided.";
  }

  [[nodiscard]] inline auto invalidCommandMsg(const std::string& token
  ) -> std ::string
  {
    return {"Invalid command '" + token + "'."};
  }

  [[nodiscard]] inline auto invalidCommandSuggesetMsg(
    const std::string& token, const std::string& suggestion
  ) -> std::string
  {
    return {
      "Invalid command '" + token + "'. Did you mean '" + suggestion + "'?"
    };
  }

  [[nodiscard]] inline auto insufficientOptionsMsg(const std::string& token
  ) -> std::string
  {
    return {"Insufficient options for command '" + token + "'."};
  }

  // --------------------------< Warning Messages >-------------------------- //

  [[nodiscard]] consteval auto MISSING_OPTION_PREFIX_MSG() noexcept -> fn::cstr
  {
    return "Option with the missing prefix '-' was discarded.";
  }

  [[nodiscard]] inline auto autofixCommandMsg(
    const std::string& token, const std::string& suggestion
  ) -> std::string
  {
    return {
      "Invalid command '" + token + "'. Closest match '" + suggestion
      + "' was used."
    };
  }

  [[nodiscard]] inline auto autofixOptionMsg(
    const std::string& token, const std::string& suggestion
  ) -> std::string
  {
    return {
      "Invalid option '" + token + "'. Closest match '" + suggestion
      + "' was used."
    };
  }

  [[nodiscard]] inline auto duplicateOptionMsg(const std::string& token
  ) -> std::string
  {
    return {"Duplicate option '" + token + "' was discarded."};
  }

  [[nodiscard]] inline auto invalidOptionMsg(const std::string& token
  ) -> std::string
  {
    return {"Invalid option '" + token + "' was dicarded."};
  }

  [[nodiscard]] inline auto invalidOptionSuggestMsg(
    const std::string& token, const std::string& suggestion
  ) -> std::string
  {
    return {
      "Invalid option '" + token + "' was discarded. Did you mean '"
      + suggestion + "'?"
    };
  }

  [[nodiscard]] inline auto missingOptionMsg(const std::string& token
  ) -> std::string
  {
    return {"Required option '" + token + "' was not found."};
  }

  [[nodiscard]] inline auto discardedOptionByLimitMsg(const std::string& token
  ) -> std::string
  {
    return {"Option '" + token + "' was discarded due to limit."};
  }

  [[nodiscard]] inline auto discardedOptionMsg(const std::string& token
  ) -> std::string
  {
    return {"Unnecessary option '" + token + "' was discarded."};
  }
} // namespace IO::_internal
