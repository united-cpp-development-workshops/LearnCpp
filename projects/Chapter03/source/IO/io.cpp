#include "pch.hpp"

#include "IO/io.hpp"

#include "Foundation/types.hpp"

#include "Game/game.hpp"
#include "Math/math.hpp"

#include <cctype>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

auto IO::getPlayerBet(fn::u32f& playerBank) -> fn::u32f
{
  // Bet input
  fn::u32f bet{};

  // Bet validation flags
  fn::bln exceedsMinBet{false};
  fn::bln canAffordBet{false};

  // Input validation loop
  while (not canAffordBet or not exceedsMinBet)
  {
    // Clear input buffer
    std::cin.clear();
    if (std::cin.rdbuf()->in_avail() > 0)
    {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Get bet
    std::cout << "Player: ";
    std::cin >> bet;

    // Validate if bet exceeds minimum bet
    exceedsMinBet = bet >= Game::MIN_BET;
    if (not exceedsMinBet)
    {
      std::cout << "Dealer: Minimum bet is " << Game::MIN_BET << " sir!\n";
      continue;
    }

    // Validate if bet can be afforded
    canAffordBet = bet <= playerBank;
    if (not canAffordBet)
    {
      std::cout << "Dealer: You cannot afford this bet sir!\n";
      continue;
    }
  }

  // Deduct bet from bank
  playerBank -= bet;
  std::cout << "Dealer: " << bet << " dollars of bet placed!\n";

  // Return bet
  return bet;
}

auto IO::printHand(
  const std::string&             holder,
  const std::vector<Game::Card>& hand,
  fn::bln                        hideFirstCard,
  fn::u16f                       adjustedHandTotal
) -> void
{
  // Print holder
  std::cout << holder << ": ";

  // Print hand
  for (fn::size index{}; index < hand.size(); ++index)
  {
    if (index == 0 and hideFirstCard)
    {
      // Hide first card if flag is set
      std::cout << "[??]";
    }
    else
    {
      // Print card
      std::cout << hand.at(index);
    }
  }

  // Print hand
  if (not hideFirstCard)
  {
    if (adjustedHandTotal == 0)
    {
      adjustedHandTotal = {Math::calculateHandTotal(hand)};
    }
    std::cout << " > " << adjustedHandTotal << '\n';
  }
  else { std::cout << " > ?\n"; }
}

auto IO::getPlayerChoice() -> PlayerChoice
{
  // Player choice input
  std::string choice{};

  // Input validation loop
  while (true)
  {
    // Clear input buffer
    std::cin.clear();
    if (std::cin.rdbuf()->in_avail() > 0)
    {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Get choice
    std::cout << "Player: ";
    std::cin >> choice;

    // Validate choice
    if (std::tolower(choice.at(0)) == 'h') { return PlayerChoice::HIT; }
    if (std::tolower(choice.at(0)) == 's') { return PlayerChoice::STAND; }

    // Invalid choice
    std::cout << "Dealer: Place say hit or stand sir!\n";
  }
}
