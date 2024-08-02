#pragma once

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>

namespace Random
{
  [[nodiscard]] auto distribute(
    fn::i32f numberOfElements, const fn::pair<fn::i32f, fn::i32f>& bounds
  ) -> fn::vec<fn::i32f>;
} // namespace Random
