#pragma once

#include "IO/io.hpp"

#include <Foundation/types.hpp>

namespace IO::_internal
{
  struct TypeRow
  {
    fn::str typeName;
    fn::str isOptional;
    fn::str header;
    fn::str standardSize;
    fn::str platformSize;
    fn::str signedness;
    fn::str minValue;
    fn::str maxValue;
    fn::str precision;
    fn::str literalSuffix;
  };

  auto               printBriefTypeInfo(Option typeName) -> fn::none;
  auto               printTypeTips(Option typeName) -> fn::none;
  [[nodiscard]] auto getTypeRow(Option typeName) -> TypeRow;
} // namespace IO::_internal
