#include "AllBansThread.h"

#include "Common/Server/Server.h"

AllBansThread::AllBansThread(CallbackFn callback)
	: mCallback(callback)
{
}

void AllBansThread::RunThread(SourceMod::IThreadHandle* pHandle)
{
	mBans = Server::GetAllBans();
}

void AllBansThread::OnTerminate(SourceMod::IThreadHandle* pHandle, bool cancel)
{
	OnThreadTerminate(this);
}

void AllBansThread::CallCallback()
{
	mCallback(mBans);
}
