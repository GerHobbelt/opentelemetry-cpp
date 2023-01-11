// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "opentelemetry/exporters/memory/in_memory_data.h"
#include "opentelemetry/sdk/trace/recordable.h"
#include "opentelemetry/sdk/trace/span_data.h"

#include <vector>

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace memory
{
class OPENTELEMETRY_API InMemorySpanData final : public exporter::memory::InMemoryData<sdk::trace::SpanData>
{
public:
  /**
   * @param buffer_size a required value that sets the size of the CircularBuffer
   */
  explicit InMemorySpanData(size_t buffer_size)
      : exporter::memory::InMemoryData<sdk::trace::SpanData>(buffer_size)
  {}

  std::vector<std::unique_ptr<sdk::trace::SpanData>> GetSpans() noexcept { return Get(); }
};
}  // namespace memory
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE
