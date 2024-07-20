#pragma once

#include "Foundation/types.hpp"

#include <cstdlib>

namespace fn
{
  /**
   * @brief The exit code for successful termination of a program.
   */
  inline constexpr idef EXIT_SUCCESS_CODE{EXIT_SUCCESS};

  /**
   * @brief The exit code for unsuccessful termination of a program.
   */
  inline constexpr idef EXIT_FAILURE_CODE{EXIT_FAILURE};
} // namespace fn
