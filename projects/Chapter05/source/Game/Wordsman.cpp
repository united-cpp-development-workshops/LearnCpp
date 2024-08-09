#include "pch.hpp"

#include "Game/Wordsman.hpp"

#include "Data/Repository.hpp"
#include "Game/_internal/constants.hpp"
#include "Game/_internal/details.hpp"
#include "IO/io.ipp"
#include "Text/text.hpp"

#include <Foundation/errors.hpp>
#include <Foundation/types.hpp>

#include <algorithm>
#include <chrono>
#include <format>
#include <locale>
#include <memory>
#include <thread>
#include <utility>

namespace Game
{
  /*-------------------------------------------------------------------------------------+--------*\
  *| [public]: Constructors                                                              | PUBLIC |*
  \*-------------------------------------------------------------------------------------+--------*/

  Wordsman::Wordsman(std::shared_ptr<Data::Repository> repository) noexcept
    : m_repository{std::move(repository)}
    , m_score{}
    , m_passRights{_internal::PASS_RIGHTS}
  {}

  /*-------------------------------------------------------------------------------------+--------*\
  *| [public]: Methods                                                                   | PUBLIC |*
  \*-------------------------------------------------------------------------------------+--------*/

  auto Wordsman::run() -> fn::none
  {
    // Main loop
    while (true)
    {
      // Print main menu
      printMainMenu();

      // Get the user input
      fn::i16l option{};
      IO::printInputPrompt("Enter an option.");
      std::cin >> option;

      // Process the user input
      switch (option)
      {
      case _internal::PLAY_OPTION:
      {
        play();
        break;
      }
      case _internal::LEARN_OPTION:
      {
        learn();
        break;
      }
      case _internal::SCORES_OPTION:
      {
        scores();
        break;
      }
      case _internal::EXIT_OPTION:
      {
        return;
      }
      default:
      {
        // Input was invalid print error message
        IO::printErrorMessage("Invalid option!");
        break;
      }
      }
    }
  }

  /*------------------------------------------------------------------------------------+---------*\
  *| [private]: Methods                                                                 | PRIVATE |*
  \*------------------------------------------------------------------------------------+---------*/

  auto Wordsman::printMainMenu() const -> fn::none
  {
    IO::printSectionDivider();

    std::cout << "      /--+---+---+---+---+---+---+---+---+--\\\n";
    std::cout << "     <=*=| W | O | R | D | S | M | A | N |=*=>\n";
    std::cout << "      \\--+---+---+---+---+---+---+---+---+--/\n";
    IO::printSectionDivider();
    IO::printTitle("MAIN MENU");
    IO::printParagraph("Welcome! What would you like to do?");
    IO::printMenuOption("Play  ", "Start the game.", _internal::PLAY_OPTION);
    IO::printMenuOption("Learn ", "Learn the rules.", _internal::LEARN_OPTION);
    IO::printMenuOption("Scores", "Show the score table.", _internal::SCORES_OPTION);
    IO::printMenuOption("Exit  ", "Exit the game.", _internal::EXIT_OPTION);
  }

  auto Wordsman::resetState() noexcept -> fn::none
  {
    // Reset the score
    m_score = {};

    // Reset pass rights
    m_passRights = {_internal::PASS_RIGHTS};
  }

  auto Wordsman::play() -> fn::none
  {
    // Check if the repository was initialized
    if (m_repository == nullptr)
    {
      throw fn::StateError{"The repository was not initialized!", "Repository was 'nullptr'."};
    }

    // Get the dictionary
    auto& dictionary{m_repository->getDictionary()};

    // Reset the game state
    resetState();

    // Game loop
    fn::i16l round{_internal::ROUND_01};
    while (round <= _internal::ROUND_XX)
    {
      // Play the round
      if (not playRound(round, selectEntry(dictionary, round)))
      {
        continue;
      }

      // Increment the round
      ++round;
    }

    // Endgame menu
    while (true)
    {
      // Print main menu
      printEndgameMenu();

      // Get the user input
      fn::i16l option{};
      IO::printInputPrompt("Enter an option.");
      std::cin >> option;

      // Process the user input
      switch (option)
      {
      case _internal::SAVE_OPTION:
      {
        save();
        return;
      }
      case _internal::PLAY_AGAIN_OPTION:
      {
        play();
        return;
      }
      case _internal::EXIT_TO_MAIN_MANU:
      {
        return;
      }
      default:
      {
        // Input was invalid print error message
        IO::printErrorMessage("Invalid option!");
        break;
      }
      }
    }
  }

