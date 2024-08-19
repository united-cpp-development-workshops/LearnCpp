#include "pch.hpp"

#include <Foundation/constants.hpp>
#include <Foundation/types.hpp>
#include <Foundation/Utility/log.ipp>
#include <Foundation/Utility/what.ipp>

#include <exception>
#include <iostream>

auto main() noexcept -> fn::idef
try
{
  // Print Hello World!
  std::cout << "Hello World!\n";

  // Return success
  return fn::EXIT_SUCCESS_CODE;
}
catch (const std::exception& exception)
{
  // Log exception
  fn::elog(fn::what(exception));

  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
catch (...)
{
  // Log unknown exception
  fn::elog(fn::UNKNOWN_EXCEPTION);

  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
