#pragma once

#include "types.hpp"

#include <vector>

namespace Random
{
  auto distribute(size numberOfElements, i32f lowerBound, i32f upperBound)
    -> std::vector<i32f>;
} // namespace Random