  [[nodiscard]] auto Wordsman::playRound(const fn::i16l round, const Model::Entry& entry) -> fn::bln
  {
    // Create the obfuscated word
    fn::str obfuscatedWord{entry.word};

    // Obfuscate the word
    std::ranges::transform(
      obfuscatedWord,
      obfuscatedWord.begin(),
      [](const fn::cdef c) noexcept -> fn::cdef
      {
        // Only obfuscate letters
        return std::isalpha(c, std::locale()) ? _internal::OBFUSCATION_CHARACTER : c;
      }
    );

    while (true)
    {
      // Print the round
      IO::printSectionDivider();
      IO::printTitle(std::format("ROUND {}/{}", round, _internal::ROUND_XX));
      IO::printSubtitle("SCORES", std::format("{}/{}", m_score, _internal::MAX_SCORE));
      IO::printSubtitle("PASSES", std::format("{}/{}", m_passRights, _internal::PASS_RIGHTS));

      // Pre-calculate the indexes of obfuscation characters
      const auto starIndexes{Text::getObfuscatedIndexes(obfuscatedWord)};

      // Print entry
      IO::printEntry(obfuscatedWord, entry.definitions);

      // Check for round end
      if (starIndexes.size() == 0)
      {
        // Print the message
        IO::printInfoMessage("Round finished!");

        // Wait 1 second
        std::this_thread::sleep_for(std::chrono::seconds{1});

        // Exit the loop
        return true;
      }

      // Input loop
      fn::bln validInput{false};
      while (not validInput)
      {
        // Print game menu
        printGameMenu();

        // Get the user input
        fn::i16l option{};
        IO::printInputPrompt("Enter an option.");
        std::cin >> option;

        switch (option)
        {
        case _internal::ASK_LETTER_OPTION:
        {
          // Reveal one letter
          const auto indexToReveal{starIndexes.at(0)};
          obfuscatedWord.at(indexToReveal) = {entry.word.at(indexToReveal)};

          // Exit the loop
          validInput = {true};
          break;
        }
        case _internal::PASS_OPTION:
        {
          // Check if has pass rights
          if (m_passRights == 0)
          {
            IO::printErrorMessage("No pass rights left!");
          }
          else
          {
            IO::printInfoMessage("Word passed.");

            // Decrement pass rights
            --m_passRights;

            // Exit the method
            return false;
          }
          break;
        }
        case _internal::GUESS_OPTION:
        {
          // Handle the guess
          _internal::handleGuess(entry.word, obfuscatedWord, m_score);

          // Wait 1 second
          std::this_thread::sleep_for(std::chrono::seconds{1});

          // Exit the loop
          validInput = {true};
          break;
        }
        default:
        {
          // Input was invalid print error message
          IO::printErrorMessage("Invalid option!");
          validInput = {false};
          break;
        }
        }
      }
    }
  }

  auto Wordsman::printGameMenu() const -> fn::none
  {
    IO::printSectionDivider();
    IO::printTitle("ACTIONS");
    IO::printParagraph("What would you like to do?");
    IO::printMenuOption("Hint ", "Ask for a letter.", _internal::ASK_LETTER_OPTION);
    IO::printMenuOption("Pass ", "Pass this word.", _internal::PASS_OPTION);
    IO::printMenuOption("Guess", "Guess the word.", _internal::GUESS_OPTION);
  }

  [[nodiscard]] auto Wordsman::selectEntry(Model::Dictionary& dictionary, const fn::i16l round)
    const -> Model::Entry
  {
    // Create the random engine
    std::default_random_engine randomEngine{std::random_device{}()};

    // Select the next entry
    const auto wordLength{_internal::getRoundWordLength(round)};

    // ---------- FIND ---------- //

    // Make sure dictionary contains this length
    if (not dictionary.contains(wordLength))
    {
      // Throw the error
      throw fn::StateError{
        "There are no words with this length in the dictionary!",
        std::format("The length was '{}'.", wordLength)
      };
    }

    // Get the mutable reference to the entries
    auto& entries{dictionary.at(wordLength)};

    // Make sure there are entries for this length
    if (entries.empty())
    {
      // Throw the error
      throw fn::StateError{"Empty entries map!", std::format("The length was '{}'.", wordLength)};
    }

    // ---------- SELECT ---------- //

    // Get a random entry iterator
    const auto entryIt{std::next(
      entries.begin(),
      std::uniform_int_distribution<fn::ptrd>{0, std::ssize(entries) - 1}(randomEngine)
    )};

    // ---------- CONSTRUCT ---------- //

    // Construct the entry
    const Model::Entry entry{.word{entryIt->first}, .definitions{entryIt->second}};

    // ---------- CLEAN ---------- //

    // Remove entry
    entries.erase(entryIt->first);

    // Remove length if no entries left
    if (entries.empty())
    {
      dictionary.erase(wordLength);
    }

    // Return the entry
    return entry;
  }

  auto Wordsman::printEndgameMenu() const -> fn::none
  {
    IO::printSectionDivider();
    IO::printTitle("ENDGAME");
    IO::printSubtitle("SCORE", std::format("{}/{}", m_score, _internal::MAX_SCORE));
    IO::printSubtitle("PASSES", std::format("{}/{}", m_passRights, _internal::PASS_RIGHTS));
    IO::printParagraph("What would you like to do?");
    IO::printMenuOption("Save", "Save the score.", _internal::SAVE_OPTION);
    IO::printMenuOption("Play", "Play again.", _internal::PLAY_AGAIN_OPTION);
    IO::printMenuOption("Exit", "Exit to main menu.", _internal::EXIT_TO_MAIN_MANU);
  }

