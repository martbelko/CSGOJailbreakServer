#pragma once

#include "Common/Logging/Logger.h"

#include <memory>

class Log
{
public:
	Log() = delete;

	static void Init();

	static const std::shared_ptr<Logger>& GetCoreLogger() { return mCoreLogger; }
private:
	static std::shared_ptr<Logger> mCoreLogger;
};

// Core log macros
#define URNA_TRACE(...)    Log::GetCoreLogger()->TraceFile(__FILE__, __LINE__, __VA_ARGS__)
#define URNA_INFO(...)     Log::GetCoreLogger()->InfoConsole(__FILE__, __LINE__, __VA_ARGS__)
#define URNA_WARN(...)     Log::GetCoreLogger()->WarnConsole(__FILE__, __LINE__, __VA_ARGS__)
#define URNA_ERROR(...)    Log::GetCoreLogger()->ErrorConsole(__FILE__, __LINE__, __VA_ARGS__)
#define URNA_CRITICAL(...) Log::GetCoreLogger()->CriticalConsole(__FILE__, __LINE__, __VA_ARGS__)
