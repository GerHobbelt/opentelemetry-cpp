// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>

#include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace trace
{
class Sampler;

/**
 * Factory class for AlwaysOffSampler.
 */
class OPENTELEMETRY_SDK_TRACE_EXPORT AlwaysOffSamplerFactory
{
public:
  /**
   * Create an AlwaysOffSampler.
   */
  static std::unique_ptr<Sampler> Create();
};

}  // namespace trace
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
