#include "pch.hpp"

#include "Game/game.hpp"
#include "types.hpp"
#include "wrappers.hpp"

#include <consoleapi2.h>
#include <WinNls.h>

#include <iostream>

auto main() noexcept -> idef
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
    cdef input{};
    std::cin >> input;

    // Exit if not 'y'
    if (input != 'y') { break; }
  }

  // Return success
  return TERMINATE_SUCCESS;
}
catch (...)
{
  // Return failure
  return TERMINATE_FAILURE;
}