  auto Wordsman::save() const -> fn::none
  {
    // Check if the repository was initialized
    if (m_repository == nullptr)
    {
      throw fn::StateError{"The repository was not initialized!", "Repository was 'nullptr'."};
    }

    // Get the username
    fn::str username;
    IO::printInputPrompt("Enter your username.");
    std::getline(std::cin >> std::ws, username);

    // Replace not allowed characters
    std::ranges::replace_if(
      username,
      [](const fn::cdef c) -> fn::bln
      {
        return c == ',';
      },
      '_'
    );

    // Get the current time
    const auto timestamp{std::format(
      "{:%Y/%m/%d %R}",
      std::chrono::zoned_time{std::chrono::current_zone(), std::chrono::system_clock::now()}
    )};

    // Save the score
    m_repository->saveScore({username, m_score, timestamp});
  }

  auto Wordsman::learn() const -> fn::none
  {
    IO::printSectionDivider();
    IO::printTitle("RULES");
    IO::printParagraph("These are the rules:");
    IO::printInfoMessage(std::format(
      "The game consists of {} rounds. Each round has a word with a specific length.",
      _internal::ROUND_XX
    ));
    IO::printInfoMessage("You are required to guess these words by their definitions.");
    IO::printInfoMessage("There may be one or several definitions for a word.");
    IO::printInfoMessage("You may ask for a letter in the word or guess it directly.");
    IO::printInfoMessage(std::format(
      "If you are stuck, you may pass the word, but you have {} rights.", _internal::PASS_RIGHTS
    ));
    IO::printInfoMessage("You will receive points for each correct guess.");
    IO::printInfoMessage("Points are calculated by the number of obfuscated letters you've guessed."
    );
    IO::printInfoMessage(
      std::format("Wrong guesses will reduce {} amount of points.", _internal::WRONG_GUESS_PENALTY)
    );
    IO::printInfoMessage("Good luck!");
  }

  auto Wordsman::scores() const -> fn::none
  {
    // Check if the repository was initialized
    if (m_repository == nullptr)
    {
      throw fn::StateError{"The repository was not initialized!", "Repository was 'nullptr'."};
    }

    // Get scores
    auto& scores{m_repository->getScores()};

    // Sort by score
    std::ranges::sort(
      scores,
      [](const Model::Save& lhs, const Model::Save& rhs) -> fn::bln
      {
        return lhs.score > rhs.score;
      }
    );

    // Max column lengths
    auto maxUsernameColLen{fn::str{_internal::USERNAME_HEADER}.length()};
    auto maxScoreColLen{fn::str{_internal::SCORE_HEADER}.length()};
    auto maxTimestampColLen{fn::str{_internal::TIMESTAMP_HEADER}.length()};

    for (const auto& score : scores)
    {
      // Get column widths
      maxUsernameColLen  = {std::max(maxUsernameColLen, score.username.length())};
      maxScoreColLen     = {std::max(maxScoreColLen, std::to_string(score.score).length())};
      maxTimestampColLen = {std::max(maxTimestampColLen, score.timestamp.length())};
    }

    // Print title
    IO::printSectionDivider();
    IO::printTitle("SCORES");

    // Print table header
    std::cout << "     +-" << fn::str(maxUsernameColLen, '-') << "-+-"
              << fn::str(maxScoreColLen, '-') << "-+-" << fn::str(maxTimestampColLen, '-')
              << "-+\n";

    std::cout << "     | ";
    std::cout << std::format("{:<{}}", _internal::USERNAME_HEADER, maxUsernameColLen);
    std::cout << " | ";
    std::cout << std::format("{:<{}}", _internal::SCORE_HEADER, maxScoreColLen);
    std::cout << " | ";
    std::cout << std::format("{:<{}}", _internal::TIMESTAMP_HEADER, maxTimestampColLen);
    std::cout << " |\n";

    std::cout << "     +-" << fn::str(maxUsernameColLen, '-') << "-+-"
              << fn::str(maxScoreColLen, '-') << "-+-" << fn::str(maxTimestampColLen, '-')
              << "-+\n";

    // Print table rows
    for (const auto& score : scores)
    {
      std::cout << "     | ";
      std::cout << std::format("{:<{}}", score.username, maxUsernameColLen);
      std::cout << " | ";
      std::cout << std::format("{:<{}}", score.score, maxScoreColLen);
      std::cout << " | ";
      std::cout << std::format("{:<{}}", score.timestamp, maxTimestampColLen);
      std::cout << " |\n";

      std::cout << "     +-" << fn::str(maxUsernameColLen, '-') << "-+-"
                << fn::str(maxScoreColLen, '-') << "-+-" << fn::str(maxTimestampColLen, '-')
                << "-+\n";
    }
  }
} // namespace Game
