// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "opentelemetry/common/timestamp.h"
#include "opentelemetry/sdk/metrics/instruments.h"
#include "opentelemetry/sdk/metrics/state/metric_storage.h"
#include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace common
{
class KeyValueIterable;
}  // namespace common

namespace context
{
class Context;
}  // namespace context

namespace sdk
{
namespace metrics
{

class OPENTELEMETRY_SDK_METRICS_EXPORT SyncMultiMetricStorage : public SyncWritableMetricStorage
{
public:
  void AddStorage(std::shared_ptr<SyncWritableMetricStorage> storage)
  {
    storages_.push_back(storage);
  }

  virtual void RecordLong(int64_t value,
                          const opentelemetry::context::Context &context) noexcept override
  {
    for (auto &s : storages_)
    {
      s->RecordLong(value, context);
    }
  }

  virtual void RecordLong(int64_t value,
                          const opentelemetry::common::KeyValueIterable &attributes,
                          const opentelemetry::context::Context &context) noexcept override
  {
    for (auto &s : storages_)
    {
      s->RecordLong(value, attributes, context);
    }
  }

  virtual void RecordDouble(double value,
                            const opentelemetry::context::Context &context) noexcept override
  {
    for (auto &s : storages_)
    {
      s->RecordDouble(value, context);
    }
  }

  virtual void RecordDouble(double value,
                            const opentelemetry::common::KeyValueIterable &attributes,
                            const opentelemetry::context::Context &context) noexcept override
  {
    for (auto &s : storages_)
    {
      s->RecordDouble(value, attributes, context);
    }
  }

private:
  std::vector<std::shared_ptr<SyncWritableMetricStorage>> storages_;
};

class OPENTELEMETRY_SDK_METRICS_EXPORT AsyncMultiMetricStorage : public AsyncWritableMetricStorage
{
public:
  void AddStorage(std::shared_ptr<AsyncWritableMetricStorage> storage)
  {
    storages_.push_back(storage);
  }

  void RecordLong(
      const std::unordered_map<MetricAttributes, int64_t, AttributeHashGenerator> &measurements,
      opentelemetry::common::SystemTimestamp observation_time) noexcept override
  {
    for (auto &s : storages_)
    {
      s->RecordLong(measurements, observation_time);
    }
  }

  void RecordDouble(
      const std::unordered_map<MetricAttributes, double, AttributeHashGenerator> &measurements,
      opentelemetry::common::SystemTimestamp observation_time) noexcept override
  {
    for (auto &s : storages_)
    {
      s->RecordDouble(measurements, observation_time);
    }
  }

private:
  std::vector<std::shared_ptr<AsyncWritableMetricStorage>> storages_;
};

}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
