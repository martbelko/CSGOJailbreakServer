#pragma once

#include "Common/Admin/Admin.h"
#include "Common/BanSystem/Ban.h"

#include "Common/Server/Threads/AsyncThread.h"
#include "Common/Server/Threads/AllAdminsThread.h"
#include "Common/Server/Threads/AllBansThread.h"

#include <string>
#include <string_view>
#include <vector>
#include <mutex>

class Server
{
public:
	Server() = delete;

	static void Init(const std::string& url, int port);

	friend void OnThreadTerminate(AsyncThread* thread)
	{
		Server::sFinishedThreadsMutex.lock();
		Server::sFinishedThreads.push_back(thread);
		Server::sFinishedThreadsMutex.unlock();
	}

	static void Run();

	static std::vector<Admin> GetAllAdmins();
	static void GetAllAdminsAsync(AllAdminsThread::CallbackFn callback);

	static std::vector<Ban> GetAllBans();
	static void GetAllBansAsync(AllBansThread::CallbackFn callback);

	static Admin GetAdminByID(uint64_t id);
	static Admin GetAdminByName(const std::string& name);
private:
	static Ban::Type ParseBanType(std::string_view typeStr);
private:
	static std::string sUrl;
	static int sPort;

	static std::vector<AsyncThread*> sFinishedThreads;
	static std::mutex sFinishedThreadsMutex;
};
