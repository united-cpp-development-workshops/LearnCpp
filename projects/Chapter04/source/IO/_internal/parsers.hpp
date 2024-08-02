#pragma once

#include "IO/io.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>
#include <Foundation/utilities.hpp>

#include <sstream>

namespace IO::_internal
{
  inline constexpr fn::f32 AUTO_FIX_THRESHOLD{0.75f};
  inline constexpr fn::f32 SUGGEST_THRESHOLD{2.5f};

  [[nodiscard]] auto getCommandMap() -> const fn::umap<Command, fn::str>&;
  [[nodiscard]] auto getOptionMap() -> const fn::umap<Option, fn::str>&;
  [[nodiscard]] auto parseCommand(fn::str& token) -> fn::opt<Command>;
  [[nodiscard]] auto invalidCmdHandler(fn::strv token) -> fn::opt<Command>;
  [[nodiscard]] auto parseOptions(std::istringstream& inputStream) -> fn::set<Option>;
  auto               invalidOptHandler(fn::strv token, fn::set<Option>& options) -> fn::none;
} // namespace IO::_internal
