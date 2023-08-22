// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <vector>

#include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{
class OPENTELEMETRY_SDK_METRICS_EXPORT AggregationConfig
{
public:
  virtual ~AggregationConfig() = default;
};

class OPENTELEMETRY_SDK_METRICS_EXPORT HistogramAggregationConfig : public AggregationConfig
{
public:
  std::vector<double> boundaries_;
  bool record_min_max_ = true;
};
}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
