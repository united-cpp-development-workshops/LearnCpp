#pragma once

#include "IO/io.hpp"

#include <Foundation/types.hpp>

#include <string>

namespace IO::_internal
{
  struct TypeRow
  {
    std::string typeName;
    std::string isOptional;
    std::string header;
    std::string standardSize;
    std::string platformSize;
    std::string signedness;
    std::string minValue;
    std::string maxValue;
    std::string precision;
    std::string literalSuffixes;
  };

  auto               printBriefTypeInfo(Option typeName) -> fn::none;
  auto               printTypeTips(Option typeName) -> fn::none;
  [[nodiscard]] auto getTypeRow(Option typeName) -> TypeRow;
} // namespace IO::_internal
