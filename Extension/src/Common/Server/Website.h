#pragma once

#include "Base.h"
#include "Common/Server/HttpResponse.h"

#include <optional>

std::optional<HttpResponse> GetWebsite(const char* request, const std::string& url, int port);
