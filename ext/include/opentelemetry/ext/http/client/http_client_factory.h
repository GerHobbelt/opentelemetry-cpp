// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include "opentelemetry/ext/http/client/http_client.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace ext
{
namespace http
{
namespace client
{
class OPENTELEMETRY_API HttpClientFactory
{
public:
  static std::shared_ptr<HttpClientSync> CreateSync();

  static std::shared_ptr<HttpClient> Create();

#ifdef ENABLE_TEST
  static std::shared_ptr<HttpClient> CreateNoSend();
#endif
};
}  // namespace client
}  // namespace http
}  // namespace ext
OPENTELEMETRY_END_NAMESPACE
