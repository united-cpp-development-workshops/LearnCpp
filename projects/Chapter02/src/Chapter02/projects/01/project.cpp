#include "Chapter02/projects/01/project.hpp"

#include "Chapter02/projects/01/blackjack.hpp"

#include <Base/announce.hpp>
#include <Windows.h>

#include <iostream>

void Project01::run()
{
  ANNOUNCE_PROJECT("Project 01: Console Blackjack");
  SetConsoleOutputCP(CP_UTF8);
  while (true)
  {
    playBlackjack();
    std::cout << "\nWould you like to play again? (y/n) ";
    char input{};
    std::cin >> input;
    if (input not_eq 'y')
    {
      break;
    }
  }
}
