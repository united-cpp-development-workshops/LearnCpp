#pragma once

#pragma once

// NOLINTBEGIN(misc-include-cleaner)

// ------------------------------< Foundation >------------------------------ //

// fn headers
#include "Foundation/constants.hpp"
#include "Foundation/types.hpp"

// fn::Support headers
#include "Foundation/Support/narrowing.ipp"
#include "Foundation/Support/NarrowingError.ipp"

// -------------------------------< Platform >------------------------------- //

// Disable min/max implementations
#ifndef NOMINMAX
  #define NOMINMAX
#endif

// Reduced set of Win32 API
#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

// NOLINTEND(misc-include-cleaner)
