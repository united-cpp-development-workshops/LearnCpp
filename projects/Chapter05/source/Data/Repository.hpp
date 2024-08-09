#pragma once

#include "Model/Dictionary.hpp"
#include "Model/Save.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>

#include <filesystem>

namespace Data
{
  /**
   * @brief Repository for dictionary data.
   */
  class Repository
  {
  public:
    /*-----------------------------------------------------------------------------------+--------*\
    *| [public]: Constructors                                                            | PUBLIC |*
    \*-----------------------------------------------------------------------------------+--------*/

    Repository(Repository&&)      = delete;
    Repository(const Repository&) = delete;

    /**
     * @brief Default constructor.
     */
    Repository() noexcept = default;

    /*-----------------------------------------------------------------------------------+--------*\
    *| [public]: Destructor                                                              | PUBLIC |*
    \*-----------------------------------------------------------------------------------+--------*/

    /**
     * @brief Default destructor.
     */
    ~Repository() noexcept = default;

    /*-----------------------------------------------------------------------------------+--------*\
    *| [public]: Operators                                                               | PUBLIC |*
    \*-----------------------------------------------------------------------------------+--------*/

    auto operator=(Repository&&) -> Repository&      = delete;
    auto operator=(const Repository&) -> Repository& = delete;

    /*-----------------------------------------------------------------------------------+--------*\
    *| [public]: Methods                                                                 | PUBLIC |*
    \*-----------------------------------------------------------------------------------+--------*/

    /**
     * @brief Saves the score.
     * @param save The data to be saved.
     */
    auto saveScore(const Model::Save& save) -> fn::none;

    /*-----------------------------------------------------------------------------------+--------*\
    *| [public]: Accessors                                                               | PUBLIC |*
    \*-----------------------------------------------------------------------------------+--------*/

    /**
     * @brief   Retrieves the dictionary.
     * @returns A mutable reference to the dictionary.
     */
    [[nodiscard]] auto getDictionary() -> Model::Dictionary&;

    /**
     * @brief   Retrieves the scores.
     * @returns A const reference to the scores.
     */
    [[nodiscard]] auto getScores() -> fn::vec<Model::Save>&;

  private:
    /*----------------------------------------------------------------------------------+---------*\
    *| [private]: Methods                                                               | PRIVATE |*
    \*----------------------------------------------------------------------------------+---------*/

    /**
     * @brief Loads the dictionary.
     */
    auto loadDictionary() -> fn::none;

    /**
     * @brief Loads the scores.
     */
    auto loadScores() -> fn::none;

    /*----------------------------------------------------------------------------------+---------*\
    *| [private]: Fields                                                                | PRIVATE |*
    \*----------------------------------------------------------------------------------+---------*/

    Model::Dictionary    m_dictionary;
    fn::bln              m_dictionaryLoaded{false};
    fn::vec<Model::Save> m_scores;
    fn::bln              m_scoresLoaded{false};
  };
} // namespace Data
