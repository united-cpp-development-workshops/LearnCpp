#pragma once

#include "Model/Dictionary.hpp"
#include "Model/Save.hpp"

#include <Foundation/types.hpp>

#include <filesystem>

namespace File::_internal
{
  /**
   * @brief  Loads a dictionary from a file.
   * @param  path Path to the file.
   * @param  dictionary Dictionary to load into.
   * @throws fn::FileError For various file related errors.
   */
  auto loadDictionary(const std::filesystem::path& path, Model::Dictionary& dictionary) -> fn::none;

  /**
   * @brief  Loads scores from a file.
   * @param  path Path to the file.
   * @param  models Saves vector to load into.
   * @throws fn::FileError For various file related errors.
   */
  auto loadScores(const std::filesystem::path& path, fn::vec<Model::Save>& saves) -> fn::none;

  /**
   * @brief  Saves the score to a file.
   * @param  path The path to the save file.
   * @param  save The data to be saved.
   * @throws fn::FileError for various file related errors.
   */
  auto saveScore(const std::filesystem::path& path, const Model::Save& save) -> fn::none;
} // namespace File::_internal
