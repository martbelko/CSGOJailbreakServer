#include "Server.h"

#include "PublicManager.h"

#include "Common/Server/Website.h"

#include <tao/json.hpp>
#include <tao/json/contrib/traits.hpp>

std::string Server::sUrl;
int Server::sPort;
std::vector<AsyncThread*> Server::sFinishedThreads;
std::mutex Server::sFinishedThreadsMutex;

void Server::Init(const std::string& url, int port)
{
	sUrl = url;
	sPort = port;
}

void Server::Run()
{
	if (!sFinishedThreads.empty() && sFinishedThreadsMutex.try_lock())
	{
		for (AsyncThread* thread : sFinishedThreads)
		{
			thread->CallCallback();
			delete thread; // Do not forget to free memory
		}

		sFinishedThreads.clear();
		sFinishedThreadsMutex.unlock();
	}
}

std::vector<Admin> Server::GetAllAdmins()
{
	std::optional<HttpResponse> response = GetWebsite("GET /api/admins", sUrl, sPort);
	if (response)
	{
		std::vector<Admin> admins;
		const tao::json::value adminsJson = tao::json::from_string(response->data);
		uint32_t len = adminsJson.get_array().size();
		for (uint32_t i = 0; i < len; ++i)
		{
			const tao::json::value& adminJson = adminsJson[i];
			Admin admin;
			admin.id = adminJson.at("id").as<uint64_t>();
			admin.steamID = adminJson.at("steamID").as<std::string>();
			admin.name = adminJson.at("name").as<std::string>();
			admin.flags = adminJson.at("flags").as<int>();

			admins.push_back(admin);
		}

		return admins;
	}
	else
		return {};
}

void Server::GetAllAdminsAsync(AllAdminsThread::CallbackFn callback)
{
	AsyncThread* thread = new AllAdminsThread(callback);
	threader->MakeThread(thread);
}

std::vector<Ban> Server::GetAllBans()
{
	std::optional<HttpResponse> response = GetWebsite("GET /api/bans", sUrl, sPort);
	if (response)
	{
		std::vector<Ban> bans;
		const tao::json::value bansJson = tao::json::from_string(response->data);
		uint32_t len = bansJson.get_array().size();
		for (uint32_t i = 0; i < len; ++i)
		{
			const tao::json::value& banJson = bansJson[i];

			Ban ban;
			ban.id = banJson.at("id").as<uint64_t>();
			ban.targetName = banJson.at("targetName").as<std::string>();
			ban.reason = banJson.at("reason").as<std::string>();
			ban.playerInfoID = banJson.at("targetInfoID").as<uint64_t>();
			ban.adminID = banJson.at("adminID").as<uint64_t>();
			ban.type = ParseBanType(banJson.at("type").as<std::string_view>());
			ban.length = banJson.at("length").as<uint64_t>();

			auto& unbanIDJson = banJson.at("unbanID");
			if (unbanIDJson != tao::json::null)
				ban.unbanID = unbanIDJson.as<uint64_t>();
			else
				ban.unbanID = 0;

			auto& serverIDJson = banJson.at("serverID");
			if (serverIDJson != tao::json::null)
				ban.serverInfoID = serverIDJson.as<uint64_t>();
			else
				ban.serverInfoID = 0;

			bans.emplace_back(std::move(ban));
		}

		return bans;
	}
	else
		return {};
}

void Server::GetAllBansAsync(AllBansThread::CallbackFn callback)
{
	AsyncThread* thread = new AllBansThread(callback);
	threader->MakeThread(thread);
}

Admin Server::GetAdminByID(uint64_t id)
{
	// TODO: Implement
	Admin admin;
	admin.id = 0;
	return admin;
}

Admin Server::GetAdminByName(const std::string& name)
{
	// TODO: Implement
	Admin admin;
	admin.id = 0;
	return admin;
}

Ban::Type Server::ParseBanType(std::string_view typeStr)
{
	if (typeStr == "NORMAL")
		return Ban::Type::Normal;
	else if (typeStr == "CT")
		return Ban::Type::Ct;
	else if (typeStr == "SILENCE")
		return Ban::Type::Silence;

	return Ban::Type::None;
}
