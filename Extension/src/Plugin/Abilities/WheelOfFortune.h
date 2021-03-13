#pragma once

#include "PublicManager.h"

#include "Timer.h"

class ShopItem;

class WheelOfFortune
{
public:
	class WheelOfFortuneCallback
	{
	public:
		virtual void OnStart(int client, float remainingTime) {};
		virtual void OnUpdate(int client, float remainingTime) {};
		virtual void OnEnd(int client, ShopItem* item) {};
	};
public:
	static void Enable(int client, float duration)
	{
		sRemainingTime[client - 1] += duration;
		if (!sTimer[client - 1])
		{
			sTimer[client - 1] = Timer(sTimerInterval, OnTimerTick, reinterpret_cast<void*>(client), TIMER_REPEAT | TIMER_FLAG_NO_MAPCHANGE);
			sCallbackClass->OnStart(client, sRemainingTime[client - 1]);
			sRemainingTime[client - 1] -= sTimerInterval;
		}
	}

	static void SetCallbackClass(WheelOfFortuneCallback* callbackClass)
	{
		sCallbackClass = callbackClass;
	}

	static void Disable(int client)
	{
		DisableRolling(client);
		sRemainingTime[client - 1] = 0.0f;
		sTimer[client - 1].Kill();
		sCallbackClass->OnEnd(client, nullptr);
	}

	static bool IsActive(int client)
	{
		return sTimer[client - 1].IsValid();
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

	static Action OnTimerTick(Timer*, void* data);
private:
	static ShopItem* GetRandomItem(int client);

	static void DisableRolling(int client)
	{
		sRemainingTime[client - 1] = 0.0f;
		sTimer[client - 1].Kill();
	}
private:
	static constexpr float sTimerInterval = 1.0f;

	static Timer sTimer[MAXPLAYERS];
	static float sRemainingTime[MAXPLAYERS];
	static WheelOfFortuneCallback* sCallbackClass;
};
