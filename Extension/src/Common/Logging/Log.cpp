#include "Log.h"

std::shared_ptr<Logger> Log::mCoreLogger;

void Log::Init()
{
	mCoreLogger = std::make_shared<Logger>("CoreLogger", "ServerLog.log");
}
