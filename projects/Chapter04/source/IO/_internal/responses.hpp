#pragma once

#include "IO/io.hpp"

#include <Foundation/containers.hpp>
#include <Foundation/types.hpp>

namespace IO::_internal
{
  auto helpResponse(const fn::set<Option>& options) -> fn::none;
  auto platformResponse(const fn::set<Option>& options) -> fn::none;
  auto exploreResponse(const fn::set<Option>& options) -> fn::none;
  auto tipsResponse(const fn::set<Option>& options) -> fn::none;
  auto metricsResponse(const fn::set<Option>& options) -> fn::none;
  auto compareResponse(const fn::set<Option>& options) -> fn::none;
  auto exitResponse(const fn::set<Option>& options) -> fn::none;
} // namespace IO::_internal
