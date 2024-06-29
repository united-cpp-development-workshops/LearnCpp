#pragma once

#include "Foundation/types.hpp"

#include <vector>

namespace Random
{
  auto distribute(
    fn::size numberOfElements, fn::i32f lowerBound, fn::i32f upperBound
  ) -> std::vector<fn::i32f>;
} // namespace Random
