#include "pch.hpp"

#include "File/_internal/details.hpp"

#include "File/_internal/constants.hpp"
#include "Model/Dictionary.hpp"
#include "Model/Save.hpp"

#include <Foundation/concepts.hpp>
#include <Foundation/containers.hpp>
#include <Foundation/errors.hpp>
#include <Foundation/types.hpp>

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

namespace File::_internal
{
  auto loadDictionary(const std::filesystem::path& path, Model::Dictionary& dictionary) -> fn::none
  {
    // Check if the file exists
    if (not std::filesystem::exists(path))
    {
      // Throw an exception
      throw fn::FileError{"File doesn't exist!", std::format("Path was '{}'.", path.string())};
    }

    // Open the file
    std::ifstream file{path};

    // Check if the file is open
    if (not file.is_open())
    {
      // Throw an exception
      throw fn::FileError{"Failed to open file!", std::format("Path was '{}'.", path.string())};
    }

    // Read the file line by line
    fn::str line;
    while (std::getline(file, line))
    {
      // ---------- PARSING LINE ---------- //

      // Parse the line
      std::istringstream stream{line};

      // Read the word
      fn::str word;
      if (not std::getline(stream, word, CSV_DELIMITER))
      {
        // Throw if failed to parse the word
        throw fn::FileError{
          "Failed to parse the word!",
          std::format("File was '{}' and line was '{}'.", path.filename().string(), line)
        };
      }

      // Count characters
      const auto wordLength{fn::narrow_cast<fn::i16l>(word.length())};

      // Read the definition
      fn::str definition;
      if (not std::getline(stream, definition))
      {
        // Throw if failed to parse the definition
        throw fn::FileError{
          "Failed to parse the definition!",
          std::format("File was '{}' and line was '{}'.", path.filename().string(), line)
        };
      }

      // ---------- ADDING TO DICTIONARY ---------- //

      // Try to add the length to the dictionary
      const auto [lengthIt, isLengthAdded]{dictionary.try_emplace(wordLength)};
      std::ignore = isLengthAdded;

      // Try to add the entry to the length
      const auto [entryIt, isEntryAdded]{lengthIt->second.try_emplace(word)};
      std::ignore = isEntryAdded;

      // Add the definition to the entry
      entryIt->second.emplace_back(definition);
    }
  }

  auto loadScores(const std::filesystem::path& path, fn::vec<Model::Save>& saves) -> fn::none
  {
    // Check if the file exists
    if (not std::filesystem::exists(path))
    {
      // Throw an exception
      throw fn::FileError{"File doesn't exist!", std::format("Path was '{}'.", path.string())};
    }

    // Open the file
    std::ifstream file{path};

    // Check if the file is open
    if (not file.is_open())
    {
      // Throw an exception
      throw fn::FileError{"Failed to open file!", std::format("Path was '{}'.", path.string())};
    }

    // Read the file line by line
    fn::str line;
    while (std::getline(file, line))
    {
      // ---------- PARSING LINE ---------- //

      // Parse the line
      std::istringstream stream{line};

      // Read the word
      fn::str username;
      if (not std::getline(stream, username, CSV_DELIMITER))
      {
        // Throw if failed to parse the word
        throw fn::FileError{
          "Failed to parse the username!",
          std::format("File was '{}' and line was '{}'.", path.filename().string(), line)
        };
      }

      // Read the score
      fn::i16f score{};
      if (not(stream >> score))
      {
        // Throw if failed to parse the word
        throw fn::FileError{
          "Failed to parse the score!",
          std::format("File was '{}' and line was '{}'.", path.filename().string(), line)
        };
      }

      // Skip the delimiter
      stream.ignore();

      // Read the timestamp
      fn::str timestamp;
      if (not std::getline(stream, timestamp))
      {
        // Throw if failed to parse the word
        throw fn::FileError{
          "Failed to parse the timestamp!",
          std::format("File was '{}' and line was '{}'.", path.filename().string(), line)
        };
      }

      // ---------- ADDING TO DICTIONARY ---------- //

      // Add the save to the vector
      saves.emplace_back(username, score, timestamp);
    }
  }

  auto saveScore(const std::filesystem::path& path, const Model::Save& save) -> fn::none
  {
    // Open the file
    std::ofstream file{path, std::ios::app};

    // Check if the file is open
    if (not file.is_open())
    {
      // Throw an exception
      throw fn::FileError{"Failed to open file!", std::format("Path was '{}'.", path.string())};
    }

    // Write save to file
    file << save.username << CSV_DELIMITER << save.score << CSV_DELIMITER << save.timestamp << '\n';
  }
} // namespace File::_internal
