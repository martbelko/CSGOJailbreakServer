#pragma once

#include "AsyncThread.h"
#include "Common/BanSystem/Ban.h"

#include <vector>

class AllBansThread : public AsyncThread
{
public:
	using CallbackFn = void(*)(std::vector<Ban>&);
public:
	AllBansThread(CallbackFn callback);

	virtual void RunThread(SourceMod::IThreadHandle* pHandle) override;
	virtual void OnTerminate(SourceMod::IThreadHandle* pHandle, bool cancel) override;

	virtual void CallCallback() override;
private:
	CallbackFn mCallback;
	std::vector<Ban> mBans;
};
