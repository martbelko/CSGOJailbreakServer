#pragma once

#include "PublicManager.h"

#include <array>

class DoubleJump
{
public:
	static void Enable(int client)
	{
		s_DJEnabled[client - 1] = true;
	}

	static void Disable(int client)
	{
		s_DJEnabled[client - 1] = false;
	}

	static void OnGameFrame()
	{
		for (int i = 1; i <= PublicManager::GetMaxClients(); i++)
		{
			if (PublicManager::IsClientInGame(i) && PublicManager::IsPlayerAlive(i) && s_DJEnabled[i - 1])
				DoDoubleJump(i);
		}
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
	static bool s_DJEnabled[MAXPLAYERS];
	static int s_LastFlags[MAXPLAYERS];
	static int s_LastButtons[MAXPLAYERS];
	static int s_JumpCount[MAXPLAYERS];
	static constexpr int MaxJumps = 2;
};

__declspec(selectany) int DoubleJump::s_JumpCount[MAXPLAYERS];
__declspec(selectany) int DoubleJump::s_LastButtons[MAXPLAYERS];
__declspec(selectany) int DoubleJump::s_LastFlags[MAXPLAYERS];
__declspec(selectany) bool DoubleJump::s_DJEnabled[MAXPLAYERS];
