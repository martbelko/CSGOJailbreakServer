#pragma once

#include "AsyncThread.h"
#include "Common/Admin/Admin.h"

#include <vector>

class AllAdminsThread : public AsyncThread
{
public:
	using CallbackFn = void(*)(std::vector<Admin>&);
public:
	AllAdminsThread(CallbackFn callback);

	virtual void RunThread(SourceMod::IThreadHandle * pHandle) override;
	virtual void OnTerminate(SourceMod::IThreadHandle* pHandle, bool cancel) override;

	virtual void CallCallback() override;
private:
	CallbackFn mCallback;
	std::vector<Admin> mAdmins;
};
