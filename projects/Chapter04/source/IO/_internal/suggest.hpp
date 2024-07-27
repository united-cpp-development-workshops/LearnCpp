#pragma once

#include <Foundation/types.hpp>

#include <string_view>

namespace IO::_internal
{
  [[nodiscard]] auto editDistance(
    std::string_view subject, std::string_view candidate
  ) -> fn::f32;
} // namespace IO::_internal
