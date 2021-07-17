#include "BanSystem.h"

#include "PublicManager.h"

#include "Common/BanSystem/Ban.h"

void BanSystem::BanClient(int target, uint64_t adminID, Ban::Type type, const std::string& reason, uint64_t lengthInSeconds)
{
	// TODO: Read from database
	std::string adminName = "TestAdmin";
	Ban::PlayerInfo playerInfo = BanSystem::GetPlayerInfo(target);
	AddBan(playerInfo, type, reason, lengthInSeconds);
	// TODO: Translate
	PM::KickClient(target, "You have been banned: Reason: TODO");
}

void BanSystem::AddBan(const Ban::PlayerInfo& playerInfo, Ban::Type type, const std::string& reason, uint64_t lengthInSeconds)
{
	// TODO: Implement
}

void BanSystem::Unban(const Ban::PlayerInfo& playerInfo)
{
	// TODO: Implement
}

Ban::PlayerInfo BanSystem::GetPlayerInfo(int client)
{
	Ban::PlayerInfo playerInfo;
	char steamID[32], steam3ID[32], steamID64[32], ip[32];
	PM::GetClientAuthId(client, AuthId_Steam2, steamID, sizeof(steamID));
	PM::GetClientAuthId(client, AuthId_Steam3, steam3ID, sizeof(steam3ID));
	PM::GetClientAuthId(client, AuthId_SteamID64, steamID64, sizeof(steamID64));
	PM::GetClientIP(client, ip, sizeof(ip));

	playerInfo.steamID = steamID;
	playerInfo.steam3ID = steam3ID;
	playerInfo.steamID64 = steamID64;
	playerInfo.ip = ip;

	return playerInfo;
}
