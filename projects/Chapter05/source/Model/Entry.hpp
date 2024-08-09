#pragma once

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>

namespace Model
{
  struct Entry
  {
    fn::str          word;
    fn::vec<fn::str> definitions;
  };
} // namespace Model
