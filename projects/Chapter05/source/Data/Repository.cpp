#include "pch.hpp"

#include "Data/Repository.hpp"

#include "File/file.ipp"
#include "IO/io.ipp"
#include "Model/Dictionary.hpp"
#include "Model/Save.hpp"

#include <Foundation/types.hpp>

#include <filesystem>
#include <iostream>

namespace Data
{
  /*-------------------------------------------------------------------------------------+--------*\
  *| [public]: Methods                                                                   | PUBLIC |*
  \*-------------------------------------------------------------------------------------+--------*/

  auto Repository::saveScore(const Model::Save& save) -> fn::none
  {
    // Check if the scores need to be loaded
    if (not m_scoresLoaded)
    {
      loadScores();
    }

    // Log saving the score
    IO::printLoadingMessage("Saving the score...");

    // Add to the cache
    m_scores.push_back(save);

    // Save the score
    File::save(save);
  }

  /*-------------------------------------------------------------------------------------+--------*\
  *| [public]: Accessors                                                                 | PUBLIC |*
  \*-------------------------------------------------------------------------------------+--------*/

  auto Repository::getDictionary() -> Model::Dictionary&
  {
    // Check if the dictionary needs to be loaded
    if (not m_dictionaryLoaded)
    {
      loadDictionary();
    }

    // Return the dictionary
    return m_dictionary;
  }

  auto Repository::getScores() -> fn::vec<Model::Save>&
  {
    // Check if the scores need to be loaded
    if (not m_scoresLoaded)
    {
      loadScores();
    }

    // Return the scores
    return m_scores;
  }

  /*------------------------------------------------------------------------------------+---------*\
  *| [private]: Methods                                                                 | PRIVATE |*
  \*------------------------------------------------------------------------------------+---------*/

  auto Repository::loadDictionary() -> fn::none
  {
    // Log loading the dictionary
    IO::printLoadingMessage("Loading the dictionary...");

    // Load the dictionary
    File::load(m_dictionary);

    // Update the flag
    m_dictionaryLoaded = {true};
  }

  auto Repository::loadScores() -> fn::none
  {
    // Log loading the scores
    IO::printLoadingMessage("Loading the scores...");

    // Load the scores
    File::load(m_scores);

    // Update the flag
    m_scoresLoaded = {true};
  }
} // namespace Data
