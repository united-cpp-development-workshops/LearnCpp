#pragma once

#include "types.hpp"

#include <cstdlib>
#include <GSL/narrow>

// ------------------------------< Constants >------------------------------- //

// Exit codes
inline constexpr idef TERMINATE_SUCCESS{EXIT_SUCCESS};
inline constexpr idef TERMINATE_FAILURE{EXIT_FAILURE};

// ------------------------------< Functions >------------------------------- //

// NOLINTBEGIN(misc-unused-using-decls)

// Narrowing
using gsl::narrow;

// NOLINTEND(misc-unused-using-decls)
