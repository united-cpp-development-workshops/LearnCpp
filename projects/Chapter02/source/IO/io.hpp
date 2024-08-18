#pragma once

#include "Math/math.ipp"
#include "Utility/utility.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>

namespace IO
{
  inline constexpr fn::i16f LEFT_MARGIN{2};
  inline constexpr fn::size DIRECTIONAL_ZOOM_INPUT_LENGTH{2};
  inline constexpr fn::f64  SQUARE{2};
  inline constexpr fn::strv X_AXIS_NAME{"Value"};
  inline constexpr fn::strv Y_AXIS_NAME{"Frequency"};

  enum class Option : fn::u8f
  {
    ZOOM_IN,
    ZOOM_IN_HORIZONTAL,
    ZOOM_IN_VERTICAL,
    ZOOM_OUT,
    ZOOM_OUT_HORIZONTAL,
    ZOOM_OUT_VERTICAL,
    STATISTICS,
    NEW_CHART,
    QUIT
  };

  auto               printWelcome() -> fn::none;
  auto               printInformative() -> fn::none;
  [[nodiscard]] auto getSamplesCountInput() -> fn::i32f;
  [[nodiscard]] auto getLowerBoundInput() -> fn::i32f;
  [[nodiscard]] auto getUpperBoundInput() -> fn::i32f;
  [[nodiscard]] auto getSizeInput() -> fn::pair<fn::u16f, fn::u16f>;
  auto               printResultsHeader() -> fn::none;
  auto               printChart(const Math::Feed& feed) -> fn::none;
  auto               printStatistics(const fn::vec<fn::i32f>& values) -> fn::none;
  auto               printOptionsHeader() -> fn::none;
  [[nodiscard]] auto getOptionInput() -> Option;
  auto               printNoFurtherZoom(Utility::Direction direction) -> fn::none;
} // namespace IO
