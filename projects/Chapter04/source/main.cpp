#include "pch.hpp"

#include "Foundation/constants.hpp"
#include "Foundation/types.hpp"

auto main() noexcept -> fn::idef
try
{
  // Return success
  return fn::TERMINATE_SUCCESS;
}
catch (...)
{
  // Return failure
  return fn::TERMINATE_FAILURE;
}
