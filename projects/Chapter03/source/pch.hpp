#pragma once

// NOLINTBEGIN(misc-include-cleaner)

// ----------------------------------------< Foundation >---------------------------------------- //

// fn headers
#include <Foundation/concepts.hpp>
#include <Foundation/constants.hpp>
#include <Foundation/containers.hpp>
#include <Foundation/errors.hpp>
#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>

// fn::Support headers
#include <Foundation/Support/consteval.ipp>
#include <Foundation/Support/narrow.ipp>

// fn::Utility headers
#include <Foundation/Utility/log.ipp>
#include <Foundation/Utility/what.ipp>

// -----------------------------------------< Platform >----------------------------------------- //

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
