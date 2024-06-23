#pragma once

#include <cstddef>
#include <vector>

namespace Random
{
  auto distribute(std::size_t numberOfElements, int lowerBound, int upperBound)
    -> std::vector<int>;
} // namespace Random
