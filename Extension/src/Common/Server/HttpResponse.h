#pragma once

#include <string>
#include <unordered_map>
#include <winsock2.h>

struct HttpResponse
{
	int version; // 10 or 11
	int status; // 200, 404, ...
	std::string reason; // human readable status (OK, ...)
	std::unordered_map<std::string, std::string> fields;
	std::string data;
};

class HttpResponseParser
{
public:
	bool Parse(SOCKET socket, HttpResponse& response);
private:
	void Split(std::string_view buffer, std::string_view delimeter, std::vector<std::string_view>& strings);

	bool ParseHeader(std::string_view buffer, HttpResponse& response);
	bool ParseFields(std::string_view buffer, HttpResponse& response);
	bool ParseHeaderAndFields(std::string_view buffer, HttpResponse& response);
};
