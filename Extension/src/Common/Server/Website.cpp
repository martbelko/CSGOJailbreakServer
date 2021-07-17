#include "Website.h"

std::optional<HttpResponse> GetWebsite(const char* request, const std::string& url, int port)
{
	WSADATA wsaData;
	SOCKET Socket;
	SOCKADDR_IN SockAddr;

	int lineCount = 0;
	int rowCount = 0;

	struct hostent* host;
	char* get_http = new char[256];

	memset(get_http, ' ', sizeof(get_http));
	strcpy(get_http, request);
	strcat(get_http, " HTTP/1.1\r\nHost: ");
	strcat(get_http, url.c_str());
	strcat(get_http, "\r\nConnection: close\r\n\r\n");

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		URNA_CRITICAL("WSAStartup failed.");
		return {};
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	host = gethostbyname(url.c_str());

	SockAddr.sin_port = htons(port);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
	{
		URNA_CRITICAL("Could not connect to website. Url = ", url, "; request = ", request);
		return {};
	}

	send(Socket, get_http, static_cast<int>(strlen(get_http)), 0);

	HttpResponse response;
	HttpResponseParser parser;
	if (!parser.Parse(Socket, response))
		return {};

	closesocket(Socket);
	WSACleanup();

	delete[] get_http;

	return std::make_optional(response);
}
