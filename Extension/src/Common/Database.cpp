#include "Database.h"

/*uint64_t Database::sIndex = 0;
std::vector<Ban> Database::mBans;

void Database::AddBan(Ban::Type type, const std::string& reason, const Ban::PlayerInfo& playerInfo)
{
	mBans.emplace_back(sIndex++, type, reason, playerInfo);
}

void Database::Unban(uint64_t id)
{
	for (uint64_t i = 0; i < mBans.size(); ++i)
	{
		if (mBans[i].GetID() == id)
		{
			mBans.erase(mBans.begin() + i);
		}
	}
}

std::vector<Ban> Database::GetBansBySteamID(std::string_view steamID)
{
	std::vector<Ban> result;
	for (Ban ban : mBans)
	{
		if (ban.GetPlayerInfo().steamID == steamID)
			result.push_back(ban);
	}

	return result;
}*/
