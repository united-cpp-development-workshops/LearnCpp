#pragma once

#include <Foundation/containers.hpp>

namespace Model
{
  /**
   * @brief Unordered map of word lengths and their entries.
   */
  using Dictionary = fn::umap<fn::i16l, fn::umap<fn::str, fn::vec<fn::str>>>;
} // namespace Model
