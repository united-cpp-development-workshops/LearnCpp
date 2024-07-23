#include "pch.hpp"

#include "Game/game.ipp"

#include <consoleapi2.h>
#include <Foundation/constants.hpp>
#include <Foundation/types.hpp>
#include <WinNls.h>

#include <iostream>

auto main() noexcept -> fn::idef
try
{
  // Set console output to UTF-8
  SetConsoleOutputCP(CP_UTF8);

  // Main loop
  while (true)
  {
    // Start game
    Game::play();

    // Ask to play again
    std::cout << "\nWould you like to play again? (y/n): ";

    // Get input
    fn::cdef input{};
    std::cin >> input;

    // Exit if not 'y'
    if (input != 'y') { break; }
  }

  // Return success
  return fn::EXIT_SUCCESS_CODE;
}
catch (...)
{
  // Return failure
  return fn::EXIT_FAILURE_CODE;
}
