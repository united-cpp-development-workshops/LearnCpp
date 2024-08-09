#pragma once

#include "Data/Repository.hpp"
#include "Game/_internal/constants.hpp"
#include "Model/Dictionary.hpp"
#include "Model/Entry.hpp"

#include <Foundation/types.hpp>

#include <memory>
#include <random>

namespace Game
{
  class Wordsman
  {
  public:
    /*-----------------------------------------------------------------------------------+--------*\
    *| [public]: Constructors                                                            | PUBLIC |*
    \*-----------------------------------------------------------------------------------+--------*/

    Wordsman(Wordsman&&)      = delete;
    Wordsman(const Wordsman&) = delete;

    /**
     * @brief Default constructor.
     */
    Wordsman() noexcept = default;

    /**
     * @brief Constructor.
     * @param repository Repository for dictionary data.
     */
    explicit Wordsman(std::shared_ptr<Data::Repository> repository) noexcept;

    /*-----------------------------------------------------------------------------------+--------*\
    *| [public]: Destructor                                                              | PUBLIC |*
    \*-----------------------------------------------------------------------------------+--------*/

    /**
     * @brief Default destructor.
     */
    ~Wordsman() noexcept = default;

    /*-----------------------------------------------------------------------------------+--------*\
    *| [public]: Operators                                                               | PUBLIC |*
    \*-----------------------------------------------------------------------------------+--------*/

    auto operator=(Wordsman&&) -> Wordsman&      = delete;
    auto operator=(const Wordsman&) -> Wordsman& = delete;

    /*-----------------------------------------------------------------------------------+--------*\
    *| [public]: Methods                                                                 | PUBLIC |*
    \*-----------------------------------------------------------------------------------+--------*/

    /**
     * @brief  Run the Wordsman.
     */
    auto run() -> fn::none;

  private:
    /*----------------------------------------------------------------------------------+---------*\
    *| [private]: Methods                                                               | PRIVATE |*
    \*----------------------------------------------------------------------------------+---------*/

    /**
     * @brief Prints the game menu.
     */
    auto printMainMenu() const -> fn::none;

    /**
     * @brief Resets the game state.
     */
    auto resetState() noexcept -> fn::none;

    /**
     * @brief  Starts the game.
     * @throws fn::StateError If the repository is not initialized.
     */
    auto play() -> fn::none;

    /**
     * @brief   Plays the round.
     * @param   round Current round.
     * @param   entry Selected entry for the round.
     * @returns A boolean indicating if next round will be played.
     */
    [[nodiscard]] auto playRound(fn::i16l round, const Model::Entry& entry) -> fn::bln;

    /**
     * @brief Prints the game menu.
     */
    auto printGameMenu() const -> fn::none;

    /**
     * @brief Selects the next entry from the dictionary.
     * @param dictionary The dictionary to select from.
     * @param round The current round.
     */
    [[nodiscard]] auto selectEntry(Model::Dictionary& dictionary, fn::i16l round) const
      -> Model::Entry;

    /**
     * @brief Prints the endgame menu.
     */
    auto printEndgameMenu() const -> fn::none;

    /**
     * @brief  Saves the score.
     * @throws fn::StateError If the repository is not initialized.
     */
    auto save() const -> fn::none;

    /**
     * @brief Prints the rules of the game.
     */
    auto learn() const -> fn::none;

    /**
     * @brief  Prints the high score table.
     * @throws fn::StateError If the repository is not initialized.
     */
    auto scores() const -> fn::none;

    /*----------------------------------------------------------------------------------+---------*\
    *| [private]: Fields                                                                | PRIVATE |*
    \*----------------------------------------------------------------------------------+---------*/

    std::shared_ptr<Data::Repository> m_repository{nullptr};
    fn::i16f                          m_score{};
    fn::i16f                          m_passRights{_internal::PASS_RIGHTS};
  };
} // namespace Game
