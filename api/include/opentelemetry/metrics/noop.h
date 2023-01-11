// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "opentelemetry/metrics/async_instruments.h"
#include "opentelemetry/metrics/meter.h"
#include "opentelemetry/metrics/meter_provider.h"
#include "opentelemetry/metrics/observer_result.h"
#include "opentelemetry/metrics/sync_instruments.h"
#include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace metrics
{

template <class T>
class OPENTELEMETRY_API NoopCounter : public Counter<T>
{
public:
  NoopCounter(nostd::string_view /* name */,
              nostd::string_view /* description */,
              nostd::string_view /* unit */) noexcept
  {}
  void Add(T /* value */) noexcept override {}
  void Add(T /* value */, const opentelemetry::context::Context & /* context */) noexcept override
  {}
  void Add(T /* value */, const common::KeyValueIterable & /* attributes */) noexcept override {}
  void Add(T /* value */,
           const common::KeyValueIterable & /* attributes */,
           const opentelemetry::context::Context & /* context */) noexcept override
  {}
};

template <class T>
class OPENTELEMETRY_API NoopHistogram : public Histogram<T>
{
public:
  NoopHistogram(nostd::string_view /* name */,
                nostd::string_view /* description */,
                nostd::string_view /* unit */) noexcept
  {}
  void Record(T /* value */,
              const opentelemetry::context::Context & /* context */) noexcept override
  {}
  void Record(T /* value */,
              const common::KeyValueIterable & /* attributes */,
              const opentelemetry::context::Context & /* context */) noexcept override
  {}
};

template <class T>
class OPENTELEMETRY_API NoopUpDownCounter : public UpDownCounter<T>
{
public:
  NoopUpDownCounter(nostd::string_view /* name */,
                    nostd::string_view /* description */,
                    nostd::string_view /* unit */) noexcept
  {}
  ~NoopUpDownCounter() override = default;
  void Add(T /* value */) noexcept override {}
  void Add(T /* value */, const opentelemetry::context::Context & /* context */) noexcept override
  {}
  void Add(T /* value */, const common::KeyValueIterable & /* attributes */) noexcept override {}
  void Add(T /* value */,
           const common::KeyValueIterable & /* attributes */,
           const opentelemetry::context::Context & /* context */) noexcept override
  {}
};

class OPENTELEMETRY_API NoopObservableInstrument : public ObservableInstrument
{
public:
  NoopObservableInstrument(nostd::string_view /* name */,
                           nostd::string_view /* description */,
                           nostd::string_view /* unit */) noexcept
  {}

  void AddCallback(ObservableCallbackPtr, void * /* state */) noexcept override {}
  void RemoveCallback(ObservableCallbackPtr, void * /* state */) noexcept override {}
};

/**
 * No-op implementation of Meter.
 */
class OPENTELEMETRY_API NoopMeter final : public Meter
{
public:
  nostd::unique_ptr<Counter<uint64_t>> CreateUInt64Counter(
      nostd::string_view name,
      nostd::string_view description = "",
      nostd::string_view unit        = "") noexcept override
  {
    return nostd::unique_ptr<Counter<uint64_t>>{new NoopCounter<uint64_t>(name, description, unit)};
  }

  nostd::unique_ptr<Counter<double>> CreateDoubleCounter(
      nostd::string_view name,
      nostd::string_view description = "",
      nostd::string_view unit        = "") noexcept override
  {
    return nostd::unique_ptr<Counter<double>>{new NoopCounter<double>(name, description, unit)};
  }

  nostd::shared_ptr<ObservableInstrument> CreateInt64ObservableCounter(
      nostd::string_view name,
      nostd::string_view description = "",
      nostd::string_view unit        = "") noexcept override
  {
    return nostd::shared_ptr<ObservableInstrument>(
        new NoopObservableInstrument(name, description, unit));
  }

  nostd::shared_ptr<ObservableInstrument> CreateDoubleObservableCounter(
      nostd::string_view name,
      nostd::string_view description = "",
      nostd::string_view unit        = "") noexcept override
  {
    return nostd::shared_ptr<ObservableInstrument>(
        new NoopObservableInstrument(name, description, unit));
  }

  nostd::unique_ptr<Histogram<uint64_t>> CreateUInt64Histogram(
      nostd::string_view name,
      nostd::string_view description = "",
      nostd::string_view unit        = "") noexcept override
  {
    return nostd::unique_ptr<Histogram<uint64_t>>{
        new NoopHistogram<uint64_t>(name, description, unit)};
  }

  nostd::unique_ptr<Histogram<double>> CreateDoubleHistogram(
      nostd::string_view name,
      nostd::string_view description = "",
      nostd::string_view unit        = "") noexcept override
  {
    return nostd::unique_ptr<Histogram<double>>{new NoopHistogram<double>(name, description, unit)};
  }

  nostd::shared_ptr<ObservableInstrument> CreateInt64ObservableGauge(
      nostd::string_view name,
      nostd::string_view description = "",
      nostd::string_view unit        = "") noexcept override
  {
    return nostd::shared_ptr<ObservableInstrument>(
        new NoopObservableInstrument(name, description, unit));
  }

  nostd::shared_ptr<ObservableInstrument> CreateDoubleObservableGauge(
      nostd::string_view name,
      nostd::string_view description = "",
      nostd::string_view unit        = "") noexcept override
  {
    return nostd::shared_ptr<ObservableInstrument>(
        new NoopObservableInstrument(name, description, unit));
  }

  nostd::unique_ptr<UpDownCounter<int64_t>> CreateInt64UpDownCounter(
      nostd::string_view name,
      nostd::string_view description = "",
      nostd::string_view unit        = "") noexcept override
  {
    return nostd::unique_ptr<UpDownCounter<int64_t>>{
        new NoopUpDownCounter<int64_t>(name, description, unit)};
  }

  nostd::unique_ptr<UpDownCounter<double>> CreateDoubleUpDownCounter(
      nostd::string_view name,
      nostd::string_view description = "",
      nostd::string_view unit        = "") noexcept override
  {
    return nostd::unique_ptr<UpDownCounter<double>>{
        new NoopUpDownCounter<double>(name, description, unit)};
  }

  nostd::shared_ptr<ObservableInstrument> CreateInt64ObservableUpDownCounter(
      nostd::string_view name,
      nostd::string_view description = "",
      nostd::string_view unit        = "") noexcept override
  {
    return nostd::shared_ptr<ObservableInstrument>(
        new NoopObservableInstrument(name, description, unit));
  }

  nostd::shared_ptr<ObservableInstrument> CreateDoubleObservableUpDownCounter(
      nostd::string_view name,
      nostd::string_view description = "",
      nostd::string_view unit        = "") noexcept override
  {
    return nostd::shared_ptr<ObservableInstrument>(
        new NoopObservableInstrument(name, description, unit));
  }
};

/**
 * No-op implementation of a MeterProvider.
 */
class OPENTELEMETRY_API NoopMeterProvider final : public MeterProvider
{
public:
  NoopMeterProvider() : meter_{nostd::shared_ptr<Meter>(new NoopMeter)} {}

  nostd::shared_ptr<Meter> GetMeter(nostd::string_view /* library_name */,
                                    nostd::string_view /* library_version */,
                                    nostd::string_view /* schema_url */) noexcept override
  {
    return meter_;
  }

private:
  nostd::shared_ptr<Meter> meter_;
};
}  // namespace metrics
OPENTELEMETRY_END_NAMESPACE
