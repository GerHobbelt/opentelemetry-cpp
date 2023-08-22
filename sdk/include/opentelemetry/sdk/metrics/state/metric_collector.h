// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <chrono>
#include <memory>

#include "opentelemetry/sdk/metrics/export/metric_producer.h"
#include "opentelemetry/sdk/metrics/instruments.h"
#include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

class OPENTELEMETRY_SDK_METRICS_EXPORT MetricReader;
class OPENTELEMETRY_SDK_METRICS_EXPORT MeterContext;

class OPENTELEMETRY_SDK_METRICS_EXPORT CollectorHandle
{
public:
  CollectorHandle()          = default;
  virtual ~CollectorHandle() = default;

  virtual AggregationTemporality GetAggregationTemporality(
      InstrumentType instrument_type) noexcept = 0;
};

/**
 * An internal opaque interface that the MetricReader receives as
 * MetricProducer. It acts as the storage key to the internal metric stream
 * state for each MetricReader.
 */

class OPENTELEMETRY_SDK_METRICS_EXPORT MetricCollector : public MetricProducer, public CollectorHandle
{
public:
  MetricCollector(MeterContext *context, std::shared_ptr<MetricReader> metric_reader);

  ~MetricCollector() override = default;

  AggregationTemporality GetAggregationTemporality(
      InstrumentType instrument_type) noexcept override;

  /**
   * The callback to be called for each metric exporter. This will only be those
   * metrics that have been produced since the last time this method was called.
   *
   * @return a status of completion of method.
   */
  bool Collect(nostd::function_ref<bool(ResourceMetrics &metric_data)> callback) noexcept override;

  bool ForceFlush(std::chrono::microseconds timeout = std::chrono::microseconds::max()) noexcept;

  bool Shutdown(std::chrono::microseconds timeout = std::chrono::microseconds::max()) noexcept;

private:
  MeterContext *meter_context_;
  std::shared_ptr<MetricReader> metric_reader_;
};
}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
