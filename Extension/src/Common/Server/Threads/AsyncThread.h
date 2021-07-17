#pragma once

#include <IThreader.h>

class AsyncThread : public SourceMod::IThread
{
public:
	virtual ~AsyncThread() = default;

	virtual void CallCallback() = 0;
};
