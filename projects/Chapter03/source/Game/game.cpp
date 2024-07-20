#include "pch.hpp"

#include "Game/game.ipp"

#include "Foundation/Support/narrow.ipp"
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
  auto createDeck(std::vector<Game::Card>& deck) -> fn::none
  {
    // Loop through suits
    for (const fn::cstr suit : {"♥", "♦", "♣", "♠"})
    {
      // Loop through ranks
      for (const fn::cdef rank :
           {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'})
      {
        // Initialize value
        fn::u16f value{};

        // Assign value to rank
        if (rank == 'T' or rank == 'J' or rank == 'Q' or rank == 'K')
        {
          value = {Game::COURT_CARD_VALUE};
        }
        else if (rank == 'A') { value = {Game::ACE_HIGH_VALUE}; }
        else { value = fn::narrow_cast<fn::u16f>(rank - '0'); }

        // Add card to deck
        deck.emplace_back(std::string{suit}, rank, value);
      }
    }
  }

  auto createDecks() -> std::vector<Game::Card>
  {
    // Initialize deck
    std::vector<Game::Card> deck{};

    // Create deck(s)
    for (fn::size index{}; index < Game::DECK_COUNT; ++index)
    {
      createDeck(deck);
    }
    return deck;
  }

  auto adjustAces(std::vector<Game::Card>& hand, fn::u16f& handTotal) noexcept
    -> fn::none
  {
    while (handTotal > Game::BLACKJACK)
    {
      // Check for aces and adjust value
      if (std::ranges::any_of(
            hand,
            [](Game::Card& card) noexcept
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

  [[nodiscard]]
  auto playPlayerRound(
    std::vector<Game::Card>& deck, std::vector<Game::Card>& hand
  ) -> std::pair<fn::u16f, fn::bln>
  {
    fn::u16f score{};
    while (true)
    {
      // Calculate hand total
      score = {Math::calculateScore(hand)};

      // Check and adjust aces
      adjustAces(hand, score);

      // Print hand
      IO::printHand("\nPlayer", hand, false, score);

      // Check for blackjack
      if (score == Game::BLACKJACK)
      {
        std::cout << "Dealer: Good sir, blackjack!\n";
        return {score, false};
      }

      // Check for bust
      if (score > Game::BLACKJACK)
      {
        std::cout << "Dealer: Sorry sir, bust!\n";
        return {score, true};
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
        hand.push_back(deck.back());
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
        return {score, false};
      }
      }
    }
  }

  [[nodiscard]]
  auto playDealerRound(
    std::vector<Game::Card>& deck, std::vector<Game::Card>& hand
  ) -> std::pair<fn::u16f, fn::bln>
  {
    fn::u16f score{};
    while (true)
    {
      // Calculate hand total
      score = {Math::calculateScore(hand)};

      // Check and adjust aces
      adjustAces(hand, score);

      // Print hand
      IO::printHand("\nDealer", hand, false, score);

      // Check for blackjack
      if (score == Game::BLACKJACK)
      {
        std::cout << "Dealer: Blackjack!\n";
        return {score, false};
      }

      // Check for bust
      if (score > Game::BLACKJACK)
      {
        std::cout << "Dealer: Bust!\n";
        return {score, true};
      }

      // Stand
      if (score >= Game::DEALER_STAND)
      {
        std::cout << "\nDealer: Standing!\n";

        // Sleep
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return {score, false};
      }

      // Hit
      std::cout << "\nDealer: Hitting!\n";
      hand.push_back(deck.back());
      deck.pop_back();

      // Sleep
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }

  auto playRound(std::vector<Game::Card>& deck, fn::u32f& playerBank)
    -> fn::none
  {
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
    std::vector<Game::Card> dealerHand{};
    std::vector<Game::Card> playerHand{};

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

    // Player turn
    const auto [playerScore, playerBusted]{playPlayerRound(deck, playerHand)};

    // Check for player bust
    if (playerBusted)
    {
      // Sleep
      std::this_thread::sleep_for(std::chrono::seconds(1));

      IO::printHand("\nDealer", dealerHand, false, 0);
      std::cout << "Player: You lost!\n";
      return;
    }

    // Dealer turn
    const auto [dealerScore, dealerBusted]{playDealerRound(deck, dealerHand)};

    // Check for dealer bust
    if (dealerBusted)
    {
      // Sleep
      std::this_thread::sleep_for(std::chrono::seconds(1));

      IO::printHand("\nDealer", dealerHand, false, dealerScore);
      std::cout << "Player: I won!\n";
      playerBank += Game::WIN_MULTIPLIER * playerBet;
      return;
    }

    // If no busts, compare hands
    if (playerScore > dealerScore)
    {
      std::cout << "\nDealer: Good sir, you won!\n";
      playerBank += Game::WIN_MULTIPLIER * playerBet;

      // Sleep
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    else if (playerScore < dealerScore)
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
} // namespace

namespace Game
{
  // Constructors
  Card::Card(std::string&& suit, fn::cdef rank, fn::u8f value) noexcept
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
  auto Card::getValue() const noexcept -> fn::u16f
  {
    return m_value;
  }

  [[nodiscard]]
  auto Card::isAce() const noexcept -> fn::bln
  {
    return m_isAce;
  }

  // Mutators
  auto Card::setValue(fn::u8f value) noexcept -> fn::none { m_value = value; }
}; // namespace Game

// NOLINTNEXTLINE
auto Game::play() -> fn::none
{
  // Reset player bank
  fn::u32f playerBank{PLAYER_STARTING_BANK};

  // Welcome message
  std::cout << "\nDealer: Welcome sir!\n";

  // Initialize deck
  std::vector<Card> deck{createDecks()};

  // Initial deck size
  const fn::size initialDeckSize{deck.size()};

  // Prepare random number generator
  std::default_random_engine eng{std::random_device{}()};

  // Shuffle deck
  std::shuffle(deck.begin(), deck.end(), eng);

  // Game loop
  while (true)
  {
    // Check if player is out of chips
    if (playerBank < Game::MIN_BET)
    {
      std::cout << "\nDealer: Sorry sir, you are out of chips!\n";
      break;
    }

    // Check if deck needs shuffling
    if (fn::narrow_cast<fn::f64>(deck.size())
        < fn::narrow_cast<fn::f64>(initialDeckSize) * SHUFFLE_THRESHOLD)
    {
      // Recreate deck
      deck = {createDecks()};
      std::cout << "\nPlayer: Game played with " << DECK_COUNT << " deck(s).\n";

      // Shuffle deck
      std::shuffle(deck.begin(), deck.end(), eng);
      std::cout << "Player: Deck(s) shuffled!\n";
    }

    // Play round
    playRound(deck, playerBank);
  }
}
