#pragma once

#include "Math/math.ipp"

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>

namespace Utility
{
  enum class Direction : fn::u8f
  {
    BOTH,
    HORIZONTAL,
    VERTICAL
  };

  [[nodiscard]] auto optionsHandler(
    fn::pair<fn::u16f, fn::u16f>&       preferredSize,
    fn::pair<fn::u16f, fn::u16f>&       currentSize,
    fn::map<fn::i32f, fn::u32f>&        frequencies,
    fn::pair<fn::u32f&, fn::u32f&>      intervals,
    const fn::vec<fn::i32f>&            values,
    const fn::pair<fn::i32f, fn::i32f>& bounds
  ) -> fn::bln;
  [[nodiscard]] auto noFurtherZoomHandler(
    fn::bln                             isZoomIn,
    Direction                           direction,
    const fn::pair<fn::u32f, fn::u32f>& intervals,
    const fn::map<fn::i32f, fn::u32f>&  frequencies
  ) -> fn::bln;
  [[nodiscard]] auto zoom(
    fn::bln                             isZoomIn,
    Direction                           zoomDirection,
    fn::pair<fn::u16f, fn::u16f>&       preferredSize,
    fn::pair<fn::u16f, fn::u16f>&       currentSize,
    const fn::vec<fn::i32f>&            values,
    const fn::pair<fn::i32f, fn::i32f>& bounds
  ) -> fn::opt<Math::Feed>;
} // namespace Utility
