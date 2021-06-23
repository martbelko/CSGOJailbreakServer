#pragma once

#include <cstdint>
#include <string>

class Ban
{
public:
	enum class Type
	{
		None = 0,
		Normal,
		CtBan,
		MuteBan,
		GagBan,
		SilenceBan
	};

	struct PlayerInfo
	{
		std::string name;
		std::string steamID;
		std::string steam3ID;
		std::string steamID64;
		std::string ip;
	};
public:
	Ban(uint64_t id, Type type, const std::string& reason, const PlayerInfo& playerInfo);

	uint64_t GetID() const;
	Type GetType() const;
	const std::string& GetReason() const;
	const PlayerInfo& GetPlayerInfo() const;
private:
	const uint64_t mID;
	Type mType;
	std::string mReason;
	PlayerInfo mPlayerInfo;
};
