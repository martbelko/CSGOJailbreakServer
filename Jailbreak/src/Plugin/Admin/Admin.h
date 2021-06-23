#pragma once

#include <CSGOExtension.h>

class Admin
{
public:
	Admin() = delete;

	static bool IsClientAdmin(int client)
	{
		return HasFlags(client, ADMFLAG_GENERIC);
	}

	static bool HasFlags(int client, int flags)
	{
		return PM::GetUserFlagBits(client) & flags == flags;
	}
};
