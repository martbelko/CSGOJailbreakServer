#pragma once

#include "PublicManager.h"

#include <array>

class DoubleJump
{
public:
	static void Enable(int client)
	{
		sEnabled[client - 1] = true;
	}

	static void Disable(int client)
	{
		sEnabled[client - 1] = false;
	}

	static bool IsActive(int client)
	{
		return sEnabled[client - 1];
	}

	static void OnGameFrame()
	{
		for (int i = 1; i <= PublicManager::GetMaxClients(); ++i)
		{
			if (PublicManager::IsClientInGame(i) && PublicManager::IsPlayerAlive(i) && sEnabled[i - 1])
				DoDoubleJump(i);
		}
	}

	static void OnClientDeath(int client)
	{
		if (IsActive(client))
			Disable(client);
	}

	static void OnClientDisconnect(int client)
	{
		if (IsActive(client))
			Disable(client);
	}

	static void OnClientTeamChange(int client, int team, int oldTeam)
	{
		if (IsActive(client))
			Disable(client);
	}
private:
	static void DoDoubleJump(int client)
	{
		int curFlags = PublicManager::GetEntityFlags(client);
		int curButtons = PublicManager::GetClientButtons(client);
		if (curFlags & FL_ONGROUND)
			s_JumpCount[client - 1] = 0;
		else if (!(s_LastButtons[client - 1] & IN_JUMP) && curButtons & IN_JUMP)
		{
			if (s_LastFlags[client - 1] & FL_ONGROUND && !(curFlags & FL_ONGROUND))
				++s_JumpCount[client - 1];
			else if (1 <= s_JumpCount[client - 1] && s_JumpCount[client - 1] < MaxJumps)
			{
				++s_JumpCount[client - 1];
				float vel[3];
				PublicManager::GetEntPropVector(client, Prop_Data, "m_vecVelocity", vel);
				vel[2] = 250.0f;
				PublicManager::TeleportEntity(client, nullptr, nullptr, vel);
			}
		}

		s_LastFlags[client - 1] = curFlags;
		s_LastButtons[client - 1] = curButtons;
	}
private:
	static bool sEnabled[MAXPLAYERS];
	static int s_LastFlags[MAXPLAYERS];
	static int s_LastButtons[MAXPLAYERS];
	static int s_JumpCount[MAXPLAYERS];
	static constexpr int MaxJumps = 2;
};
