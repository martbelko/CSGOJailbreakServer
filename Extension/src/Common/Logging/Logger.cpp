#include "Logger.h"

#include "PublicManager.h"

#include <ctime>
#include <fstream>

Logger::Logger(const std::string& name, const std::string& logFilename)
	: mName(name)
{
	std::string path = "./csgo/addons/sourcemod/logs/" + logFilename;
	mOutFile.open(path, std::ios_base::app | std::ios_base::out);
	if (mOutFile.is_open())
		TraceConsole(__FILE__, __LINE__, "File ", name, " was successfully opened for logging!");
	else
	{
		CriticalConsole(__FILE__, __LINE__, "File ", name, " could not be opened for logging!");
		PM::SetFailState("File (%s) could not be opened for logging!", name.c_str());
	}
}

Logger::~Logger()
{
	if (mOutFile.is_open())
		mOutFile.close();
}

std::string Logger::FormatOutput(const char* file, uint32_t line, const std::string& text)
{
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	std::stringstream timess;
	timess << (now->tm_hour) << ':'
		<< (now->tm_min) << ':'
		<< now->tm_sec;
	std::stringstream ss;
	ss << "{" << timess.str() << "} " << mName << ": " << text << " [" << file << ", line: " << line << "]";
	return ss.str();
}

void Logger::TraceConsoleImpl(const char* file, uint32_t line, const std::string& text)
{
	std::string finalText = "==== [TRACE] " + FormatOutput(file, line, text);
	PM::PrintToServer(finalText.c_str());
}

void Logger::InfoConsoleImpl(const char* file, uint32_t line, const std::string& text)
{
	std::string finalText = "==== [INFO] " + FormatOutput(file, line, text);
	PM::PrintToServer(finalText.c_str());
}

void Logger::WarnConsoleImpl(const char* file, uint32_t line, const std::string& text)
{
	std::string finalText = "==== [WARNING] " + FormatOutput(file, line, text);
	PM::PrintToServer(finalText.c_str());
}

void Logger::ErrorConsoleImpl(const char* file, uint32_t line, const std::string& text)
{
	std::string finalText = "==== [ERROR] " + FormatOutput(file, line, text);
	PM::PrintToServer(finalText.c_str());
}

void Logger::CriticalConsoleImpl(const char* file, uint32_t line, const std::string& text)
{
	std::string finalText = "=== [CRITICAL] " + FormatOutput(file, line, text);
	PM::PrintToServer(finalText.c_str());
}

void Logger::TraceFileImpl(const char* file, uint32_t line, const std::string& text)
{
	std::string finalText = "[TRACE] " + FormatOutput(file, line, text);
	mOutFile << finalText << "\n\n";
	mOutFile.flush();
}

void Logger::InfoFileImpl(const char* file, uint32_t line, const std::string& text)
{
	std::string finalText = "[INFO] " + FormatOutput(file, line, text);
	mOutFile << finalText << "\n\n";
	mOutFile.flush();
}

void Logger::WarnFileImpl(const char* file, uint32_t line, const std::string& text)
{
	std::string finalText = "[WARNING] " + FormatOutput(file, line, text);
	mOutFile << finalText << "\n\n";
	mOutFile.flush();
}

void Logger::ErrorFileImpl(const char* file, uint32_t line, const std::string& text)
{
	std::string finalText = "[ERROR] " + FormatOutput(file, line, text);
	mOutFile << finalText << "\n\n";
	mOutFile.flush();
}

void Logger::CriticalFileImpl(const char* file, uint32_t line, const std::string& text)
{
	std::string finalText = "[CRITICAL] " + FormatOutput(file, line, text);
	mOutFile << finalText << "\n\n";
	mOutFile.flush();
}
