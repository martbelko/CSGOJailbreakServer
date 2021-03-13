#pragma once

#include "Plugin/Utils.h"

#include "Timer.h"

class BlindAbility
{
public:
	class BlindAbilityCallback
	{
	public:
		virtual void OnStart(float remainingTime) {};
		virtual void OnUpdate(float remainingTime) {};
		virtual void OnEnd() {};
	};
public:
	static void Enable(float time)
	{
		sRemainingTime += time;
		if (!sTimer)
		{
			sTimer = Timer(sTimerInterval, BlindAbility::OnTimerTick, nullptr, TIMER_REPEAT | TIMER_FLAG_NO_MAPCHANGE);

			std::vector<int> players;
			players.reserve(PM::GetMaxClients());
			for (int i = 1; i <= PM::GetMaxClients(); ++i)
			{
				if (PM::IsClientInGame(i) && PM::GetClientTeam(i) == CS_TEAM_CT)
					players.push_back(i);
			}

			players.push_back(1);
			EnableBlind(players.data(), players.size());
			sCallbackClass->OnStart(sRemainingTime);
			sRemainingTime -= sTimerInterval;
		}
	}

	static void SetCallbackClass(BlindAbilityCallback* callbackClass)
	{
		sCallbackClass = callbackClass;
	}

	static bool IsActive()
	{
		return sRemainingTime != 0.0f;
	}

	static void DisableForClient(int client)
	{
		DisableBlind(&client, 1);
	}

	static void Disable()
	{
		std::vector<int> players;
		players.reserve(PM::GetMaxClients());
		for (int i = 1; i <= PM::GetMaxClients(); ++i)
		{
			if (PM::IsClientInGame(i) && PM::GetClientTeam(i) == CS_TEAM_CT)
				players.push_back(i);
		}
		DisableBlind(players.data(), players.size());

		sRemainingTime = 0.0f;
		sTimer.Kill();
		sCallbackClass->OnEnd();
	}

	static void OnClientDeath(int client)
	{
		if (PublicManager::GetClientTeam(client) == CS_TEAM_CT && IsActive())
			DisableForClient(client);
	}

	static void OnClientDisconnect(int client)
	{
		if (PublicManager::GetClientTeam(client) == CS_TEAM_CT && IsActive())
			DisableForClient(client);
	}

	static void OnClientTeamChange(int client, int team, int oldTeam)
	{
		if (team == CS_TEAM_T && oldTeam == CS_TEAM_CT && IsActive())
			DisableForClient(client);
	}

	static Action OnTimerTick(Timer*, void*)
	{
		if (sRemainingTime <= 0.0f)
		{
			std::vector<int> players;
			players.reserve(PM::GetMaxClients());
			for (int i = 1; i <= PublicManager::GetMaxClients(); ++i)
				if (PublicManager::IsClientInGame(i) && PublicManager::GetClientTeam(i) == CS_TEAM_CT)
					players.push_back(i);

			players.push_back(1);
			DisableBlind(players.data(), players.size());

			sCallbackClass->OnEnd();
			sRemainingTime = 0.0f;
			return Plugin_Stop;
		}
		else
		{
			sCallbackClass->OnUpdate(sRemainingTime);
			sRemainingTime -= sTimerInterval;
		}

		return Plugin_Continue;
	}
private:
	static void EnableBlind(int clients[], int count)
	{
		Utils::FadeUserMessage(clients, count, sBlackColor, FADE_IN | FADE_PURGE);
	}

	static void DisableBlind(int clients[], int count)
	{
		Utils::FadeUserMessage(clients, count, sNormalColor, FADE_IN | FADE_STAYOUT | FADE_PURGE);
	}
private:
	static constexpr int sBlackColor[4] = { 0, 0, 0, 255 };
	static constexpr int sNormalColor[4] = { 0, 0, 0, 0 };
	static constexpr float sTimerInterval = 1.0f;

	static Timer sTimer;
	static float sRemainingTime;
	static BlindAbilityCallback* sCallbackClass;
};
