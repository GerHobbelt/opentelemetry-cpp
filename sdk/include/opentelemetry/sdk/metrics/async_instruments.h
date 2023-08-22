// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>

#include "opentelemetry/metrics/async_instruments.h"
#include "opentelemetry/metrics/observer_result.h"
#include "opentelemetry/sdk/metrics/instruments.h"
#include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

class OPENTELEMETRY_SDK_METRICS_EXPORT AsyncWritableMetricStorage;
class OPENTELEMETRY_SDK_METRICS_EXPORT ObservableRegistry;

class OPENTELEMETRY_SDK_METRICS_EXPORT ObservableInstrument : public opentelemetry::metrics::ObservableInstrument
{
public:
  ObservableInstrument(InstrumentDescriptor instrument_descriptor,
                       std::unique_ptr<AsyncWritableMetricStorage> storage,
                       std::shared_ptr<ObservableRegistry> observable_registry);

  void AddCallback(opentelemetry::metrics::ObservableCallbackPtr callback,
                   void *state) noexcept override;

  void RemoveCallback(opentelemetry::metrics::ObservableCallbackPtr callback,
                      void *state) noexcept override;

  const InstrumentDescriptor &GetInstrumentDescriptor();

  AsyncWritableMetricStorage *GetMetricStorage();

private:
  InstrumentDescriptor instrument_descriptor_;
  std::unique_ptr<AsyncWritableMetricStorage> storage_;
  std::shared_ptr<ObservableRegistry> observable_registry_;
};
}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
