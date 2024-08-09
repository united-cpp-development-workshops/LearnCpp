#pragma once

#include "File/_internal/details.hpp"
#include "File/structure.hpp"
#include "Model/Dictionary.hpp"
#include "Model/Save.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/errors.hpp>
#include <Foundation/types.hpp>

#include <filesystem>

namespace File
{
  /**
   * @brief  Depending on the model type, load a model from a file.
   * @tparam TModel Type of the model.
   * @param  model model to load into.
   * @throws fn::FileError If loading fails.
   */
  template <typename TModel>
  requires fn::IsSame<TModel, Model::Dictionary> or fn::IsSame<TModel, fn::vec<Model::Save>>
  auto load(TModel& model) -> fn::none;

  /**
   * @brief  Depending on the model type, save a model to a file.
   * @tparam TModel Type of the model.
   * @param  model model to save.
   * @throws fn::FileError If saving fails.
   */
  template <typename TModel>
  requires fn::IsSame<TModel, fn::unit>
  auto save(const TModel& model) -> fn::none;
} // namespace File

/*------------------------------------------------------------------------------------------------*\
*| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Implementation >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
\*------------------------------------------------------------------------------------------------*/

namespace File
{
  template <typename TModel>
  requires fn::IsSame<TModel, Model::Dictionary> or fn::IsSame<TModel, fn::vec<Model::Save>>
  auto load(TModel& model) -> fn::none
  {
    // Load based on the model type
    if constexpr (fn::IsSame<TModel, Model::Dictionary>)
    {
      // Load the dictionary
      _internal::loadDictionary(
        {std::filesystem::current_path() / ASSETS_FOLDER_NAME / DICTIONARY_FILE_NAME}, model
      );
    }
    else if constexpr (fn::IsSame<TModel, fn::vec<Model::Save>>)
    {
      // Load the scores
      _internal::loadScores(
        {std::filesystem::current_path() / DATA_FOLDER_NAME / SAVES_FILE_NAME}, model
      );
    }
    else
    {
      // Throw an exception
      throw fn::FileError{"Failed to load the model!", "Unknown model type."};
    }
  }

  template <typename TModel>
  requires fn::IsSame<TModel, Model::Save>
  auto save(const TModel& model) -> fn::none
  {
    // Save based on the model type
    if constexpr (fn::IsSame<TModel, Model::Save>)
    {
      // Save the score
      _internal::saveScore(
        {std::filesystem::current_path() / DATA_FOLDER_NAME / SAVES_FILE_NAME}, model
      );
    }
  }
} // namespace File
