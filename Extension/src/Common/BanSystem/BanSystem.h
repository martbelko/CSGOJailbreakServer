#pragma once

#include "Common/BanSystem/Ban.h"

#include <string>

class BanSystem
{
public:
	BanSystem() = delete;

	static void BanClient(int target, uint64_t adminID, Ban::Type type, const std::string& reason, uint64_t lengthInSeconds);

	static void AddBan(const Ban::PlayerInfo& playerInfo, Ban::Type type, const std::string& reason, uint64_t lengthInSeconds);
	static void Unban(const Ban::PlayerInfo& playerInfo);

	static Ban::PlayerInfo GetPlayerInfo(int client);
};
