#include "pch.hpp"

#include "Game/game.hpp"

#include "Foundation/Support/narrowing.ipp"
#include "Foundation/types.hpp"

#include "IO/io.hpp"
#include "Math/math.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace
{
  auto createDeck() -> std::vector<Game::Card>
  {
    // Initialize deck
    std::vector<Game::Card> deck{};

    // Create deck(s)
    for (fn::size index{}; index < Game::DECK_COUNT; ++index)
    {
      // Loop through suits
      for (const fn::cstr suit : {"♥", "♦", "♣", "♠"})
      {
        // Loop through ranks
        for (const fn::cdef rank :
             {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'})
        {
          // Initialize value
          fn::u8f value{};

          // Assign value to rank
          if (rank == 'T' or rank == 'J' or rank == 'Q' or rank == 'K')
          {
            value = {Game::COURT_CARD_VALUE};
          }
          else if (rank == 'A') { value = {Game::ACE_HIGH_VALUE}; }
          else { value = fn::narrow_cast<fn::u8f>(rank - '0'); }

          // Add card to deck
          deck.emplace_back(suit, rank, value);
        }
      }
    }
    return deck;
  }

  auto adjustAces(std::vector<Game::Card>& hand, fn::u16f& handTotal) noexcept
    -> void
  {
    while (handTotal > Game::BLACKJACK)
    {
      // Check for aces and adjust value
      if (std::any_of(
            hand.begin(),
            hand.end(),
            [](Game::Card& card) noexcept -> bool
            {
              if (card.isAce() and card.getValue() == Game::ACE_HIGH_VALUE)
              {
                card.setValue(Game::ACE_LOW_VALUE);
                return true;
              }
              return false;
            }
          ))
      {
        handTotal -= (Game::ACE_HIGH_VALUE - Game::ACE_LOW_VALUE);
      }
      else { break; }
    }
  }
} // namespace

namespace Game
{
  // Constructors
  Card::Card(std::string suit, fn::cdef rank, fn::u8f value) noexcept
    : m_suit{std::move(suit)}
    , m_rank{rank}
    , m_value{value}
    , m_isAce{rank == 'A'}
  {}

  // Accessors
  [[nodiscard]]
  auto Card::getSuit() const noexcept -> const std::string&
  {
    return m_suit;
  }

  [[nodiscard]]
  auto Card::getRank() const noexcept -> fn::cdef
  {
    return m_rank;
  }

  [[nodiscard]]
  auto Card::getValue() const noexcept -> fn::u8f
  {
    return m_value;
  }

  [[nodiscard]]
  auto Card::isAce() const noexcept -> bool
  {
    return m_isAce;
  }

  // Mutators
  auto Card::setValue(fn::u8f value) noexcept -> void { m_value = value; }

  // Friends
  auto operator<<(std::ostream& os, const Card& card) -> std::ostream&
  {
    os << '[' << card.getSuit() << card.getRank() << ']';
    return os;
  }
}; // namespace Game

// NOLINTNEXTLINE
auto Game::play() -> void
{
  // Reset player bank
  fn::u32f playerBank{PLAYER_STARTING_BANK};

  // Welcome message
  std::cout << "\nDealer: Welcome sir!\n";

  // Initialize deck
  std::vector<Card> deck{createDeck()};

  // Initial deck size
  const fn::size initialDeckSize{deck.size()};

  // Prepare random number generator
  std::random_device         rd{};
  std::default_random_engine eng{rd()};

  // Shuffle deck
  std::shuffle(deck.begin(), deck.end(), eng);

  // Game loop
  while (true)
  {
    // Check if player is out of chips
    if (playerBank < MIN_BET)
    {
      std::cout << "\nDealer: Sorry sir, you are out of chips!\n";
      break;
    }

    // Check if deck needs shuffling
    if (fn::narrow_cast<fn::f64>(deck.size())
        < fn::narrow_cast<fn::f64>(initialDeckSize) * SHUFFLE_THRESHOLD)
    {
      // Recreate deck
      deck = createDeck();
      std::cout << "\nPlayer: Game played with " << DECK_COUNT << " deck(s).\n";

      // Shuffle deck
      std::shuffle(deck.begin(), deck.end(), eng);
      std::cout << "Player: Deck(s) shuffled!\n";
    }

    // Start round
    std::cout << "\nDealer: Round is starting!\n";

    // Sleep
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Print bank
    std::cout << "Player: I have " << playerBank << " dollar chips.\n";

    // Get player bet
    std::cout << "\nDealer: Place your bet sir!\n";
    const fn::u32f playerBet{IO::getPlayerBet(playerBank)};

    // Initialize hands
    std::vector<Card> dealerHand{};
    std::vector<Card> playerHand{};

    // Initial deals
    for (fn::size index{}; index < 2; ++index)
    {
      // Announce card deal
      std::cout << "\nPlayer: Dealer deals " << index + 1 << ". cards.\n";

      // Deal cards
      dealerHand.push_back(deck.back());
      deck.pop_back();
      playerHand.push_back(deck.back());
      deck.pop_back();

      // Print hands
      IO::printHand("Player", playerHand, false, 0);
      IO::printHand("Dealer", dealerHand, true, 0);

      // Sleep
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    fn::u16f playerHandTotal{0};
    bool     playerBust{false};
    bool     playerTurn{true};
    while (playerTurn)
    {
      // Calculate hand total
      playerHandTotal = Math::calculateHandTotal(playerHand);

      // Check and adjust aces
      adjustAces(playerHand, playerHandTotal);

      // Print hand
      IO::printHand("\nPlayer", playerHand, false, playerHandTotal);

      // Check for blackjack
      if (playerHandTotal == BLACKJACK)
      {
        std::cout << "Dealer: Good sir, blackjack!\n";
        break;
      }

      // Check for bust
      if (playerHandTotal > BLACKJACK)
      {
        std::cout << "Dealer: Sorry sir, bust!\n";
        playerBust = {true};
        break;
      }

      // Choice
      std::cout << "Dealer: Hit or stand sir?\n";
      const auto choice{IO::getPlayerChoice()};

      // Process choice
      switch (choice)
      {
      case IO::PlayerChoice::HIT:
      {
        std::cout << "\nDealer: Alright sir, here you go!\n";
        playerHand.push_back(deck.back());
        deck.pop_back();

        // Sleep
        std::this_thread::sleep_for(std::chrono::seconds(1));
        break;
      }
      case IO::PlayerChoice::STAND:
      {
        std::cout << "\nDealer: Alright sir, standing!\n";

        // Sleep
        std::this_thread::sleep_for(std::chrono::seconds(1));
        playerTurn = {false};
        break;
      }
      }
    }

    // Check for player bust
    if (playerBust)
    {
      // Sleep
      std::this_thread::sleep_for(std::chrono::seconds(1));

      IO::printHand("\nDealer", dealerHand, false, 0);
      std::cout << "Player: You lost!\n";
      continue;
    }

    // Dealer turn
    fn::u16f dealerHandTotal{0};
    bool     dealerBust{false};
    while (true)
    {
      // Calculate hand total
      dealerHandTotal = Math::calculateHandTotal(dealerHand);

      // Check and adjust aces
      adjustAces(dealerHand, dealerHandTotal);

      // Print hand
      IO::printHand("\nDealer", dealerHand, false, dealerHandTotal);

      // Check for blackjack
      if (dealerHandTotal == BLACKJACK)
      {
        std::cout << "Dealer: Blackjack!\n";
        break;
      }

      // Check for bust
      if (dealerHandTotal > BLACKJACK)
      {
        std::cout << "Dealer: Bust!\n";
        dealerBust = true;
        break;
      }

      // Stand
      if (dealerHandTotal >= DEALER_STAND)
      {
        std::cout << "\nDealer: Standing!\n";

        // Sleep
        std::this_thread::sleep_for(std::chrono::seconds(1));
        break;
      }

      // Hit
      std::cout << "\nDealer: Hitting!\n";
      dealerHand.push_back(deck.back());
      deck.pop_back();

      // Sleep
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Check for dealer bust
    if (dealerBust)
    {
      // Sleep
      std::this_thread::sleep_for(std::chrono::seconds(1));

      IO::printHand("\nDealer", dealerHand, false, dealerHandTotal);
      std::cout << "Player: I won!\n";
      playerBank += WIN_MULTIPLIER * playerBet;
      continue;
    }

    // If no busts, compare hands
    if (playerHandTotal > dealerHandTotal)
    {
      std::cout << "\nDealer: Good sir, you won!\n";
      playerBank += WIN_MULTIPLIER * playerBet;

      // Sleep
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    else if (playerHandTotal < dealerHandTotal)
    {
      std::cout << "\nDealer: Sorry sir, you lost!\n";

      // Sleep
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    else
    {
      std::cout << "\nDealer: It's a tie sir!\n";
      playerBank += playerBet;

      // Sleep
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }
}
