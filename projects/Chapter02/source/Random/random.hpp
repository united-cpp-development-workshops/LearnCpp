#pragma once

#include <Foundation/types.hpp>

#include <utility>
#include <vector>

namespace Random
{
  [[nodiscard]] auto distribute(
    fn::i32f numberOfElements, const std::pair<fn::i32f, fn::i32f>& bounds
  ) -> std::vector<fn::i32f>;
} // namespace Random
