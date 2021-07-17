#include "AllAdminsThread.h"

#include "Common/Server/Server.h"

AllAdminsThread::AllAdminsThread(CallbackFn callback)
	: mCallback(callback)
{
}

void AllAdminsThread::RunThread(SourceMod::IThreadHandle* pHandle)
{
	mAdmins = Server::GetAllAdmins();
}

void AllAdminsThread::OnTerminate(SourceMod::IThreadHandle* pHandle, bool cancel)
{
	OnThreadTerminate(this);
}

void AllAdminsThread::CallCallback()
{
	mCallback(mAdmins);
}
