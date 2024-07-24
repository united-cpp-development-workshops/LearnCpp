#pragma once

#include <Foundation/types.hpp>

#include <string>

namespace IO::_internal
{
  // ---------------------------< Error Messages >--------------------------- //
  [[nodiscard]] constexpr auto NO_INPUT_MSG() noexcept -> fn::cstr;
  [[nodiscard]] constexpr auto NO_COMMAND_MSG() noexcept -> fn::cstr;
  [[nodiscard]] constexpr auto INVALID_COMMAND_MSG(const std::string& token
  ) -> std::string;
  [[nodiscard]] constexpr auto INSUFFICIENT_OPTIONS_MSG(const std::string& token
  ) -> std::string;

  // --------------------------< Warning Messages >-------------------------- //
  [[nodiscard]] constexpr auto MISSING_OPTION_PREFIX_MSG() noexcept -> fn::cstr;
  [[nodiscard]] constexpr auto DUPLICATE_OPTION_MSG(const std::string& token
  ) -> std::string;
  [[nodiscard]] constexpr auto INVALID_OPTION_MSG(const std::string& token
  ) -> std::string;
  [[nodiscard]] constexpr auto MISSING_OPTION_MSG(const std::string& token
  ) -> std::string;
  [[nodiscard]] constexpr auto DISCARDED_OPTION_BY_LIMIT_MSG(
    const std::string& token
  ) -> std::string;
  [[nodiscard]] constexpr auto DISCARDED_OPTION_MSG(const std::string& token
  ) -> std::string;
} // namespace IO::_internal

/*----------------------------------------------------------------------------*\
*| >>>>>>>>>>>>>>>>>>>>>>>>>>>>> Implementation <<<<<<<<<<<<<<<<<<<<<<<<<<<<< |*
\*----------------------------------------------------------------------------*/

namespace IO::_internal
{
  // ---------------------------< Error Messages >--------------------------- //

  [[nodiscard]] constexpr auto NO_INPUT_MSG() noexcept -> fn::cstr
  {
    return "No input was provided.";
  }

  [[nodiscard]] constexpr auto NO_COMMAND_MSG() noexcept -> fn::cstr
  {
    return "No command was provided.";
  }

  [[nodiscard]] constexpr auto INVALID_COMMAND_MSG(const std::string& token
  ) -> std ::string
  {
    return {"Invalid command: '" + token + "'."};
  }

  [[nodiscard]] constexpr auto INSUFFICIENT_OPTIONS_MSG(const std::string& token
  ) -> std::string
  {
    return {"Insufficient options for command '" + token + "'."};
  }

  // --------------------------< Warning Messages >-------------------------- //

  [[nodiscard]] constexpr auto MISSING_OPTION_PREFIX_MSG() noexcept -> fn::cstr
  {
    return "Option with the missing prefix '--' was found and discarded.";
  }

  [[nodiscard]] constexpr auto DUPLICATE_OPTION_MSG(const std::string& token
  ) -> std::string
  {
    return {"Duplicate option '" + token + "' was found and discarded."};
  }

  [[nodiscard]] constexpr auto INVALID_OPTION_MSG(const std::string& token
  ) -> std::string
  {
    return {"Invalid option '" + token + "' was found and dicarded."};
  }

  [[nodiscard]] constexpr auto MISSING_OPTION_MSG(const std::string& token
  ) -> std::string
  {
    return {"Required option '" + token + "' was not found."};
  }

  [[nodiscard]] constexpr auto DISCARDED_OPTION_BY_LIMIT_MSG(
    const std::string& token
  ) -> std::string
  {
    return {"Option '" + token + "' was discarded due to limit."};
  }

  [[nodiscard]] constexpr auto DISCARDED_OPTION_MSG(const std::string& token
  ) -> std::string
  {
    return {"Unnecessary option '" + token + "' was discarded."};
  }
} // namespace IO::_internal
