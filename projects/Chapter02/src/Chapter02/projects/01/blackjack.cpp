#include "Chapter02/projects/01/blackjack.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <string>
#include <thread>
#include <vector>

constexpr unsigned int PLAYER_STARTING_BANK{1'000};
constexpr std::size_t  DECK_COUNT{6};
constexpr float        SHUFFLE_THRESHOLD{0.5f};
constexpr unsigned int BLACKJACK{21};
constexpr unsigned int DEALER_STAND{17};
constexpr unsigned int MIN_BET{10};
constexpr unsigned int WIN_MULTIPLIER{2};

unsigned int playerBank{PLAYER_STARTING_BANK};

struct Card
{
public:
  Card(std::string suit, char rank, unsigned int value)
    : suit{suit}
    , rank{rank}
    , value{value}
    , isAce{rank == 'A'}
  {}

public:
  std::string  suit;
  char         rank;
  unsigned int value;
  bool         isAce;

public:
  static friend std::ostream& operator<<(std::ostream& os, const Card& card)
  {
    os << '[' << card.suit << card.rank << ']';
    return os;
  }
};

static std::vector<Card> createDeck()
{
  // Initialize deck
  std::vector<Card> deck{};

  // Create deck(s)
  for (std::size_t i{}; i < DECK_COUNT; ++i)
  {
    // Loop through suits
    for (const auto suit : {"♥", "♦", "♣", "♠"})
    {
      // Loop through ranks
      for (const auto rank :
           {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'})
      {
        unsigned int value{};

        // Assign value to rank
        if (rank == 'T' or rank == 'J' or rank == 'Q' or rank == 'K')
        {
          value = 10;
        }
        else if (rank == 'A')
        {
          value = 11;
        }
        else
        {
          value = static_cast<unsigned int>(rank - '0');
        }

        // Add card to deck
        deck.push_back(Card(suit, rank, value));
      }
    }
  }
  return deck;
}

static unsigned int getPlayerBet()
{
  // Bet input
  unsigned int bet{};

  // Bet validation flags
  bool exceedsMinBet{false};
  bool canAffordBet{false};

  // Input validation loop
  while (not(canAffordBet and exceedsMinBet))
  {
    // Clear input buffer
    std::cin.clear();
    if (std::cin.rdbuf()->in_avail())
    {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Get bet
    std::cout << "Player: ";
    std::cin >> bet;

    // Validate if bet exceeds minimum bet
    exceedsMinBet = bet >= MIN_BET;
    if (not exceedsMinBet)
    {
      std::cout << "Dealer: Minimum bet is " << MIN_BET << " sir!\n";
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

  return bet;
}

static unsigned int calculateHandTotal(const std::vector<Card>& hand)
{
  return std::reduce(
    hand.begin(),
    hand.end(),
    0u,
    [](unsigned int total, const Card& card) { return total + card.value; }
  );
}

static void printHand(
  const std::string&       holder,
  const std::vector<Card>& hand,
  const bool               hideFirstCard,
  unsigned int             adjustedHandTotal = 0
)
{
  // Print holder
  std::cout << holder << ": ";

  // Print hand
  for (std::size_t i{}; i < hand.size(); ++i)
  {
    if (i == 0 and hideFirstCard)
    {
      // Hide first card if flag is set
      std::cout << "[??]";
    }
    else
    {
      // Print card
      std::cout << hand[i];
    }
  }

  // Print hand
  if (not hideFirstCard)
  {
    if (adjustedHandTotal == 0)
    {
      adjustedHandTotal = calculateHandTotal(hand);
    }
    std::cout << " > " << adjustedHandTotal << '\n';
  }
  else
  {
    std::cout << " > ?\n";
  }
}

enum class PlayerChoice
{
  HIT,
  STAND
};

static PlayerChoice getPlayerChoice()
{
  // Player choice input
  std::string choice{};

  // Input validation loop
  while (true)
  {
    // Clear input buffer
    std::cin.clear();
    if (std::cin.rdbuf()->in_avail())
    {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Get choice
    std::cout << "Player: ";
    std::cin >> choice;

    // Validate choice
    if (std::tolower(choice[0]) == 'h')
    {
      return PlayerChoice::HIT;
    }
    else if (std::tolower(choice[0]) == 's')
    {
      return PlayerChoice::STAND;
    }
    else
    {
      std::cout << "Dealer: Place say hit or stand sir!\n";
    }
  }
}

static void adjustAces(std::vector<Card>& hand, unsigned int& handTotal)
{
  while (handTotal > BLACKJACK)
  {
    // Check for aces and adjust value
    if (std::any_of(hand.begin(), hand.end(), [](Card& card) {
          if (card.isAce and card.value == 11)
          {
            card.value = 1;
            return true;
          }
          return false;
        }))
    {
      handTotal -= 10;
    }
    else
    {
      break;
    }
  }
}

void playBlackjack()
{
  // Reset player bank
  playerBank = PLAYER_STARTING_BANK;

  // Welcome message
  std::cout << "\nDealer: Welcome sir!\n";

  // Initialize deck
  std::vector<Card> deck{createDeck()};

  // Initial deck size
  std::size_t initialDeckSize{deck.size()};

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
    if (deck.size() < initialDeckSize * SHUFFLE_THRESHOLD)
    {
      // Recreate deck
      deck = createDeck();
      std::cout << "\nObserved: Game played with " << DECK_COUNT
                << " deck(s).\n";

      // Shuffle deck
      std::shuffle(deck.begin(), deck.end(), eng);
      std::cout << "Observed: Deck(s) shuffled!\n";
    }

    // Start round
    std::cout << "\nDealer: Round is starting!\n";

    // Sleep
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Print bank
    std::cout << "Observed: You have " << playerBank << " dollar chips.\n";

    // Get player bet
    std::cout << "\nDealer: Place your bet sir!\n";
    unsigned int playerBet{getPlayerBet()};

    // Initialize hands
    std::vector<Card> dealerHand{};
    std::vector<Card> playerHand{};

    // Initial deals
    for (std::size_t i{}; i < 2; ++i)
    {
      // Announce card deal
      std::cout << "\nObserved: Dealer deals " << i + 1 << ". cards.\n";

      // Deal cards
      dealerHand.push_back(deck.back());
      deck.pop_back();
      playerHand.push_back(deck.back());
      deck.pop_back();

      // Print hands
      printHand("Player", playerHand, false);
      printHand("Dealer", dealerHand, true);

      // Sleep
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    unsigned int playerHandTotal{0};
    bool         playerBust{false};
    while (true)
    {
      // Calculate hand total
      playerHandTotal = calculateHandTotal(playerHand);

      // Check and adjust aces
      adjustAces(playerHand, playerHandTotal);

      // Print hand
      printHand("\nPlayer", playerHand, false, playerHandTotal);

      // Check for end of round conditions
      if (playerHandTotal == BLACKJACK)
      {
        std::cout << "Dealer: Good sir, blackjack!\n";
        break;
      }
      else if (playerHandTotal > BLACKJACK)
      {
        std::cout << "Dealer: Sorry sir, bust!\n";
        playerBust = true;
        break;
      }

      // Choice
      std::cout << "Dealer: Hit or stand sir?\n";
      PlayerChoice choice{getPlayerChoice()};

      // Process choice
      switch (choice)
      {
      case PlayerChoice::HIT:
        std::cout << "\nDealer: Alright sir, here you go!\n";
        playerHand.push_back(deck.back());
        deck.pop_back();

        // Sleep
        std::this_thread::sleep_for(std::chrono::seconds(1));
        break;
      case PlayerChoice::STAND:
        std::cout << "\nDealer: Alright sir, standing!\n";

        // Sleep
        std::this_thread::sleep_for(std::chrono::seconds(1));
        goto playerTurnOver;
      }
    }
  playerTurnOver:

    // Check for player bust
    if (playerBust)
    {
      // Sleep
      std::this_thread::sleep_for(std::chrono::seconds(1));

      printHand("\nDealer", dealerHand, false);
      std::cout << "Observed: You lost!\n";
      continue;
    }

    // Dealer turn
    unsigned int dealerHandTotal{0};
    bool         dealerBust{false};
    while (true)
    {
      // Calculate hand total
      dealerHandTotal = calculateHandTotal(dealerHand);

      // Check and adjust aces
      adjustAces(dealerHand, dealerHandTotal);

      // Print hand
      printHand("\nDealer", dealerHand, false, dealerHandTotal);

      // Check for end of round conditions
      if (dealerHandTotal == BLACKJACK)
      {
        std::cout << "Dealer: Blackjack!\n";
        break;
      }
      else if (dealerHandTotal > BLACKJACK)
      {
        std::cout << "Dealer: Bust!\n";
        dealerBust = true;
        break;
      }

      // Choice
      if (dealerHandTotal >= DEALER_STAND)
      {
        std::cout << "\nDealer: Standing!\n";

        // Sleep
        std::this_thread::sleep_for(std::chrono::seconds(1));
        break;
      }
      else
      {
        std::cout << "\nDealer: Hitting!\n";
        dealerHand.push_back(deck.back());
        deck.pop_back();

        // Sleep
        std::this_thread::sleep_for(std::chrono::seconds(1));
      }
    }

    // Check for dealer bust
    if (dealerBust)
    {
      // Sleep
      std::this_thread::sleep_for(std::chrono::seconds(1));

      printHand("\nDealer", dealerHand, false, dealerHandTotal);
      std::cout << "Observed: You won!\n";
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
