#pragma once

#include "PublicManager.h"

#include "Timer.h"

class Invisibility
{
public:
	class InvisibilityCallback
	{
	public:
		virtual void OnStart(int client, float remainingTime) {};
		virtual void OnUpdate(int client, float remainingTime) {};
		virtual void OnEnd(int client) {};
	};
public:
	static void Enable(int client, float duration)
	{
		sRemainingTime[client - 1] += duration;
		if (!sTimer[client - 1])
		{
			sTimer[client - 1] = Timer(sTimerInterval, OnTimerTick, reinterpret_cast<void*>(client), TIMER_REPEAT | TIMER_FLAG_NO_MAPCHANGE);
			EnableInvisibility(client);
			sCallbackClass->OnStart(client, sRemainingTime[client - 1]);
			sRemainingTime[client - 1] -= sTimerInterval;
		}
	}

	static void SetCallbackClass(InvisibilityCallback* callbackClass)
	{
		sCallbackClass = callbackClass;
	}

	static void Disable(int client)
	{
		DisableInvisibility(client);
		sRemainingTime[client - 1] = 0.0f;
		sTimer[client - 1].Kill();
		sCallbackClass->OnEnd(client);
	}

	static bool IsActive(int client)
	{
		return sTimer[client - 1].IsValid();
	}

	static void OnClientDeath(int client)
	{
		if (PM::GetClientTeam(client) == CS_TEAM_CT && IsActive(client))
			Disable(client);
	}

	static void OnClientDisconnect(int client)
	{
		if (PM::GetClientTeam(client) == CS_TEAM_CT && IsActive(client))
			Disable(client);
	}

	static void OnClientTeamChange(int client, int team, int oldTeam)
	{
		if (team == CS_TEAM_T && oldTeam == CS_TEAM_CT && IsActive(client))
			Disable(client);
	}

	static Action OnTimerTick(Timer*, void* data)
	{
		int client = reinterpret_cast<int>(data);
		if (sRemainingTime[client - 1] <= 0.0f)
		{
			DisableInvisibility(client);
			sCallbackClass->OnEnd(client);
			sRemainingTime[client - 1] = 0.0f;
			return Plugin_Stop;
		}
		else
		{
			sCallbackClass->OnUpdate(client, sRemainingTime[client - 1]);
			sRemainingTime[client - 1] -= sTimerInterval;
		}

		return Plugin_Continue;
	}
private:
	static void EnableInvisibility(int client)
	{
		PublicManager::SetEntityRenderMode(client, RenderMode::RENDER_NONE);
	}

	static void DisableInvisibility(int client)
	{
		PublicManager::SetEntityRenderMode(client, RenderMode::RENDER_TRANSCOLOR);
	}
private:
	static constexpr float sTimerInterval = 1.0f;

	static Timer sTimer[MAXPLAYERS];
	static float sRemainingTime[MAXPLAYERS];
	static InvisibilityCallback* sCallbackClass;
};
