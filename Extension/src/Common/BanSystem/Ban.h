#pragma once

#include "Base.h"

#include "Common/Admin/Admin.h"

#include <cstdint>
#include <string>

struct Unban
{
	uint64_t id;
	uint64_t adminID;
	std::string reason;
};

struct Ban
{
	enum class Type
	{
		None = 0,
		Normal,
		Ct,
		Silence
	};

	struct PlayerInfo
	{
		std::string steamID;
		std::string steam3ID;
		std::string steamID64;
		std::string ip;
	};

	struct ServerInfo
	{
		std::string serverName;
		std::string serverIP;
	};

	uint64_t id;
	Type type;
	uint64_t length; // In minutes
	std::string reason;
	std::string targetName;

	uint64_t adminID;
	uint64_t unbanID;
	uint64_t playerInfoID;
	uint64_t serverInfoID;
};
