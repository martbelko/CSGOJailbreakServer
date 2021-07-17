#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

class Logger
{
public:
	Logger(const std::string& name, const std::string& logFilename);
	~Logger();

	template<typename... Args>
	void TraceConsole(const char* file, uint32_t line, Args&&... args)
	{
		std::string str = Format(std::forward<Args>(args)...);
		TraceConsoleImpl(file, line, str);
	}

	template<typename... Args>
	void InfoConsole(const char* file, uint32_t line, Args&&... args)
	{
		std::string str = Format(std::forward<Args>(args)...);
		InfoConsoleImpl(file, line, str);
	}

	template<typename... Args>
	void WarnConsole(const char* file, uint32_t line, Args&&... args)
	{
		std::string str = Format(std::forward<Args>(args)...);
		WarnConsoleImpl(file, line, str);
	}

	template<typename... Args>
	void ErrorConsole(const char* file, uint32_t line, Args&&... args)
	{
		std::string str = Format(std::forward<Args>(args)...);
		ErrorConsoleImpl(file, line, str);
	}

	template<typename... Args>
	void CriticalConsole(const char* file, uint32_t line, Args&&... args)
	{
		std::string str = Format(std::forward<Args>(args)...);
		CriticalConsoleImpl(file, line, str);
	}

	template<typename... Args>
	void TraceFile(const char* file, uint32_t line, Args&&... args)
	{
		std::string str = Format(std::forward<Args>(args)...);
		TraceFileImpl(file, line, str);
	}

	template<typename... Args>
	void InfoFile(const char* file, uint32_t line, Args&&... args)
	{
		std::string str = Format(std::forward<Args>(args)...);
		InfoFileImpl(file, line, str);
	}

	template<typename... Args>
	void WarnFile(const char* file, uint32_t line, Args&&... args)
	{
		std::string str = Format(std::forward<Args>(args)...);
		WarnFileImpl(file, line, str);
	}

	template<typename... Args>
	void ErrorFile(const char* file, uint32_t line, Args&&... args)
	{
		std::string str = Format(std::forward<Args>(args)...);
		ErrorFileImpl(file, line, str);
	}

	template<typename... Args>
	void CriticalFile(const char* file, uint32_t line, Args&&... args)
	{
		std::string str = Format(std::forward<Args>(args)...);
		CriticalFileImpl(file, line, str);
	}
private:
	static std::string Format()
	{
		return std::string();
	}

	template<typename T, typename... Args>
	static std::string Format(const T& arg, Args&&... args)
	{
		const char* x = "a";
		std::stringstream ss;
		ss << arg;
		return ss.str() + Format(std::forward<Args>(args)...);
	}

	std::string FormatOutput(const char* file, uint32_t line, const std::string& text);

	void TraceConsoleImpl(const char* file, uint32_t line, const std::string& text);
	void InfoConsoleImpl(const char* file, uint32_t line, const std::string& text);
	void WarnConsoleImpl(const char* file, uint32_t line, const std::string& text);
	void ErrorConsoleImpl(const char* file, uint32_t line, const std::string& text);
	void CriticalConsoleImpl(const char* file, uint32_t line, const std::string& text);

	void TraceFileImpl(const char* file, uint32_t line, const std::string& text);
	void InfoFileImpl(const char* file, uint32_t line, const std::string& text);
	void WarnFileImpl(const char* file, uint32_t line, const std::string& text);
	void ErrorFileImpl(const char* file, uint32_t line, const std::string& text);
	void CriticalFileImpl(const char* file, uint32_t line, const std::string& text);
private:
	std::string mName;
	std::ofstream mOutFile;
};
