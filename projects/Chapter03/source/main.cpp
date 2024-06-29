#include "pch.hpp"

#include "Foundation/constants.hpp"
#include "Foundation/types.hpp"

#include "Game/game.hpp"

#include <consoleapi2.h>
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
    std::cout << "\nWould you like to play again? (y/n) ";

    // Get input
    fn::cdef input{};
    std::cin >> input;

    // Exit if not 'y'
    if (input != 'y') { break; }
  }

  // Return success
  return fn::TERMINATE_SUCCESS;
}
catch (...)
{
  // Return failure
  return fn::TERMINATE_FAILURE;
}
