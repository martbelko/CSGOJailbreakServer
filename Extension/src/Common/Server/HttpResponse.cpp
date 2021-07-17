#include "HttpResponse.h"

#include <winsock2.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <unordered_map>

#pragma comment(lib,"ws2_32.lib")

#define CRLF "\r\n"

bool HttpResponseParser::Parse(SOCKET socket, HttpResponse& response)
{
	char buffer[5000] = { 0 };
	bool isHeader = true;
	uint32_t bytesRead = 0;
	while (recv(socket, buffer + bytesRead, sizeof(buffer), 0) > 0)
	{
		if (isHeader)
		{
			std::string_view bufferStr = buffer;
			size_t i = bufferStr.find(CRLF CRLF);
			if (i == std::string::npos)
			{
				bytesRead = static_cast<uint32_t>(bufferStr.length());
				continue;
			}

			char tempChar = buffer[i];
			buffer[i] = 0;

			char bufferHeader[sizeof(buffer)] = { 0 };
			strcpy(bufferHeader, buffer);

			if (!ParseHeaderAndFields(bufferHeader, response))
				return false;

			buffer[i] = tempChar;
			uint32_t len = static_cast<uint32_t>(strlen(buffer + i + 4));
			memmove(buffer, buffer + i + 4, len);
			buffer[len] = 0;
			bytesRead = static_cast<uint32_t>(strlen(buffer));
			isHeader = false;
		}

		const std::string& lenStr = response.fields["Content-Length"];
		std::istringstream ss(lenStr);
		uint32_t contentLen;
		ss >> contentLen;

		std::string_view bufferStr = buffer;
		response.data += std::string(bufferStr);

		if (contentLen <= response.data.length())
			return true;

		memset(buffer, 0, sizeof(buffer));
		bytesRead = 0;
	}

	return false;
}

void HttpResponseParser::Split(std::string_view buffer, std::string_view delimeter, std::vector<std::string_view>& strings)
{
	for (size_t i = buffer.find(delimeter); i != std::string::npos; buffer = buffer.substr(i + 2), i = buffer.find(delimeter))
	{
		std::string_view token = buffer.substr(0, i);
		strings.emplace_back(token);
	}
}

bool HttpResponseParser::ParseHeader(std::string_view buffer, HttpResponse& response)
{
	size_t versionIndex = buffer.find(" ");
	std::string_view versionStr = buffer.substr(0, versionIndex);
	response.version = versionStr.find("1.0") == std::string::npos ? 11 : 10;

	size_t statusIndex = buffer.find(" ", versionIndex + 1);
	std::string_view statusStr = buffer.substr(versionIndex + 1, statusIndex);
	std::stringstream ss;
	ss << statusStr;
	ss >> response.status;

	response.reason = buffer.substr(buffer.find_last_of(" ") + 1);

	return true;
}

bool HttpResponseParser::ParseFields(std::string_view buffer, HttpResponse& response)
{
	std::vector<std::string_view> strings;
	Split(buffer, CRLF, strings);
	for (std::string_view entry : strings)
	{
		size_t i = entry.find(": ");
		response.fields[std::string(entry.substr(0, i))] = std::string(entry.substr(i + 2));
	}

	return true;
}

bool HttpResponseParser::ParseHeaderAndFields(std::string_view buffer, HttpResponse& response)
{
	size_t i = buffer.find(CRLF);
	return ParseHeader(buffer.substr(0, i), response) &&
		ParseFields(buffer.substr(i + 2), response);
}
