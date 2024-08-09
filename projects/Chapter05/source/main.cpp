#include "pch.hpp"

#include "Data/Repository.hpp"
#include "Game/Wordsman.hpp"

#include <Foundation/constants.hpp>
#include <Foundation/errors.hpp>
#include <Foundation/types.hpp>
#include <Foundation/Utility/log.ipp>
#include <Foundation/Utility/what.ipp>

#include <exception>
#include <filesystem>
#include <iostream>
#include <memory>

auto main() noexcept -> fn::idef
try
{
  // Initialize the repository
  const auto repository{std::make_shared<Data::Repository>()};

  // Initialize the game
  Game::Wordsman game{repository};

  // Run the game
  game.run();

  // Return success
  return fn::EXIT_SUCCESS_CODE;
}
catch (const fn::FileError& error)
{
  // Log error
  fn::elog(error);

  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
catch (const fn::StateError& error)
{
  // Log error
  fn::elog(error);

  // Return failure
  return fn::EXIT_FAILURE_CODE;
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
